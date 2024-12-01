#ifndef FILES_GRAPH_H
#define FILES_GRAPH_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "page.h"

typedef struct Graph {
    Page pages[P];
    double W_in[P][P];
    double W_out[P][P];
    int n;
} Graph;

Graph *initial_Graph();
void deleteGraph();

#endif
