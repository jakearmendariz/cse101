#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <setjmp.h>

#include "Graph.h"
#include "List.h"

#define FIRST_TEST DG_getSize
#define MAXSCORE 40


enum Test_e {
  DG_getSize = 0, // directed graph tests
  DG_getSource,
  DG_getParent,
  DG_getDist,
  DG_getPath,

  UG_getSize, // undirected graph tests
  UG_getSource,
  UG_getParent,
  UG_getDist,
  UG_getPath,

  NUM_TESTS,
};


char *testName(int test) {

  if (test == DG_getSize) return "DG_getSize";
  if (test == DG_getSource) return "DG_getSource";
  if (test == DG_getParent) return "DG_getParent";
  if (test == DG_getDist) return "DG_getDist";
  if (test == DG_getPath) return "DG_getPath";

  if (test == UG_getSize) return "UG_getSize";
  if (test == UG_getSource) return "UG_getSource";
  if (test == UG_getParent) return "UG_getParent";
  if (test == UG_getDist) return "UG_getDist";
  if (test == UG_getPath) return "UG_getPath";

  return "";
}

// return 0 if pass otherwise the number of the test that was failed
int runTest(Graph *pA, List *pL, List *pC, int test) {
  Graph A = *pA;
  List L = *pL;
  List C = *pC;
  switch(test) {

    case DG_getSize:
      {
        if (getSize(A) != 0) return 1;
        addArc(A, 54, 1);
        addArc(A, 54, 2);
        addArc(A, 54, 3);
        addArc(A, 1, 54);
        addArc(A, 1, 55);
        if (getSize(A) != 5) return 2;
        BFS(A, 67);
        if (getSize(A) != 5) return 3;
        addArc(A, 55, 1);
        if (getSize(A) != 6) return 4;
        return 0;
      }
    case DG_getSource:
      {
        if (getSource(A) != NIL) return 1;
        BFS(A, 42);
        if (getSource(A) != 42) return 2;
        BFS(A, 88);
        if (getSource(A) != 88) return 3;
        return 0;
      }
    case DG_getParent:
      {
        for (uint8_t i = 1; i <= 100; i++)
          if (getParent(A, i) != NIL) return 1;
        addArc(A, 64, 4);
        addArc(A, 64, 3);
        addArc(A, 42, 2);
        addArc(A, 2, 64);
        addArc(A, 4, 2);
        addArc(A, 3, 42);
        BFS(A, 42);
        if (getParent(A, 42) != NIL) return 2;
        if (getParent(A, 2) != 42) return 3;
        if (getParent(A, 8) != NIL) return 4;
        return 0;
      }
    case DG_getDist:
      {
        for (uint8_t i = 1; i <= 100; i++)
          if (getDist(A, i) != INF) return 1;
        addArc(A, 64, 4);
        addArc(A, 64, 3);
        addArc(A, 42, 2);
        addArc(A, 2, 64);
        addArc(A, 4, 2);
        addArc(A, 3, 42);
        BFS(A, 64);
        if (getDist(A, 64) != 0) return 2;
        if (getDist(A, 2) != 2) return 3;
        BFS(A, 4);
        if (getDist(A, 42) != 4) return 4;
        if (getDist(A, 43) != INF) return 5;
        BFS(A, 99);
        if (getDist(A, 64) != INF) return 6;
        return 0;
      }
    case DG_getPath:
      {
        addArc(A, 64, 4);
        addArc(A, 64, 3);
        addArc(A, 42, 2);
        addArc(A, 2, 64);
        addArc(A, 4, 2);
        addArc(A, 3, 42);
        BFS(A, 3);
        getPath(L, A, 64);
        append(C, 3);
        append(C, 42);
        append(C, 2);
        append(C, 64);

        printf("\nL\n");
        printList(stdout, L);

        printf("\nC\n");
        printList(stdout, C);
        printf("\n");

        
        if (!equals(L, C)) return 1;
        moveFront(L);
        BFS(A, 2);
        getPath(L, A, 2);
        append(C, 2);
        printf("\nL:\n");
        printList(stdout, L);

        printf("\nC:\n");
        printList(stdout, C);
        printf("\n");

        if (!equals(L, C)) return 2;
        /**
        What should happen here? It is adding a path to something that can't be found
        */
        getPath(L, A, 99);
        printf("\nL\n");
        printList(stdout, L);

        printf("\nC\n");
        printList(stdout, C);
        printf("\n");

        if (equals(L, C)){
            printf("L should not equal C here\n");
            //return 3;
        }
        clear(L);
        clear(C);
        append(C, NIL);
        BFS(A, 99);
        getPath(L, A, 2);

        printf("\nL\n");
        printList(stdout, L);

        printf("\nC\n");
        printList(stdout, C);
        printf("\n");

        if (!equals(C, L)) return 4;

        return 0;
      }
    case UG_getSize:
      {
        if (getSize(A) != 0) return 1;
        addEdge(A, 54, 1);
        addEdge(A, 54, 2);
        addEdge(A, 54, 3);
        addEdge(A, 1, 55);
        if (getSize(A) != 4) return 2;
        BFS(A, 67);
        if (getSize(A) != 4) return 3;
        addEdge(A, 55, 2);
        if (getSize(A) != 5) return 4;
        return 0;
      }
    case UG_getSource:
      {
        if (getSource(A) != NIL) return 1;
        BFS(A, 42);
        if (getSource(A) != 42) return 2;
        BFS(A, 88);
        if (getSource(A) != 88) return 3;
        return 0;
      }
    case UG_getParent:
      {
        for (uint8_t i = 1; i <= 100; i++)
          if (getParent(A, i) != NIL) return 1;
        addEdge(A, 64, 4);
        addEdge(A, 64, 3);
        addEdge(A, 42, 2);
        addEdge(A, 2, 64);
        addEdge(A, 4, 2);
        addEdge(A, 3, 42);
        BFS(A, 42);
        if (getParent(A, 42) != NIL) return 2;
        if (getParent(A, 64) != 2) return 3;
        if (getParent(A, 3) != 42) return 4;
        if (getParent(A, 8) != NIL) return 5;
        return 0;
      }
    case UG_getDist:
      {
        for (uint8_t i = 1; i <= 100; i++)
          if (getDist(A, i) != INF) return 1;
        addEdge(A, 64, 4);
        addEdge(A, 64, 3);
        addEdge(A, 42, 2);
        addEdge(A, 2, 64);
        addEdge(A, 4, 2);
        addEdge(A, 3, 42);
        BFS(A, 64);
        if (getDist(A, 64) != 0) return 2;
        if (getDist(A, 2) != 1) return 3;
        BFS(A, 4);
        if (getDist(A, 42) != 2) return 4;
        if (getDist(A, 43) != INF) return 5;
        BFS(A, 99);
        if (getDist(A, 64) != INF) return 6;
        return 0;
      }
    case UG_getPath:
      {
        addEdge(A, 64, 4);
        addEdge(A, 64, 3);
        addEdge(A, 42, 2);
        addEdge(A, 2, 64);
        addEdge(A, 4, 2);
        addEdge(A, 3, 42);
        BFS(A, 3);
        getPath(L, A, 64);
        append(C, 3);
        append(C, 64);
        printf("\nL\n");
        printList(stdout, L);

        printf("\nC\n");
        printList(stdout, C);
        printf("\n");

        if (!equals(L, C)) return 1;
        moveFront(L);
        BFS(A, 2);
        getPath(L, A, 2);
        append(C, 2);
        printf("\nL\n");
        printList(stdout, L);

        printf("\nC\n");
        printList(stdout, C);
        printf("\n");

        if (!equals(L, C)) return 2;
        getPath(L, A, 99);
        printf("\nL\n");
        printList(stdout, L);

        printf("\nC\n");
        printList(stdout, C);
        printf("\n");

        if (equals(L, C)) return 3;
        clear(L);
        clear(C);
        append(C, NIL);
        BFS(A, 99);
        getPath(L, A, 2);
        if (!equals(C, L)) return 4;
        return 0;
      }
  }
  return 254;
}


int main () {
  
  int testStatus = 0;
  int testsPassed = 0;

  printf("\n"); // more spacing
  for (int i = 0; i < 10; i++) {
    Graph A = newGraph(100);
    List L = newList();
    List C = newList();
    testStatus = runTest(&A, &L, &C, i);
    freeGraph(&A);
    freeList(&L);
    freeList(&C);
    
    if (testStatus == 0) {
      testsPassed++;
    }else{
        printf("Failed test %d\n", i);
    }
  }
  return 0;
}