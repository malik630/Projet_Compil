#include "thompson.h"
#include <stdio.h>
#include <string.h>

int next_state_id = 0;
bool show_construction = false;

void initAFN(AFN* afn) {
    afn->state_count = 0;
    afn->trans_count = 0;
    afn->final_count = 0;
}

int newState(AFN* afn) {
    int state = next_state_id++;
    afn->states[afn->state_count++] = state;
    return state;
}

void addTransition(AFN* afn, int from, int to, int symbol) {
    afn->transitions[afn->trans_count].from_state = from;
    afn->transitions[afn->trans_count].to_state = to;
    afn->transitions[afn->trans_count].symbol = symbol;
    afn->trans_count++;
}

AFN thompsonSymbol(char c) {
    AFN afn;
    initAFN(&afn);
    
    int start = newState(&afn);
    int final = newState(&afn);
    
    afn.start_state = start;
    afn.final_states[0] = final;
    afn.final_count = 1;
    
    addTransition(&afn, start, final, c);
    
    if (show_construction) {
        printf("    [Thompson] Symbole '%c': q%d --'%c'--> q%d\n", c, start, c, final);
    }
    
    return afn;
}

AFN thompsonRange(char start_char, char end_char) {
    AFN afn;
    initAFN(&afn);
    
    int start = newState(&afn);
    int final = newState(&afn);
    
    afn.start_state = start;
    afn.final_states[0] = final;
    afn.final_count = 1;
    
    for (char c = start_char; c <= end_char; c++) {
        addTransition(&afn, start, final, c);
    }
    
    if (show_construction) {
        printf("    [Thompson] Plage [%c-%c]: q%d --[%c-%c]--> q%d\n", 
               start_char, end_char, start, start_char, end_char, final);
    }
    
    return afn;
}

AFN thompsonConcat(AFN afn1, AFN afn2) {
    AFN result = afn1;
    
    for (int i = 0; i < afn2.state_count; i++) {
        result.states[result.state_count++] = afn2.states[i];
    }
    for (int i = 0; i < afn2.trans_count; i++) {
        result.transitions[result.trans_count++] = afn2.transitions[i];
    }
    
    for (int i = 0; i < afn1.final_count; i++) {
        addTransition(&result, afn1.final_states[i], afn2.start_state, EPSILON);
    }
    
    result.final_count = afn2.final_count;
    for (int i = 0; i < afn2.final_count; i++) {
        result.final_states[i] = afn2.final_states[i];
    }
    
    return result;
}

AFN thompsonUnion(AFN afn1, AFN afn2) {
    AFN result;
    initAFN(&result);
    
    int new_start = newState(&result);
    int new_final = newState(&result);
    
    for (int i = 0; i < afn1.state_count; i++) {
        result.states[result.state_count++] = afn1.states[i];
    }
    for (int i = 0; i < afn1.trans_count; i++) {
        result.transitions[result.trans_count++] = afn1.transitions[i];
    }
    for (int i = 0; i < afn2.state_count; i++) {
        result.states[result.state_count++] = afn2.states[i];
    }
    for (int i = 0; i < afn2.trans_count; i++) {
        result.transitions[result.trans_count++] = afn2.transitions[i];
    }
    
    addTransition(&result, new_start, afn1.start_state, EPSILON);
    addTransition(&result, new_start, afn2.start_state, EPSILON);
    
    for (int i = 0; i < afn1.final_count; i++) {
        addTransition(&result, afn1.final_states[i], new_final, EPSILON);
    }
    for (int i = 0; i < afn2.final_count; i++) {
        addTransition(&result, afn2.final_states[i], new_final, EPSILON);
    }
    
    result.start_state = new_start;
    result.final_states[0] = new_final;
    result.final_count = 1;
    
    return result;
}

AFN thompsonStar(AFN afn) {
    AFN result;
    initAFN(&result);
    
    int new_start = newState(&result);
    int new_final = newState(&result);
    
    for (int i = 0; i < afn.state_count; i++) {
        result.states[result.state_count++] = afn.states[i];
    }
    for (int i = 0; i < afn.trans_count; i++) {
        result.transitions[result.trans_count++] = afn.transitions[i];
    }
    
    addTransition(&result, new_start, afn.start_state, EPSILON);
    addTransition(&result, new_start, new_final, EPSILON);
    
    for (int i = 0; i < afn.final_count; i++) {
        addTransition(&result, afn.final_states[i], new_final, EPSILON);
        addTransition(&result, afn.final_states[i], afn.start_state, EPSILON);
    }
    
    result.start_state = new_start;
    result.final_states[0] = new_final;
    result.final_count = 1;
    
    return result;
}

AFN thompsonPlus(AFN afn) {
    AFN star = thompsonStar(afn);
    AFN afn_copy = afn;
    return thompsonConcat(afn_copy, star);
}