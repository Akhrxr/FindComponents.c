/****************************************************************************************
* Akhror Rakhmatov, arakhmat@ucsc.edu, PA2
*  Graph.c
*  Public section for graph ADT
*****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include"Graph.h"

typedef struct ListObj* List;

// s is source
//v is vertex
//u is edge
// structs --------------------------------------------------------------------

typedef struct GraphObj{
    int size;
    int order;
    int source;
    List* adj;
    int* color;
    int* dist;
    int* parent;
    int* discover;
    int* finish;

} GraphObj;

void Visit(Graph G, int x, List S);
void ListVertices(Graph G, List A);

Graph newGraph(int n){
    if (n < 0) {
        printf("Graph Error: Cannot make an empty graph of size n.\n");
        exit(EXIT_FAILURE);
    }
    Graph G;
    G = malloc(sizeof(GraphObj));
    G->parent = malloc(sizeof(int) *(n+1));
    G->dist = malloc(sizeof(int) *(n+1));
    G->color = malloc(sizeof(int) *(n+1));
    G->adj = malloc(sizeof(List) *(n+1));
    G->discover = malloc(sizeof(int) *(n+1));
    G->finish = malloc(sizeof(int) *(n+1));
    assert(G != NULL);
    G->order = n;
    G->size  = 0;
    G->source = NIL;
    for (int i = 1; i <= n; ++i) {
        G->adj[i] = newList();
        G->color[i] = 0;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF; // 0 is white, 1 is grey, 2 is black.
        G->parent[i] = NIL;
        G->dist[i] = INF;
    }
    return G;
}

void freeGraph(Graph* pG){
    int n, i;
    if(pG!=NULL && *pG!=NULL) {
        n = getOrder(*pG);
        for (i = 1; i <= n; ++i) {
            freeList(&(*pG)->adj[i]);
        }
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->dist);
        free((*pG)->finish);
        free((*pG)->discover);
        free(*pG);
        *pG = NULL;
   }
}

int getOrder(Graph G) {
    if( G==NULL ){
        fprintf(stderr, "Graph Error: getOrder called on NULL Graph\n");
        exit(1);
    }
    return G->order;
}
int getSize(Graph G) {
    if( G==NULL ){
        fprintf(stderr, "Graph Error: getSize called on NULL Graph\n");
        exit(1);
    }
    return G->size;
}
int getSource(Graph G) {
    if( G==NULL ){
        fprintf(stderr, "Graph Error: getSource called on NULL Graph\n");
        exit(1);
    }
    return G->source;
}

int getParent(Graph G, int u) {
    if( G==NULL ){
        fprintf(stderr, "Graph Error: getOrder called on NULL Graph\n");
        exit(1);
    }
    if (u > getOrder(G)) {
        fprintf(stderr, "Number of edges is larger than number of vertices\n");
        exit(1);
    }
    if (u < 1) {
        fprintf(stderr, "Number of edges is larger than number of vertices\n");
        exit(1);
    }
    return G->parent[u];
}

int getDiscover(Graph G, int u) {
    if( G==NULL ){
        fprintf(stderr, "Graph Error: getDiscover called on NULL Graph\n");
        exit(1);
    }
    if (u > getOrder(G)) {
        fprintf(stderr, "Number of edges is larger than number of vertices\n");
        exit(1);
    }
    if (u < 1) {
        fprintf(stderr, "Number of edges is negative\n");
        exit(1);
    }
    return G->discover[u];
}

int getFinish(Graph G, int u) {
    if( G==NULL ){
        fprintf(stderr, "Graph Error: getFinish called on NULL Graph\n");
        exit(1);
    }
    if (u > getOrder(G)) {
        fprintf(stderr, "Number of edges is larger than number of vertices\n");
        exit(1);
    }
    if (u < 1) {
        fprintf(stderr, "Number of edges is negative\n");
        exit(1);
    }
    return G->finish[u];
}

int getDist(Graph G, int u) {
    if( G==NULL ){
        fprintf(stderr, "Graph Error: getDist called on NULL Graph\n");
        exit(1);
    }
    if (u > getOrder(G)) {
        fprintf(stderr, "Number of edges is larger than number of vertices\n");
        exit(1);
    }
    if (u < 1) {
        fprintf(stderr, "Number of edges is negative\n");
        exit(1);
    }
    if (G->source < 1 ) {
        return INF;
    }
    return G->dist[u];
}

void getPath(List L, Graph G, int u) {
    if( G==NULL ){
        fprintf(stderr, "Graph Error: getPath called on NULL Graph\n");
        exit(1);
    }
    if( L == NULL ){
        fprintf(stderr, "List Error: getPath called on NULL List\n");
        exit(1);
    }
    if (u > getOrder(G)) {
        fprintf(stderr, "Number of edge is larger than number of vertices\n");
        exit(1);
    }
    if (u < 1) {
        fprintf(stderr, "Number of edge is negative\n");
        exit(1);
    }
    if (u == G->source) {
        append(L, u);
    }
    else if (getParent(G, u) == NIL) {
        append(L, NIL);
    }
    else {
        getPath(L, G, getParent(G, u));
        append(L, u);
    }
}

/*** Manipulation procedures ***/


