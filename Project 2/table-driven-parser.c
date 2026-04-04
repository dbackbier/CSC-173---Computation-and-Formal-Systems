#include "table-driven-parser.h"
#include <stdbool.h>
#include <stdlib.h>
#include "parsetree.h"
#include "recursive-descent-parser.h"
#include "stack.h"

/* Indexes of syntactic categories:
 * <A> : 0
 * <B> : 1
 * <C> : 2
 * <D> : 3
 * <E> : 4
 * -------------------------------------
 * Table table[row][col] rows are productions, columns are terminals
 *         0 1 2 3 4
 *         b c e ( )
 *  0 <A>  1 1
 *  1 <B>  2 3
 *  2 <C>    4
 *  3 <D>    5 6 6 6
 *  4 <E>      7 8
 */

int** newTDP(int nrow, int ncol) {
    int** table = (int**) malloc(sizeof(int*) * nrow);
    if (table == NULL) {
        return NULL;
    }

    for (int i = 0; i < nrow; i++) {
        table[i] = (int*) malloc(sizeof(int) * ncol);
        if (table[i] == NULL) {
            return NULL;
        }

        for (int j = 0; j < ncol; j++) {
            table[i][j] = 0; // initialize all indexes to 0
        }
    }

    // for <A>
    table[0][0] = 1;
    table[0][1] = 1;

    // for <B>
    table[1][0] = 2;
    table[1][1] = 3;

    // for <C>
    table[2][1] = 4;

    // for <D>
    table[3][1] = 5;
    table[3][2] = 6;
    table[3][3] = 6;
    table[3][4] = 6;

    // for <E>
    table[4][2] = 7;
    table[4][3] = 8;

    return table;
}

int findProduction(int** table, char c, char nonTerminal) {
    int col;
    int row;
    // find row
    switch (nonTerminal) {
        case 'A':
            row = 0;
            break;
        case 'B':
            row = 1;
            break;
        case 'C':
            row = 2;
            break;
        case 'D':
            row = 3;
            break;
        case 'E':
            row = 4;
            break;
        default:
            row = 0;
    }

    // find col
    if (c == 'b') {
        col = 0;
    } else if (c == 'c') {
        col = 1;
    } else if (c == 'e') {
        col = 2;
    } else if (c == '(') {
        col = 3;
    } else if (c == ')') {
        col = 4;
    } else {
        col = 0;
    }

    return table[row][col];
}

bool isTerminal(char c) {
    if (c == 'b') {
        return true;
    }

    if (c == 'c') {
        return true;
    }

    if (c == '\0') {
        return true;
    }

    if (c == 'e') {
        return true;
    }

    if (c == '(' || c == ')') {
        return true;
    }

    return false;
}

TREE parseTDP(char* input, int** table) {
    nextTerminal = input;
    STACK stack = newSTACK();
    push(stack, 'A');
    TREE tdpTREE = makeNode0('A');
    while (!isEmpty(stack)) {
        char curr = top(stack);
        if (isTerminal(curr)) {
            if (top(stack) == *nextTerminal) {
                pop(stack);
                nextTerminal += 1;
                continue;
            }
            return NULL;
        }
        int prod = findProduction(table, *nextTerminal, top(stack));

        pop(stack);
        switch (prod) {
            case 1:
                push(stack, 'E');
                push(stack, 'B');
                addChildtoLeaf2(tdpTREE, curr, makeNode0('B'), makeNode0('E'));
                break;
            case 2:
                push(stack, 'b');
                addChildtoLeaf1(tdpTREE, curr, makeNode0('b'));
                break;
            case 3:
                push(stack, 'C');
                addChildtoLeaf1(tdpTREE, curr, makeNode0('C'));
                break;
            case 4:
                push(stack, 'D');
                push(stack, 'c');
                addChildtoLeaf2(tdpTREE, curr, makeNode0('c'), makeNode0('D'));
                break;
            case 5:
                push(stack, 'C');
                addChildtoLeaf1(tdpTREE, curr, makeNode0('C'));
                break;
            case 6:
                addChildtoLeaf1(tdpTREE, curr, makeNode0('_'));
                break;
            case 7:
                push(stack, 'e');
                addChildtoLeaf1(tdpTREE, curr, makeNode0('e'));
                break;
            case 8:
                push(stack, ')');
                push(stack, 'E');
                push(stack, '(');
                addChildtoLeaf3(tdpTREE, curr, makeNode0('('), makeNode0('E'), makeNode0(')'));
                break;
            default:
                return NULL;
        }
    }
    return tdpTREE;
}