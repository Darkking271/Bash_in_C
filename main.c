/*
 * File:   main.c
 * Authors: Alex Voytovich
 *          Marcus Giarusso
 *
 * This assignment is written as a C program which produces auto-complete
 * suggestions, similar to what Bash does when beginning to type a command and
 * pressing <tab>. More specifically, this program will read all of the file
 * names in a user directory and store them in a hash table data structure made
 * up of a 27 element array of linked lists
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

void parseDir(char[]);
int retrieveId(char);
bool checkequal(char[], char[], int);

typedef struct node
{
    char * x[100];
    struct node * next;
} node_t;

/*
 *
 */
int main(int argc, char** argv)
{
    char dirname[100];

    //User enters wanted directory
    printf( "Enter a directory :");
    scanf("%s", dirname);

    //Directory parsing function
    parseDir(dirname);
    return 0;
}

void parseDir(char dirname[100])
{
    //Initialize linked list array
    node_t * list[27];
    for(int i = 0; i < 27; i++)
    {
        list[i] = NULL;
        list[i] = malloc(sizeof(node_t));
    }

    //Initialize directing reading tools
    DIR *dir;
    struct dirent *direxp;
    dir = opendir(dirname);
    char *str[100];

    //Parse directory, and sort into lists
    if(dir != NULL)
    {
        while ((direxp = readdir(dir)) != NULL)
        {
            strcpy(str, direxp -> d_name);
            int a = str[0];
            int n = retrieveId(a);
            node_t * current = list[n];
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = malloc(sizeof(node_t));
            strcpy(current->next->x, str);
            current->next->next = NULL;
        }
        closedir(dir);
    }
    else
    {
        //If directory doesn't exist, tell user, and end program
        printf("Directory Not Found!");
        return;
    }

    //Search files in directory
    char file[30];
    while(!checkequal(file, "0", 1))
    {
        printf("\n(0 to quit) Search: ");
        scanf("%s", file);
        int b = retrieveId(file[0]);
        int len = strlen(file);
        node_t* node = list[b];
        while (node != NULL)
        {
            //Check if strings are equal, and if they are, print it
            if (checkequal(node->x, file, len))
            {
                printf("%s\n", node->x);
            }

            node = node->next;
        }
        //printf("\n(0 to quit) Search: ");
    }
}

//Hashing function
int retrieveId(char a)
{
    a = tolower(a);
    int x;
    if (isalpha(a))
        x = (int)a - 97;
    else
        x = 26;
    return x;
}

//Function for comparing strings
bool checkequal(char a[], char b[], int len)
{
    bool status = false;
    for (int i = 0; i < len; i++)
    {
        if (tolower(a[i]) == tolower(b[i]))
            status = true;
        else
        {
            status = false;
            break;
        }
    }
    return status;
}
