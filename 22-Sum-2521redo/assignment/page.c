#include <stdio.h>
#include <stdlib.h>
#include "page.h"

void deletePage(Page *p) {
    for (int i = 0; i <  p->endLine; i++) {
        free(p->text[i]);
    }
    free(p->url);
}