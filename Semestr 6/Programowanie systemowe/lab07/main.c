#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>

void start();
long stop();

typedef struct {
    pthread_t thread_id;
    int lifetime_sec;
    struct timespec end_time;
    int signaled;
} thread_info_t;

void factorial() {
    unsigned long long result = 1;
    unsigned long long i = 1;
    while (1) {
        result *= i;
        i++;
    }
}

void signal_handler(int sig) {
    long duration_ms = stop();

    printf("Ended thread %lu. Execution time: %ld ms\n",
           (unsigned long)pthread_self(), duration_ms);

    pthread_exit(NULL);
}

void *thread_function(void *arg) {
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

    start();
    factorial();
}

int main(int argc, char *argv[]) {

    int max_process_lifetime = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    srand(time(NULL));

    struct timespec current_time;

    thread_info_t *threads = malloc(num_threads * sizeof(thread_info_t));

    for (int i = 0; i < num_threads; i++) {
        threads[i].lifetime_sec = (rand() % max_process_lifetime) + 1;
        threads[i].signaled = 0;

        clock_gettime(CLOCK_REALTIME, &current_time);
        threads[i].end_time = current_time;
        threads[i].end_time.tv_sec += threads[i].lifetime_sec;

        pthread_create(&threads[i].thread_id, NULL, thread_function, NULL);

        printf("Created thread %lu. Assigned lifetime: %d seconds\n",
               (unsigned long)threads[i].thread_id, threads[i].lifetime_sec);
    }

    int threads_remaining = num_threads;

    while (threads_remaining > 0) {
        for (int i = 0; i < num_threads; i++) {
            if (threads[i].signaled == 0) {
                clock_gettime(CLOCK_REALTIME, &current_time);
                if (current_time.tv_sec > threads[i].end_time.tv_sec ||
                    (current_time.tv_sec == threads[i].end_time.tv_sec &&
                     current_time.tv_nsec >= threads[i].end_time.tv_nsec)) {

                    pthread_kill(threads[i].thread_id, SIGUSR1);

                    threads[i].signaled = 1;
                    threads_remaining--;
                }
            }
        }

        if (threads_remaining > 0) {
            struct timespec sleep_duration = {0, 10 * 1000000};
            nanosleep(&sleep_duration, NULL);
        }
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i].thread_id, NULL);
    }

    free(threads);

    return 0;
}