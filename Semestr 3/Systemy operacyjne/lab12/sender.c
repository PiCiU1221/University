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

    // Check if exactly 1 argument was passed
    if (argc != 2) {
        fprintf(stderr, "Pass exactly 1 argument\n");
        return 1;
    }
    
    char *filename = argv[1];
    
    if (access(filename, F_OK) == -1) {
        fprintf(stderr, "File doesn't exist\n");
        return 1;
    }
    
    key_t key = ftok(filename, 'A');
    
    printf("Key: %d\n", key);
    
    // 0666 to create a shared memory segment with read and write permissions
    int shmid = shmget(key, 100, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }
    
    // Pointer to the shared memory
    void *memory_pointer= shmat(shmid, NULL, 0);
    if (memory_pointer == (void*)-1) {
        perror("shmat");
        return 1;
    }
    
    // Open file in read-only mode
    int file_descriptor = open(filename, O_RDONLY);
    if (file_descriptor == -1) {
        perror("open_file");
        return 1;
    }
    
    // Create semaphore for sending
    sem_t *sen_sem = sem_open("/sender_semaphore", O_CREAT | O_EXCL, 0666, 0);
    if (sen_sem == SEM_FAILED) {
        perror("sen_open");
        return 1;
    }
    
    // Create semaphore for receiving
    sem_t *rec_sem = sem_open("/receiver_semaphore", O_CREAT | O_EXCL, 0666, 0);
    if (rec_sem == SEM_FAILED) {
        perror("rec_open");
        return 1;
    }
    
    // Create semaphore to signal the end of the file
    sem_t *end_sem = sem_open("/end_semaphore", O_CREAT | O_EXCL, 0666, 0);
    if (end_sem == SEM_FAILED) {
		perror("end_open");
		return 1;
	}
    
    ssize_t bytesRead;

    // Loop to read the file until the end
    while (1) {
        // Wait for the receiver to signal that it's ready
        sem_wait(rec_sem);
        
        // Clear the shared memory
        memset(memory_pointer, 0, 100);

        // Read from the file
        bytesRead = read(file_descriptor, memory_pointer, 100);
        if (bytesRead == -1) {
            perror("read");
            return 1;
        }
        
        // Print what you've read to the console
		printf("Read from file:\n%.*s\n\n", (int)bytesRead, (char*)memory_pointer);

        // If bytesRead < 100, it means end of file
        if (bytesRead < 100) {
			// Signal the receiver that the file has ended
			sem_post(end_sem);
			sem_post(sen_sem);
            break;
        }

        // Signal the receiver that data is ready
        sem_post(sen_sem);
    }
    
    // Wait for the receiver to signal that it has finished writing
    sem_wait(rec_sem);
    
    // Close semaphores
    sem_close(sen_sem);
    sem_close(rec_sem);
	sem_close(end_sem);
	
	// Remove semaphores
	sem_unlink("/sender_semaphore");
	sem_unlink("/receiver_semaphore");
	sem_unlink("/end_semaphore");
    
    // Close the file reader
    close(file_descriptor);
    
    // Detach from the shared memory
    shmdt(memory_pointer);
    
    // Remove the shared memory segment
	shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}
