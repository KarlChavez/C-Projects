#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define ARRAY_SIZE 1000000
#define THREAD_NO 10

int sum = 0;

void *sum_array(void *arg){
    int *subArray = (int*) arg;
    size_t i;

    //without synchronization
    for (i=0; i < ARRAY_SIZE/THREAD_NO; i++){
	sum += subArray[i];
    }
}

int main(){
    int num[THREAD_NO][ARRAY_SIZE/THREAD_NO];
    
    pthread_t p[THREAD_NO];
    size_t i = 0, j = 0;

    srand(100);
    //initialize arrays
    for(i=0; i< THREAD_NO; i++){
	for(j=0; j< ARRAY_SIZE/THREAD_NO; j++){
            num[i][j] = rand() % 100;
	}
    }

    //create threads
    for(i=0; i<THREAD_NO; i++){
	pthread_create(&p[i], NULL, sum_array, &num[i][0]);
    }
    
    //join threads
    for(i=0; i<THREAD_NO; i++){
	pthread_join(p[i], NULL);
    }

    printf("sum = %d\n", sum);
    return 0;
}
