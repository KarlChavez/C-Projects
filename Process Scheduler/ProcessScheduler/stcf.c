#include "lab4.h"
#define MAX_INT 2147483647

/* Calculates and outputs the average wait and the turn around time of processes
 * using the passed in CPU burst and arrival time arrays. The function performs
 * the shortest time to completion first when determining what process runs. The
 * function selects a process that has arrived and has the shortest CPU burst out 
 * of all the processes. It will run the process until the function finds a shorter
 * CPU burst time.
 *
 * @param arg
 *  	 2-dimensional array containing processes' CPU burst and arrival times 
 *
 * @updates 
 * 	 {@code arg}
 *
 * @requires
 *       The passing argument is a 2 dimensional array of CPU burst and arrival times
 *       and the values of CPU burst and arrival times are >=0.
 *
 * @ensures
 *       The program will output the correct average wait and turn around time using
 *       the passed in the CPU burst and arrival time arrays assuming the @require has
 *       been met 
 */

void *STCF(void *arg) {
	int (* test)[3] = (int (*)[3]) arg; 

	int i = 0, k = 0,j = 0;	
	int burstTime[test[0][2]]; //burst time array
	int arrivalTime[test[0][2]]; //arrival time array
	int arrivalMin = MAX_INT, burstMin = MAX_INT; //minimum arrival and burst time
	size_t length = sizeof(burstTime)/sizeof(burstTime[0]); //length of burstTime and arrivalTime array
	int arrivalCur=0; //current arrival time
	int arrivalTemp, burstTemp; // temporary variables for arrival and burst values
	float waitTime = 0,turnTime = 0; //wait and turnaround times
	int sumBurst = 0; //sum of all CPU Bursts
	int flag = 0; //flag variable for waiting between processes
	
	//inserting burst and arrival time values into the burstTime and arrivalTime arrays
	for(i=0; i<test[0][2]; i++){
		burstTime[i]=test[i][0];
		arrivalTime[i]=test[i][1];
	}
	
	//finds the shortest arrival time
	for (i=0; i<length; i++){
                if (arrivalTime[i] < arrivalMin){
                        arrivalMin = arrivalTime[i];
                }
        }

	for (i=0; i<length; i++){
                sumBurst+=burstTime[i];
        }
	
	//sorts the arrays from shortest to longest bursts
	for(i=0; i<length; i++){
		for (j=i; j<length; j++){
			if (burstTime[j]<=burstTime[i]){
				//checking if the process is the shortest burst
				if (burstTime[j] < burstTime[i] || (burstTime[j] == burstTime[i] && arrivalTime[j]<arrivalTime[i])){
				burstTemp = burstTime[i];
				arrivalTemp = arrivalTime[i];

				arrivalTime[i] = arrivalTime[j];
				burstTime[i] = burstTime[j];

				arrivalTime[j] = arrivalTemp;
				burstTime[j] = burstTemp;
				}
			}
		}
	}
	
	//SCTF algorithm
	arrivalCur = arrivalMin;
	restart:
	flag = 1;
	for(i=k; i<length; i++){
		//finds a process that is available within the arrival time	
		if (arrivalTime[i]<=arrivalCur){
			burstTime[i]--; 
			arrivalCur++; //increase current arrival time
			flag = 0;
			//check if the process has no more burst time
			if (burstTime[i]==0){
				turnTime = turnTime + (arrivalCur-arrivalTime[i]); 
				k++; //increase index
				//if every process is finished, then terminate	
				if (k==length){
					goto label;		
				}
			}
			//switches processes when another process has a shorter burst time
			else if (i!=k && burstTime[i] <= burstTime[i-1]){
				if (burstTime[i] < burstTime[i-1] || (burstTime[i] == burstTime[i-1] && arrivalTime[i]<arrivalTime[i-1])){
                                	burstTemp = burstTime[i-1];
                                	arrivalTemp = arrivalTime[i-1];

                                	arrivalTime[i-1] = arrivalTime[i];
                                	burstTime[i-1] = burstTime[i];

                                	arrivalTime[i] = arrivalTemp;
                                	burstTime[i] = burstTemp;
				}					
			}
			goto restart;
		}				
	}

	//checks if none of the processes were picked
	if (flag == 1 && k<length){
                arrivalCur = MAX_INT;
		for (i=k; i<length; i++){
                	if (arrivalTime[i] < arrivalCur){
                        	arrivalCur = arrivalTime[i];
                        }
                }
               	goto restart; //skips to the next available process and runs the algorithm again
        }	                
	
	//printing the average wait and turn around time while using locks 
	label:
	sem_wait(&mutex); 
	printf("\nAverage Wait Time for STCF is: %.2f\n", (turnTime-sumBurst)/length); 
	printf("Average Turn Around time for STCF is: %.2f\n", turnTime/length);
	sem_post(&mutex);
}
