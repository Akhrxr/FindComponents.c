/***************************************************************************************
* Akhror Rakhmatov, arakhmat@ucsc.edu, PA2
*  Graph.h
*  Private section for Graph ADT
****************************************************************************************/
#ifndef Graph_H_INCLUDE_
#define Graph_H_INCLUDE_
#include<stdbool.h>
#include"List.h"

#define FORMAT "%d" 
#define INF -2
#define NIL -1
#define UNDEF -3

typedef struct GraphObj* Graph;



/*** Constructors-Destructors ***/
//newGraph()
//Creates a new graph with number of vertices n.
Graph newGraph(int n);

//freeGraph()
//clears Graph G and frees all memory of it.
void freeGraph(Graph* pG);


/*** Access functions ***/
//getOrder()
//Returns the number of vertices in the graph G.
int getOrder(Graph G);

//getSize()
//Returns the number of edges in the graph G.
int getSize(Graph G);

//getSource()
//Returns the source called in BFS. If BFS not called yet, returns nil.
int getSource(Graph G);

//getParent()
//Returns the parent vertex of u in BFS tree or NIL is BFS() has not been called yet.
int getParent(Graph G, int u);

//getDiscover()
//Returns the time of discovery for int u in DFS()
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */

//getFinish()
//Returns the time of finish for int u in DFS()
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */

//getDist()
//Returns the distance from source to u in Graph G or INF if BFS() has not been called yet.
int getDist(Graph G, int u);

//getPath()
//Appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no path exists.
void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/

//makeNull()
//Deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G);

//addEdge()
//Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u. 
void addEdge(Graph G, int u, int v);

//addArc()
//Inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v)
void addArc(Graph G, int u, int v);

//BFS()
//Runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly. 
void BFS(Graph G, int s);

//DFS()
//Will perform the depth first search algorithm on Graph G.
//Arg S defines the order in which vertices are to be processed in the main loop (5-7) of DFS.
//When DFS is complete, S will store the vertices by decreasing finish times (hence 𝑆 is considered to be a stack).
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */

/*** Other operations ***/

//transpose()
//Returns a new graph with the transpose of Graph G.
Graph transpose(Graph G);

//copyGraph()
//Returns a new graph with the same elements as Graph G.
Graph copyGraph(Graph G);

//printGraph()
//Prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G);

#endif