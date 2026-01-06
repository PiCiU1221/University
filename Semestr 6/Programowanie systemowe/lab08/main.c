#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdatomic.h>

#define MAX_PASSWORD_LENGTH 36

typedef struct {
    const char* start_ptr;
    const char* end_ptr;

    const char* salt;
    const char* hashed_password;
    volatile int* found;
    int benchmark_mode;
} ThreadArgs;

char* generate_hash(const char* password, const char* salt);

char* extract_salt(const char* full_hash) {
    // skip '$6$' prefix
    const char* p = full_hash + 3;
    // strchr returns a pointer to the first occurrence of '$'
    const char* salt_end = strchr(p, '$');
    size_t length = salt_end - p;

    // 3 charactes for '$6$' + 1 for null terminator
    char* salt = malloc(length + 4);
    // copy prefix '$6$'
    memcpy(salt, "$6$", 3);
    // copy salt
    memcpy(salt + 3, p, length);
    salt[length + 3] = '\0';

    return salt;
}

void* worker(void* arg) {
    ThreadArgs* args = arg;
    const char* ptr = args->start_ptr;
    const char* end = args->end_ptr;

    while (ptr < end && !*args->found) {
        const char* line_end = memchr(ptr, '\n', end - ptr);
        if (!line_end) {
            break;
        }
            
        size_t len = line_end - ptr;

        char password[MAX_PASSWORD_LENGTH] = {0};
        memcpy(password, ptr, len);

        char* candidate = generate_hash(password, args->salt);
        if (strcmp(candidate, args->hashed_password) == 0) {
            if (!args->benchmark_mode) {
                if (!__sync_lock_test_and_set(args->found, 1)) {
                    printf("Password found: %s\n", password);
                }
                break;
            }
        }

        ptr = line_end + 1;
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    const char* hashed_password = argv[1];
    const char* filename = argv[2];

    char* salt = extract_salt(hashed_password);

    int fd = open(filename, O_RDONLY | O_NOATIME);
    struct stat st;
    fstat(fd, &st);
    size_t size = st.st_size;

    char* mapped = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);

    int n_threads;
    int benchmark_mode = 0;

    if (argc >= 4) {
        benchmark_mode = 1;
        n_threads = atoi(argv[3]);
    } else {
        n_threads = sysconf(_SC_NPROCESSORS_ONLN);
    }

    pthread_t threads[n_threads];
    ThreadArgs args[n_threads];

    volatile int found = 0;

    size_t base = 0;
    size_t chunk = size / n_threads;

    printf("Using %d threads\n", n_threads);

    for (int i = 0; i < n_threads; ++i) {
        const char* start = mapped + base;
        const char* end;

        if (i == n_threads - 1) {
            end = mapped + size;
        } else {
            end = mapped + base + chunk;
        }

        if (i != 0) {
            while (start < mapped + size && *start != '\n') {
                start++;
            }
            if (start < mapped + size) {
                start++;
            }
        }
        if (i != n_threads - 1) {
            while (end < mapped + size && *end != '\n') {
                end++;
            }
            if (end < mapped + size) {
                end++;
            }
        }

        args[i] = (ThreadArgs){
            .start_ptr = start,
            .end_ptr = end,
            .salt = salt,

            .hashed_password = hashed_password,
            .found = &found,
            .benchmark_mode = benchmark_mode,
        };

        base = end - mapped;
        pthread_create(&threads[i], NULL, worker, &args[i]);
    }

    for (int i = 0; i < n_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    if (!found) {
        printf("No matching password found.\n");
    }

    munmap(mapped, size);
    close(fd);
    free(salt);

    return 0;
}
