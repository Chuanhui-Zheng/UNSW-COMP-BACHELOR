#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_URL_NAME 20
#define MAX_LINE_LENGTH 128


int get_number(Graph* graph, char* url) {
    for (int i = 0; i < graph->n; i++) {
        Page* page = graph->pages + i;
        if (strcmp(page->url, url) == 0) {
            return i;
        }
    }
    return -1;
}
static void initial_all_pages(Graph* graph);
static void initPage(Graph* graph, int i);
static void get_outLink(FILE* fp, Graph* graph, int current);
static void get_text(FILE* fp, Graph* graph, int i);
static void initial_W(Graph* g);
static double update_W_in(Graph* g, int from, int to);
static double update_W_out(Graph* g, int from, int to);


// Initial the graph of simple search
Graph* initial_Graph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    // open the file
    FILE *f = fopen("collection.txt", "rw");
    if (f == NULL) {
        fprintf(stderr, "Can't open.\n");
        exit(EXIT_FAILURE);
    }

    graph->n = 0;
    char name[MAX_URL_NAME];
    while (fscanf(f, "%s", name) == 1) {
        Page* page = graph->pages + graph->n;
        page->url = (char*)malloc(strlen(name) + 1);
        strcpy(page->url, name);
        graph->n++;
    }
    fclose(f);
    // iniial the pages;
    initial_all_pages(graph);
    // initial_W
    initial_W(graph);
    return graph;
}
// Free the graph
void deleteGraph(Graph* graph) {
    for (int i = 0; i < graph->n; i++) {
        deletePage(graph->pages + i);
    }
    free(graph);
}

static void initial_all_pages(Graph* graph) {
    for (int i = 0; i < graph->n; i++) {
        initPage(graph , i);
    }
}

static void initPage(Graph* graph, int i) {
    Page* page = graph->pages + i;
    page->rank = 1.0 / graph->n;

    char fileName[MAX_URL_NAME] = "";
    sprintf(fileName, "%s.txt", page->url);
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't open %s\n", fileName);
        exit(EXIT_FAILURE);
    }

    get_outLink(fp, graph, i);
    get_text(fp, graph, i);
    
	fclose(fp);
}

static void get_outLink(FILE* fp, Graph* graph, int current) {
    char line[MAX_LINE_LENGTH + 1];
    char url[MAX_URL_NAME];
    fscanf(fp,"%s", line);
    fgets(line, MAX_LINE_LENGTH + 1, fp);

    Page* page = graph->pages + current;
    page->endLine = 0;

    while (fscanf(fp, "%s", url) == 1) {
        if (strcmp(url, "#end") == 0) {
            fgets(line, MAX_LINE_LENGTH + 1, fp);
            break;
        }
        if (strcmp(page->url, url) == 0) {
            continue;
        }
        int to = get_number(graph, url);

        Page* toPage = graph->pages + to;

        toPage->inLink[toPage->inNum] = current;
        toPage->inNum++;
        page->outLink[page->outNum] = to;
        page->outNum++;
    }
    
}

static void get_text(FILE* fp, Graph* graph, int i) {
    char line[MAX_LINE_LENGTH + 1];
    fscanf(fp,"%s", line);
    fgets(line, MAX_LINE_LENGTH + 1, fp);

    Page* page = graph->pages + i;
	while (fgets(line, MAX_LINE_LENGTH + 1, fp) != NULL) {
        if (!strcmp(line, "#end Section-2\n")) {
            break;
        }

        if (strlen(line) == 1 && line[0] == '\n') {
            continue;
        }

		page->text[page->endLine] = (char*)malloc(strlen(line) + 1);
        strcpy(page->text[page->endLine], line);

        page->endLine++;
	}
}
// initial_W using the function 
// update_W_in and update_W_out
static void initial_W(Graph* g) {
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->pages[i].outNum; j++) {
            int from = i;
            int to = g->pages[i].outLink[j];
            g->W_in[from][to] = update_W_in(g, from, to);
            g->W_out[from][to] = update_W_out(g, from, to);
        }
    }
}
// upadate the W in
static double update_W_in(Graph* g, int from, int to) {
    Page* fromPage = g->pages + from;
    Page* toPage = g->pages + to;

    double O = toPage->inNum ? toPage->inNum : 0.5;
    int sum = 0;
    for (int i = 0; i < fromPage->outNum; i++) {
        int in = fromPage->outLink[i];
        sum += g->pages[in].inNum ? g->pages[in].inNum : 0.5;
    }
    return (double)O / sum;
}
// update the W out
static double update_W_out(Graph* g, int from, int to) {
    Page* fromPage = g->pages + from;
    Page* toPage = g->pages + to;

    double O = toPage->outNum ? toPage->outNum : 0.5;
    double sum = 0;
    for (int i = 0; i < fromPage->outNum; i++) {
        int in = fromPage->outLink[i];
        sum += g->pages[in].outNum ? g->pages[in].outNum : 0.5;
    }
    return (double)O / sum;
}
