#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "array.h"


struct Array {
    ArrayItem *arr;
    int index;
    int capacity;
};


Array *array_init(void) {
    Array *a = (Array *) malloc(sizeof(Array));
    a->capacity = 100;
    a->index = 0;
    a->arr = (ArrayItem *) malloc(sizeof(ArrayItem) * 100);

    return a;
}

void array_free(Array *a) {
    for (int i = 0; i < a->index; i++) {
        free(a->arr[i].key);
    }
    free(a->arr);
    free(a);
}

// find the index of given key. if not exist, return -1.
int find_index(Array *a, char *key) {
    for (int i = 0; i < a->index; i++) {
        if (!strcmp(a->arr[i].key, key)) {
            return i;
        }
    }
    return -1;


}

void *array_search(Array *a, char *key) {
    int i = find_index(a, key);
    return i == -1 ? NULL : a->arr[i].item;
}


int array_add(Array *a, char *key, void *item) {
    if (find_index(a, key) != -1) {
        return 0;
    }

    if (a->index == a->capacity) {
        a->capacity *= 2;
        a->arr = realloc(a->arr, sizeof(ArrayItem) * a->capacity);
    }

    a->arr[a->index].item = item;
    char *newKey = (char *) malloc(strlen(key) + 1);
    strcpy(newKey, key);
    a->arr[a->index].key = newKey;
    a->index++;
    return 1;
}


ArrayItem *array_iterate(Array *a, ArrayItem *prev) {
    if (!a) {
        return NULL;
    }
     else if (!prev) {
        return a->index == 0 ? NULL : &(a->arr[0]);
    }
    int i = find_index(a, prev->key);
    return i == a->index - 1 ? NULL : &(a->arr[i + 1]);
}
