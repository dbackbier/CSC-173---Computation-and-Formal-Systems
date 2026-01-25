#include <stdlib.h>
#include <stdio.h>
#include "Employee.h"

typedef struct Node* Node;

struct Node {
    void* data;
    struct Node* next;
};

Node new_Node(void* data) {
    Node node = (Node) malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

typedef struct LinkedList* LinkedList;

struct LinkedList {
    Node head;
};

LinkedList new_LinkedList() {
    LinkedList list = (LinkedList) malloc(sizeof(struct LinkedList));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    return list;
}

void prepend(LinkedList list, void* data) {
    Node node = new_Node(data);
    if (node != NULL) {
        node->next = list->head;
        list->head = node;
    }
}

void* getFirst(LinkedList list) {
    if (list->head == NULL) {
        return NULL;
    }
    return list->head->data;
}