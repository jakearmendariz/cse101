/***
    Graph.c
    Jake Armendariz
    pa4
    jsarmend
    Graphs
    1650932
 ***/
#include "Graph.h"
//#include "List.h"

typedef struct GraphObj
{
    List *adj; //I am trying to turn this into an array of undefinite size inside of Matrix.c newMatrix function
    int order;
    int size;
    int *color;
    int *parent;
    int *dist;    
    int source;
} GraphObj;


Graph newGraph(int n){
    if(n < 0){
        fprintf(stderr, "Error, couldn't create graph of negative verticies in newGraph\n");
    }
    Graph G = malloc(sizeof(GraphObj));
    G->order = n;
    G->adj = calloc(n+1, sizeof(List));
    G->size = 0;
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->dist = calloc(n+1, sizeof(int));
    G->source = NIL;
    for(int i =0; i < n+1; i++){
        G->adj[i] = newList();
        G->parent[i] = NIL;
        G->dist[i] = INF;
       
    }
    return G;
}
void freeGraph(Graph* pG){
    Graph G = *pG;
    for(int i =0; i <= G->order; i++){
        freeList(&(G->adj[i]));
    }
    free(G->color);
    free(G->parent);
    free(G->dist);
    free(G);
    *pG = NULL;
}
/*** Access functions ***/
//Number of verticies
int getOrder(Graph G){
    return G->order;
}
//Number of edges
int getSize(Graph G){
    return G->size;
}
//Source of last breadth first search, if never done before it returns a -1
int getSource(Graph G){
    return G->source;
}
//
int getParent(Graph G, int u){
    if(G->source == NIL){
        return NIL;
    }
    return G->parent[u];
}
int getDist(Graph G, int u){
     if(G->source < 0){
        return INF;
    }
    return G->dist[u];
}
void getPath(List L, Graph G, int u){
    //clear(L);
    if(G->source == NIL){
        printf("Cannot find shortest path until Breadth first search is preformed\n");
        return;
    }
    if(G->source == u){
        append(L, u);
        return;
    }
    
    if(G->parent[u] == NIL){
        append(L, -1);
        return;
    }
    
    int node = u;
    int counter = 0;
    List K = newList();
    while(node != G->source){
        prepend(K, node);
        node = G->parent[node];
        counter++;
        if(counter > (G->size*2)){
            //INF
            clear(K);
            return;
        }
    }
    prepend(K, node);

    while(length(K) > 0){
        moveFront(K);
        append(L, get(K));
        deleteFront(K);
    }
    freeList(&K);
}
/*** Manipulation procedures ***/
//Deletes the previous graph, returns an empty null graph of equal size
void makeNull(Graph G){
    int n = G->order;
    freeGraph(&G);
    G = newGraph(n);
}

/**
* Before doing BFS we need to clear the helper arrays
*/
void clearhelpers(Graph G){
    free(G->color);
    free(G->parent);
    free(G->dist);
    int n = G->order;
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->dist = calloc(n+1, sizeof(int));
    for(int i = 0; i <= G->order; i++){
        G->parent[i] = NIL;
        G->dist[i] = INF;
        G->color[i] = 0;
    }
}
void addEdge(Graph G, int u, int v){
    insertInOrder(G->adj[u], v);
    insertInOrder(G->adj[v], u);
    G->size ++;
}
void addArc(Graph G, int u, int v){
    append(G->adj[u], v);
    G->size++;
}

void printDistance(Graph G){
    for(int i = 1; i < G->order+1; i++){
        printf("%d: %d\n", i, G->dist[i]);
    }
}
//BFS from source s
void BFS(Graph G, int s)
{
    if(s > G->order || s < 0){
        fprintf(stderr, "Error in BFS, source is not the graph range\n");
        return;
    }
    clearhelpers(G);
    int distance = 0;
    G->source = s;
    G->dist[s] = distance;
    G->parent[s] = NIL;
    List que = newList();
    moveFront(G->adj[s]);
    distance = 1;
    append(que, s);
    while(length(que) > 0){
        moveFront(que);
        int vert = get(que);
        moveFront(G->adj[vert]);
        while(indexIt(G->adj[vert]) != -1){
            int indx = get(G->adj[vert]);
            if(G->color[indx] == 0){//If color is white
                G->color[indx] = 1;//Set color to gray
                G->dist[indx] = G->dist[vert]+1;
                G->parent[indx] = vert;
                append(que, indx);
            }
            moveNext(G->adj[vert]);
        }
        deleteFront(que);
        distance++;//Increase distance as checking other rows
        G->color[vert] = 2;//Sets color to black, all neighboring nodes were reached...
    }
    
}
/*** Other operations ***/
void printGraph(FILE* out, Graph G){
    for(int i = 1; i <= G->order; i++){
        fprintf(out, "%d: ",i );
        moveFront(G->adj[i]);
        while(indexIt(G->adj[i]) !=  -1){
            fprintf(out, "%d", get(G->adj[i]));
            moveNext(G->adj[i]);
            if(indexIt(G->adj[i]) !=  -1){
                fprintf(out, " ");
            }
        }
        fprintf(out, "\n");
    }
}
