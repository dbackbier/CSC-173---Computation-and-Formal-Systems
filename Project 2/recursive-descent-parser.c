#include "recursive-descent-parser.h"
#include "parsetree.h"
#include <stdbool.h>
#include <stddef.h>

char *nextTerminal;

bool lookahead(char c) {
    return *nextTerminal == c;
}

bool match(char c) {
    if (lookahead(c)) {
        nextTerminal += 1;
        return true;
    }
    return false;
}

// A -> B E
TREE A(void) {
    TREE tB = B();
    if (tB == NULL) {
        return NULL;
    }

    TREE tE = E();
    if (tE == NULL) {
        return NULL;
    }

    TREE root = makeNode1('A', tB);
    tB->rightSibling = tE;

    return root;
}

// B -> b | C
TREE B(void) {
    if (lookahead('b')) {
        if (!match('b')) {
            return NULL;
        }
        return makeNode1('B', makeNode0('b'));
    }
    TREE tC = C();
    if (tC == NULL) {
        return NULL;
    }
    return makeNode1('B', tC);
}

// C -> c D
TREE C(void) {
    if (!lookahead('c')) {
        return NULL;
    }
    if (!match('c')) {
        return NULL;
    }
    TREE tc = makeNode0('c');

    TREE tD = D();
    if (tD == NULL) {
        return NULL;
    }

    TREE root = makeNode1('C', tc);
    tc->rightSibling = tD;

    return root;
}

// D -> C | ''
TREE D(void) {
    TREE tC = C();
    if (tC != NULL) {
        return makeNode1('D', tC);
    }

    return makeNode1('D', makeNode0('_')); // '_' is a replacement for empty string
}

// E -> ( E ) | e
TREE E(void) {
    if (lookahead('e')) {
        if (!match('e')) {
            return NULL;
        }
        return makeNode1('E', makeNode0('e'));
    }
    if (lookahead('(')) {
        if (!match('(')) {
            return NULL;
        }

        TREE tE = E();
        if (tE == NULL) {
            return NULL;
        }

        if (!match(')')) {
            return NULL;
        }

        TREE y1 = makeNode0('(');
        TREE y2 = makeNode0(')');
        TREE root = makeNode1('E', y1);
        y1->rightSibling = tE;
        tE->rightSibling = y2;

        return root;
    }
    return NULL;
}