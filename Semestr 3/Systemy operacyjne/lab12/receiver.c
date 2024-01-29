#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <fcntl.h>
#include <semaphore.h>
#include <string.h>

int main(int argc, char *argv[]) {

    // Check if exactly 2 arguments were passed
    if (argc != 3) {
        fprintf(stderr, "Pass exactly 2 arguments\n");
        return 1;
    }
    
    key_t key = atoi(argv[1]);
	char *filename = argv[2];
    
	// 0666 to create a shared memory segment with read and write permissions
	// using the key from the sender program, so that both programs will have
	// access to the same shared memory
    int shmid = shmget(key, 100, IPC_CREAT | 0666);
	if (shmid == -1) {
        perror("shmget");
        return 1;
    }

	// Pointer to the shared memory
    void *memory_pointer= shmat(shmid, NULL, 0);
	if (memory_pointer == (void *)-1) {
        perror("shmat");
        return 1;
    }

	// Open file in write-only mode
	// If it doesn't exist create it
	// If it exists clear it
	int file_descriptor = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (file_descriptor == -1) {
        perror("open");
        return 1;
    }

	// Open existing sender semaphore
    sem_t *sen_sem = sem_open("/sender_semaphore", 0);
	if (sen_sem == SEM_FAILED) {
        perror("sen_open");
        return 1;
    }

	// Open existing receiver semaphore
    sem_t *rec_sem = sem_open("/receiver_semaphore", 0);
	if (rec_sem == SEM_FAILED) {
        perror("rec_open");
        return 1;
    }

	// Open existing semaphore to check the end of the file
    sem_t *end_sem = sem_open("/end_semaphore", 0);
	if (end_sem == SEM_FAILED) {
        perror("end_open");
        return 1;
    }

	// Loop to write to the file until the end signal is received
    while (1) {
        // Signal the sender that it can proceed
        sem_post(rec_sem);

        // Wait for a signal from the sender
        sem_wait(sen_sem);

		size_t dataSize = strlen((char *)memory_pointer);

        // Write 100 bytes from shared memory to the file
        ssize_t bytesWritten = write(file_descriptor, memory_pointer, dataSize);
		if (bytesWritten == -1) {
            perror("write");
            return 1;
        }

		// Print what you've written to the file
		printf("Written to file:\n%.*s\n\n", (int)bytesWritten, (char*)memory_pointer);

		// Check if the end signal is received
        if (sem_trywait(end_sem) == 0) {
            break;
        }
    }

	// Signal the sender that the writing has ended
	sem_post(rec_sem);

	// Close semaphores
    sem_close(sen_sem);
    sem_close(rec_sem);
	sem_close(end_sem);

	// Close the file writer
    close(file_descriptor);

	// Detach from the shared memory
    shmdt(memory_pointer);

	return 0;
}
