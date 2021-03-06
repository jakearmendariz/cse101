/*** 
    Constructors-Destructors
    Jake Armendariz
    pa4
    jsarmend
    Graphs
    1650932
 ***/

#ifndef Graph_h
#define Graph_h

#include "List.h"

#define NIL -1
#define INF -2

typedef struct GraphObj *Graph;
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
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);
void printDistance(Graph G);
void weightedEdge(Graph G, int u, int v, int weight);
void weightedArc(Graph G, int u, int v, int weight);
void relax(Graph G, int u, int v);
void Dijkstra(Graph G, int s);
void clearhelpers(Graph G);

#endif // if graph was including