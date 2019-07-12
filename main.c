#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

sem_t groupSem, singleSem;

int semValue(sem_t semaphore){
    int value;
    sem_getvalue(&semaphore, &value);
    return value;
}

void *groupQueue(void *ptr){
    sem_post(&groupSem);
    //sleep(1);

}

void *singleQueue(void *ptr){
    sem_post(&singleSem);
    sleep(2);

}

void *rolerCoaster(void *ptr) {
    int array[3];
    int group = 0;
    int x = 0;
        if(semValue(groupSem) > 0 && semValue(singleSem) > 0) {
            //printf("%d ", semValue(groupSem));
            while(x < 10) {
                x++;
                for(int i = 0; i < 3; i++) {
                    sleep(1);
                    array[i] = rand() % 2 + 2;
                    //printf("%d", array[i]);
                }
                if(array[0] == 3 && array[1] == 3){
                    sem_wait(&groupSem);
                    printf("**************\nThis cart left.\nIn the cart there are: %d - %d\nthere are %d groups in the queue.", array[0], array[1], semValue(groupSem));
                }
            }

            /*for(int i = 0; i< 3; i++){

                array[i] = rand() %2 +2;
                printf("%d", array[i]);
            }*/


        }


}


int main() {
    sem_init(&groupSem, 0, 0);
    sem_init(&singleSem, 0, 0);
    int targ[3];
    pthread_t thread[3];
    int i = 0;
    while(i< 10) {
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