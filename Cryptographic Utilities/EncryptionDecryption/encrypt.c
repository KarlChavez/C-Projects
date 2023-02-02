#include <stdio.h>
#include "lab2header.h"


int main()
{
        int n,i,k,count;
	
	/*Storing characters inside an array*/
	int groupChar[BIT+1];
	
	/*Keeps track on how many characters are inputted*/
	count = 0;

	n = 1;
        while (n)
        {	
		i = getchar();
		/*When the program reaches end of file*/
		if (i == EOF)
		{
			for (k=0; k<count; k++)
			{
				printf("%c", groupChar[k]);
			}
			n = 0;
		}
		groupChar[count] = i;
		count++;
		/*When we have obtained 8 characters*/
		if (count == (BIT+1) && i != EOF)
		{
			encryption(groupChar);
			/*Resets count*/
			count = 0;
		}
        }
        return 0;
}
