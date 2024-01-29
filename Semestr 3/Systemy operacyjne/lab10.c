#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

double result = 3.0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int from;
    int size;
} ThreadData;

void *threadFunction(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int from = data->from;
    int size = data->size;
    pthread_t tid = pthread_self();

    printf("Thread %lx size=%d first==%d\n", tid, size, from);

    double threadResult = 0;
    double temp = 0.0;

    for (int i = from; i < from + size; i++) {
        double o = i * 2 + 2;
		temp = 4.0 / (o * (o + 1) * (o + 2));

        if (i % 2 == 0) {
            threadResult += temp;
        } else {
            threadResult -= temp;
        }
    }

    pthread_mutex_lock(&mutex);

    result += threadResult;

    pthread_mutex_unlock(&mutex);

    printf("Thread %lx sum=%.20f\n", tid, threadResult);

    pthread_exit(NULL);
}

double calculatePiIterative(int n) {
    double result2 = 3.0;
    double temp = 0.0;

    for (int i = 0; i < n; i++) {
        double o = i * 2 + 2;
        temp = 4.0 / (o * (o + 1) * (o + 2));

        if (i % 2 == 0) {
            result2 += temp;
        } else {
            result2 -= temp;
        }
    }

    return result2;
}

// Function to calculate the elapsed time
void sub_timespec(struct timespec t1, struct timespec t2, struct timespec *td) {
    td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec = t2.tv_sec - t1.tv_sec;
    if (td->tv_sec > 0 && td->tv_nsec < 0) {
        td->tv_nsec += 1000000000;
        td->tv_sec--;
    } else if (td->tv_sec < 0 && td->tv_nsec > 0) {
        td->tv_nsec -= 1000000000;
        td->tv_sec++;
    }
}

int main(int argc, char *argv[]) {

    // ARGUMENT VERIFICATION

    // Check if exactly 2 arguments were passed
    if (argc != 3) {
        fprintf(stderr, "Pass exactly 2 arguments\n");
        return 1;
    }

    // Check if the arguments have a correct length
    if (strlen(argv[1]) < 1 || strlen(argv[1]) > 7) {
        fprintf(stderr, "Bad 'n' length (from 1 to 7 characters)\n");
        return 1;
    } else if (strlen(argv[2]) < 1 || strlen(argv[2]) > 3) {
        fprintf(stderr, "Bad 'w' length (from 1 to 3 characters)\n");
        return 1;
    }

    // Check if the arguments are numbers
    for (int i = 0; argv[1][i] != '\0'; i++) {
        if (!isdigit(argv[1][i])) {
            fprintf(stderr, "'n' is not a number\n");
            return 1;
        }
    }
    for (int i = 0; argv[2][i] != '\0'; i++) {
        if (!isdigit(argv[2][i])) {
            fprintf(stderr, "'w' is not a number\n");
            return 1;
        }
    }

    // Convert arguments to int
    int n = atoi(argv[1]);
    int w = atoi(argv[2]);

    // Check if the arguments are in the correct range
    if (n <= 1 || n >= 1000000) {
        fprintf(stderr, "'n' has to fit in this range (1 < n < 1000000)\n");
        return 1;
    } else if (w <= 1 || w >= min(100, n)) {
        fprintf(stderr, "'w' has to fit in this range (1 < w < min(100,n))\n");
        return 1;
    }

    // END OF ARGUMENT VERIFICATION

    pthread_t threads[w];

    int numberForThreads = n / w;
    int remainder = n % w;
    int from;
    int size;

    ThreadData data[w];

    struct timespec start, finish, delta;
    clock_gettime(CLOCK_MONOTONIC, &start);

    if (remainder != 0) {
        for (int i = 0; i < w - 1; i++) {
            data[i].from = i * numberForThreads;
            data[i].size = numberForThreads;

            pthread_create(&threads[i], NULL, threadFunction, (void *)&data[i]);
        }

        data[w - 1].from = (w - 1) * numberForThreads;
        data[w - 1].size = numberForThreads + remainder;

        pthread_create(&threads[w - 1], NULL, threadFunction, (void *)&data[w - 1]);
    } else {
        for (int i = 0; i < w; i++) {
            data[i].from = i * numberForThreads;
            data[i].size = numberForThreads;

            pthread_create(&threads[i], NULL, threadFunction, (void *)&data[i]);
        }
    }

    // Join threads before printing the result
    for (int i = 0; i < w; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);
    sub_timespec(start, finish, &delta);

    // Convert to seconds
	double seconds = (double)delta.tv_sec + (double)delta.tv_nsec / 1e9;

    // Print the result in nanoseconds
    printf("\nw/Threads  PI=%.20f time=%f nanoseconds\n", result, seconds);

    clock_gettime(CLOCK_MONOTONIC, &start);
    double iterativeResult = calculatePiIterative(n);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    sub_timespec(start, finish, &delta);

    // Convert to seconds
	seconds = (double)delta.tv_sec + (double)delta.tv_nsec / 1e9;

    // Print the result in nanoseconds
    printf("wo/Threads PI=%.20f time=%f nanoseconds\n\n", iterativeResult, seconds);

    return 0;
}
