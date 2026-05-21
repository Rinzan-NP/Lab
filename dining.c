#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define  N  5

sem_t room;
sem_t chopstick[N];
sem_t mutex;

void* philosopher(void* args){
    int id = *(int*) args;
    while(1){
        
        printf("Philosoper %d is thinking\n",id);
        sleep(1);
        sem_wait(&room);
        sem_wait(&chopstick[id]);
        sem_wait(&chopstick[(id+1)%N]);
        sem_wait(&mutex);
        printf("Philosoper %d is Eating \n",id);
        sem_post(&mutex);
        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id+1)%N]);
        sem_post(&room);
    }
}
int main(){
    pthread_t tid[N];
    int phil[N];
    int i = 0;
    
    
    sem_init(&room, 0 ,N-1);
    sem_init(&mutex,0,1);
    
    for(i=0;i<N;i++){
        sem_init(&chopstick[i],0,1);
    }
    
    for(i=0;i<N;i++){
        phil[i] = i;
        pthread_create(&tid[i],NULL,philosopher,&phil[i]);
    }
    
    for(i=0;i<N;i++){
        pthread_join(tid[i],NULL);
    }

}