#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h>

sem_t groupSem, singleSem;

int semValue(sem_t semaphore){
    int value;
    sem_getvalue(&semaphore, &value);
    return value;
}

void *groupQueue(void *ptr){
    sem_post(&groupSem);
    sleep(1);

}

void *singleQueue(void *ptr){
    sem_post(&singleSem);
    sleep(2);

}

void *rolerCoaster(void *ptr) {
    if (semValue(&groupSem) > 0) {
        printf("%d ", semValue(groupSem));
        

    }
}


int main() {
    sem_init(&groupSem, 0, 0);
    sem_init(&singleSem, 0, 0);
    int targ[3];
    pthread_t thread[3];
    int i = 0;
    while(i< 100) {
        i++;
        pthread_create(&thread[0], NULL, &groupQueue, (void *) &targ[0]);
        pthread_create(&thread[1], NULL, &singleQueue, (void *) &targ[1]);
        pthread_create(&thread[2], NULL, &rolerCoaster, (void *) &targ[2]);
        pthread_join(thread[0], NULL);
        pthread_join(thread[1], NULL);
        pthread_join(thread[2], NULL);
    }
    sem_destroy(&groupSem);
    sem_destroy(&singleSem);
    return 0;
}