#include "nfa.h"
#include "dfa.h"
#include "LinkedList.h"
#include "IntHashSet.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#define DFA_STATE_TABLE_SIZE 4096

typedef struct NFA* NFA;

typedef struct DFAStateEntry {
    IntHashSet set;
    int index;
    struct DFAStateEntry *next;
} DFAState;

typedef struct DFAStateTable{
    DFAState **buckets;
    int size;
} DFAStateTable;

struct NFA {
    int nstates;
    IntHashSet currentStates;
    IntHashSet** transitionTable;
    bool* accepting;
};

DFAStateTable new_DFAStateTable(int size) {
    DFAStateTable this;
    this.size = size;
    this.buckets = calloc(size, sizeof(DFAState *));
    return this;
}

NFA new_NFA(int nstates) {
    NFA nfa = (NFA)malloc(sizeof(struct NFA));
    if (nfa == NULL) {
        return NULL;
    }
    nfa->nstates = nstates;
    nfa->currentStates = new_IntHashSet(nstates);
    nfa->transitionTable = malloc(sizeof(IntHashSet*) * nstates);
    nfa->accepting = (bool*)malloc(sizeof(bool) * nstates);

    for (int i = 0; i < nstates; i++) {
        nfa->transitionTable[i] = malloc(sizeof(IntHashSet*) * 128);
        nfa->accepting[i] = false;
        for (int j = 0; j < 128; j++) {
            nfa->transitionTable[i][j] = new_IntHashSet(nstates);
        }
    }

    return nfa;
}

int DFAStateTable_lookup(DFAStateTable *this, IntHashSet set) {
    int h = DFAStateTable_hash(this, set);
    DFAState *e = this->buckets[h];
    while (e != NULL) {
        if (IntHashSet_equals(e->set, set)) {
            return e->index;
        }
        e = e->next;
    }
    return -1;
}

void DFAStateTable_insert(DFAStateTable *this, IntHashSet set, int index) {
    uint64_t h = hash_IntHashSet(set) % this->size;
    DFAState *e = malloc(sizeof(DFAState));
    e->set = set;
    e->index = index;
    e->next = this->buckets[h];
    this->buckets[h] = e;
}

int DFAStateTable_hash(DFAStateTable *table, IntHashSet set) {
    return hash_IntHashSet(set) % table->size;
}

void NFA_free(NFA nfa) {
    for (int i = 0; i < nfa->nstates; i++) {
        free(nfa->transitionTable[i]);
    }
    free(nfa->transitionTable);
    free(nfa->accepting);
    IntHashSet_free(nfa->currentStates);
    free(nfa);
}

int NFA_get_size(NFA nfa) {
    return nfa->nstates;
}

IntHashSet NFA_get_transitions(NFA nfa, int state, unsigned char sym) {
    return nfa->transitionTable[state][(int)sym];
}

void NFA_add_transition(NFA nfa, int src, unsigned char sym, int dst) {
    if (!IntHashSet_lookup(nfa->transitionTable[src][(int)sym], dst)) {
        IntHashSet_insert(nfa->transitionTable[src][(int)sym], dst);
    }
}

void NFA_add_transition_str(NFA nfa, int src, char *str, int dst) {
    for (int i = 0; i < strlen(str); i++) {
        NFA_add_transition(nfa, src, str[i], dst);
    }
}

void NFA_add_transition_all(NFA nfa, int src, int dst) {
    for (int i = 0; i < 128; i++) {
        NFA_add_transition(nfa, src, (char)i, dst);
    }
}

void NFA_set_accepting(NFA nfa, int state, bool value) {
    nfa->accepting[state] = value;
}

bool NFA_get_accepting(NFA nfa, int state) {
    return nfa->accepting[state];
}

bool NFA_execute(NFA nfa, char *input) {
    if (nfa->currentStates) { IntHashSet_free(nfa->currentStates); }
    nfa->currentStates = new_IntHashSet(nfa->nstates);
    IntHashSet_insert(nfa->currentStates, 0);
    // find all possible final states of the input
    for (int i = 0, n = strlen(input); i < n; i++) {
        unsigned char sym = (unsigned char)input[i];
        IntHashSet next = new_IntHashSet(nfa->nstates);
        IntHashSetIterator it = IntHashSet_iterator(nfa->currentStates);
        while (IntHashSetIterator_hasNext(it)) {
            int c = IntHashSetIterator_next(it);
            IntHashSet_union(next, NFA_get_transitions(nfa, c, sym));
            /* printf("After '%c': { ", sym);
            IntHashSetIterator dbg = IntHashSet_iterator(nfa->currentStates);
            while (IntHashSetIterator_hasNext(dbg)) {
                printf("%d ", IntHashSetIterator_next(dbg));
            }
            printf("}\n");
            free(dbg);
            */// debugging
        }
        free(it);
        IntHashSet_free(nfa->currentStates);
        nfa->currentStates = next;
    }
    // find if any of the possible final states are accepting states and return accordingly
    IntHashSetIterator ai = IntHashSet_iterator(nfa->currentStates);
    while (IntHashSetIterator_hasNext(ai)) {
        int i = IntHashSetIterator_next(ai);
        if (nfa->accepting[i]) {
            free(ai);
            return true;
        }
    }
    free(ai);
    return false;
}

