#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char* argv[]){
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
    fscanf(in, " %d", &a);
    Graph G = newGraph(a);
    List L = newList();
    int one = 1;
    int two = 1;
    while(one != 0 || two != 0)
    {
        fscanf(in, " %d", &one);
        fscanf(in, " %d", &two);
        addArc(G, one, two);
        //printf("one: %d  two: %d\n", one, two);
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    one = 1;
    two = 1;
    fscanf(in, " %d", &one);
    fscanf(in, " %d", &two);
    while(one != 0 || two != 0)
    {
        
        fscanf(in, " %d", &one);
        if(fscanf(in, " %d", &two) == EOF){
            break;
        }
       // printf("Repeating\n");
    }
    vertexList(G, L);
    DFS(G, L); 
    fprintf(out, "\n");
    
    findandPrintComponents(out, G);
    freeGraph(&G);
    freeList(&L);



    return 0;
}