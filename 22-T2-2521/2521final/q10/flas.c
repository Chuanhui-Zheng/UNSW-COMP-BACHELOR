
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List flas(List l) {
    // TODO : The function takes a list and returns a pointer to the node at the start of the longest ascending sublist in the list. An ascending sublist in a list
    // set a result variable
    if (l == NULL) {
        return NULL;
    }
    List result = ListNew();
    List i = l;
    result = l;
    int max_length = 1;
    while (i != NULL) {
        int length = 1;
        List last = i;
        List j = i->next;
        while (j != NULL && j->value > last->value) {
            length++;
            last = j;
            j = j->next;
        }
        if (length > max_length) {
            max_length = length;
            result = i;
        }
        i = j;
    }
    if (max_length == 1) {
        return NULL;
    }
    return result;
}

