#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node* leftChild;
    struct Node* rightChild;
};

struct Node* new_Node(int val) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->val = val;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

void printNode(struct Node* node) {
    if (node == NULL) {
        return;
    }
    printf("Node[%d] ", node->val);
}

struct Node* addNode(struct Node* node, int val) {
    if (node == NULL) {
        node = new_Node(val);
    } else if (val < node->val) {
        node->leftChild = addNode(node->leftChild, val);
    } else {
        node->rightChild = addNode(node->rightChild, val);
    }
    return node;
}

void printTreeInOrder(struct Node* node) { // in-order/ infix print
    if (node != NULL) {
        printTreeInOrder(node->leftChild);
        printf("%d ", node->val);
        printTreeInOrder(node->rightChild);
    }
}

struct Tree {
    struct Node* root;
};

struct Tree* new_Tree() {
    struct Tree* tree = (struct Tree*)malloc(sizeof(struct Tree));
    if (tree == NULL) {
        return NULL;
    }
    tree->root = NULL;
    return tree;
}

void addToTree(struct Tree* tree, int val) {
    tree->root = addNode(tree->root, val);
}

void printTree(struct Tree *tree) {
    printNode(tree->root);
}

int lookUpNode(struct Tree* tree, int val) {
    struct Node* node = tree->root;
    while (node != NULL) {
        if (val < node->val) {
            node = node->leftChild;
        } else if (val > node->val) {
            node = node->rightChild;
        } else {
            return 1;
        }
    }
    return 0;
}

int lookUpTree(struct Tree* tree, int val) {
    return lookUpNode(tree, val);
}

int main(int argc, char* argv[]) {
    struct Node* node = new_Node(10);
    struct Node* node2 = new_Node(20);
    struct Node* node3 = new_Node(30);
    printNode(node);
    printNode(node2);
    printNode(node3);
    printf("\n");
    struct Tree* tree = new_Tree();
    addToTree(tree, 15);
    addToTree(tree, 35);
    addToTree(tree, 45);
    addToTree(tree, 5);
    addToTree(tree, 25);
    printTree(tree);
    printf("\n");
    printf("%d\n", lookUpTree(tree, 5));
    printf("%d\n", lookUpTree(tree, 40));
}