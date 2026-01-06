#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <mqueue.h>
#include <semaphore.h>
#include <errno.h>
#include <crypt.h>
#include <signal.h>

#define MAX_HASH_LENGTH 128
#define MAX_PASS_LENGTH 36
#define MAX_NAME_LENGTH 64

char* shm_addr = NULL;
int shm_size = 0;

int* task_statuses = NULL;
int task_statuses_size = 0;

char* found_pass = NULL;

mqd_t mqd = -1;
sem_t* found_sem = SEM_FAILED;
char* salt = NULL;

struct Task {
    size_t start;
    size_t end;
    int id;
    char hashed_password[MAX_HASH_LENGTH];

    char shm_name[MAX_NAME_LENGTH];
    char status_shm_name[MAX_NAME_LENGTH];
    char sem_name[MAX_NAME_LENGTH];
    char found_pass_shm_name[MAX_NAME_LENGTH];
};

void cleanup() {
    if (shm_addr) munmap(shm_addr, shm_size);
    if (task_statuses) munmap(task_statuses, task_statuses_size * sizeof(int));
    if (found_pass) munmap(found_pass, MAX_PASS_LENGTH);
    if (found_sem != SEM_FAILED) sem_close(found_sem);
    if (mqd != -1) mq_close(mqd);
    if (salt) free(salt);
}

void sigint_handler(int sig) {
    cleanup();
    exit(0);
}

char* extract_salt(const char* full_hash) {
    const char* p = full_hash + 3;
    const char* salt_end = strchr(p, '$');
    size_t length = salt_end - p;

    char* salt = malloc(length + 4);
    memcpy(salt, "$6$", 3);
    memcpy(salt + 3, p, length);
    salt[length + 3] = '\0';

    return salt;
}

int main(int argc, char* argv[]) {
    const char* mq_name = argv[1];
    int n_tasks = atoi(argv[2]);

    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    mqd = mq_open(mq_name, O_RDONLY | O_NONBLOCK);

    struct Task task;
    ssize_t received = mq_receive(mqd, (char*)&task, sizeof(struct Task), NULL);
    if (received < 0) {
        printf("There are no tasks in the queue.\n");
        return 1;
    }

    int fd_shm = shm_open(task.shm_name, O_RDONLY, 0);
    struct stat st;
    fstat(fd_shm, &st);
    shm_size = st.st_size;

    shm_addr = mmap(NULL, shm_size, PROT_READ, MAP_SHARED, fd_shm, 0);
    close(fd_shm);

    int fd_status_shm = shm_open(task.status_shm_name, O_RDWR, 0);
    task_statuses_size = task.id + n_tasks + 1;
    task_statuses = mmap(NULL, task_statuses_size * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd_status_shm, 0);
    close(fd_status_shm);

    found_sem = sem_open(task.sem_name, 0);

    int fd_found_pass_shm = shm_open(task.found_pass_shm_name, O_RDWR, 0);
    found_pass = mmap(NULL, MAX_PASS_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd_found_pass_shm, 0);
    close(fd_found_pass_shm);

    const char* ptr = shm_addr + task.start;
    const char* end = shm_addr + task.end;
    salt = extract_salt(task.hashed_password);

    int tasks_done = 0;

    while (tasks_done < n_tasks) {
        if (received < 0) {
            printf("There are no tasks in the queue.\n");
            break;
        }

        printf("Processing task %d...\n", task.id);

        while (ptr < end) {
            if (sem_wait(found_sem) == -1) {
                perror("sem_wait failed");
                break;
            }
            if (found_pass[0] != '\0') {
                if (sem_post(found_sem) == -1) {
                    perror("sem_post failed");
                }
                break;
            }
            if (sem_post(found_sem) == -1) {
                perror("sem_post failed");
                break;
            }

            const char* line_end = memchr(ptr, '\n', end - ptr);
            if (!line_end) {
                break;
            }
                
            size_t len = line_end - ptr;

            char password[MAX_PASS_LENGTH] = {0};
            memcpy(password, ptr, len);

            char* candidate = crypt(password, salt);

            if (strcmp(candidate, task.hashed_password) == 0) {
                if (sem_wait(found_sem) == -1) {
                    perror("sem_wait failed");
                    break;
                }

                strncpy(found_pass, password, MAX_PASS_LENGTH - 1);
                found_pass[MAX_PASS_LENGTH - 1] = '\0';

                if (sem_post(found_sem) == -1) {
                    perror("sem_post failed");
                    break;
                }

                break;
            }

            ptr = line_end + 1;
        }

        task_statuses[task.id] = 1;
        tasks_done++;

        if (tasks_done < n_tasks) {
            received = mq_receive(mqd, (char*)&task, sizeof(struct Task), NULL);
            if (received < 0) {
                if (errno == EAGAIN) {
                    printf("No tasks currently in the queue. Exiting.\n");
                    break;
                } else {
                    perror("mq_receive");
                    break;
                }
            }

            ptr = shm_addr + task.start;
            end = shm_addr + task.end;
        }
    }

    cleanup();
    return 0;
}
