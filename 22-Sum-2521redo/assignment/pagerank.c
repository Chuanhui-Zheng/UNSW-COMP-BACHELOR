#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Res.h"

static double NextPagePr(Graph *g, double d, int index);
static void NextPRs(Graph *g, double d, double *new_pr);
static double NextDiff(Graph *g, double *new_pr);
static void update(Graph *g, double *new_pr);
static void calculateRank(Graph *g, double d, double diffPR, int maxIterations);
    

int main(int argc, char *argv[]) {
    // argc is the number of command-line arguments, which includes the
    // program name
    // argv is the array of command-line arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s dampingFactor diffPR maxIterations\n",
                argv[0]);
        return EXIT_FAILURE;
    }
    double d = atof(argv[1]);
    double diffPR = atof(argv[2]);
    int maxIterations = atoi(argv[3]);
    Graph *g = initial_Graph();
    calculateRank(g, d, diffPR, maxIterations);
    printRank(g);
    
    deleteGraph(g);

}

static double NextPagePr(Graph *g, double d, int index) {
    Page *p = g->pages + index;
    double r = 0.0;
    for (int i = 0; i < p->inNum; i++) {
        int from = p->inLink[i];
        //int to = index;
        r += (g->pages[from].rank) / g->pages[from].outNum;
    }
    r *= d;
    r += (1 - d) / g->n;
    return r;
}

static void NextPRs(Graph *g, double d, double *new_pr) {
    for (int i = 0; i < g->n; i++) {
        new_pr[i] = NextPagePr(g, d, i);
    }
}

static double NextDiff(Graph *g, double *new_pr) {
    double r = 0;
    for (int i = 0; i < g->n; i++) {
        r += fabs(g->pages[i].rank - new_pr[i]);
    }
    return r;
}

static void update(Graph *g, double *new_pr) {
    for (int i = 0; i < g->n; i++) {
        g->pages[i].rank = new_pr[i];
    }
}

static void calculateRank(Graph *g, double n, double diffPR, int maxIterations) {
    int i;
    double diff;
    double *new_pr = (double*)malloc(sizeof(double) * g->n);
    for (i = 0, diff = diffPR; i < maxIterations && diff >= diffPR; i++) {
        NextPRs(g, n, new_pr);
        diff = NextDiff(g, new_pr);
        update(g, new_pr);
    }
    free(new_pr);
}