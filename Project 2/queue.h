#ifndef PROJECT_2_QUEUE_H
#define PROJECT_2_QUEUE_H

#include "parsetree.h"
#include <stdbool.h>

typedef struct qNode {
    TREE val;
    struct qNode *next;
} qNode;

typedef struct {
    qNode *head;
    qNode *tail;
} QUEUE;

extern bool isQEmpty(QUEUE *q);
extern void enqueue(QUEUE *q, TREE val);
extern TREE dequeue(QUEUE *q);

#endif //PROJECT_2_QUEUE_H