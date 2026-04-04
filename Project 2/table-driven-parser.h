#ifndef PROJECT_2_TABLE_DRIVEN_PARSER_H
#define PROJECT_2_TABLE_DRIVEN_PARSER_H

#include <stdbool.h>
#include "parsetree.h"

extern int** newTDP(int nrow, int ncol);
extern int findProduction(int** table, char c, char nonTerminal);
extern bool isTerminal(char c);
extern TREE parseTDP(char* input, int** table);

#endif //PROJECT_2_TABLE_DRIVEN_PARSER_H