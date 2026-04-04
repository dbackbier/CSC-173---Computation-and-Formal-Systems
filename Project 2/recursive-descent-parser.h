#ifndef PROJECT_2_RECURSIVE_DESCENT_PARSER_H
#define PROJECT_2_RECURSIVE_DESCENT_PARSER_H

#include <stdbool.h>
#include "parsetree.h"

extern char* nextTerminal;

extern bool lookahead(char c);
extern bool match(char c);

extern TREE A(void);
extern TREE B(void);
extern TREE C(void);
extern TREE D(void);
extern TREE E(void);

#endif //PROJECT_2_RECURSIVE_DESCENT_PARSER_H