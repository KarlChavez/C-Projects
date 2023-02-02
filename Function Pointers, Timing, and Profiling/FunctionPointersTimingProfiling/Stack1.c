#include <stdio.h>
#include <stdlib.h>
#include "lab4.h"


Stack* newStack1(){

	/*Initialization*/
	Stack *newStack = malloc(sizeof(Stack));
	Stack *rep = malloc(sizeof(Stack1));
	rep->length = 0;
	
	/*Changing struct members*/
	newStack->Stack = rep;
	newStack->pop = popS1;
	newStack->push = pushS1;
	newStack->length = lengthS1;
	
	return newStack;
}


void pushS1(void *voidHead, int x)
{
	/*Initialization of a new node and a pointer to voidHead*/
	LLNode *newNode;
	Stack1 *newStack;
	newStack = malloc(sizeof(Stack1));
	newStack = (Stack1*)voidHead;

	/*Creating a new node and putting x into the data*/
	newNode = malloc(sizeof(LLNode));
	newNode->data = x;
	
	/*Adding the node to the list*/
	if (newStack->length == 0)
	{
		newStack->length = newStack->length + 1;
		newStack->lastNode = newNode;
		newStack->firstNode = newNode;
	}
	else
	{
		newStack->length = newStack->length + 1;
		newNode->next = newStack->firstNode;
		newStack->firstNode = newNode;
	}
}

int popS1(void *voidHead)
{
	/*Initialization of int to hold data, temporary node pointer, and pointer to voidHead*/
	int num;
	Stack1 *newStack;
	LLNode *temp;
	newStack = malloc(sizeof(Stack1));
	newStack = (Stack1*)voidHead;
	temp = malloc(sizeof(LLNode));
	
	num = newStack->firstNode->data;	
	
	/*Changing the firstNode pointer and freeing variable*/
	temp = newStack->firstNode;
	newStack->firstNode = newStack->firstNode->next;
	newStack->length = newStack->length - 1;

	free(temp);
	return num;
}

int lengthS1(void *voidHead)
{
	/*Initialization*/
	int result;
	Stack1 *newStack;
        newStack = malloc(sizeof(Stack1));
        newStack = (Stack1*)voidHead;

	result = newStack->length;
	return result;
}

