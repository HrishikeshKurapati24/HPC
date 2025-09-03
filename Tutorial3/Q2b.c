#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define N 5
#define INCR 100000

int count = 0;
pthread_mutex_t lock;

void* increment(void* num){
    for(int i=0;i<INCR;i++){
        pthread_mutex_lock(&lock);
        count = count + 1;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(){
    pthread_t threads[N];

    pthread_mutex_init(&lock,NULL);

    for(int i=0;i<N;i++){
        pthread_create(&threads[i],NULL,increment,NULL);
    }

    for(int i=0;i<N;i++){
        pthread_join(threads[i],NULL);
    }
    printf("Final counter value is %d\n",count);

    return 0;
}