#define CHILDREN 64
#define NAME 65
#define TEXT 257
 
typedef struct node
{       
        /*Determine whether it's a directory or file*/
        int val;
        
        /*Name of file or directory*/
        char name[NAME];
        
        /*ONLY FOR FILE stores text*/
        char text[TEXT];
        
        /*ONLY FOR DIRECTORY size*/
        int size;
        
        /* points to the next and previous node*/
        struct node *next;
        struct node *prev;
        
        /*ONLY FOR DIRECTORY points to a different directory*/
        struct node *cdNext;
        struct node *cdPrev;
} node;

/*Creates directory*/
node *createD(char nameF[])
{       
        node *dir = malloc(sizeof(node));
        node *dir2 = malloc(sizeof(node));
        
        if (dir != NULL && dir2 != NULL)
        {       
                /*make val = 1 for directory*/
                dir->val = 1;
                dir2->val = 1;
                
                /*make size of directory zero*/
                dir->size = 0;
                dir2->size = 0;
                
                /*Assigning pointers*/
                dir->next = NULL;
                dir2->prev = NULL;
                dir->cdNext = dir2;
                dir2->cdPrev = dir;
                
                /*Copying name*/
                strcpy(dir2->name, nameF);
                strcpy(dir->name, nameF);
        }
        return dir;
}

/*Creates file*/
node *createF(char nameF[], char textF[])
{
        node *fil = malloc(sizeof(node));
        if (fil != NULL)
        {
                /*make val = 0 for file*/
                fil->val = 0;

                /*Assigning pointer*/
                fil->next = NULL;

                /*Copying name*/
                strcpy(fil->name, nameF);

                /*Copying text*/
                strcpy(fil->text, textF);
        }
        return fil;
}

/*Links files*/
void linkFile(node *fil, node **dir)
{
        node *prev;

        /*Increases the size of the directory*/
        (*dir)->size = ((*dir)->size) + 1;

        /*Terse link list*/
        while(*dir != NULL)
        {
                prev = *dir;
                dir = &((**dir).next);
        }
        fil->next = *dir;
        *dir = fil;
        (**dir).prev = prev;

}

/*Links directory to current directory*/
void linkDirectory(node *insert, node **dir)
{
        node *prev;

        /*Increases the size of the directory*/
        (*dir)->size = ((*dir)->size) + 1;

        /*Terse link list*/
        while(*dir != NULL)
        {
                prev = *dir;
                dir = &((**dir).next);
        }
        insert->next = *dir;
        *dir = insert;
        (**dir).prev = prev;
}

/*
 *
 * UNIX COMMANDS FUNCTIONS
 *
*/

/* "cd .." command*/
node *cdDot(node **dir)
{
        node *newDirectory;
        node *prev;
        if ((**dir).cdPrev == NULL)
        {
                printf("\nError! You are in the main directory. You cannot move up\n");
                newDirectory = *dir;
        }
        else
        {
                *dir = (**dir).cdPrev;
                while(*dir != NULL)
                {
                        prev = *dir;
                        dir = &((**dir).prev);
                }
                newDirectory = prev;
        }
        return newDirectory;

}

/* "cd <name>" command */
node *cdPath(node **dir, char nameP[])
{       
        node *newDirectory;
        /*Goes through list until it finds the directory*/
        while (*dir != NULL && ((strcmp((**dir).name, nameP) !=0 || (((**dir).val) !=1))))
        {       
                dir = &((**dir).next);
        }
        
        /*Directory is non-existent*/
        if (*dir == NULL)
        {       
                printf("\nThe directory doesn't exist!");
                newDirectory = *dir;
        }
        else
        {       
                newDirectory = (**dir).cdNext;
        }
        
        return newDirectory;
}

/* "ls" command */
void ls(node **dir)
{
        printf("\n");

        /*Empty Directory*/
        if ((**dir).size == 0)
        {
                printf("This directory doesn't have any files or directories");
        }
        else
        {
                /*skips the current directory*/
                dir = &((**dir).next);

                /*Prints everything on the directory*/
                while(*dir != NULL)
                {
                        if ((**dir).val == 0)
                        {
                                printf("%s(file) ", (**dir).name);
                        }
                        else
                        {
                                printf("%s(directory) ", (**dir).name);
                        }
                        dir = &((**dir).next);
                }
        }
        printf("\n");
}

/* "pwd" command */
void pwd(node **dir)
{       
        printf("\nYour current directory is: %s\n", (**dir).name);
}

