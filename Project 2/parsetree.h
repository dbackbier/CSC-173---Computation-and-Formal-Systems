
#ifndef PROJECT_2_PARSETREE_H
#define PROJECT_2_PARSETREE_H

typedef struct NODE *TREE;
struct NODE {
    char label;
    TREE leftmostChild, rightSibling;
};

extern TREE makeNode0(char x);
extern TREE makeNode1(char x, TREE t);
extern TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4);
extern void addChildtoLeaf1(TREE root, char target, TREE child);
extern void addChildtoLeaf2(TREE root, char target, TREE child1, TREE child2);
extern void addChildtoLeaf3(TREE root, char target, TREE child1, TREE child2, TREE child3);
extern void printTree(TREE t, int level);

#endif //PROJECT_2_PARSETREE_H