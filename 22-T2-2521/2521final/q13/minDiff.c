
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

typedef struct QueueRep *queue;

typedef struct node {
   int data;
   struct node *next;
} NodeT;

typedef struct QueueRep {
   int   length;
   NodeT *head;
   NodeT *tail;
} QueueRep;

// set up empty queue
queue newQueue() {
   queue Q = malloc(sizeof(QueueRep));
   Q->length = 0;
   Q->head = NULL;
   Q->tail = NULL;
   return Q;
}

// check whether queue is empty
int QueueIsEmpty(queue Q) {
   return (Q->length == 0);
}

// insert an int at end of queue
void QueueEnqueue(queue Q, int v) {
   NodeT *new = malloc(sizeof(NodeT));
   assert(new != NULL);
   new->data = v;
   new->next = NULL;
   if (Q->tail != NULL) {
      Q->tail->next = new;
      Q->tail = new;
   } else {
      Q->head = new;
      Q->tail = new;
   }
   Q->length++;
}

// remove int from front of queue
int QueueDequeue(queue Q) {
   assert(Q->length > 0);
   NodeT *p = Q->head;
   Q->head = Q->head->next;
   if (Q->head == NULL) {
      Q->tail = NULL;
   }
   Q->length--;
   int d = p->data;
   free(p);
   return d;
}



int minDiff(BSTree t, int l) {
  if (l == 0) {
    return 0;
  }
  if (t->left == NULL || t->right == NULL) {
    return 0;
  }
  int *min = malloc(sizeof(int));
  *min = 0;
  queue Q = newQueue();
  QueueEnqueue(Q, t->key);
  while (!QueueIsEmpty(Q))
  {
    int v = QueueDequeue(Q);
    if (t->left != NULL) {
      QueueEnqueue(Q, t->left->key);
    if (t->right != NULL) {
      QueueEnqueue(Q, t->right->key);
    }
    }
  }
  


    return -1;
}

