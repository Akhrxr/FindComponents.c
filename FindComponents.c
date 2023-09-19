/***************************************************************************************
* Akhror Rakhmatov, arakhmat@ucsc.edu, PA2
*  FindPath.c
*  Uses functions in Graph.c to find 
****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char **argv) {
    FILE *in, *out;
    if (argc != 3) {
        fprintf( stderr, "Incorrect number of command line arguments, please include a file in and file out only\n" );
        exit(1);
    }
    in = fopen(argv[1], "r");
    if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
    }
    out = fopen(argv[2], "w");
    if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
    }
    
    int vertic;
    fscanf(in, "%d", &vertic);
    Graph G = newGraph(vertic);
    List A = newList();
    int v1, v2;
    while (1) {
        fscanf(in, "%d %d", &v1, &v2);
        if (!v1 && !v2) {
            break;
        }
        addArc(G, v1, v2);
    }
    fprintf(out, "Adjacency list representation of G: \n");
    printGraph(out, G);
    fprintf(out, "\n");
    ListVertices(G, A);
    Graph R = transpose(G);
    DFS(G, A);
    DFS(R, A);
    int count = 0;
    if (length(A) != 0 && getSize(R) != 0) {
        for(moveFront(A); index(A) != -1; moveNext(A)) {
          int verty = get(A);
          if (getParent(R, verty) == NIL) {
            ++count;
          }
        }
    }
    fprintf(out, "G contains %d strongly connected components: \n", count);
    if (length(A) != 0 && getSize(R) != 0) {
        moveFront(A);
    }
    int compo = 1;
    while (index(A) != -1) {
      int i = get(A);
      if (getParent(R, i) == NIL) {
        fprintf(out, "Component %d: %d", compo, i);
        moveNext(A);
        if (index(A) != -1) {
          int u = get(A);
          while (getParent(R, u) != NIL) {
            if (getParent(R, u) != NIL) {
              fprintf(out, " %d", u);
            }
            if (getParent(R, u) == NIL) {
              break;
            }
            moveNext(A);
            if (index(A) != -1) {
              u = get(A);
            }
            else {
              break;
            }
          }
          fprintf(out, "\n");
          ++compo;
        }
      }
      else {
        moveNext(A);
      }
    }
    freeGraph(&G);
    freeGraph(&R);
    freeList(&A);
    fclose(out); 
    fclose(in);
    return 0;
}