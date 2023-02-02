
My partner and I are solving the task-level parallelism problem for threads. The task-level parallelism is an important issue to solve because data inconsistency can occur when there is more than one thread accessing the critical section. We used a binary semaphore, a synchronization tool, to solve the issue. The binary semaphore solves the issue as it lets only one thread access the critical section.

Introduction and Background
The task-level parallelism problem tackles the main issue of threads accessing shared resources such as files or variables. Threads can execute in parallel, meaning they can run multiple instructions at the same time. Since threads can execute in parallel, they can be interrupted (non-atomic) mid-execution, thus leading to data inconsistency. The result of a program is unpredictable when the data is inconsistent. 
	
Our program creates four thread methods for each CPU scheduling algorithm learned in class. All four thread methods run in parallel, calculate the average wait and turnaround time, and print the values to the screen. The issue is that the print statements are inconsistent because of parallelism. 
To solve the problem, we used a binary semaphore so only one thread method can print the average wait and turnaround time without being interrupted by other thread methods. The print statements will be consistent for each thread method, thus making it easier for the users to read the output of the program. Otherwise, the output will be unorganized and confusing. 

Methodology and Implementation
As mentioned above, the program creates four thread methods for each CPU scheduling algorithm. They are first-come-first-serve (FCFS), shortest-job-first (SJF), shortest-time-completion-first (STCF), and round robin (RR). We used code from “PthreadsDataParallelism” to create and join the thread methods from lines 5-48 in “main.c”. (Kelley). A 2-dimensional array containing CPU bursts and arrival times of each process is passed into each thread method. We implemented each CPU scheduling algorithm to calculate the correct average wait and turnaround time. We used the “Jaimie-Scheduling-lecture4” slides in class to help implement each algorithm (Kelley 12-23). 
Once the algorithms have calculated the values, we locked the binary semaphore using “sem_wait(&mutex)”, printed the average wait and turnaround time for the corresponding thread function, and then unlocked it through “sem_post(&mutex)”. We are using the binary semaphore as a mutex. Unlocking and locking the binary semaphore prevents all four thread methods from printing at the same time inconsistently. 
The bulk of the work of this lab came from implementing the four CPU scheduling algorithms. My partner, Griffin Lavy, implemented FCFS and RR while I implemented SJF and STCF. 

Results
SJF and STCF were difficult to implement because we were using an array as the data structure. Since an array has a fixed size, it made moving and finding arrival and burst times troublesome. Also, segmentation faults occurred more frequently because I was accessing out-of-bound indexes. In the end, our expectations were met. We were able to output the correct wait and turnaround time for each CPU algorithm efficiently and neatly to the users of the program. 

Conclusion
As a group, we could have found a more efficient way to calculate each CPU scheduling algorithm. If we had to do this again, I would use a different data structure like a stack or queue instead of a fixed array. We were unable to create a faster runtime because of the array structure. This code can be applied to other issues where many thread methods are active at once. Both Griffin and I handled the workload evenly. We gave each other two algorithms to implement and both worked the header and main. 
