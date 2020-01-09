/***
    Graph.c
    Jake Armendariz
    pa4
    jsarmend
    Graphs
    1650932
 ***/
#include "Graph.h"
#include <stdlib.h>
//#include "List.h"

typedef struct GraphObj
{
    List *adj; //I am trying to turn this into an array of undefinite size inside of Matrix.c newMatrix function
    int order;
    int size;
    int *color;
    int *parent;
    int *d;  
    int *finish;  
    int source;
} GraphObj;

/**
* Creates a new graph with n verticies
*/
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
    G->d = calloc(n+1, sizeof(int));
    G->finish = calloc(n+1, sizeof(int));
    G->source = NIL;
    for(int i =0; i < n+1; i++){
        G->adj[i] = newList();
        G->parent[i] = NIL;
        G->d[i] = INF;
        G->finish[i] = UNDEF;
    }
    return G;
}
/**
* Free graph frees the graph
*/
void freeGraph(Graph* pG){
    if(pG != NULL && (*pG) != NULL){
        Graph G = *pG;
        for(int i =0; i <= G->order; i++){
            freeList(&(G->adj[i]));
        }
        free(G->color);
        free(G->parent);
        free(G->d);
        free(G->finish);
        free(G);
        *pG = NULL;
    }
}
/*** Access functions ***/
//Number of verticies
int getOrder(Graph G){
    if(G == NULL){
        fprintf(stderr, "Error in getOrder function, null graph\n");
        return 0;
    }
    return G->order;
}
//Number of edges
int getSize(Graph G){
     if(G == NULL){
        fprintf(stderr, "Error in getSize function, null graph\n");
        return 0;
    }
    return G->size;
}
//Source of last breadth first search, if never done before it returns a -1
int getSource(Graph G){
     if(G == NULL){
        fprintf(stderr, "Error in getSource function, null graph\n");
        return NIL;
    }
    return G->source;
}
//
int getParent(Graph G, int u){
     if(G == NULL){
        fprintf(stderr, "Error in getParent function, null graph\n");
        return NIL;
    }
    return G->parent[u];
}
int getDiscover(Graph G, int u){
     if(G == NULL){
        fprintf(stderr, "Error in getOrder function, null graph\n");
        return INF;
    }
    return G->d[u];
} 

int getFinish(Graph G, int u){
     if(G == NULL){
        fprintf(stderr, "Error in getFinish function, null graph\n");
        return NIL;
    }
    return G->finish[u];
}

/*** Manipulation procedures ***/
//Deletes the previous graph, returns an empty null graph of equal size
void makeNull(Graph G){
    int n = G->order;
    freeGraph(&G);
    G = newGraph(n);
}

/**
* Clear Helpers
* Before doing BFS we need to clear the helper arrays
*/
void clearhelpers(Graph G){
    free(G->color);
    free(G->parent);
    free(G->d);
    free(G->finish);
    int n = G->order;
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->finish = calloc(n+1, sizeof(int));
    G->d = calloc(n+1, sizeof(int));
    for(int i = 0; i <= G->order; i++){
        G->parent[i] = NIL;
        G->d[i] = UNDEF;
        G->color[i] = 0;
        G->finish[i] = UNDEF;
    }
}

/**
* addEdge
* Inserts a two way edge in Graph G from u -> v
*/
void addEdge(Graph G, int u, int v){
    if(G == NULL){
        fprintf(stderr, "Error, in addEdge, null graph\n");
        return;
    }
    insertInOrder(G->adj[u], v);
    insertInOrder(G->adj[v], u);
    G->size++;
}

/**
* AddArc
* Inserts a directed edge from u -> v
*/
void addArc(Graph G, int u, int v){
    if(G == NULL){
        fprintf(stderr, "Error, in addArc, null graph\n");
        return;
    }
    insertInOrder(G->adj[u], v);
    G->size++;
}

void appendArc(Graph G, int u, int v){
    append(G->adj[u], v);
    G->size++;
}

/**
* initList
* initiates the list with the decreasing finish times of G
*/
void initList(Graph G, List s){
    clear(s);
    int arr[G->order];
    for(int i = 1; i <= G->order; i++){
        arr[i-1] = G->finish[i];//List the finishing times
        append(s, i);//Lists the verticies
    }

   /**
   Bubble sort on the array
   */
     for(int i = 0; i < G->order-1; i++){
         moveFront(s);
        for(int j = 0; j < G->order-1; j++){
            if(arr[j] < arr[j+1]){//If the list is not in decreasing order
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;

                //A and B are the two verticies, we switch them
                int a = get(s);
                moveNext(s);
                int b = get(s);
                set(s, a);
                movePrev(s);
                set(s, b);
            }
            moveNext(s);
        }
     }
   
}

