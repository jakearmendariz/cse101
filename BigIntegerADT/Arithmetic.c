/*
* Jake Armendariz
* jsarmend
* pa3
* cse101
* Arithmetic
* This file will take an input and output file
* Containing two numbers, that will have these operations preformed
* 𝐴, 𝐵, 𝐴 + 𝐵, 𝐴 − 𝐵, 𝐴 − 𝐴, 3𝐴 − 2𝐵, 𝐴𝐵, 𝐴^2, 𝐵^2, 9𝐴^4 + 16𝐵^5
*/

/**
 * 
 * List of bugs:
 * On in2 the input is modifed, after the 610 it gets werid and does work. Looks fine for in1 and in3
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "BigInteger.h"

int main(int argc, char *argv[])
{
    //printf("Sparce.C\n");
    FILE *in, *out;

    // check command line for correct number of arguments
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if (in == NULL)
    {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if (out == NULL)
    {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    int a;
    fscanf(in, "%d", &a);
    char *str1 = malloc(a * 4);
    //fgets(str1, a, in);

    char c;
    int i = 0;
    for (; i < a + 0; i++)
    {
        fscanf(in, " %c", &c);
        str1[i] = c;
        //printf("%c", c);
        if (c == '+' || c == '-')
        {
            a += 1;
        }
    }
    //printf("\n");
    //String 2
    fscanf(in, "%d", &a);
    char *str2 = malloc(a * 4);
    for (i = 0; i < a + 0; i++)
    {
        fscanf(in, " %c", &c);
        str2[i] = c;
        if (c == '+' || c == '-')
        {
            a += 1;
        }
    }
    //out = stdout;
    BigInteger A = stringToBigInteger(str1);
    BigInteger B = stringToBigInteger(str2);
    BigInteger C = newBigInteger();
    //printf("A: \n");
    printBigInteger(out, A);
    fprintf(out, "\n");

    //printf("B:\n");
    printBigInteger(out, B);
    fprintf(out, "\n");

    //printf("A+B:\n");
    C = sum(A, B);
    printBigInteger(out, C);
    fprintf(out, "\n");

    //printf("A-B:\n");
    subtract(C, A, B);
    printBigInteger(out, C);
    fprintf(out, "\n");

    //printf("A-A:\n");
    C = diff(A, A);
    printBigInteger(out, C);
    fprintf(out, "\n");

   // printf("3A-2B:\n");
    C = diff(MultiplyByConstant(A, 3), MultiplyByConstant(B, 2));
    printBigInteger(out, C);
    fprintf(out, "\n");

    //printf("A*B:\n");
    C = prod(A, B);
    printBigInteger(out, C);
    fprintf(out, "\n");

   // printf("A*A:\n");
    multiply(C, A, A);
    printBigInteger(out, C);
    fprintf(out, "\n");

    //printf("B*B:\n");
    C = prod(B, B);
    printBigInteger(out, C);
    fprintf(out, "\n");

    //9A^4 + 16B^5
    //printf("9A^4 + 16B^5:\n");
    C = sum(MultiplyByConstant(prod(prod(A, A), prod(A, A)), 9), MultiplyByConstant(prod(B, prod(prod(B, B), prod(B, B))), 16));
    printBigInteger(out, C);


    
}
