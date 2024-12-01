#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

#define MAX_LINE_LENGTH 128

typedef struct Res {
    char* url;
    int num;
    double pageRank;
} Res;


static void trans_urls(char* line, Array* a);
static Array* searching(Array* a, int argc, char* argv[], int* total);
static int cmpfunc(const void* a, const void* b);
static void printRes(Array* count, int n, Array* ranks);
static void free_all(Array* a);
Array* inverted_index();
void handleRank(char* line, Array* a);
Array* read_PageRank();
void free_array(Array* a);

int main(int argc, char* argv[]) {
  
    Array* a = inverted_index();
    Array* pageRank = read_PageRank();

    int total = 0;
    Array* count = searching(a, argc, argv, &total);
    printRes(count, total, pageRank);
    char filename[] = "searchPagerank.exp";
    FILE *f = fopen(filename, "r");
    char c;
    while ((c = fgetc(f)) != EOF) {
        putchar(c);
    }
    fclose(f);
    free_all(a);
    free_array(pageRank);
    return 0;

}

static void trans_urls(char* line, Array* a) {
    char* it = strtok(line, " ");
    Array* it_urls = array_init();
    char* url;
    while ((url = strtok(NULL, " "))) {
        array_add(it_urls, url, NULL);
    }
    array_add(a, it, it_urls);
}


static Array* searching(Array* a, int argc, char* argv[], int* total) {
    Array* count = array_init();

    for (int i = 0; i < argc; i++) {
        char* it = argv[i];
        Array* urls;
        if (!(urls = array_search(a, it))) continue;
        ArrayItem* p = array_iterate(urls, NULL);
        for (; p; p = array_iterate(urls, p)) {
            if (!(p->key)) continue;
            int* url_cnt;
            if (!(url_cnt = array_search(count, p->key))) {
                url_cnt = (int*)malloc(sizeof(int));
                *url_cnt = 0;
                array_add(count, p->key, url_cnt);
                (*total)++;
            }
            (*url_cnt)++;
        }
    }
    return count;
}

static int cmpfunc(const void* a, const void* b) {
    if (((Res*)a)->num != ((Res*)b)->num)
        return ((Res*)a)->num < ((Res*)b)->num;
    if ( ((Res*)a)->pageRank != ((Res*)b)->pageRank)
        return ((Res*)a)->pageRank < ((Res*)b)->pageRank;
    return strcmp(((Res*)a)->url, ((Res*)b)->url) > 0;
}

static void printRes(Array* count, int n, Array* ranks) {
    Res* res = (Res*) malloc(sizeof(Res) * n);
    int i = 0;
    ArrayItem* a = array_iterate(count, NULL);
    for (; a; a = array_iterate(count, a)) {
        if (!(a->key)) {
            continue;
        }
        res[i].num = *(int*)(a->item);
        res[i].url = a->key;

        /*double rank = *(double*)(array_search(ranks, a->key));
        res[i].pageRank = rank;*/
        free(a->item);
        i++;
    }

    qsort(res, n, sizeof(Res), cmpfunc);
    /*int outNum = n < 30 ? n : 30;
    for (int i = 0; i < outNum; i++) {
        printf("%s\n", res[i].url);
    }*/
    free(res);
    array_free(count);
}

static void free_all(Array* a) {
    ArrayItem* it = array_iterate(a, NULL);
    for (; it; it = array_iterate(a, it)) {
        if (it->key) {
            Array* it_urls = (Array*)(it->item);
            array_free(it_urls);
        }
    }
    array_free(a);
}

Array* inverted_index() {
    FILE* fp = fopen("invertedIndex.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't open invertedIndex.txt\n");
        exit(EXIT_FAILURE);
    }
  
    Array* a = array_init();

    char line[MAX_LINE_LENGTH + 1];
    while (fgets(line, MAX_LINE_LENGTH + 1, fp) != NULL) {
        line[strlen(line) - 1] = '\0';
        trans_urls(line, a);
    }
    fclose(fp);
    return a;
}

void handleRank(char* line, Array* a) {
    char* url = strtok(line, " ");
    strtok(NULL, " ");
    double* rank = (double*)malloc(sizeof(double));
    *rank =  atof(strtok(NULL, " "));
    array_add(a, url, rank);
}

Array* read_PageRank() {
    FILE* fp = fopen("pagerankList.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't open pagerankList.txt\n");
        exit(EXIT_FAILURE);
    }
    
    Array* a = array_init();

    char line[MAX_LINE_LENGTH + 1];
    while (fgets(line, MAX_LINE_LENGTH + 1, fp) != NULL) {
        line[strlen(line) - 1] = '\0';
        handleRank(line, a);
    }
    fclose(fp);
    return a;
}

void free_array(Array* a) {
    ArrayItem* it = array_iterate(a, NULL);
    for (; it; it = array_iterate(a, it)) {
        if (it->key) {
        free(it->item);
        }
    }
    array_free(a);
}