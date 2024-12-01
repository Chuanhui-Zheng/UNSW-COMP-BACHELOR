#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Res.h"

typedef struct Res {
    double weight;
    char *url;
    int outNum;

}Res;

static int compare(const void * a, const void * b) {
    if (fabs(((Res*)a)->weight - ((Res*)b)->weight) > 0.0000001) {
        return ((Res*)a)->weight < ((Res*)b)->weight;
    }
    return strcmp(((Res*)a)->url, ((Res*)b)->url) > 0;
}

void printRank(Graph *g) {
    struct Res res[P];
    for (int i = 0; i < g->n; i++) {
        res[i].url = g->pages[i].url;
        res[i].weight = g->pages[i].rank;
        res[i].outNum = g->pages[i].outNum;
    }
    qsort(res, g->n, sizeof(Res), compare);
    FILE *output = fopen("./pagerankList.txt", "w");
    for (int i = 0; i < g->n; i++) {
        fprintf(output, "%s, %d, %.7lf\n", res[i].url, res[i].outNum, res[i].weight);
    }
    fclose(output);
}