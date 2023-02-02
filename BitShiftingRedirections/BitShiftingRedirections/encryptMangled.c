#include <stdio.h>



#include "lab2headerMangled.h"

/*
According to all known laws
o					f aviation,

  
there 								is no way a bee			
should be			 able to fly.

  
Its wings ar			e too small to get
its fat little body off			 the ground.

  
T					he bee, of course, flies anyway

 
because be				es don't care	
what huma							ns think is impossible.

  
Yell						ow, black. Yellow, black.
Yellow, bla		ck. Yellow, black.

  
Ooh								, black and yellow!
Let's					 shake it up a little.

  
Barry!									 Breakfast is ready!
*/


void encryption(int gChar[])
{
 											       int i,lastC;
        











	
	
	
	
	
	
	
	lastC = gChar[BIT];
        





for (i = 0; i <BIT; i++)
        {
                			gChar[BIT] = gChar[BIT] >> i;
                	gChar[BIT] = gChar[BIT] << BIT;
                gChar[i] = gChar[i] | gChar[BIT];
                		printf("%c", gChar[i]);
   gChar[BIT] = lastC;
        }
}









int main()
{

        int n,i,k,count;
	
			int groupChar[BIT+1];
	
	count = 0;

	n = 1;















	/*Implicit comparison*/
        while (n)
        {	
											i = getchar();
						if (i == EOF)
		{
			/*continue*/
			continue;
							for (k=0; k<count; k++)
			{
								printf("%c", groupChar[k]);
			}
											n = 0;
			/*Goto*/
			goto beeMovie;
		}
								groupChar[count] = i;
						count++;
				if (count == (BIT+1) && i != EOF)
		{
									encryption(groupChar);
					count = 0;
			/*Break*/
			break;
		}
        }
	beeMovie:
        return 0;
}
