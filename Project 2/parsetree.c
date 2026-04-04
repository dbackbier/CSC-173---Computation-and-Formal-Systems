#include "parsetree.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

TREE makeNode0(char x) {
    TREE root = (TREE) malloc(sizeof(struct NODE));
    root->label = x;
    root->leftmostChild = NULL;
    root->rightSibling = NULL;
    return root;
}

TREE makeNode1(char x, TREE t) {
    TREE root = makeNode0(x);
    root->leftmostChild = t;
    return root;
}

TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4) {
    TREE root = makeNode1(x, t1);
    t1->rightSibling = t2;
    t2->rightSibling = t3;
    t3->rightSibling = t4;
    return root;
}

void addChildtoLeaf1(TREE root, char target, TREE child) {
    if (root == NULL) {
        return;
    }

    QUEUE queue = {NULL, NULL};
    enqueue(&queue, root);
    TREE targetNode = NULL;

    while (!isQEmpty(&queue)) {
        TREE curr = dequeue(&queue);

        if (curr->label == target && curr->leftmostChild == NULL) {
            targetNode = curr;
        }

        TREE childPtr = curr->leftmostChild;
        while (childPtr != NULL) {
            enqueue(&queue, childPtr);
            childPtr = childPtr->rightSibling;
        }
    }

    if (targetNode != NULL) {
        targetNode->leftmostChild = child;
    }
}

void addChildtoLeaf2(TREE root, char target, TREE child1, TREE child2) {
    if (root == NULL) {
        return;
    }

    QUEUE queue = {NULL, NULL};
    enqueue(&queue, root);
    TREE targetNode = NULL;

    while (!isQEmpty(&queue)) {
        TREE curr = dequeue(&queue);

        if (curr->label == target && curr->leftmostChild == NULL) {
            targetNode = curr;
        }

        TREE childPtr = curr->leftmostChild;
        while (childPtr != NULL) {
            enqueue(&queue, childPtr);
            childPtr = childPtr->rightSibling;
        }
    }

    if (targetNode != NULL) {
        targetNode->leftmostChild = child1;
        child1->rightSibling = child2;
    }
}

void addChildtoLeaf3(TREE root, char target, TREE child1, TREE child2, TREE child3) {
    if (root == NULL) {
        return;
    }

    QUEUE queue = {NULL, NULL};
    enqueue(&queue, root);
    TREE targetNode = NULL;

    while (!isQEmpty(&queue)) {
        TREE curr = dequeue(&queue);

        if (curr->label == target && curr->leftmostChild == NULL) {
            targetNode = curr;
        }

        TREE childPtr = curr->leftmostChild;
        while (childPtr != NULL) {
            enqueue(&queue, childPtr);
            childPtr = childPtr->rightSibling;
        }
    }

    if (targetNode != NULL) {
        targetNode->leftmostChild = child1;
        child1->rightSibling = child2;
        child2->rightSibling = child3;
    }
}

void printTree(TREE tree, int level) {
    if (tree == NULL) {
        return;
    }

    for (int i = 0; i < level; i++) {
        printf("    ");
    }

    printf("%c\n", tree->label);

    printTree(tree->leftmostChild, level + 1);
    printTree(tree->rightSibling, level);
}