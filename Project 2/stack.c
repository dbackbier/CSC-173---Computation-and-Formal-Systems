#include "stack.h"
#include <stdbool.h>
#include <stdlib.h>

struct STACK{
    int top;
    int cap;
    char* elements;
};

STACK newSTACK(void) {
    STACK this = (STACK) malloc(sizeof(struct STACK));
    this->top = -1;
    this->cap = 8; // initial cap
    this->elements = (char*)malloc(sizeof(char) * this->cap);
    return this;
}

void freeSTACK(STACK this) {
    free(this->elements);
    free(this);
}

void clear(STACK this) {
    this->top = -1;
}

bool isEmpty(STACK this) {
    return this->top < 0;
}

bool isFull(STACK this) {
    return this->top >= this->cap - 1;
}

void resize(STACK this) {
    this->cap *= 2;
    this->elements = realloc(this->elements, this->cap * sizeof(char));
}

void push(STACK this, char element) {
    if (isFull(this)) {
        resize(this);
    }
    this->elements[++this->top] = element;
}

char pop(STACK this) {
    if (isEmpty(this)) {
        return '\0';
    }
    return this->elements[this->top--];
}

char top(STACK this) {
    if (isEmpty(this)) {
        return '\0';
    }
    return this->elements[this->top];
}