/*Karl Chavez*/

/* Reminder if you play league to feed the poros in ARAM. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lab4.h"


void enqueue(Queue* this, int x){
	this->enqueue(this->Queue, x);
}

int dequeue(Queue* this){
	return this->dequeue(this->Queue);
}

int queueLength(Queue* this){
	return this->length(this->Queue);
}

void push(Stack *this, int x){
	this->push(this->Stack, x);
}

int pop(Stack *this){
	return this->pop(this->Stack);
}

int stackLength(Stack *this){
	return this->length(this->Stack);
}

/*
void QueueTest(int type){
	Queue* newQueue = newQueue1();

	int i, removed, errors;
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	errors = 0;

	for(i = 0; i < NUM_ENTRIES; i++){
		enqueue(newQueue, i);
	}

	for(i = 0; i < NUM_ENTRIES; i++){
		removed = dequeue(newQueue);
		if(removed != i){
			printf("Expected %i, removed %i\n", i, removed);
			errors++;
		}
	}

	printf("Ended with %i errors\n", errors);

	end = clock();
	cpu_time_used = ((double)(end-start))/CLOCKS_PER_SEC;
	printf("Took %f seconds\n", cpu_time_used);
}
*/

void StackTest(int type){
	Stack* newStack = type == 1 ? newStack1(): newStack2();

	int i, removed, errors;
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	errors = 0;

	for(i = 0; i < NUM_ENTRIES; i++){
		push(newStack, i);
	}

	for(i = 0; i < NUM_ENTRIES; i++){
		removed = pop(newStack);
		if(removed != NUM_ENTRIES - i - 1){
			printf("Expected %i, removed %i\n", NUM_ENTRIES - i - 1, removed);
			errors++;
		}
	}

	printf("Ended with %i errors\n", errors);

	end = clock();
	cpu_time_used = ((double)(end-start))/CLOCKS_PER_SEC;
	printf("Took %f seconds\n", cpu_time_used);
	
}

int main(int argc, char *argv[]){

	int test = 0;

	printf("Stack1\n");
	StackTest(1);
	
	printf("Stack2\n");
	StackTest(2);
		
	return 0;
}