/* "cat" command */
void cat(node **dir, char nameT[])
{
        char *token;
        char textF[TEXT];
        int i = 0;;

        /*Finds the file and prints the text*/
        while (*dir != NULL && ((strcmp((**dir).name, nameT) !=0)))
        {
                dir = &((**dir).next);
        }
        /* Not in directory */
        if (dir == NULL)
        {
                printf("%s is not in the directory!", nameT);
        }
        else
        {
                /*If it's a directory*/
                if ((**dir).val == 1)
                {
                        printf("\n%s is a directory\n");
                }
                /*Printing out text in file*/
                else
                {
                        printf("\n");
                        while((**dir).text[i] != '\0')
                        {
                                printf("%c", (**dir).text[i]);
                                i++;
                        }
                        printf("\n");
                }
        }
        return;
}

/* "rm" command*/
void rm(node **dir, char nameD[])
{       
        node *prev;
        node *next;
        node *size = *dir;
        if ((*dir)->size == 0)
        {       
                printf("\nError! The directory is empty\n");
        }
        else
        {       
                /*Goes through list until it finds the file*/ 
                while (*dir != NULL && ((strcmp((**dir).name, nameD) !=0 || (((**dir).val) !=0))))
                {       
                        prev = *dir;
                        dir = &((**dir).next);
                }
                /*Not in the directory*/
                if (*dir == NULL)
                {       
                        printf("\nError! Not in the directory\n");
                }
                /*Removing a node from the end of list*/
                else if ((**dir).next == NULL)
                {       
                        size->size = size->size - 1;
                        (**dir).prev = NULL;
                        prev->next = NULL;
                }
                /*Removing in between a list*/
                else
                {       
                        size->size = size->size - 1;
                        dir = &((**dir).next);
                        next = *dir; 
                        prev->next = next;
                        next->prev = prev;
                        (**dir).next = NULL;
                        (**dir).prev = NULL;
                }
        }
}

/* "mkdir" command*/
void mkdir(node **dir, char name[])
{       
        int loop = 1;
        node *temp;
        node *newDirectory;
        
        /*If the directory holds more than 64 children*/
        if ((*dir)->size == CHILDREN)
        {       
                printf("\nError: This directory is full\n");
        }
        else
        {       
                /*If file name exceeds 64 characters*/
                if (strlen(name) > CHILDREN)
                {       
                        while(loop)
                        {       
                                printf("\nName of the the directory is too long. Enter another name: ");
                                scanf("%s", name);
                                
                                if (strlen(name) < NAME)
                                {       
                                        loop = 0;
                                }
                        }
                }
                else
                {       
                        /*Checks for duuplicates*/
                        temp = *dir;
                        while(temp != NULL && ((strcmp(temp->name, name) !=0 || ((temp->val) !=1))))
                        {       
                                temp = (temp->next);
                        }
                        if (temp == NULL)
                        {       
                                newDirectory = createD(name);
                                linkDirectory(newDirectory, &(*dir));
                        }
                        else
                        {       
                                printf("\nError! There already exists a directory with the same name in this directory\n");
                        }
                }
        }
        return;
 
}

/* "rmdir" command*/
void rmdir(node **dir, char nameD[])
{       
        node *prev;
        node *next;
        node *size = *dir;
        if ((*dir)->size == 0)
        {       
                printf("\nError! The directory is empty\n");
        }
        else
        {       
                /*Goes through list until it finds the directory*/
                while (*dir != NULL && ((strcmp((**dir).name, nameD) !=0 || (((**dir).val) !=1))))
                {       
                        prev = *dir;
                        dir = &((**dir).next);
                }       
                /*Not in the directory*/
                if (*dir == NULL)
                {       
                        printf("\nError! Not in the directory\n");
                }
                /*Removing a node from the end of list*/
                else if ((**dir).next == NULL)
                {       
                        size->size = size->size - 1;
                        (**dir).prev = NULL;
                        prev->next = NULL;
                }
                /*Removing in between a list*/
                else
                {       
                        size->size = size->size - 1;
                        dir = &((**dir).next);
                        next = *dir; 
                        prev->next = next;
                        next->prev = prev;
                        (**dir).next = NULL;
                        (**dir).prev = NULL;
                }
        }
}