DFA nfa_to_dfa(NFA nfa) {
    // find # of dfa states, all reachable subsets of NFA states
    int nfaSize = NFA_get_size(nfa);
    LinkedList DFAStatesList = new_LinkedList(); // using linkedlist because it has O(1) insertions and dont have to identify a size
    LinkedList workList = new_LinkedList();

    IntHashSet initialStates = new_IntHashSet(1);
    IntHashSet_insert(initialStates, 0);

    DFAStateTable table = new_DFAStateTable(1021);

    LinkedList_add_at_end(DFAStatesList, initialStates);
    LinkedList_add_at_end(workList, initialStates);
    while (!LinkedList_isEmpty(workList)) {
        IntHashSet curr = LinkedList_pop(workList);
        for (int c = 0; c < 128; c++) {
            IntHashSet next = new_IntHashSet(nfaSize);

            IntHashSetIterator it = IntHashSet_iterator(curr);
            while (IntHashSetIterator_hasNext(it)) {
                int state = IntHashSetIterator_next(it);
                IntHashSet dsts = NFA_get_transitions(nfa, state, (char)c);
                IntHashSetIterator dt = IntHashSet_iterator(dsts);
                while (IntHashSetIterator_hasNext(dt)) {
                    IntHashSet_insert(next, IntHashSetIterator_next(dt));
                }
            }
            free(it);

            if (IntHashSet_isEmpty(next)) {
                IntHashSet_free(next);
                continue;
            }
            int idx = DFAStateTable_lookup(&table, next);
            if (idx == -1) {
                int newIndex = LinkedList_size(DFAStatesList);
                DFAStateTable_insert(&table, next, newIndex);
                LinkedList_add_at_end(DFAStatesList, next);
                LinkedList_add_at_end(workList, next);
            }
        }
    }
    // get transitions
    DFA dfa = new_DFA(LinkedList_size(DFAStatesList));
    for (int i = 0; i < DFA_get_size(dfa); i++) {
        IntHashSet curr = LinkedList_elementAt(DFAStatesList, i);
        for (int j = 0; j < 128; j++) {
            IntHashSet next = new_IntHashSet(nfaSize);
            IntHashSetIterator si = IntHashSet_iterator(curr);

            while (IntHashSetIterator_hasNext(si)) {
                IntHashSet_union(next, NFA_get_transitions(nfa, IntHashSetIterator_next(si), (char)j));
            }
            free(si);

            int nextIndex = DFAStateTable_lookup(&table, next);
            while (nextIndex < LinkedList_size(DFAStatesList) && !IntHashSet_equals(next, LinkedList_elementAt(DFAStatesList, nextIndex))) {
                nextIndex++;
            }

            if (IntHashSet_isEmpty(next)) {
                DFA_set_transition(dfa, i, (char)j, 0);
                IntHashSet_free(next);
                continue;
            }

            DFA_set_transition(dfa, i, (char)j, nextIndex);
            IntHashSet_free(next);
        }
    }

    // get accepting states
    LinkedListIterator it = LinkedList_iterator(DFAStatesList);
    while (LinkedListIterator_hasNext(it)) {
        IntHashSet subset = LinkedListIterator_next(it);

        // get DFA index from table
        int dfaIndex = DFAStateTable_lookup(&table, subset);

        // check if any NFA state in this subset is accepting
        bool accepting = false;
        IntHashSetIterator sit = IntHashSet_iterator(subset);
        while (IntHashSetIterator_hasNext(sit)) {
            int nfaState = IntHashSetIterator_next(sit);
            if (NFA_get_accepting(nfa, nfaState)) {
                accepting = true;
                break;
            }
        }
        free(sit);

        if (accepting) {
            DFA_set_accepting(dfa, dfaIndex, true);
        }
    }
    free(it);
    return dfa;
}