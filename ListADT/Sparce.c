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
#include "Matrix.h"

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

       fclose(in);
    fclose(out);

    return (0);
}
