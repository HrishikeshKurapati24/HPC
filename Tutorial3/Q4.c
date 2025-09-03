#include <pthread.h>
#include <stdio.h>

#define N 8
#define THREADS 4

int arr[N] = {1,2,3,4,5,6,7,8}, prefix_sum[N];
pthread_t tid[THREADS];

void* partial_prefix(void* arg) {
    int t = *(int*)arg;
    int start = t * (N / THREADS);
    int end = (t == THREADS-1) ? N : start + (N / THREADS);

    prefix_sum[start] = arr[start];
    for (int i = start+1; i < end; i++)
        prefix_sum[i] = prefix_sum[i-1] + arr[i];
    return NULL;
}

int main() {
    int ids[THREADS];
    for (int i = 0; i < THREADS; i++) {
        ids[i] = i;
        pthread_create(&tid[i], NULL, partial_prefix, &ids[i]);
    }
    for (int i = 0; i < THREADS; i++)
        pthread_join(tid[i], NULL);

    for (int i = 1; i < THREADS; i++) {
        int offset = prefix_sum[i*(N/THREADS)-1];
        for (int j = i*(N/THREADS); j < (i==THREADS-1?N:i*(N/THREADS)+(N/THREADS)); j++)
            prefix_sum[j] += offset;
    }

    for (int i = 0; i < N; i++) printf("%d ", prefix_sum[i]);
    printf("\n");
    return 0;
}
