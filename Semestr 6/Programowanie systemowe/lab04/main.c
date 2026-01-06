#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <stdbool.h>
#include <time.h>

int main(int argc, char *argv[]) {
    bool print_program_output = false;
    int opt;
    int number_of_runs = 1;

    while ((opt = getopt(argc, argv, "+vt:")) != -1) { 
        switch (opt) {
            case 'v': 
                print_program_output = true; 
                break;
            case 't': 
                number_of_runs = atoi(optarg);
                break;
            default:
                return 1;
        }
    }

    double total_real_time = 0.0;
    double total_user_time = 0.0;
    double total_system_time = 0.0;

    for (int i = 0; i < number_of_runs; i++) {
        struct rusage usage;
        
        struct timespec start_time, end_time;
        clock_gettime(CLOCK_REALTIME, &start_time);

        pid_t pid = fork();
        
        if (pid == 0) { 
            if (!print_program_output) {
                close(1);
                close(2);

                int h = open("/dev/null", O_WRONLY);

                dup2(h, 1);
                dup2(h, 2);
                close(h);
            }

            execvp(argv[optind], &argv[optind]);
        } else {
            pid_t terminated_pid = wait4(pid, NULL, 0, &usage);

            clock_gettime(CLOCK_REALTIME, &end_time);
            double real_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

            double user_time = usage.ru_utime.tv_sec + usage.ru_utime.tv_usec / 1e6;
            double system_time = usage.ru_stime.tv_sec + usage.ru_stime.tv_usec / 1e6;
            double elapsed_time = user_time + system_time;

            total_real_time += real_time;
            total_user_time += user_time;
            total_system_time += system_time;

            printf("========== Run: %d ==========\n", i+1);
            printf("Real time:   %.6f seconds\n", real_time);
            printf("User time:   %.6f seconds\n", user_time);
            printf("System time: %.6f seconds\n\n", system_time);
        }
    }

    if (number_of_runs > 1) {
        printf("Average real time:   %.6f seconds\n", total_real_time / number_of_runs);
        printf("Average user time:   %.6f seconds\n", total_user_time / number_of_runs);
        printf("Average system time: %.6f seconds\n", total_system_time / number_of_runs);
    }

    return 0;
}
