/*Karl Chavez*/
#define ADDZERO 127
#define BIT 7

void encryption(int gChar[])
{
        int i,lastC;
	/*Initializes the last character*/
        lastC = gChar[BIT];
        for (i = 0; i <BIT; i++)
        {
                gChar[BIT] = gChar[BIT] >> i;

		/*Shifts left the right amount for comparison*/
                gChar[BIT] = gChar[BIT] << BIT;
	
		/*Builds the decrypted character*/
                gChar[i] = gChar[i] | gChar[BIT];
	
                printf("%c", gChar[i]);
		/*Resets the last char*/
                gChar[BIT] = lastC;
        }
}

void decryption(int gChar[])
{
        /*Variable to hold the original values*/
        int gCharTemp[BIT];
	/*Decrypted Character*/
        int deChar = 0;
        int f = ADDZERO;
        /*The 8th Character*/
        int i,k,j,r,n;
        /*Copying Values*/
        for (i = 0; i<BIT; i++ )
        {
                gCharTemp[i] = gChar[i];
        }

        /*Shifting bites into the correct placement*/
        for (i = 0; i<BIT; i++)
        {
                gCharTemp[i] = gCharTemp[i] >> BIT;
                gCharTemp[i] = gCharTemp[i] << i;
                deChar = deChar | gCharTemp[i];

        }
        /*Printing out the characters*/
        for(i = 0; i<7; i++)
        {
                /*Makes the first bit of each character 0*/
                gChar[i] = gChar[i] & f;
                printf("%c", gChar[i]);
        }
	/*Prints out the 8th character*/
        printf("%c", deChar);
}