/**
* Depth First Search
* 
* Depth first search in order of List s
* Initializes List s with the verticies in order of decreasing finish times
*/
void DFS(Graph G, List s)
{
    if(G == NULL || s == NULL){
        fprintf(stderr, "Error, in addEdge, null graph\n");
        return;
    }
    if(length(s) != G->order){
        fprintf(stderr, "Error, in DFS, list must be the same size has G's order\n");
        return;
    }
    clearhelpers(G);
    int time = 0;
    //For each node in the graph
    moveFront(s);
    while(get(s) != -1){
        if(G->color[get(s)] == 0){
            time = Visit(G, get(s), time);
        }
        moveNext(s);
    }
    initList(G, s);
}

/**
* Visit
* A helper function
* Explores nodes in DFS
*/
int Visit(Graph G, int x, int time){
    time++;
    G->d[x] = time;
    G->color[x] = 1;
    moveFront(G->adj[x]);
    while(indexIt(G->adj[x]) != -1){
        
        if(G->color[get(G->adj[x])] == 0){
            G->parent[get(G->adj[x])] = x;
            time = Visit(G, get(G->adj[x]), time);
        }
        moveNext(G->adj[x]);
    }
    G->color[x] = 2;
    time++;
    G->finish[x] = time;
    return time;
}

void vertexList(Graph G, List L){
    clear(L);
    for(int i = 1; i <= G->order; i++){
        append(L, i);
    }
}

Graph transpose(Graph G){
    if(G == NULL){
        fprintf(stderr, "Error, in addEdge, null graph\n");
        return NULL;
    }
    Graph H = newGraph(G->order);
    for(int i = 1; i <= G->order; i++){
        List L = G->adj[i];
        moveFront(L);
        while(get(L) != -1){
            addArc(H, get(L), i);
            moveNext(L);
        }
    }
    return H;
}

/**
Copies the graph using the adjacency list
*/
Graph copyGraph(Graph G){
    if(G == NULL){
        fprintf(stderr, "Error, in copyGraph, null graph\n");
        return NULL;
    }
    Graph copy = newGraph(G->order);
    for(int i = 1; i <= G->order; i++){
        moveFront(G->adj[i]);
        while(get(G->adj[i]) != -1){
            addArc(copy, i, get(G->adj[i]));
        }
    }
    return copy;
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
//A helper function of mine to print everything in DFS
void print_DFS(Graph G){
    printf("Vert\tdisc\tfin\tparent\n");
      for(int i = 1; i <= G->order; i++){
          printf("%d:\t%d\t%d\t%d\n", i, G->d[i], G->finish[i], G->parent[i]);
      }
}

/**
Finds and prints the conneted components of G
*/
void findandPrintComponents(FILE* out, Graph G){
    
    List L = newList();
    vertexList(G, L);
    DFS(G, L);
    Graph H = transpose(G);
    DFS(H, L);

    int counter = 0;
    moveFront(L);
    while(get(L) != -1){
        if(H->parent[get(L)] == -1){
            counter++;
            ///printf("\n");
        }
        //printf("%d ", get(L));
        moveNext(L);
    }
    fprintf(out, "G contains %d strongly connected components:\n", counter);
    Graph J = newGraph(counter);
    moveFront(L);
    int size = counter;
    counter++;
    while(get(L) != -1){
        if(H->parent[get(L)] == -1){
            counter--;
        }
        appendArc(J, counter, get(L));
        //fprintf(out, "fuck society\n");
        moveNext(L);
    }
    //printGraph(stdout, J);

    for(int i = 1; i <= size; i++){
        fprintf(out, "Component %d: ",i );
        moveFront(J->adj[i]);
        //printf("length of adj: %d\n", length(J->adj[i]));
        while(indexIt(J->adj[i]) !=  -1){
            fprintf(out, "%d", get(J->adj[i]));
            moveNext(J->adj[i]);
            if(indexIt(J->adj[i]) !=  -1){
                fprintf(out, " ");
            }
        }
        fprintf(out, "\n");
    }
    freeList(&L);
    freeGraph(&J);
}




