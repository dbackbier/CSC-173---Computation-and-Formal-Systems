#include "queue.h"
#include "parsetree.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

bool isQEmpty(QUEUE *q) {
    return q->head == NULL;
}

void enqueue(QUEUE *q, TREE val) {
    qNode *p = (qNode *) malloc(sizeof(qNode));
    p->val = val;
    p->next = NULL;
    if (q->tail) {
        q->tail->next = p;
    } else {
        q->head = p;
    }
    q->tail = p;
}

TREE dequeue(QUEUE *q) {
    if (isQEmpty(q)) {
        return NULL;
    }
    qNode *temp = q->head;
    TREE val = temp->val;
    q->head = q->head->next;
    if (!q->head) {
        q->tail = NULL;
    }
    free(temp);
    return val;
}