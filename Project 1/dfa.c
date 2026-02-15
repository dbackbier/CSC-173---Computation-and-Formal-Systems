#include "dfa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "IntHashSet.h"

typedef struct DFA* DFA;

struct DFA {
    int nstates;
    int currentState;
    int** transitionTable;
    bool* accepting;
};

DFA new_DFA(int nstates) {
    DFA dfa = (DFA) malloc(sizeof(struct DFA));
    if (dfa == NULL) {
        return NULL;
    }
    dfa->nstates = nstates;
    dfa->currentState = 0;
    dfa->transitionTable = (int**) malloc(sizeof(int*) * nstates);
    // Initialize empty transition table
    for (int i = 0; i < nstates; i++) {
        dfa->transitionTable[i] = (int*) malloc(sizeof(int) * 128);
        for (int j = 0; j < 128; j++) {
            dfa->transitionTable[i][j] = 0;
        }
    }
    dfa->accepting = (bool*) malloc(sizeof(bool) * nstates);
    // Initialize empty accepting array
    for (int i = 0; i < nstates; i++) {
        dfa->accepting[i] = false;
    }
    return dfa;
}

/**
 * Free the given DFA.
 */
void DFA_free(DFA dfa) {
    for (int i = 0; i < dfa->nstates; i++) {
        free(dfa->transitionTable[i]);
    }
    free(dfa->transitionTable);
    free(dfa->accepting);
    free(dfa);
}

/**
 * Return the number of states in the given DFA.
 */
int DFA_get_size(DFA dfa) {
    return dfa->nstates;
}

/**
 * Return the state specified by the given DFA's transition function from
 * state src on input symbol sym.
 */
int DFA_get_transition(DFA dfa, int src, unsigned char sym) {
    return dfa->transitionTable[src][(int)sym];
}

/**
 * For the given DFA, set the transition from state src on input symbol
 * sym to be the state dst.
 */
void DFA_set_transition(DFA dfa, int src, unsigned char sym, int dst) {
    dfa->transitionTable[src][(int)sym] = dst;
}

/**
 * Set the transitions of the given DFA for each symbol in the given str.
 * This is a nice shortcut when you have multiple labels on an edge between
 * two states.
 */
void DFA_set_transition_str(DFA dfa, int src, char *str, int dst) {
    for (int i = 0; i < strlen(str); i++) {
        DFA_set_transition(dfa, src, str[i], dst);
    }
}

/**
 * Set the transitions of the given DFA for all input symbols.
 * Another shortcut method.
 */
void DFA_set_transition_all(DFA dfa, int src, int dst) {
    for (int i = 0; i < 128; i++) { // 128 ASCII chars, 0-127
        dfa->transitionTable[src][i] = dst;
    }
}

/**
 * Set whether the given DFA's state is accepting or not.
 */
void DFA_set_accepting(DFA dfa, int state, bool value) {
    dfa->accepting[state] = value;
}

/**
 * Return true if the given DFA's state is an accepting state.
 */
bool DFA_get_accepting(DFA dfa, int state) {
    return dfa->accepting[state];
}

/**
 * Run the given DFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
bool DFA_execute(DFA dfa, char *input) {
    dfa->currentState = 0;
    for (int i = 0; i < strlen(input); i++) {
        char sym = input[i];
        int src = dfa->currentState;
        dfa->currentState = DFA_get_transition(dfa, src, sym);
        // printf("After '%c': { %d }\n", sym, dfa->currentState); debugging
    }
    return DFA_get_accepting(dfa, dfa->currentState);
}

/**
 * Print the given DFA to System.out.
 */
void DFA_print(DFA dfa) {
    for (int i = 0; i < dfa->nstates; i++) {
        for (int j = 0; j < dfa->nstates; j++) {
            printf("%d ", dfa->transitionTable[i][j]);
        }
    }
}