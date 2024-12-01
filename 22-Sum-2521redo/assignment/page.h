#ifndef FILES_PAGE_H
#define FILES_PAGE_H

static const int P = 1000;

typedef struct Page {

    char *url;
    char *text[P];
    int endLine;
    double rank;
    int inLink[P];
    int inNum;
    int outLink[P];
    int outNum;

} Page;

void deletePage(Page *p);

#endif