#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_SIZE 25

void bubbleSort(int arr[MAX_SIZE], int n) {
    // Bubble Sort algorithm
    int i, j, temp;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void bubbleSortD(int arr[MAX_SIZE], int n) {
    // Bubble Sort algorithm
    int i, j, temp;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void displayArray(int arr[MAX_SIZE], int n) {
    // Display the array
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[MAX_SIZE], n, i, status;
    
    // Accept the number of values in the array
    printf("Enter the number of values in the array: ");
    scanf("%d", &n);

    if (n > MAX_SIZE) {
        printf("Array size exceeds the maximum limit.\n");
        return 1;
    }

    // Accept the array elements
    printf("Enter the array elements: ");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process id=%d\n", pid);
        printf("\nChild process\n");
        printf("Child process id=%d\n", getpid());

        // Sort the array using Bubble Sort in the child process
        bubbleSortD(arr, n);

        // Display the sorted array in the child process
        printf("Sorted Array in Child Process: ");
        displayArray(arr, n);

        // Child process completes, becomes a zombie until the parent waits for it
        exit(0);
    } else {
        // Parent process
        printf("\nParent process\n");
        printf("Parent process id=%d\n", getpid());

        // Wait for the child process to complete
        wait(&status);

        // Sort the array using Bubble Sort in the parent process
        bubbleSort(arr, n);

        // Display the sorted array in the parent process
        printf("Sorted Array in Parent Process: ");
        displayArray(arr, n);
        printf("Parent process id=%d\n", pid);

        // Parent process completes, child becomes orphan
    }

    return 0;
}       