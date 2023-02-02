#include <stdio.h>
#include <stdlib.h>
#include "lab4.h"

Stack* newStack2(){

        /*Initialization*/
        Stack *newStack = malloc(sizeof(Stack));
        Stack2 *rep = malloc(sizeof(Stack2));
        rep->length = 0;
	rep->arrSize = MIN_SIZE;

        /*Changing struct members*/


        newStack->Stack = rep;
        newStack->pop = popS2;
        newStack->push = pushS2;
        newStack->length = lengthS2;

        return newStack;
}


void pushS2(void *voidHead, int x)
{
	/*Initialization of a pointer to voidHead and new entries*/
	Stack2 *newStack;
	int *newEntries;
	int i;
	newStack = malloc(sizeof(Stack2));
	newStack = (Stack2*)voidHead;


	/*If the array is empty*/
  	if (newStack->length == 0)
        {
                /*Create a new array*/
                newEntries = malloc((MIN_SIZE)*sizeof(int));
		
		/*Adds element into the first index*/
                *(newEntries) = x;
		newStack->length = newStack->length +1;

		/*Points to new entries*/
		newStack->entries = newEntries;		
        }
	
	/*If the array is filled up*/
	else if (newStack->length == newStack->arrSize)
	{
		/*Create a new array twice the size*/
		newEntries = malloc((2*(newStack->arrSize))*sizeof(int));
		newStack->arrSize = 2*(newStack->arrSize);
	
		/*Copy the elements over*/
                for(i = 0; i < newStack->length; i++)
                {
			*((newEntries)+i) = *((newStack->entries)+i);       
                }
                
                /*Adds element to the top of stack*/
		*(newEntries+(newStack->length)) = x;
		newStack->length = newStack->length +1;
			
		/*Points to new entries*/ 		
		newStack->entries = newEntries;		
	}

	/*If the array reaches a quarter of its current max size*/
	else if(newStack->length == ((newStack->arrSize)/4))
	{
		/*Create a new array half the size*/
                newEntries = malloc(((newStack->arrSize)/2)*sizeof(int));
                newStack->arrSize = ((newStack->arrSize)/2);

		/*Copy the elements over*/
                for(i = 0; i < newStack->length; i++)
                {       
                        *((newEntries)+i) = *((newStack->entries)+i);
                }

		/*Adds element to the top of stack*/
                *(newEntries+(newStack->length)) = x;
		newStack->length = newStack->length +1;
		
                /*Points to new entries*/
                newStack->entries = newEntries;	
	}	
	else
	{
		/*Adds element to the top of stack*/
                *((newStack->entries)+(newStack->length)) = x;
                newStack->length = newStack->length +1;
	}
}


int popS2(void *voidHead)
{
	/*Initialization of a pointer to voidHead and int to hold data*/
	int result;
	Stack2 *newStack;
        newStack = malloc(sizeof(Stack2));
        newStack = (Stack2*)voidHead;

	/*Obtaining the element we want to pop*/
	result = *((newStack->entries)+(newStack->length)-1);
	newStack->length = newStack->length -1;

	return result;
}

int lengthS2(void *voidHead)
{
	/*Initialization of a pointer to voidHead and int variable holder*/
        Stack2 *newStack;
	int result;
        newStack = malloc(sizeof(Stack2));
        newStack = (Stack2*)voidHead;

	result = newStack->length;
	return result;
}

