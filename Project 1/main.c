#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "dfa.h"
#include "LinkedList.h"
#include "nfa.h"

DFA DFA_for_is_cba() {
    DFA dfa = new_DFA(5);
    DFA_set_accepting(dfa, 3, true);
    DFA_set_transition_all(dfa, 3, 4);

    for (int i = 0; i < 5; i++) {
        DFA_set_transition_all(dfa, i, 4);
    }

    DFA_set_transition(dfa, 0, 'c', 1);
    DFA_set_transition(dfa, 1, 'b', 2);
    DFA_set_transition(dfa, 2, 'a', 3);

    return dfa;
}

DFA DFA_for_ends_ad_ed() {
    DFA dfa = new_DFA(4);
    DFA_set_accepting(dfa, 3, true);

    for (int i = 0; i < 4; i++) {
        DFA_set_transition_all(dfa, i, 0);
    }

    DFA_set_transition(dfa, 0, 'a', 1);
    DFA_set_transition(dfa, 0, 'e', 2);
    DFA_set_transition(dfa, 1, 'a', 1);
    DFA_set_transition(dfa, 1, 'e', 2);
    DFA_set_transition(dfa, 1, 'd', 3);
    DFA_set_transition(dfa, 2, 'e', 2);
    DFA_set_transition(dfa, 2, 'a', 1);
    DFA_set_transition(dfa, 2, 'd', 3);
    DFA_set_transition(dfa, 3, 'a', 1);
    DFA_set_transition(dfa, 3, 'e', 2);

    return dfa;
}

DFA DFA_with_one_digit() {
    DFA dfa = new_DFA(3);
    DFA_set_accepting(dfa, 1, true);

    for (int i = 1; i < 3; i++) {
        DFA_set_transition_all(dfa, i, i);
    }

    for (int i = '0'; i <= '9'; i++) {
        DFA_set_transition(dfa, 0, (char)i, 1);
        DFA_set_transition(dfa, 1, (char)i, 2);
        DFA_set_transition(dfa, 2, (char)i, 2);
    }

    return dfa;
}

DFA DFA_even0s_odd1s() {
    DFA dfa = new_DFA(5);
    DFA_set_accepting(dfa, 3, true);

    for (int i = 0; i < 5; i++) {
        DFA_set_transition_all(dfa, i, 4);
    }

    DFA_set_transition(dfa, 0, '0', 2);
    DFA_set_transition(dfa, 0, '1', 3);
    DFA_set_transition(dfa, 1, '0', 3);
    DFA_set_transition(dfa, 1, '1', 2);
    DFA_set_transition(dfa, 2, '0', 0);
    DFA_set_transition(dfa, 2, '1', 1);
    DFA_set_transition(dfa, 3, '0', 1);
    DFA_set_transition(dfa, 3, '1', 0);
    // no transitions from state 4, basically an 'auto-reject' state for symbols that the dfa doesn't accept

    return dfa;
}

bool DFA_run(DFA dfa, char* input) {
    bool result = DFA_execute(dfa, input);
    printf("\nThe input '%s' is %s by the DFA\n", input, result ? "accepted" : "rejected");
    return result;
}

void DFA_repl(DFA dfa) {
    char input[256];
    printf("Enter inputs then input 'Q' when done.\n");
    while (fgets(input, sizeof(input), stdin) != NULL) {
        input[strlen(input) - 1] = '\0';
        if (strcmp(input, "Q") == 0) {
            break;
        }
        DFA_run(dfa, input);
        printf("Enter inputs then input 'Q' when done.\n");
    }
}

NFA NFA_ends_with_mad() {
    NFA nfa = new_NFA(4);
    NFA_set_accepting(nfa, 3, true); // state 3 is accepting

    NFA_add_transition_all(nfa, 0, 0);
    NFA_add_transition(nfa, 0, 'm', 1);
    NFA_add_transition(nfa, 1, 'a', 2);
    NFA_add_transition(nfa, 2, 'd', 3);
    return nfa;
}

