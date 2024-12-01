////////////////////////////////////////////////////////////////////////////////
// COMP1521 22T1 --- Assignment 2: `Allocator', a simple sub-allocator        //
// <https://www.cse.unsw.edu.au/~cs1521/22T1/assignments/ass2/index.html>     //
//                                                                            //
// Written by YOUR-NAME-HERE (z5555555) on INSERT-DATE-HERE.                  //
//                                                                            //
// 2021-04-06   v1.0    Team COMP1521 <cs1521 at cse.unsw.edu.au>             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "allocator.h"

// DO NOT CHANGE CHANGE THESE #defines

/** minimum total space for heap */
#define MIN_HEAP 4096

/** minimum amount of space to split for a free chunk (excludes header) */
#define MIN_CHUNK_SPLIT 32

/** the size of a chunk header (in bytes) */
#define HEADER_SIZE (sizeof(struct header))

/** constants for chunk header's status */
#define ALLOC 0x55555555
#define FREE 0xAAAAAAAA

// ADD ANY extra #defines HERE

// DO NOT CHANGE these struct defintions

typedef unsigned char byte;

/** The header for a chunk. */
typedef struct header {
    uint32_t status; /**< the chunk's status -- shoule be either ALLOC or FREE */
    uint32_t size;   /**< number of bytes, including header */
    byte     data[]; /**< the chunk's data -- not interesting to us */
} header_type;


/** The heap's state */
typedef struct heap_information {
    byte      *heap_mem;      /**< space allocated for Heap */
    uint32_t   heap_size;     /**< number of bytes in heap_mem */
    byte     **free_list;     /**< array of pointers to free chunks */
    uint32_t   free_capacity; /**< maximum number of free chunks (maximum elements in free_list[]) */
    uint32_t   n_free;        /**< current number of free chunks */
} heap_information_type;

// Footnote:
// The type unsigned char is the safest type to use in C for a raw array of bytes
//
// The use of uint32_t above limits maximum heap size to 2 ** 32 - 1 == 4294967295 bytes
// Using the type size_t from <stdlib.h> instead of uint32_t allowing any practical heap size,
// but would make struct header larger.


// DO NOT CHANGE this global variable
// DO NOT ADD any other global  variables

/** Global variable holding the state of the heap */
static struct heap_information my_heap;

// ADD YOUR FUNCTION PROTOTYPES HERE


// Initialise my_heap
int init_heap(uint32_t size) {

    // PUT YOUR CODE HERE
    int i = 0;
    while((size + i)%4!=0){
        i++;
    }
    uint32_t newsize = size + i;
    if(newsize<MIN_HEAP){
        newsize = MIN_HEAP;
    }
    my_heap.heap_size = newsize;
    byte *newmem = malloc(newsize);
    my_heap.heap_mem = newmem; 
    my_heap.free_capacity = newsize / HEADER_SIZE;
    my_heap.free_list = malloc(newsize/HEADER_SIZE);
    my_heap.n_free = 1;
    my_heap.free_list[0] = newmem;
    struct header *new = (struct header *) newmem;
    new->status = FREE;
    new->size = newsize;

    return 0; // CHANGE ME
}


// Allocate a chunk of memory large enough to store `size' bytes
void *my_malloc(uint32_t size) {

    // PUT YOUR CODE HERE
    int i = 0;
    while((size + i)%4!=0){
        i++;
    }
    uint32_t newsize = size + i;
    struct header *want = NULL;
    i = 0;
    int k = i;
    while(i<my_heap.n_free){
        struct header *j = (struct header *)my_heap.free_list[i];
        if (j->size>=newsize+HEADER_SIZE && want == NULL){
            want = j;
            k = i;
        }
        if (j->size>=newsize+HEADER_SIZE && j->size<want->size){
            want = j;
            k = i;
        }
        i++;
    }
    if (want->size<newsize+HEADER_SIZE+MIN_CHUNK_SPLIT){
        want->status = ALLOC;
        int a = k;
        while(a<my_heap.n_free){
            my_heap.free_list[a] = my_heap.free_list[a+1];
            a++;
        }
        my_heap.n_free = my_heap.n_free -1;
        return want->data;

    }
    else{
        struct header *new = (struct header *)(want->data+newsize);
        new->status = FREE;
        new->size = want->size - newsize - HEADER_SIZE;
        want->status = ALLOC;
        want->size = newsize + HEADER_SIZE;
        my_heap.free_list[k] = (byte *)new;
        return want->data;
    }

    return NULL; // CHANGE ME
}


