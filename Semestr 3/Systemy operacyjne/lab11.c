#include <iostream>
#include <process.h>
#include <windows.h>

#define MAX_THREADS 100

HANDLE mutex;
float threadSum = 0;

// Thread-specific data structure
struct ThreadData {
	float* floatArray;
	int numElements;
};

// Thread function
DWORD WINAPI ThreadFunction(void* param) {
	ThreadData* threadData = static_cast<ThreadData*>(param);

	// Print thread information
	DWORD threadId = GetCurrentThreadId();
	printf("Thread #%lu size=%d\n", threadId, threadData->numElements);

	// Calculate partial sum
	float partialSum = 0;
	for (int i = 0; i < threadData->numElements; i++) {
		partialSum += threadData->floatArray[i];
	}

	// Lock the mutex to update the global sum
	WaitForSingleObject(mutex, INFINITE);
	threadSum += partialSum;
	ReleaseMutex(mutex);

	// Print partial sum
	printf("Thread #%lu sum=%.6f\n", threadId, partialSum);

	delete threadData;

	return 0;
}

int main(int argc, char* argv[]) {
	// Check if the user passed 2 arguments
	if (argc != 3) {
		fprintf(stderr, "Exactly 2 arguments are required\n");
		return 1;
	}

	// Check if the first argument has a correct length
	if (strlen(argv[1]) < 1 || strlen(argv[1]) > 7) {
		fprintf(stderr, "First argument has incorrect lenght (1 to 7)\n");
		return 1;
	}

	// Check if the arguments are numbers
	for (int i = 0; argv[1][i] != '\0'; i++) {
		if (!isdigit(argv[1][i])) {
			fprintf(stderr, "First argument is not a number\n");
			return 1;
		}
	}

	for (int i = 0; argv[2][i] != '\0'; i++) {
		if (!isdigit(argv[2][i])) {
			fprintf(stderr, "Second argument is not a number\n");
			return 1;
		}
	}

	int n = atoi(argv[1]);
	int w = atoi(argv[2]);

	if (!(0 < n && n < 1000000 && 0 < w && w < n && w < 100)) {
		fprintf(stderr, "Invalid arguments. Both must be integers with 0 < n < 1000000 and 0 < w < n and w < 100.\n");
		return 1;
	}

	// If we are here the input data is correct

	float* floatArray = (float*)malloc(n * sizeof(float));

	if (floatArray == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return 1;
	}

	srand(0);
	for (int i = 0; i < n; i++) {
		floatArray[i] = 1000. * rand() / RAND_MAX;
	}

	int elementsPerThread = n / w;
	int remainder = n % w;

	//printf("%s %s\n", argv[1], argv[2]);
	//printf("%d %d\n", n, w);
	//printf("%d %d\n", elementsPerThread, remainder);

	mutex = CreateMutex(NULL, FALSE, NULL);
	if (mutex == NULL) {
		fprintf(stderr, "Mutex creation failed\n");
		free(floatArray);
		return 1;
	}

	// Thread handles array
	HANDLE threadHandles[MAX_THREADS] = { NULL };

	// Record the start time
	DWORD startTime = GetTickCount();

	for (int i = 0; i < w; i++) {
		ThreadData* threadData = new ThreadData;
		threadData->floatArray = floatArray + i * elementsPerThread;

		// Add the remainder for the last thread
		if (i == w - 1) {
			threadData->numElements = elementsPerThread + remainder;
		}
		else {
			threadData->numElements = elementsPerThread;
		}

		// Create the actual thread
		threadHandles[i] = CreateThread(NULL, 0, &ThreadFunction, threadData, 0, NULL);
		if (threadHandles[i] == NULL) {
			fprintf(stderr, "Thread creation failed\n");

			// Clean up: Close previously created threads, release memory, and close mutex
			for (int j = 0; j < i; j++) {
				CloseHandle(threadHandles[j]);
			}
			CloseHandle(mutex);
			free(floatArray);

			return 1;
		}
	}

	// Wait for all threads to finish
	WaitForMultipleObjects(w, threadHandles, TRUE, INFINITE);

	// Record the end time
	DWORD endTime = GetTickCount();

	// Close thread handles and release memory
	for (int i = 0; i < w; i++) {
		CloseHandle(threadHandles[i]);
	}

	DWORD elapsedTime = endTime - startTime;
	printf("\nw /Threads: sum=%.6f, time=%.3f sec\n", threadSum, elapsedTime / 1000.0);

	CloseHandle(mutex);

	// Sum without threads
	float withoutThreadsSum = 0;

	startTime = GetTickCount();

	for (int i = 0; i < n; i++) {
		withoutThreadsSum += floatArray[i];
	}

	endTime = GetTickCount();

	elapsedTime = endTime - startTime;
	printf("wo/Threads: sum=%.6f, time=%.3f sec\n", withoutThreadsSum, elapsedTime / 1000.0);

	free(floatArray);

	return 0;
}