NFA NFA_contains_abc() {
    NFA nfa = new_NFA(4);
    NFA_set_accepting(nfa, 3, true); // state 3 is accepting

    NFA_add_transition_all(nfa, 0, 0);
    NFA_add_transition(nfa, 0, 'a', 1);
    NFA_add_transition(nfa, 1, 'b', 2);
    NFA_add_transition(nfa, 2, 'c', 3);
    NFA_add_transition_all(nfa, 3, 3);
    return nfa;
}

NFA NFA_woodpecker() {
    NFA nfa = new_NFA(13);
    NFA_set_accepting(nfa, 10, true);
    NFA_set_accepting(nfa, 12, true);

    for (int i = 0; i < 13; i++) {
        NFA_add_transition_all(nfa, i, i);
    }

    // from state 0
    NFA_add_transition(nfa, 0, 'w', 1);
    NFA_add_transition(nfa, 0, 'o', 2);
    NFA_add_transition(nfa, 0, 'd', 4);
    NFA_add_transition(nfa, 0, 'p', 5);
    NFA_add_transition(nfa, 0, 'c', 6);
    NFA_add_transition(nfa, 0, 'k', 7);
    NFA_add_transition(nfa, 0, 'r', 8);
    NFA_add_transition(nfa, 0, 'e', 9);

    // from state 1
    NFA_add_transition(nfa, 1, 'k', 12);
    NFA_add_transition(nfa, 1, 'd', 12);
    NFA_add_transition(nfa, 1, 'p', 12);
    NFA_add_transition(nfa, 1, 'c', 12);
    NFA_add_transition(nfa, 1, 'r', 12);

    // from state 2
    NFA_add_transition(nfa, 2, 'o', 3);

    // from state 3
    NFA_add_transition(nfa, 3, 'o', 10);

    //from state 4
    NFA_add_transition(nfa, 4, 'w', 12);
    NFA_add_transition(nfa, 4, 'k', 12);
    NFA_add_transition(nfa, 4, 'p', 12);
    NFA_add_transition(nfa, 4, 'c', 12);
    NFA_add_transition(nfa, 4, 'r', 12);

    // from state 5
    NFA_add_transition(nfa, 5, 'w', 12);
    NFA_add_transition(nfa, 5, 'd', 12);
    NFA_add_transition(nfa, 5, 'k', 12);
    NFA_add_transition(nfa, 5, 'c', 12);
    NFA_add_transition(nfa, 5, 'r', 12);

    // from state 6
    NFA_add_transition(nfa, 6, 'w', 12);
    NFA_add_transition(nfa, 6, 'd', 12);
    NFA_add_transition(nfa, 6, 'p', 12);
    NFA_add_transition(nfa, 6, 'k', 12);
    NFA_add_transition(nfa, 6, 'r', 12);

    // from state 7
    NFA_add_transition(nfa, 7, 'w', 12);
    NFA_add_transition(nfa, 7, 'd', 12);
    NFA_add_transition(nfa, 7, 'p', 12);
    NFA_add_transition(nfa, 7, 'c', 12);
    NFA_add_transition(nfa, 7, 'r', 12);

    // from state 8
    NFA_add_transition(nfa, 8, 'w', 12);
    NFA_add_transition(nfa, 8, 'd', 12);
    NFA_add_transition(nfa, 8, 'p', 12);
    NFA_add_transition(nfa, 8, 'c', 12);
    NFA_add_transition(nfa, 8, 'k', 12);

    // from state 9
    NFA_add_transition(nfa, 9, 'e', 11);

    // state 10 is accepting so no transitions (other than the all transition)

    // from state 11
    NFA_add_transition(nfa, 11, 'e', 10);

    // state 12 is accepting so no transitions (other than the all transition)

    return nfa;
}

