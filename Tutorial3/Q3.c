#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 4  

typedef struct {
    int *arr;
    int left;
    int right;
} ThreadNum;

pthread_mutex_t lock;       
int thread_count = 0;     

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right);

void* threadedMergeSort(void* arg) {
    ThreadNum* nums = (ThreadNum*) arg;
    mergeSort(nums->arr, nums->left, nums->right);
    free(arg);
    return NULL;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        pthread_t tid;
        int spawn_thread = 0;

        if (thread_count < MAX_THREADS) {
            spawn_thread = 1;
            thread_count++;

            ThreadNum* nums = malloc(sizeof(ThreadNum));
            nums->arr = arr;
            nums->left = left;
            nums->right = mid;

            pthread_create(&tid, NULL, threadedMergeSort, nums);
        } else {
            mergeSort(arr, left, mid);
        }

        mergeSort(arr, mid + 1, right);

        if (spawn_thread) {
            pthread_join(tid, NULL);
            thread_count--;
        }

        merge(arr, left, mid, right);
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7, 1, 50, 23, 9, 15, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    mergeSort(arr, 0, n - 1);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
