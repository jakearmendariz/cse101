#include "Graph.h"

int main(){
    Graph G = newGraph(6);
    addEdge(G, 1, 2);
    addEdge(G, 2, 4);
    addEdge(G, 1, 3);
    addEdge(G, 2, 5);
    addEdge(G, 2, 6);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    addEdge(G, 5, 6);
    printGraph(stdout, G);
/*
1 4
1 5
4 5
2 3
2 6
3 7
6 7
0 0
2 7
3 6
1 7
0 0
*/
    List L = newList();

    BFS(G, 5);
    printf("\nThe distance from 1 to 5 is %d\n", getDist(G, 1));
    printf("The shortest path from 1 to 5 is: ");
    getPath(L,G, 1);
    printList(stdout, L);

    
    BFS(G, 6);
    printf("\nThe distance from 3 to 6 is %d\n", getDist(G, 3));
    printf("The shortest path from 3 to 6 is: ");
    getPath(L,G, 3);
    printList(stdout, L);
    
    freeGraph(&G);

    return 0;
}