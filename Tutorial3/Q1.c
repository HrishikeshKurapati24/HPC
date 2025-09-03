#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

#define N 5

pthread_mutex_t chopsticks[N];

void* philosopher(void* num){
    int id = *(int*)num;
    while(1){
        printf("philosopher %d is thinking..\n",id);
        sleep(1);

        printf("philosopher %d is hungry\n", id);

        if(id%2 == 0){
            pthread_mutex_lock(&chopsticks[id]);
            printf("philosopher %d has picked up the left chopstick \n",id);

            pthread_mutex_lock(&chopsticks[(id+1)%N]);
            printf("philosopher %d has picked up the right chopstick \n",id);
        }
        else{
            pthread_mutex_lock(&chopsticks[(id+1)%N]);
            printf("philosopher %d has picked up the right chopstick \n",id);

            pthread_mutex_lock(&chopsticks[id]);
            printf("philosopher %d has picked up the left chopstick \n",id);
        }

        printf("philosopher %d is eating..\n",id);
        sleep(1);

        pthread_mutex_unlock(&chopsticks[id]);
        pthread_mutex_unlock(&chopsticks[(id+1)%N]);

        printf("philosopher %d has finished eating\n",id);
    }
    return NULL;
}

int main(){
    pthread_t philo[N];
    int ids[N];

    for(int i=0;i<N;i++){
        pthread_mutex_init(&chopsticks[i],NULL);
    }
    for(int i=0;i<N;i++){
        ids[i]=i;
        pthread_create(&philo[i],NULL,philosopher,&ids[i]);
    }

    for(int i=0;i<N;i++){
        pthread_join(philo[i],NULL);
    }

    return 0;
}