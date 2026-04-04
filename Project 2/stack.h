
#ifndef PROJECT_2_STACK_H
#define PROJECT_2_STACK_H

#include <stdbool.h>

typedef struct STACK *STACK;

extern STACK newSTACK();
extern void freeSTACK(STACK this);
extern void clear(STACK this);
extern bool isEmpty(STACK this);
extern bool isFull(STACK this);
extern void resize(STACK this);
extern void push(STACK this, char element);
extern char pop(STACK this);
extern char top(STACK this);

#endif //PROJECT_2_STACK_H