#include "lab4.h"
/**
*Returns the average turnaround time utilizing the FCFS algorithm with the given processes' arrival 
*time and burst time
*
*@params
*burstTime: an array of burst times with the index associating to a given process
*arrivalTime: an array of arrival times with the index associating to a given process
*length: an integer that tracks the number of processes input by the user
*
*@return
*Returns a float value associated to the average turn around time 
*/
float averageTurnAroundTimeFCFS(int* burstTime, int* arrivalTime, int length){
	int i;
	int overallTurnAround= burstTime[0];
	float averageTurnAround=0;
	int overallTime = burstTime[0];
	for(i=1; i<length; i++){
		//checks if the arrival time is greater than the current current time
		if((arrivalTime[i]-overallTime)>0){
			//if arrival time is greater than the overall time is now set to the arrival time of the current process
			overallTime=arrivalTime[i];
			
		}
		//adds to the overall time the burst time of the current process
		overallTime=overallTime+burstTime[i];
		//adds to the overall turnaround the (time process finished - arrival time of process)
		overallTurnAround= overallTurnAround + (overallTime-arrivalTime[i]);
		
	}
	//gets average turn around of all processes
	averageTurnAround = ((float)(overallTurnAround))/length;
	return averageTurnAround;
}

/**
*Returns the average wait time utilizing the FCFS algorithm with the given processes' arrival 
*time and burst time
*
*@params
*burstTime: an array of burst times with the index associating to a given process
*arrivalTime: an array of arrival times with the index associating to a given process
*length: an integer that tracks the number of processes input by the user
*
*@return
*Returns a float value associated to the average wait time 
*/
float averageWaitTimeFCFS(int* burstTime, int* arrivalTime, int length){
	int i;
	int overallWait= 0;
	float averageWait=0;
	//sets the overall time to the time the first process arrived plus the time its burst time
	int overallTime = burstTime[0]+arrivalTime[0];
	for(i=1; i<length; i++){
		//if the arrival time is less than overalltime than the process had to wait
		if((arrivalTime[i]-overallTime)<0){
			//adds the (current time - when the process arrived) to overall wait
			overallWait=overallWait+((overallTime-arrivalTime[i]));
		}
		if((arrivalTime[i]-overallTime)>0){
			overallTime=overallTime+(arrivalTime[i]-overallTime);
		}
			overallTime=overallTime+burstTime[i];
	}
	//calculates the average wait of all processes
	averageWait= ((float)(overallWait))/length;
	return averageWait;
	
}
/**
*Prints the average wait time and turn around time of the processes input by the user utilizing the FCFS algorithm
*
*@params
*arg: A multidimensional array where each row index represents a process and column 1 is the burst time
*for the given process and column 2 is the arrival time
*
*/
void *FCFS(void *arg) {
	int (* test)[3] = (int (*)[3]) arg; 
	int burstTime[test[0][2]];
	int arrivalTime[test[0][2]];
	int i;
	int j;
	int currentProcess = -1;
	int nextProcess = 0;
	int minArrival=0;
	//seperates the multidimensional arry into 2 arrays for easier use
	for(i=0; i<test[0][2]; i++){
		burstTime[i]=test[i][0];
		arrivalTime[i]=test[i][1];
	}
	
	//sorts the two arrays by arrival time
	for(i=0; i<(test[0][2]-1); i++){
		minArrival=i;
		for(j=i+1; j<test[0][2]; j++){
			if(arrivalTime[minArrival]>arrivalTime[j]){
				minArrival=j;	
			}
		}
		
		int temp1 = burstTime[minArrival];
		int temp2 = arrivalTime[minArrival];
		burstTime[minArrival]= burstTime[i];
		arrivalTime[minArrival]= arrivalTime[i];
		burstTime[i]=temp1;
		arrivalTime[i]=temp2;
		
	}
	float averageWait= averageWaitTimeFCFS(burstTime, arrivalTime, test[0][2]);
	float averageTurnAround= averageTurnAroundTimeFCFS(burstTime, arrivalTime, test[0][2]);
	//utilizes a mutex for better printing format
	sem_wait(&mutex);
	printf("\nAverage Wait for FCFS: %.2f\n", averageWait);
	printf("Average Turn Around Time for FCFS: %.2f\n", averageTurnAround);
	sem_post(&mutex);
	
	
}
