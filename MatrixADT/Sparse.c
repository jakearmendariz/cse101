/*
* Jake Armendariz
* cse101
* Lex.c
* This file will take an input and output file
*/

/**
 * 
 * List of bugs:
 * My input isn't taking in some entries. in1 on my computer in4 on the website expects 40 inputs, I only get 37
 * My output is not printing decimal places
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "Matrix.h"

int main(int argc, char *argv[])
{
    //printf("Sparce.C\n");
    FILE *in, *out;

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
    int n, a, b;
    fscanf(in, "%d %d %d", &n, &a, &b);

   // printf("Inputs:%d %d %d\n", n, a, b);
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    int k, l;
    double x;

    for (int i = 0; i < a; i++)
    {
        fscanf(in, "%d %d %lf\n", &k, &l, &x);
        changeEntry(A, k, l, x);
      //  printf("%d %d %.1f\n", k, l, x);
    }
    for (int i = 0; i < b; i++)
    {

        fscanf(in, "%d %d %lf\n", &k, &l, &x);
        changeEntry(B, k, l, x);
        //printEntry(B, k + 1, l + 1);
        //printf("%d %d %.1f\n", k, l, x);
    }

    fprintf(out, "A has %d non-zero entries: \n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");

    fprintf(out, "B has %d non zero-entries: \n", NNZ(B));
    printMatrix(out, B);
    fprintf(out, "\n");

    Matrix C = scalarMult(1.5, A);
    fprintf(out, "(1.5)*A = \n");
    printMatrix(out, C);
    fprintf(out, "\n");

    Matrix D = sum(A, B);
    fprintf(out, "A+B = \n");
    printMatrix(out, D);
    fprintf(out, "\n");

    Matrix Z = sum(A, A);
    fprintf(out, "A+A = \n");
    printMatrix(out, Z);
    fprintf(out, "\n");

    Matrix E = diff(B, A);
    fprintf(out, "B-A =\n");
    printMatrix(out, E);
    fprintf(out, "\n");

    Matrix Y = diff(A, A);
    fprintf(out, "A-A =\n");
    printMatrix(out, Y);
    fprintf(out, "\n");

    Matrix F = transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, F);
    fprintf(out, "\n");

    Matrix G = product(A, B);
    fprintf(out, "A*B =\n");
    printMatrix(out, G);
    fprintf(out, "\n");

    Matrix H = product(B, B);
    fprintf(out, "B*B =\n");
    printMatrix(out, H);
    fprintf(out, "\n");

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);

    fclose(in);
    fclose(out);

    return (0);
}
