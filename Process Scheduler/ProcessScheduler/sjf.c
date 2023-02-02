#include "lab4.h"
#define MAX_INT 2147483647

/** Calculates and outputs the average wait and the turn around time of processes
 *  using the passed in CPU burst and arrival time arrays. The function performs 
 *  the shortest job first when determining what process runs. The function selects 
 *  the process with the shortest CPU burst that has arrived and fully runs it and 
 *  then finds the next shortest burst.
 *
 * @param arg
 * 	2-dimensional array containing processes' CPU burst and arrival times.
 *
 * @updates {@code arg} 
 *
 * @requires
 * 	The passing argument is a 2-dimensional array of CPU burst and arrival times
 * 	and the values of CPU burst and arrival times are >=0.
 *
 * @ensures
 * 	The program will output the correct average wait and turn around time using
 * 	the passed in the CPU burst and arrival time arrays assuming the @require has
 * 	been met. 
 */
void *SJF(void *arg) {
	int (* test)[3] = (int (*)[3]) arg; 

	int i,k,j;	
	int burstTime[test[0][2]]; //burst time array
	int arrivalTime[test[0][2]]; //arrival time array
	int arrivalMin = MAX_INT, burstMin = MAX_INT; //minimum of arrival and burst time
	size_t length = sizeof(burstTime)/sizeof(burstTime[0]); //length of burstTime and arrivalTime array
	int arrivalCur; //current arrival time
	float waitTime = 0,turnTime = 0; //wait and turnaround times
	int sumBurst = 0; //sum of CPU bursts
	int flag = 0; //flag variable for waiting between processes
	
	//inserting burst and arrival time values into burstTime and arrivalTime arrays
	for(i=0; i<test[0][2]; i++){
		burstTime[i]=test[i][0];
		arrivalTime[i]=test[i][1];
	}
	
	for(i=0; i<length; i++){
		sumBurst+=burstTime[i];
	}
	
	//finds the earliest arrival time of a process
	for (i=0; i<length; i++){
		if (arrivalTime[i] < arrivalMin){
			arrivalMin = arrivalTime[i];
		}
	}

	//SJF algorithm
	for(j=0; j<length; j++){
		//finds a process with the shortest job within the available arrival time
		goBack:
		flag = 1;
		for(i=0; i<length; i++){
			if (arrivalTime[i]<=arrivalMin && burstTime[i]<burstMin && burstTime[i] >=0){
				arrivalCur = arrivalTime[i];
				burstMin = burstTime[i];
				k=i;
				flag = 0; //found a process
			}
		}
	
		//if there is a wait between processes, find the next shortest arrival time
		if (flag == 1 && j<length){
			arrivalMin = MAX_INT;
			for (i=0; i<length; i++){
                		if (arrivalTime[i] < arrivalMin && burstTime[i] >=0){
                        		arrivalMin = arrivalTime[i];
                		}
			}
			goto goBack; //skips to the next available process and runs the algorithm again
		}
		
		//calculates wait time and turnaround time
		turnTime = turnTime + ((arrivalMin + burstMin) - arrivalTime[k]);
		arrivalMin = arrivalMin + burstMin;
		burstMin = MAX_INT;
		burstTime[k] = -1;
	}
	
	//prints the average wait time and turn around with locks
	sem_wait(&mutex);
	printf("\nAverage Wait Time for SJF is: %.2f\n", (turnTime-sumBurst)/length);
	printf("Average Turnaround Time for SJF is: %.2f\n", turnTime/length);
	sem_post(&mutex);

}
