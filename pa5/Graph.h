/*** 
    Constructors-Destructors
    Jake Armendariz
    pa5
    jsarmend
    Graphs
    1650932
 ***/

#ifndef Graph_h
#define Graph_h

#include "List.h"

#define NIL -1
#define INF -2
#define UNDEF -2

typedef struct GraphObj *Graph;
Graph transpose(Graph G);
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);
void printDistance(Graph G);

/* pa5: The new functions*/
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */
int Visit(Graph G, int x, int time);

Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);
void print_DFS(Graph G);
void vertexList(Graph G, List L);
void findandPrintComponents(FILE* out, Graph G);
#endif // if graph was including