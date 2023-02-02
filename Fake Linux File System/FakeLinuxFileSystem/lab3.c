#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

int main()
{
	/*For the while loop*/
	int quit = 1;

	/*User input*/
	char input[TEXT];
	char *token;

	/*Points to the currect directory*/
	node *curDir;

	/*This is the "main" directory*/
	node *cdMain = createD("main");

	/*Assigns the directory pointer to the main directory*/	
	curDir = cdMain;

	while(quit)
        {
                /*Asking for input*/
                printf("\nType a command: ");
                scanf(" %[^\n]", input);
                token = strtok(input, " ");
		
		/* file command */
                if (strcmp(token, "file") == 0)
                {
                        fileCommand(&curDir);
                }
		/* mkdir command */
                else if (strcmp(token, "mkdir") == 0)
                {
			token = strtok(NULL, " ");
                        while(token != NULL)
                        {
                                mkdir(&curDir, token);
                                token = strtok(NULL, " ");
                        }
                }
		/* rmdir command */
		else if (strcmp(token, "rmdir") == 0)
                {
			token = strtok(NULL, " ");
                        while(token != NULL)
                        {
                                rmdir(&curDir, token);
                                token = strtok(NULL, " ");
                        }
                }
		/* rm command */
		else if (strcmp(token, "rm") == 0)
                {
			token = strtok(NULL, " ");
                        while(token != NULL)
                        {
                                rm(&curDir, token);
                                token = strtok(NULL, " ");
                        }
                }
		/* cd commands */
                else if (strcmp(token, "cd") == 0)
                {
			token = strtok(NULL, " ");
			
			/* Takes you back to main directory*/
			if (token == NULL || (strcmp(token, ".") == 0))
			{
				curDir = cdMain;
			}
			else if (strcmp(token, "..") == 0)
			{
				curDir = cdDot(&curDir);
			}
			else
			{
				curDir = cdPath(&curDir, token);
			}
                }
		/* pwd command */
		else if (strcmp(token, "pwd") == 0)
		{
			pwd(&curDir);
		}
		/* ls command */
		else if (strcmp(token, "ls") == 0)
		{
			ls(&curDir);			
		}
		/* cat command */
		else if (strcmp(token, "cat") == 0)
		{
			token = strtok(NULL, " ");
			while(token != NULL)
			{
				cat(&curDir, token);
				token = strtok(NULL, " ");
			}		
		}
		/* clear command */
		else if (strcmp(token, "clear") == 0)
                {
                        clear();
                }
		/* reset command */
		else if (strcmp(token, "reset") == 0)
                {
			curDir = cdMain;
                        reset(&curDir);
                }
		/* info command */
		else if (strcmp(token, "info") == 0)
                {
                        infoD(&curDir);
                }
		/* dirprint command */
		else if (strcmp(token, "dirprint") == 0)
                {
			curDir = cdMain;
                        dirprint(&curDir);
			printf("\n");
                }
		/* help command */
		else if (strcmp(token, "help") == 0)
                {
			help();
                }
		/* quit command */
		else if (strcmp(token, "quit") == 0)
                {
                        quit = 0;
			printf("\nThe program has been terminated. Have a nice day TA graders :D\n\n");
                }
                else
                {
			printf("\nInvalid command! Type \"help\" for the list of commands.\n");
                }
        }
	/* Freeing main */			
	free(cdMain); 	
	return 0;
}

