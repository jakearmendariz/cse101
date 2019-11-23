/*
* Jake Armendariz
* cse101
* Lex.c
* This file will take an input and output file
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <strings.h>
#include <ctype.h>
#include "List.h"

extern int strcmp(const char *, const char *);
extern char *strtok(char *, const char *);

#define MAX_LEN 255
int main(int argc, char *argv[])
{
    FILE *in, *out;
    char line[MAX_LEN];

    // check command line for correct number of arguments
    if (argc != 3)
    {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if (in == NULL)
    {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if (out == NULL)
    {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    //char *a[] = char * [10];

    //read each line of input file, then count and print tokens *'
    char maxInput[255][255];
    int i = 0;
    while (fgets(line, MAX_LEN, in) != NULL)
    {

        strcpy(maxInput[i], line);

        i++;
    }

    char words[i][255];
    int j = 0;
    for (j = 0; j < i; j++)
    {
        strcpy(words[j], maxInput[j]);
        printf("%s", maxInput[j]);
    }
    for (int j = 0; j < i; j++)
    {
        //printf("%s", words[j]);
    }
    List order = newList();
    append(order, 0);

    int size = i;
    for (int i = 1; i < size; i++)
    {
        int zeroIndex = 0;
        //printf("i = %d\n", i);
        moveBack(order);
        for (int j = length(order) - 1; j >= 0; j--)
        {
            if (strcmp(words[i], words[valueAt(order, j)]) < 0)
            {
                //printf("j = %d\n", j);
                if (j == 0)
                {
                    zeroIndex = 1; //In zero index
                }
                else
                {
                    movePrev(order);
                }
            }
        }

        if (zeroIndex == 1)
        {
            //printf("inserting %d before %d\n", i, indexIt(order));
            insertBefore(order, i);
        }
        else
        {
            //printf("inserting %d after %d\n", i, indexIt(order));
            insertAfter(order, i);
        }
        //printList(stdout, order);
        //printf("\n");
    }
    //printf("Complete\n");
    moveFront(order);
    for (int j = 0; j < size; j++)
    {
        //printf("%s", words[valueAt(order, j)]);
        fprintf(out, "%s", words[valueAt(order, j)]);
        moveNext(order);
    }

    //printList(stdout, order);
    freeList(&order);
    fclose(in);
    fclose(out);

    return (0);
}