bool NFA_run(NFA nfa, char* input) {
    bool result = NFA_execute(nfa, input);
    printf("\nThe input '%s' is %s by the NFA\n", input, result ? "accepted" : "rejected");
    return result;
}

void NFA_repl(NFA nfa) {
    char input[256];
    printf("Enter inputs then input 'Q' when done.\n");
    while (fgets(input, sizeof(input), stdin) != NULL) {
        input[strlen(input) - 1] = '\0';
        if (strcmp(input, "Q") == 0) {
            break;
        }
        NFA_run(nfa, input);
        printf("Enter inputs then input 'Q' when done.\n");
    }
}

int main(void) {
    printf("Project 1 by Dane Backbier");
    // DFAs
    // For exactly 'cba'
    printf("Testing DFA that accepts strings exactly 'cba'\n");
    DFA dfa_cba = DFA_for_is_cba();
    DFA_repl(dfa_cba);
    DFA_free(dfa_cba);

    // For ends in ad or ed
    printf("\nTesting DFA that accepts strings ending in 'ad' or 'ed'\n");
    DFA dfa_ends_ad_ed = DFA_for_ends_ad_ed();
    DFA_repl(dfa_ends_ad_ed);
    DFA_free(dfa_ends_ad_ed);

    // For contains one digit
    printf("\nTesting DFA that accepts strings with one digit\n");
    DFA dfa_one_digit = DFA_with_one_digit();
    DFA_repl(dfa_one_digit);
    DFA_free(dfa_one_digit);

    // For even # of 0s and odd # of 1s
    printf("\nTesting DFA that accepts strings with an even # of 0s and odd # of 1s\n");
    DFA dfa_even0s_odd1s = DFA_even0s_odd1s();
    DFA_repl(dfa_even0s_odd1s);
    DFA_free(dfa_even0s_odd1s);

    // NFAs
    // For ending in 'mad'
    printf("\nTesting NFA that accepts strings ending in 'mad'\n");
    NFA nfa_ends_with_mad = NFA_ends_with_mad();
    NFA_repl(nfa_ends_with_mad);
    //NFA_free(nfa_ends_with_mad);

    // For containing 'abc'
    printf("\nTesting NFA that accepts strings containing 'abc'\n");
    NFA nfa_contains_abc = NFA_contains_abc();
    NFA_repl(nfa_contains_abc);
    //NFA_free(nfa_contains_abc);

    // For not a woodpecker anagram
    printf("\nTesting NFA that accepts strings that aren't anagrams of 'woodpecker'\n");
    NFA nfa_woodpecker = NFA_woodpecker();
    NFA_repl(nfa_woodpecker);
    //NFA_free(nfa_woodpecker);

    // Testing NFA to DFA
    // For ending in 'mad'
    printf("\nTesting NFA to DFA conversion for an NFA that accepts strings ending in 'mad'\n");
    DFA dfa_ends_with_mad = nfa_to_dfa(nfa_ends_with_mad);
    DFA_repl(dfa_ends_with_mad);
    DFA_free(dfa_ends_with_mad);
    NFA_free(nfa_ends_with_mad);

    // For containing 'abc'
    printf("\nTesting NFA to DFA conversion for an NFA that accepts strings containing 'abc'\n");
    DFA dfa_for_contains_abc = nfa_to_dfa(nfa_contains_abc);
    DFA_repl(dfa_for_contains_abc);
    DFA_free(dfa_for_contains_abc);
    NFA_free(nfa_contains_abc);

    // For not a woodpecker anagram
    printf("\nTesting NFA to DFA conversion for an NFA that accepts strings that aren't anagrams of 'woodpecker'\n");
    DFA dfa_woodpecker = nfa_to_dfa(nfa_woodpecker);
    DFA_repl(dfa_woodpecker);
    DFA_free(dfa_woodpecker);
    NFA_free(nfa_woodpecker);

    return 0;
}