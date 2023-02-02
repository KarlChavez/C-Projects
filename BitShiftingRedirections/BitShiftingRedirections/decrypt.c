#include <stdio.h>
#include "lab2header.h"

int main()
{
        int n,k,i,count;
        int groupChar[BIT];
        /*To run the loop*/
        count = 0;
        n = 1;
        while (n)
        {
                i = getchar();
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
                if (count == BIT && i != EOF)
                {
                        decryption(groupChar);
                        /*Resets count*/
                        count = 0;
                }
        }
        return 0;
}
