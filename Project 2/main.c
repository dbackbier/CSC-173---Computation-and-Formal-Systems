#include "recursive-descent-parser.h"
#include "parsetree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table-driven-parser.h"

void RDPrepl(void) {
    char input[256];
    printf("Enter inputs then input 'Q' when done.\n");
    while (true) {
        printf(">  ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "Q") == 0) {
            break;
        }
        nextTerminal = input;
        TREE res = A();
        if (res && (*nextTerminal == '\n' || *nextTerminal == '\0')) {
            printf("Parsing successful, input is in language.\n");
            printTree(res,0);
        } else {
            printf("Parsing failed, input is not in language.\n");
        }
        printf("Enter inputs then input 'Q' when done.\n");
    }
}

void TDPrepl(void) {
    char input[256];

    int** parseTable = newTDP(5, 5); // 5 syntactic categories, and 6 terminal symbols
    printf("Enter inputs then input 'Q' when done.\n");
    while (true) {
        printf(">  ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "Q") == 0) {
            for (int i = 0; i < 5; i++) {
                free(parseTable[i]);
            }
            free(parseTable);
            break;
        }

        TREE res = parseTDP(input, parseTable);
        if (res && (*nextTerminal == '\n' || *nextTerminal == '\0')) {
            printf("Parsing successful, input is in language.\n");
            printTree(res,0);
        } else {
            printf("Parsing failed, input is not in language.\n");
        }
    }
}

int main() {
    printf("Testing recursive descent parser.\n");
    RDPrepl();
    printf("\nTesting table driven parser.\n");
    TDPrepl();
    return 0;
}