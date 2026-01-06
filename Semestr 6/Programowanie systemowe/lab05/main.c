#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

volatile sig_atomic_t create_children = 1;
volatile sig_atomic_t random_exit_code = 0;
volatile sig_atomic_t children_count = 0;

void factorial() {
    unsigned long long result = 1;
    unsigned long long i = 1;
    while (1) {
        result *= i;
        i++;
    }
}

void sigalrm_handler(int sig) {
    exit(random_exit_code);
}

void sigchld_handler(int sig, siginfo_t *si, void *unused) {
    time_t termination_time = time(NULL);

    char formatted_time[100];
    struct tm *time_info = localtime(&termination_time);
    strftime(formatted_time, sizeof(formatted_time), "%a %b %d %H:%M:%S %Y", time_info);

    printf("\t[ %d ] [ %d ] [ %s ]\n", si->si_pid, si->si_status, formatted_time);

    children_count--;
}

void sigint_handler(int sig) {
    create_children = 0;
}

int main(int argc, char *argv[]) {

    int max_process_lifetime = atoi(argv[1]);
    int creation_interval = atoi(argv[2]);

    struct sigaction sa_chld;
    sa_chld.sa_sigaction = sigchld_handler;
    sa_chld.sa_flags = SA_SIGINFO;
    sigemptyset(&sa_chld.sa_mask);
    sigaction(SIGCHLD, &sa_chld, NULL);

    struct sigaction sa_int;
    sa_int.sa_handler = sigint_handler;
    sa_int.sa_flags = 0;
    sigemptyset(&sa_int.sa_mask);
    sigaction(SIGINT, &sa_int, NULL);

    struct timespec sleep_time, remaining_time;

    while (create_children) {
        pid_t pid = fork();
        children_count++;

        if (pid == 0) {
            setpgid(0, 0);
            
            srand(time(NULL));
            int random_number = rand() % max_process_lifetime + 1;
            random_exit_code = random_number;
            
            time_t creation_time = time(NULL);
            char formatted_time[100];
            struct tm *time_info = localtime(&creation_time);
            strftime(formatted_time, sizeof(formatted_time), "%a %b %d %H:%M:%S %Y", time_info);

            printf("[ %d ] [ %d ] [ %s ]\n", getpid(), random_number, formatted_time);

            struct sigaction sa_alrm;
            sa_alrm.sa_handler = sigalrm_handler;
            sa_alrm.sa_flags = 0;
            sigemptyset(&sa_alrm.sa_mask);
            sigaction(SIGALRM, &sa_alrm, NULL);

            alarm(random_number);

            factorial();
        } else {
            sleep_time.tv_sec = creation_interval;
            sleep_time.tv_nsec = 0;

            while (nanosleep(&sleep_time, &remaining_time) == -1) {
                sleep_time = remaining_time;
            }
        }
    }

    while (children_count > 0);

    return 0;
}
