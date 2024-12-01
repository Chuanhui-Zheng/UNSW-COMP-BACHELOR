#ifndef ARRAY_H
#define ARRAY_H

typedef struct Array Array;

// data structure stored
// in Array
typedef struct {
    void *item;
    char *key;
} ArrayItem;

Array *array_init(void);

void array_free(Array *a);

void *array_search(Array *a, char *key);

int array_add(Array *a, char *key, void *item);


ArrayItem *array_iterate(Array *a, ArrayItem *prev);

#endif