// Deallocate chunk of memory referred to by `ptr'
void my_free(void *ptr) {
    if (ptr == NULL){
        fprintf(stderr,"Attempt to free unallocated chunk\n");
        exit(1);
    }
    // PUT YOUR CODE HERE
    struct header  *p= (struct header*)(ptr - HEADER_SIZE);
    if (p->status == FREE){
        fprintf(stderr,"Attempt to free unallocated chunk\n");
        exit(1);
    }
    p->status = FREE;
    int i = 0;
    while(i<my_heap.n_free){
        if ((byte *)my_heap.free_list[i]>=(byte *)p){
            break;
        }
        i++;
    }    
    int a = my_heap.n_free;
    while(a>i){
        my_heap.free_list[a] = my_heap.free_list[a-1];
        a--;
    }
    my_heap.free_list[i] = (byte *)p;
    my_heap.n_free++;
    if(i+1!=my_heap.n_free){
        struct header *next = (struct header *)my_heap.free_list[i+1];
        if((byte *)next == (byte *)p + p->size){
            
            p->size = p->size + next->size;
            a = i+1;
            while(a < my_heap.n_free){
                my_heap.free_list[a]=my_heap.free_list[a+1];
                a++;
            }
            my_heap.n_free = my_heap.n_free -1;
        }
    }
    if(i != 0){
        struct header *last = (struct header *)my_heap.free_list[i-1];
        if((byte *)last +last->size == (byte *)p){
            last->size = last->size + p->size;
            int b = i;
            while(b < my_heap.n_free){
                my_heap.free_list[b]=my_heap.free_list[b+1];
                b++;
            }
            my_heap.n_free = my_heap.n_free -1;
        }
    }
    

}


// DO NOT CHANGE CHANGE THiS FUNCTION
//
// Release resources associated with the heap
void free_heap(void) {
    free(my_heap.heap_mem);
    free(my_heap.free_list);
}


// DO NOT CHANGE CHANGE THiS FUNCTION

// Given a pointer `obj'
// return its offset from the heap start, if it is within heap
// return -1, otherwise
// note: int64_t used as return type because we want to return a uint32_t bit value or -1
int64_t heap_offset(void *obj) {
    if (obj == NULL){
        return -1;
    }
    int64_t offset = (byte *)obj - my_heap.heap_mem;
    if (offset < 0 || offset >= my_heap.heap_size) {
        return -1;
    }

    return offset;
}


// DO NOT CHANGE CHANGE THiS FUNCTION
//
// Print the contents of the heap for testing/debugging purposes.
// If verbosity is 1 information is printed in a longer more readable form
// If verbosity is 2 some extra information is printed
void dump_heap(int verbosity) {

    if (my_heap.heap_size < MIN_HEAP || my_heap.heap_size % 4 != 0) {
        printf("ndump_heap exiting because my_heap.heap_size is invalid: %u\n", my_heap.heap_size);
        exit(1);
    }

    if (verbosity > 1) {
        printf("heap size = %u bytes\n", my_heap.heap_size);
        printf("maximum free chunks = %u\n", my_heap.free_capacity);
        printf("currently free chunks = %u\n", my_heap.n_free);
    }

    // We iterate over the heap, chunk by chunk; we assume that the
    // first chunk is at the first location in the heap, and move along
    // by the size the chunk claims to be.

    uint32_t offset = 0;
    int n_chunk = 0;
    while (offset < my_heap.heap_size) {
        struct header *chunk = (struct header *)(my_heap.heap_mem + offset);

        char status_char = '?';
        char *status_string = "?";
        switch (chunk->status) {
        case FREE:
            status_char = 'F';
            status_string = "free";
            break;

        case ALLOC:
            status_char = 'A';
            status_string = "allocated";
            break;
        }

        if (verbosity) {
            printf("chunk %d: status = %s, size = %u bytes, offset from heap start = %u bytes",
                    n_chunk, status_string, chunk->size, offset);
        } else {
            printf("+%05u (%c,%5u) ", offset, status_char, chunk->size);
        }

        if (status_char == '?') {
            printf("\ndump_heap exiting because found bad chunk status 0x%08x\n",
                    chunk->status);
            exit(1);
        }

        offset += chunk->size;
        n_chunk++;

        // print newline after every five items
        if (verbosity || n_chunk % 5 == 0) {
            printf("\n");
        }
    }

    // add last newline if needed
    if (!verbosity && n_chunk % 5 != 0) {
        printf("\n");
    }

    if (offset != my_heap.heap_size) {
        printf("\ndump_heap exiting because end of last chunk does not match end of heap\n");
        exit(1);
    }

}

// ADD YOUR EXTRA FUNCTIONS HERE
