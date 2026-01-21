#include "subset.h"
#include <ctype.h>

StateSet epsilon(AFN* afn, StateSet states) {
    StateSet closure = states;
    bool added = true;
    
    while (added) {
        added = false;
        for (int i = 0; i < closure.count; i++) {
            int state = closure.states[i];
            
            for (int j = 0; j < afn->trans_count; j++) {
                if (afn->transitions[j].from_state == state && 
                    afn->transitions[j].symbol == EPSILON) {
                    
                    int target = afn->transitions[j].to_state;
                    
                    bool found = false;
                    for (int k = 0; k < closure.count; k++) {
                        if (closure.states[k] == target) {
                            found = true;
                            break;
                        }
                    }
                    
                    if (!found && closure.count < MAX_STATES) {
                        closure.states[closure.count++] = target;
                        added = true;
                    }
                }
            }
        }
    }
    
    return closure;
}

StateSet move(AFN* afn, StateSet states, int symbol) {
    StateSet result;
    result.count = 0;
    
    for (int i = 0; i < states.count; i++) {
        int state = states.states[i];
        
        for (int j = 0; j < afn->trans_count; j++) {
            if (afn->transitions[j].from_state == state && 
                afn->transitions[j].symbol == symbol) {
                
                int target = afn->transitions[j].to_state;
                
                bool found = false;
                for (int k = 0; k < result.count; k++) {
                    if (result.states[k] == target) {
                        found = true;
                        break;
                    }
                }
                
                if (!found && result.count < MAX_STATES) {
                    result.states[result.count++] = target;
                }
            }
        }
    }
    
    return result;
}

bool stateSetEqual(StateSet s1, StateSet s2) {
    if (s1.count != s2.count) return false;
    
    for (int i = 0; i < s1.count; i++) {
        bool found = false;
        for (int j = 0; j < s2.count; j++) {
            if (s1.states[i] == s2.states[j]) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

int findStateSet(AFD* afd, StateSet set) {
    for (int i = 0; i < afd->state_count; i++) {
        if (stateSetEqual(afd->states[i], set)) {
            return i;
        }
    }
    return -1;
}

AFD subsetConstruction(AFN* afn) {
    AFD afd;
    afd.state_count = 0;
    
    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < 256; j++) {
            afd.transitions[i][j] = -1;
        }
        afd.final_states[i] = false;
    }
    
    StateSet initial;
    initial.count = 1;
    initial.states[0] = afn->start_state;
    initial = epsilon(afn, initial);
    
    afd.states[afd.state_count++] = initial;
    afd.start_state = 0;
    
    int unprocessed[MAX_STATES];
    int unprocessed_count = 1;
    unprocessed[0] = 0;
    
    while (unprocessed_count > 0) {
        int current_idx = unprocessed[--unprocessed_count];
        StateSet current = afd.states[current_idx];
        
        for (int symbol = 0; symbol < 256; symbol++) {
            if (!isalnum(symbol) && symbol != '_' && symbol != '.') continue;
            
            StateSet m = move(afn, current, symbol);
            if (m.count == 0) continue;
            
            StateSet target = epsilon(afn, m);
            if (target.count == 0) continue;
            
            int target_idx = findStateSet(&afd, target);
            
            if (target_idx == -1) {
                target_idx = afd.state_count;
                afd.states[afd.state_count++] = target;
                unprocessed[unprocessed_count++] = target_idx;
            }
            
            afd.transitions[current_idx][symbol] = target_idx;
        }
    }
    
    for (int i = 0; i < afd.state_count; i++) {
        StateSet state = afd.states[i];
        for (int j = 0; j < state.count; j++) {
            for (int k = 0; k < afn->final_count; k++) {
                if (state.states[j] == afn->final_states[k]) {
                    afd.final_states[i] = true;
                    break;
                }
            }
        }
    }
    
    return afd;
}