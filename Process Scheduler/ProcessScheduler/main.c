#include "lab4.h"
#define CPUSCHEDULING 4

void main(int argc, char *argv[]){
	int numPrograms= argc-1;
	int processInfo[numPrograms][3];
	int i=0;
	int j;
	int minArrival;
	sem_init(&mutex, 0, 1);

	pthread_attr_t attr;

	//number of threads equal to the number of CPU scheduling algorithms which is 4
	pthread_t p[CPUSCHEDULING];

	pthread_attr_init(&attr);

	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

	pthread_attr_setschedpolicy(&attr, SCHED_OTHER);
	
	//opens each file input by the user and reads in the arrival time and burst time in each
	for(i=0; i< numPrograms; i++){
		FILE* ptr;
		int temp;
	    	ptr = fopen(argv[i+1], "r");
	 
			if (NULL == ptr) {
				printf("file can't be opened \n");
		    	}
		fscanf(ptr, "%d", &processInfo[i][0]);
		fscanf(ptr, "%d", &processInfo[i][1]);
		processInfo[0][2]=numPrograms;
		fclose(ptr);
	}
	
	//create the threads	
	pthread_create(&p[0], &attr, FCFS, (void *)processInfo);
	pthread_create(&p[1], &attr, RoundRobin, (void *)processInfo);
	pthread_create(&p[2], &attr, STCF, (void *)processInfo);
	pthread_create(&p[3], &attr, SJF, (void *)processInfo);	

	//join on each thread
	pthread_join(p[0], NULL);
	pthread_join(p[1], NULL);
	pthread_join(p[2], NULL);
	pthread_join(p[3], NULL);
}