void makeNull(Graph G) {
    if( G==NULL ){
        fprintf(stderr, "Graph Error: makeNull called on NULL Graph\n");
        exit(1);
    }
    G->size = 0;
    G->source = NIL;
    int n = getOrder(G);
    for (int i = 1; i <= n; ++i) {
        G->parent[i] = NIL;
        G->dist[i] = INF;
        G->color[i] = 0;
        clear(G->adj[i]);
    }

}

void addEdge(Graph G, int u, int v) {
    if( G==NULL ){
        fprintf(stderr, "Graph Error: addEdge called on NULL Graph\n");
        exit(1);
    }
    if (u > getOrder(G)) {
        fprintf(stderr, "Number of edge is larger than number of vertices\n");
        exit(1);
    }
    if (u < 1) {
        fprintf(stderr, "Number of edge is negative\n");
        exit(1);
    }
    if (v > getOrder(G)) {
        fprintf(stderr, "Number of vertex is larger than number of vertices\n");
        exit(1);
    }
    if (v < 1) {
        fprintf(stderr, "Number of vertex is less than 1\n");
        exit(1);
    }
    List A = (G->adj[u]);
    List B = (G->adj[v]);
    if (length(B) == 0) {
        append(B, u);
    }
    else {
        int notran = 1;
        for (moveFront(B); index(B) != -1; moveNext(B)) {
            int i = get(B);
            if (i == v) {
                notran = 0;
            }
        }
        if (notran) {
            moveFront(B);
            while (get(B) < u) {
                moveNext(B);
                if (index(B) == -1) {
                    break;
                }
            }
            if (index(B) == -1) {
                append(B, u);
            }
            else {
                insertBefore(B, u);
            }
        }
    }
    if (length(A) == 0) {
        append(A, v);
    }
    else {
        int notran = 1;
        for (moveFront(B); index(B) != -1; moveNext(B)) {
            int i = get(B);
            if (i == v) {
                notran = 0;
            }
        }
        if (notran) {
            moveFront(A);
            while (get(A) < v) {
                moveNext(A);
                if (index(A) == -1) {
                    break;
                }
            }
            if (index(A) == -1) {
                append(A, v);
            }
            else {
                insertBefore(A, v);
            }
        }
    }
    ++G->size;
}

void addArc(Graph G, int u, int v) {
    if( G==NULL ){
        fprintf(stderr, "Graph Error: addArc called on NULL Graph\n");
        exit(1);
    }
    if (u > getOrder(G)) {
        fprintf(stderr, "Number of edge is larger than number of vertices\n");
        exit(1);
    }
    if (u < 1) {
        fprintf(stderr, "Number of edge is negative\n");
        exit(1);
    }
    if (v > getOrder(G)) {
        fprintf(stderr, "Number of vertex is larger than number of vertices\n");
        exit(1);
    }
    if (v < 1) {
        fprintf(stderr, "Number of vertex is less than 1\n");
        exit(1);
    }
    List B = G->adj[u];
    if (length(B) == 0) {
        append(B, v);
        ++G->size;
    }
    else {
        int notran = 1;
        for (moveFront(B); index(B) != -1; moveNext(B)) {
            int i = get(B);
            if (i == v) {
                notran = 0;
            }
        }
        if (notran) {
            moveFront(B);
            while (get(B) < v) {
                moveNext(B);
                if (index(B) == -1) {
                    break;
                }
            }
            if (index(B) == -1) {
                append(B, v);
            }
            else {
                insertBefore(B, v);
            }
            ++G->size;
        }
    }
}

