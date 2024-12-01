
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"



// #include <stdbool.h>

// typedef struct adjNode *AdjList;
// struct adjNode {
//     int v;
//     AdjList next;
// };

// typedef struct graph *Graph;
// struct graph {
//     AdjList *edges;  // array of lists
//     int      nV;     // #vertices
//     int      nE;     // #edges
// };

// // vertices are ints
// typedef int Vertex;

// // Create a new graph
// Graph GraphNew(int nV);

// // Frees all memory associated with the given graph
// void GraphFree(Graph g);

// // Number of vertices in the given graph
// int GraphNumVertices(Graph g);

// // Inserts a directed edge from 'v' to 'w'
// void GraphInsertEdge(Graph g, Vertex v, Vertex w);

// // Prints the given graph to stdout
// void GraphShow(Graph g);
// indegree
int inDegree(Graph g, Vertex v)  {
    int count = 0;
    for (int i = 0; i < g->nV; i++) {
        AdjList curr = g->edges[i];
        while (curr != NULL) {
            if (curr->v == v) {
                count++;
            }
            curr = curr->next;
        }
    }
    return count;
}

// outdegree
int outDegree(Graph g, Vertex v) {
    int count = 0;
    for (int i = 0; i < g->nV; i++) {
    if (i != v) continue;
        AdjList curr = g->edges[i];
        while (curr != NULL) {
                count++;
            curr = curr->next;
        }
    }
    return count;
}


int GraphNumVertices(Graph g) {
    return g->nV;
}
int mmax(int a, int b) {
    if (a > b) return a;
    return b;
}
int maxDegreeDiff(Graph g) {
    // TODO : In the example below, the maximum absolute degree difference occurs at vertex 0: the indegree of vertex 0 is 1, the outdegree of vertex 0 is 3, is 2, and this is the maximum difference in the graph.
    int max_diff = -222;
    int indegree = 0;
    int outdegree = 0;
    // find the max difference in the graph
    for (int i = 0; i < GraphNumVertices(g); i++) {
        indegree = inDegree(g, i);
        outdegree = outDegree(g, i);
        // printf("indegree: %d, outdegree: %d, vertice: %d\n", indegree, outdegree, i);
        if (indegree > outdegree) {
            max_diff = mmax(indegree - outdegree, max_diff);
        } else {
            max_diff = mmax(outdegree - indegree, max_diff);
        }
        // printf("max_diff: %d\n", max_diff);
    }
    return max_diff;
}

