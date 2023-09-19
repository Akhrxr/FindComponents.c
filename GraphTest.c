//-----------------------------------------------------------------------------
// GraphClient.c
// Test client for the Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"
#include"Graph.c"
#include"List.c"

int main(int argc, char* argv[]){
   int i, n=8;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   Graph A = newGraph(100);
   List L = newList();

   char j = '8';
   int u = atoi(&j);


   if (getSize(A) != 0)
      return 1;
    addEdge(A, 54, 1);
    addEdge(A, 54, 2);
    addEdge(A, 54, 3);
    addEdge(A, 1, 55);
    if (getSize(A) != 4)
      return 2;
    for (int i = 1; i <= 100; i++) {
      append(L, i);
    }
    DFS(A, L);
    if (getSize(A) != 4)
      return 3;
    addEdge(A, 1, 56);
    if (getSize(A) != 5)
      return 4;



   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 2,3);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,4);
   addArc(G, 3,7);
   addArc(G, 4,8);
   addArc(G, 4,3);
   addArc(G, 5,1);
   addArc(G, 5,6);
   addArc(G, 6,7);
   addArc(G, 7,6);
   addArc(G, 7,8);
   addArc(G, 8,8);
   printGraph(stdout, G);

   DFS(G, S);
   printList(stdout, S);
   Graph N = transpose(G);
   printGraph(stdout, N);
   DFS(N, S);
   printList(stdout, S);
   if (length(S) != 0 && getSize(N) != 0) {
    moveFront(S);
    while (index(S) != -1) {
      int i = get(S);
      int g = getParent(N, i);
      if (getParent(N, i) == NIL) {
        fprintf(stdout, "%d: %d", i, i);
        moveNext(S);
        int u = get(S);
        while (getParent(N, u) != NIL) {
          if (getParent(N, u) != NIL) {
            fprintf(stdout, " %d", u);
          }
          if (getParent(N, u) == NIL) {
            break;
          }
          moveNext(S);
          if (index(S) != -1) {
            u = get(S);
          }
          else {
            break;
          }
        }
        fprintf(stdout, "\n");
      }
      else {
        moveNext(S);
      }
    }
   }
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   return(0);
}
