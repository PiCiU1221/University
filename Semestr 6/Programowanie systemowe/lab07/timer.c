#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

pthread_key_t start_time_key;
pthread_once_t key_once = PTHREAD_ONCE_INIT;

void create_key() {
    pthread_key_create(&start_time_key, free);
}

void start() {
    pthread_once(&key_once, create_key);
    
    struct timespec *start_time = pthread_getspecific(start_time_key);
    if (start_time == null) {
        start_time = (struct timespec *)malloc(sizeof(struct timespec));
    }

    clock_gettime(CLOCK_REALTIME, start_time);
    pthread_setspecific(start_time_key, start_time);
}

long stop() {
    struct timespec *start_time = pthread_getspecific(start_time_key);
    // start() wasnt called first
    if (start_time == NULL) {
        return -1;
    }

    struct timespec end_time;
    clock_gettime(CLOCK_REALTIME, &end_time);

    long start_ns = start_time->tv_sec * 1000000000 + start_time->tv_nsec;
    long end_ns = end_time.tv_sec * 1000000000 + end_time.tv_nsec;
    long elapsed_ns = end_ns - start_ns;

    long elapsed_ms = elapsed_ns / 1000000;

    return elapsed_ms;
}
