#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

sem_t mutex;

void *FCFS(void *arg);
void *RoundRobin(void *arg);
void *STCF(void *arg);
void *SJF(void *arg);
