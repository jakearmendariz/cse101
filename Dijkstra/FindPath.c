#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
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
    int three = 1;
    while(one != 0 || two != 0)
    {
        fscanf(in, " %d", &one);
        fscanf(in, " %d", &two);
        fscanf(in, " %d", &three);
        weightedArc(G, one, two, three);
        //printf("one: %d  two: %d weight: %d\n", one, two, three);
    }
    printGraph(out, G);
    one = 1;
    two = 1;
    fscanf(in, " %d", &one);
    fscanf(in, " %d", &two);
    while(one != 0 || two != 0)
    {
        
        //BFS(G, one);
        Dijkstra(G, one);
        getPath(L,G, two);
        if(length(L) == 0 || getDist(G, two) < 0){
            fprintf(out, "\nThe distance from %d to %d is infinity\n",one, two);
            fprintf(out, "No %d-%d path exists\n",one, two);
        }else{
            fprintf(out, "\nThe distance from %d to %d is %d\n",one, two, getDist(G, two));
            fprintf(out, "A shortest %d-%d path is: ",one, two);
            printList(out, L);
            fprintf(out, "\n");
        }
        clear(L);
        fscanf(in, " %d", &one);
        fscanf(in, " %d", &two);
    }
    freeGraph(&G);
   
    return 0;
}