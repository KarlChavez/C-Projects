#include <stdio.h>
#include <pthread.h>
#define THREAD_NO 10

void *mythread(void *arg) {
    size_t id = (size_t)arg; //line fixed
    printf("my id is %d\n", id);
}

int main(){
    pthread_t p[THREAD_NO];
    size_t i = 0;
	
    //create threads
    for(i=0; i<THREAD_NO; i++){
        pthread_create(&p[i], NULL, mythread, (void*)i); //line fixed
    }

    //join threads
    for(i=0; i<THREAD_NO; i++){
	pthread_join(p[i], NULL);
    }
    return 0;
}
