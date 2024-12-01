
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"



// typedef struct graph *Graph;

// // graph representation (adjacency matrix)
// struct graph {
//     int nV;            // #vertices
//     int numStdEdges;   // #STD_ROAD edges
//     int numFastEdges;  // #FAST_ROAD edges
//     bool **stdEdges;   // matrix of STD_ROAD edges
//     bool **fastEdges;  // matrix of FAST_ROAD edges
// };

// typedef enum {
// 	NO_ROAD = ' ',
// 	STD_ROAD = 's',
// 	FAST_ROAD = 'f',
// } Road;

// // vertices denoted by integers 0..N-1
// typedef int Vertex;

// // edges are pairs of vertices (end-points)
// typedef struct edge {
//     Vertex v;
//     Vertex w;
// } Edge;

// // operations on graphs
// Graph GraphNew(int nV);
// void GraphAddEdge(Graph g, Edge e, Road t);
// void GraphRemoveEdge(Graph g, Edge e, Road t);
// void GraphFree(Graph g);
// void GraphShow(Graph g);



int dayTrip(Graph g, Vertex s, Vertex vs[]) {
    // TODO : The function takes a graph representation of the road network and a starting vertex, and stores all the vertices which are reachable from the starting vertex by driving for up to one day in the given vs[] array. The function then returns the number of reachable vertices.
    // from s to find all vertice in g reachable from s in one day
    int i, j, count = 0;
    bool *visited = calloc(g->nV, sizeof(bool));
    for (i = 0; i < g->nV; i++) {
        visited[i] = false;
    }
    visited[s] = true;
    // SDT one day, highway 0.5 day
    // find all reachable vertices from s in 1 day
    // get all adjacent vertices of s by stdEdges
    // find 0.5 day
    for (i = 0; i < g->nV; i++) {
        for (j = 0; j < g->nV; j++) {
            if (g->fastEdges[i][j] == true ) {
                 if (i == s && visited[j] == false ) {
                            visited[j] = true;
                    count++;
                    vs[count] = j;
                }
                if (j == s && visited[i] == false ) {
                            visited[i] = true;
                    count++;
                    vs[count] = i;
                }
            

            }
        }
    }
    // find 1 day
    for (i = 0; i < g->nV; i++) {
        for (j = 0; j < g->nV; j++) {
            if (g->stdEdges[i][j] == true ) {
                 if (i == s && visited[j] == false ) {
                            visited[j] = true;
                    count++;
                    vs[count] = j;
                }
                if (j == s && visited[i] == false ) {
                            visited[i] = true;
                    count++;
                    vs[count] = i;
                }
            

            }
        }
    }
    // find two 0.5 day
    
    
    return count;
}

