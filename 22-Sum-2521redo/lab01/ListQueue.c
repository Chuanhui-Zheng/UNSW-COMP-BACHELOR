// Implementation of the Queue ADT using a linked list

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

typedef struct node *Node;
struct node {
    Item item;
    Node next;
};

struct queue {
    Node head;
    Node tail;
    int  size;
};

/**
 * Creates a new empty queue
 */
Queue QueueNew(void) {
    Queue q = malloc(sizeof(*q));
    if (q == NULL) {
        fprintf(stderr, "couldn't allocate Queue\n");
        exit(EXIT_FAILURE);
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/**
 * Frees all resources associated with the given queue
 */
void QueueFree(Queue q) {
    Node curr = q->head;
    while (curr != NULL) {
        Node temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(q);
}

/**
 * Adds an item to the end of the queue
 */
void QueueEnqueue(Queue q, Item it) {
    // new node with it
    Node new = malloc(sizeof(*new));
    new->item = it;
    new->next = NULL;
    
    // when the list is empty
    if (q->head == NULL) {
        q->head = new;
        q->tail = new;
    // add to the end when the list in not empty
    } else {
        q->tail->next = new;
        q->tail = new;
    }
    // size increase by 1
    q->size++;
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q) {
    // it is the item of head
    Item it = q->head->item;
    // head is first node of q
    Node head = q->head;
    // change the head to the next node
    q->head = q->head->next;
    free(head);
    // if there is only on node in the list
    // change the tail to NULL
    if(q->head == NULL) {
        q->tail = NULL;
    }
    // size decrease by 1
    q->size--;
    return it;
}

/**
 * Gets the item at the front of the queue without removing it
 * Assumes that the queue is not empty
 */
Item QueueFront(Queue q) {
    assert(q->size > 0);

    return q->head->item;
}

/**
 * Gets the size of the given queue
 */
int QueueSize(Queue q) {
    return q->size;
}

/**
 * Returns true if the queue is empty, and false otherwise
 */
bool QueueIsEmpty(Queue q) {
    return q->size == 0;
}

/**
 * Prints the items in the queue to the given file with items space-separated
 */
void QueueDump(Queue q, FILE *fp) {
    for (Node curr = q->head; curr != NULL; curr = curr->next) {
        fprintf(fp, "%d ", curr->item);
    }
    fprintf(fp, "\n");
}

/**
 * Prints out information for debugging
 */
void QueueDebugPrint(Queue q) {

}