void BFS(Graph G, int s) {
    if( G==NULL ){
        fprintf(stderr, "Graph Error: BFS() called on NULL Graph\n");
        exit(1);
    }
    if (s < 0) {
        fprintf(stderr, "Invalid source\n");
        exit(1);
    }
    if (s > getOrder(G)) {
        fprintf(stderr, "Invalid source\n");
        exit(1);
    }
    int n = getOrder(G);
    for (int i = 1; i <= n; ++i) {
        G->parent[i] = NIL;
        G->dist[i] = INF;
        G->color[i] = 0;
    }
    G->source = s;
    G->color[s] = 1;
    G->dist[s] = 0;
    G->parent[s] = NIL;
    List L = newList();
    append(L, s);
    while (length(L)!= 0) {
        moveFront(L);
        int x = get(L);
        deleteFront(L);
        if (length(G->adj[x]) != 0) {
            moveFront(G->adj[x]);
        }
        if (index(G->adj[x]) >  -1) {
            for (int counter = 0; counter <= length(G->adj[x]); counter++) {
                if (index(G->adj[x]) >  -1) {
                    int y = get(G->adj[x]);
                    if (G->color[y] == 0) {
                        G->color[y] = 1;
                        G->dist[y] = G->dist[x] + 1;
                        G->parent[y] = x;
                        append(L, y);
                    }
                    moveNext(G->adj[x]);
                }
            }
            G->color[x] = 1;
        }
    }
    freeList(&L);
}

int time = 0;

void DFS(Graph G, List S) {
    if( G==NULL ){
        fprintf(stderr, "Graph Error: DFS() called on NULL Graph\n");
        exit(1);
    }
    if ( S==NULL ){
        fprintf(stderr, "List Error: DFS() called on NULL List\n");
        exit(1);
    }
    if (length(S) != getOrder(G)) {
        fprintf(stderr, "List/Graph Error: DFS() called on Graph/List with mismatching length/vertices\n");
        exit(1);
    }
    for (int i = 1; i <= getOrder(G); ++i ) {
        G->color[i] = 0;
        G->parent[i] = NIL;
    }
    List B = copyList(S);
    clear(S);
    for (moveFront(B); index(B) != -1; moveNext(B) ) {
        int i = get(B);
        if (G->color[i] == 0) {
            Visit(G, i, S);
        }
    }
    time = 0;
    freeList(&B);
}

//Visit void Visit(Graph G, int x, List S, int* time)
void Visit(Graph G, int x, List S) {
    G->discover[x] = ++time; // same as line 422
    G->color[x] = 1;
    if (length(G->adj[x]) > 0) {
        for (moveFront(G->adj[x]); index(G->adj[x]) != -1; moveNext(G->adj[x])) {
            int y = get(G->adj[x]);
            if (G->color[y] == 0) {
                G->parent[y] = x;
                Visit(G, y, S);
            }
        }
    }
    G->color[x] = 2;
    G->finish[x] = ++time; //++(*time) if pointer
    prepend(S, x);
}

/*** Other operations ***/

Graph transpose(Graph G) {
    int n = getOrder(G);
    Graph Q = newGraph(n);
    if (n != 0) {
        for (int i = 1; i <= n; ++i) {
            List A = G->adj[i];
            if (length(A) != 0) {
                moveFront(A);
                while (index(A) != -1) {
                    addArc(Q, get(A), i);
                    moveNext(A);
                }
            }
        }
    }
   return(Q);
}

Graph copyGraph(Graph G) {
    int n = getOrder(G);
    Graph Q = newGraph(n);
    if (n != 0) {
        for (int i = 1; i <= n; ++i) {
            List A = G->adj[i];
            if (length(A) != 0) {
                moveFront(A);
                while (index(A) != -1) {
                    addArc(Q, i, get(A));
                    moveNext(A);
                }
            }
        }
    }
   return(Q);
}

void ListVertices(Graph G, List S) {
    if (!G) {
        fprintf(stderr, "Error calling ListVertices on an null graph.\n");
        exit(EXIT_FAILURE);
    }
    if (!S) {
        fprintf(stderr, "Error calling ListVertices on an null list.\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 1; i <= G->order; i++){
        append(S, i);
    }
}

void printGraph(FILE* out, Graph G) {
    if (!G) {
        fprintf(stderr, "Error calling printGraph on an empty graph.\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 1; i <= G->order; i++){
        List A = G->adj[i];
        if (length(A) != 0) {
            moveFront(A);
        }
        fprintf(out, "%d: ", i);
        while(index(A) >  -1) {
            fprintf(out, "%d ", get(A));
            moveNext(A);
        }
        fprintf(out, "\n");
    }
}
