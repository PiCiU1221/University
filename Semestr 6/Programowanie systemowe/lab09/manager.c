#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <mqueue.h>
#include <errno.h>
#include <semaphore.h>
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

const char* mq_name = "/task_queue";
const char* shm_name = "/password-file-shm";
const char* status_shm_name = "/task-status-shm";
const char* sem_name = "/password_found_sem";
const char* found_pass_shm_name = "/found_password_shm";

struct Task* tasks = NULL;

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
    if (task_statuses) munmap(task_statuses, task_statuses_size);
    if (found_pass) munmap(found_pass, MAX_PASS_LENGTH);
    if (found_sem != SEM_FAILED) sem_close(found_sem);
    if (mqd != -1) mq_close(mqd);

    mq_unlink(mq_name);
    shm_unlink(shm_name);
    shm_unlink(status_shm_name);
    sem_unlink(sem_name);
    shm_unlink(found_pass_shm_name);

    if (tasks) free(tasks);
}

void sigint_handler(int sig) {
    cleanup();
    exit(0);
}

int tasks_remaining(int *statuses, int n_tasks) {
    int remaining = 0;
    for (int i = 0; i < n_tasks; i++) {
        if (statuses[i] == 0) {
            remaining++;
        }
    }
    return remaining;
}

int main(int argc, char* argv[]) {
    const char* filename = argv[1];
    const char* hashed_password = argv[2];
    const int n_tasks = atoi(argv[3]);

    const int short_interval_sec = 1;
    const int long_interval_sec = 15;

    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    int fd_file = open(filename, O_RDONLY);
    struct stat st;
    fstat(fd_file, &st);
    shm_size = st.st_size;

    int fd_shm = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd_shm, shm_size);

    shm_addr = mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
    close(fd_shm);
    char* file_data = mmap(NULL, shm_size, PROT_READ, MAP_PRIVATE, fd_file, 0);
    memcpy(shm_addr, file_data, shm_size);

    munmap(file_data, shm_size);
    close(fd_file);

    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 20;
    attr.mq_msgsize = sizeof(struct Task);
    attr.mq_curmsgs = 0;

    mqd = mq_open(mq_name, O_CREAT | O_RDWR | O_NONBLOCK, 0666, &attr);
    printf("Created message queue: %s\n", mq_name);

    int fd_found_pass_shm = shm_open(found_pass_shm_name, O_CREAT | O_EXCL | O_RDWR, 0666);
    ftruncate(fd_found_pass_shm, MAX_PASS_LENGTH);
    
    found_pass = mmap(NULL, MAX_PASS_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd_found_pass_shm, 0);
    close(fd_found_pass_shm);
    found_pass[0] = '\0';

    tasks = malloc(n_tasks * sizeof(struct Task));

    size_t chunk_size = shm_size / n_tasks;
    size_t current_offset = 0;

    for (int i = 0; i < n_tasks; ++i) {
        tasks[i].id = i;
        tasks[i].start = current_offset;

        strncpy(tasks[i].hashed_password, hashed_password, MAX_HASH_LENGTH - 1);
        tasks[i].hashed_password[MAX_HASH_LENGTH - 1] = '\0';

        size_t proposed_end = (i == n_tasks - 1) ? shm_size : (current_offset + chunk_size);

        while (proposed_end < shm_size && shm_addr[proposed_end] != '\n') {
            proposed_end++;
        }
        if (proposed_end < shm_size) {
            proposed_end++;
        }

        tasks[i].end = proposed_end;
        current_offset = proposed_end;

        strcpy(tasks[i].shm_name, shm_name);
        strcpy(tasks[i].status_shm_name, status_shm_name);
        strcpy(tasks[i].sem_name, sem_name);
        strcpy(tasks[i].found_pass_shm_name, found_pass_shm_name);
    }

    int fd_status_shm = shm_open(status_shm_name, O_CREAT | O_RDWR, 0666);
    task_statuses_size = n_tasks * sizeof(int);
    ftruncate(fd_status_shm, task_statuses_size);
    task_statuses = mmap(NULL, task_statuses_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_status_shm, 0);
    close(fd_status_shm);
    memset(task_statuses, 0, task_statuses_size);

    found_sem = sem_open(sem_name, O_CREAT | O_EXCL, 0666, 1);

    int remaining = 0;
    int last_remaining = -1;

    int tasks_remaining_temp = 0;
    int last_tasks_remaining = -1;

    int found = 0;

    for (int i = 0; i < n_tasks; i++) {
        sem_wait(found_sem);
        found = (found_pass[0] != '\0');
        sem_post(found_sem);
        if (found) break;
        
        while (1) {
            sem_wait(found_sem);
            found = (found_pass[0] != '\0');
            sem_post(found_sem);
            if (found) break;

            tasks_remaining_temp = tasks_remaining(task_statuses, n_tasks);
            if (tasks_remaining_temp != last_tasks_remaining) {
                printf("%d task(s) still remaining to complete...\n", tasks_remaining_temp);
                last_tasks_remaining = tasks_remaining_temp;
            }

            if (mq_send(mqd, (const char*)&tasks[i], sizeof(struct Task), 0) == 0) {
                break;
            } else if (errno == EAGAIN) {
                remaining = n_tasks - i;

                if (remaining != last_remaining) {
                    printf("%d task(s) still waiting to be added to the queue...\n", remaining);
                    last_remaining = remaining;
                }
                usleep(10000);
                continue;
            } else {
                perror("mq_send");
                exit(1);
            }
        }
    }

    int seconds_passed = 0;

    while (1) {
        sleep(short_interval_sec);
        seconds_passed += short_interval_sec;

        sem_wait(found_sem);
        found = (found_pass[0] != '\0');
        sem_post(found_sem);
        if (found) break;

        tasks_remaining_temp = tasks_remaining(task_statuses, n_tasks);
        if (tasks_remaining_temp == 0) {
            printf("All tasks completed.\n");
            break;
        }

        if (tasks_remaining_temp != last_tasks_remaining) {
            printf("%d task(s) still remaining to complete...\n", tasks_remaining_temp);
            last_tasks_remaining = tasks_remaining_temp;
        }

        if (seconds_passed >= long_interval_sec) {
            seconds_passed = 0;

            for (int i = 0; i < n_tasks; ++i) {
                if (task_statuses[i] == 0) {

                    sem_wait(found_sem);
                    found = (found_pass[0] != '\0');
                    sem_post(found_sem);
                    if (found) break;

                    printf("Resending task %d...\n", i);

                    while (1) {
                        sem_wait(found_sem);
                        found = (found_pass[0] != '\0');
                        sem_post(found_sem);
                        if (found) break;

                        if (mq_send(mqd, (const char*)&tasks[i], sizeof(struct Task), 0) == 0) {
                            break;
                        } else if (errno == EAGAIN) {
                            usleep(10000);
                        } else {
                            perror("mq_send");
                            exit(1);
                        }
                    }
                }
            }
        }
    }

    if (found) {
        printf("Password found: %s\n", found_pass);
    } else {
        printf("Password not found.\n");
    }

    cleanup();
    return 0;
}
