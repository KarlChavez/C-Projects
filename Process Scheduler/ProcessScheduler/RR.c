#include "lab4.h"

/**
*Returns the total turnaround time utilizing the RoundRobin algorithm with the given quantum time and processes' arrival time and *burst time
*
*@params
*	burstTime: an array of burst times with the index associating to a given process
*	arrivalTime: an array of arrival times with the index associating to a given process to be manipulated
*	arrivalTimeOrig: an array of arrival times with the index associating to a given process
*	length: an integer that tracks the number of processes input by the user
*
*
*@returns
*	Returns the total turnaround time of all processes
*/
int totalTurnAroundTimeRR(int* burstTime, int* arrivalTime, int* arrivalTimeOrig, int length, int quantum){
	int i;
	int j;
	int overallTurnAround= 0;
	int overallBurst=0;
	int stillBurstTime=1;
	//checks if there are processes that still have burst time
	while(stillBurstTime==1){
		int currentlyRunning=0;
		stillBurstTime=0;
		for(i=0; i<length; i++){
			//checks if the current process is waiting and if it still has burst time
			if(arrivalTime[i]<=0 && burstTime[i]>0){
				//if a process still has burst time then stillBurstTime is set to 1
				stillBurstTime=1;
				//counts the processes that currently have burst time and are waiting
				currentlyRunning=currentlyRunning+1;
				//checks if the burst time of the process is less than or equal to the quantum
				if(burstTime[i]-quantum<=0){
					overallBurst=overallBurst+burstTime[i];
					for(j=0; j<length; j++){
						arrivalTime[j]=arrivalTime[j]-burstTime[i];
					}
					burstTime[i]=0;
					//The process has finished so the turnaround time of the current process is added
					overallTurnAround= overallTurnAround+(overallBurst-arrivalTimeOrig[i]);
					
		
				}
				else{
					//the quantum is added to the total time
					overallBurst=overallBurst+quantum;
					//the quantum is subtracted from the burst time of the current process
					burstTime[i]=burstTime[i]-quantum;
					//the quantum is subtracted from all the processes arrival time
					for(j=0; j<length; j++){
						arrivalTime[j]=arrivalTime[j]-quantum;
					}
				}
			}
			//checks if the current process still burst time, still hasn't arrived and if there are no other processes with burst time
			if(burstTime[i]>0 && arrivalTime[i]>0 && currentlyRunning==0){
				//adds the process' arrival time to the overall time
				overallBurst=overallBurst+arrivalTime[i];
				currentlyRunning=1;
				stillBurstTime=1;
				int temp=arrivalTime[i];
				for(j=0; j<length; j++){
					arrivalTime[j]=arrivalTime[j]-temp;
					if(arrivalTime[j]<0){
						arrivalTime[j]=0;
					}
				}
				
			}		
	
			
		}
	}

	return overallTurnAround;
	
}
/**
*Prints the average wait time and turn around time of the processes input by the user utilizing the Round Robin algorithm
*
*@params
*arg: A multidimensional array where each row index represents a process and column 1 is the burst time
*for the given process and column 2 is the arrival time
*
*/

void *RoundRobin(void *arg) {
	int (* test)[3] = (int (*)[3]) arg; 
	int burstTime1[test[0][2]];
	int arrivalTime1[test[0][2]];
	int burstTime2[test[0][2]];
	int arrivalTime2[test[0][2]];
	int quantum=5;
	int i;
	int j;
	int currentProcess = -1;
	int nextProcess = 0;
	int minArrival=0;
	int totalBurstTime=0;
	//seperates the test array into 4 seperate arrays with 2 being arrival time and 2 being the burst times of the processes
	for(i=0; i<test[0][2]; i++){
		burstTime1[i]=test[i][0];
		arrivalTime1[i]=test[i][1];
		burstTime2[i]=test[i][0];
		arrivalTime2[i]=test[i][1];
	}
	
	//sorts the 4 arrays by the arrival time of each process
	for(i=0; i<(test[0][2]-1); i++){
		minArrival=i;
		for(j=i+1; j<test[0][2]; j++){
			if(arrivalTime1[minArrival]>arrivalTime1[j]){
				minArrival=j;	
			}
		}
		
		int temp1 = burstTime1[minArrival];
		int temp2 = arrivalTime1[minArrival];
		burstTime1[minArrival]= burstTime1[i];
		arrivalTime1[minArrival]= arrivalTime1[i];
		burstTime2[minArrival]= burstTime2[i];
		arrivalTime2[minArrival]= arrivalTime2[i];
		burstTime1[i]=temp1;
		arrivalTime1[i]=temp2;
		burstTime2[i]=temp1;
		arrivalTime2[i]=temp2;
		
	}
	
	int totalTA=totalTurnAroundTimeRR(burstTime1, arrivalTime1, arrivalTime2, test[0][2], quantum);
	float averageTA = ((float)totalTA)/test[0][2];
	//calculates the total wait time based on the overall turn around time of all processes
	for(i=0; i<test[0][2]; i++){
		totalBurstTime=totalBurstTime+burstTime2[i];
	}
	float averageWaitTime=((float)(totalTA-totalBurstTime))/test[0][2];
	if(averageWaitTime<0){
		averageWaitTime=0;
	}
	//mutex is utilized for better formatted printing
	sem_wait(&mutex);
	printf("\nAverage Wait for RoundRobin: %.2f\n", averageWaitTime);
	printf("Average Turn Around Time for RoundRobin: %.2f\n", averageTA);
	sem_post(&mutex);
	
}