/*"file" command"*/
void fileCommand(node **dir)
{
        char name[NAME];
        char text[TEXT];
        int loop = 1;
        node *temp;
        node *newFile;

        /*If the directory holds more than 64 children*/
        if ((*dir)->size == 64)
        {
                printf("\nError: This directory is full\n");
        }
        else
        {
                printf("\nEnter the name of the file: ");
                scanf("%s", name);

                /*If file name exceeds 64 characters*/
                if (strlen(name) > CHILDREN)
                {
                        while(loop)
                        {
                                printf("\nName of the the file is too long. Try again");
                                scanf("%s", name);

                                if (strlen(name) < NAME)
                                {
                                        loop = 0;
                                }
                        }
                }
                else
                {
                        printf("\nEnter the text of your file: ");
                        scanf(" %[^\n]", text);

                        /*If the text exceeds 256 characters*/
                        if (strlen(text) > (TEXT-1))
                        {
                                while(loop)
                                {
                                        printf("\nText file is too long. Try again\n");
                                        scanf(" %[^\n]", text);

                                        if (strlen(text) < TEXT)
                                        {
                                                loop = 0;
                                        }
                                }
                        }

                        /*Checks for duuplicates*/
                        temp = *dir;
                        while(temp != NULL && ((strcmp(temp->name, name) !=0 || ((temp->val) !=0))))
                        {
                                temp = (temp->next);
                        }
                        if (temp == NULL)
                        {
                                newFile = createF(name, text);
                                linkFile(newFile, &(*dir));
                        }
                        else
                        {
                                printf("\nError! There already exists a file with the same name in this directory\n");
                        }

                }
        }
        return;
}

/* "clear" command */
void clear()
{
        int i;
        for (i = 0; i < NAME; i++)
        {
                printf("\n");
        }
}

/* "reset" command*/
void reset(node **dir)
{
        /*Resets size to 0 and detaches all nodes from main*/
        (**dir).size = 0;
        (**dir).next = NULL;
}

/* "info" command */
void infoD(node **dir)
{
        int countDirectory = 0;
        int countFile = 0;

        printf("\nIn your current directory (%s), ", (**dir).name);
        /*Goes through the current directory and counts the number of directories and files*/
        while(*dir != NULL)
                {
                        dir = &((**dir).next);
                        if (*dir != NULL)
                        {
                                if ((**dir).val == 0)
                                {
                                        countFile++;
                                }
                                else
                                {
                                        countDirectory++;
                                }
                        }
                }
                printf("there are %i files and %i directories.\n", countFile, countDirectory);
}

/* "dirprint" */
void dirprint(node **dir)
{
        node *start;
        start = *dir;

        /*Prints out current directory*/
        printf("\nDirectory %s: ", (**dir).name);

        /*Ptints out children*/
        while(*dir != NULL)
        {
                dir = &((**dir).next);
                if (*dir != NULL && ((**dir).val == 0))
                {
                        printf("%s (file) ", (**dir).name);
                }
                else if (*dir != NULL && ((**dir).val == 1))
                {
                        printf("%s (directory) ", (**dir).name);
                }
        }

        /*Checks for other directories*/
        start = (start->next);
        while(start != NULL)
        {
                if (start->val == 1)
                {
                        dirprint(&(start->cdNext));
                }
                start = (start->next);
        }
}

/* "help" command */
void help()
{
        printf("\nCommands \"cd\" and \"cd .\" move you back to the main directory.\n");
        printf("\nCommand \"cd ..\" moves you back one directory.\n");
        printf("\nCommand \"cd <name>\" changes to desired directory.\n");
        printf("\nCommand \"ls\" prints the list of files and directories in the current directory.\n");
        printf("\nCommand \"pwd\" prints the name of the current directory\n");
        printf("\nCommand \"cat <name> <name> ...\" displays the contents of one or more files and directories.\n");
        printf("\nCommand \"rm <name>\" removes desired directory.\n");
        printf("\nCommand \"mkdir <name>\" creates directory with the desired name.\n");
        printf("\nCommand \"rmdir <name>\" removes desired directory.\n");
        printf("\nCommand \"file\" creates a file and asks the user to input the name and the text contents of the file.\n");
        printf("\nCommand \"clear\" clears the terminal screen.\n");
        printf("\nCommand \"reset\" clears the whole inventory and gives you an empty main directory.\n");
        printf("\nCommand \"info\" prints out the current directory and the number of files and directories in your current directory.\n");
        printf("\nCommand \"dirprint\" prints the current directory, the siblings of the current directory, and so on, up to and including the root.\n");
        printf("\nCommand \"quit\" quits the program.\n");
}


