#include <stdio.h>
#include <stdlib.h>

#include "lab4.h"


Queue* newQueue1(){

	Queue *newQueue = malloc(sizeof(Queue));
	Queue1 *rep = malloc(sizeof(Queue1));
	rep->length = 0;
	
	/*Changing struct members*/
	newQueue->Queue = rep;
	newQueue->enqueue = enqueueQ1;
	newQueue->dequeue = dequeueQ1;
	newQueue->length = lengthQ1;

	return newQueue;	
}

void enqueueQ1(void *voidHead, int x){
	
	/*Initialization of a new node and a pointer to voidHead*/	
	LLNode *newNode;
	Queue1 *newQueue;
	newQueue = malloc(sizeof(Queue1));
	newQueue = (Queue1*)voidHead;

	/*Creating a new node and putting x into the data*/	
	newNode = malloc(sizeof(LLNode));
	newNode->data = x;

	/*Adding the node to the list*/
	if (newQueue->length == 0)
	{
		newQueue->length = newQueue->length + 1;
		newQueue->lastNode = newNode;
		newQueue->firstNode = newNode;
	}
	else
	{
		newQueue->length = newQueue->length + 1;
		newQueue->lastNode->next = newNode;
		newQueue->lastNode = newNode;
	}
}


int dequeueQ1(void *voidHead){
	
	/*Initialization of int to hold data, temporary node pointer, and pointer to voidHead*/	
	int num;
	Queue1 *newQueue;
	LLNode *temp;
	newQueue = malloc(sizeof(Queue1));
        newQueue = (Queue1*)voidHead;
	temp = malloc(sizeof(LLNode));

	num = newQueue->firstNode->data;

	/*Changing the firstNode pointer and freeing variable*/
	temp = newQueue->firstNode;
	newQueue->firstNode = newQueue->firstNode->next;
	newQueue->length = newQueue->length - 1;
	
	free(temp);	
	return num;
}

int lengthQ1(void *voidHead){
	
	/*Initialization*/
	Queue1 *newQueue;
        newQueue = malloc(sizeof(Queue1));
        newQueue = (Queue1*)voidHead;
	
	return newQueue->length;	
}



