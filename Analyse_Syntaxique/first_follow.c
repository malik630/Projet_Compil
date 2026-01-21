
#include "grammar.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Helper functions for symbol sets
void addToSet(SymbolSet* set, TokenType terminal) {
    if (!isInSet(set, terminal)) {
        set->terminals[set->count++] = terminal;
    }
}

bool isInSet(SymbolSet* set, TokenType terminal) {
    for (int i = 0; i < set->count; i++) {
        if (set->terminals[i] == terminal) {
            return true;
        }
    }
    return false;
}

void unionSets(SymbolSet* dest, SymbolSet* src) {
    for (int i = 0; i < src->count; i++) {
        addToSet(dest, src->terminals[i]);
    }
}

void printSymbolSet(SymbolSet* set) {
    printf("{ ");
    if (set->has_epsilon) {
        printf("ε ");
    }
    for (int i = 0; i < set->count; i++) {
        printf("%s ", tokenTypeToString(set->terminals[i]));
    }
    printf("}");
}

// Check if a single symbol can derive epsilon
bool canDeriveEpsilon(Grammar* grammar, GrammarSymbol symbol, bool* nullable) {
    if (symbol.type == SYM_EPSILON) {
        return true;
    }
    
    if (symbol.type == SYM_TERMINAL) {
        return false;
    }
    
    // Non-terminal: check if already computed
    NonTerminal nt = symbol.value.non_terminal;
    if (nullable[nt]) {
        return true;
    }
    
    return false;
}

// Check if a sequence of symbols can derive epsilon
bool canProductionDeriveEpsilon(Grammar* grammar, GrammarSymbol* symbols, int length, bool* nullable) {
    if (length == 0) return true;
    
    for (int i = 0; i < length; i++) {
        if (!canDeriveEpsilon(grammar, symbols[i], nullable)) {
            return false;
        }
    }
    return true;
}

// Compute which non-terminals are nullable (can derive epsilon)
void computeNullable(Grammar* grammar, bool* nullable) {
    printf("\n[FIRST/FOLLOW] Computing nullable non-terminals...\n");
    
    // Initialize all to false
    for (int i = 0; i < NT_COUNT; i++) {
        nullable[i] = false;
    }
    
    // Iterate until no changes
    bool changed = true;
    int iteration = 0;
    
    while (changed) {
        changed = false;
        iteration++;
        
        for (int i = 0; i < grammar->production_count; i++) {
            Production* prod = &grammar->productions[i];
            NonTerminal left = prod->left_side;
            
            // Skip if already nullable
            if (nullable[left]) continue;
            
            // Check if this production can derive epsilon
            if (prod->right_side_length == 0 || prod->right_side[0].type == SYM_EPSILON) {
                nullable[left] = true;
                changed = true;
                printf("  Iteration %d: %s can derive ε (direct)\n", iteration, nonTerminalToString(left));
            } else {
                // Check if all symbols in RHS are nullable
                bool all_nullable = true;
                for (int j = 0; j < prod->right_side_length; j++) {
                    GrammarSymbol sym = prod->right_side[j];
                    if (sym.type == SYM_TERMINAL) {
                        all_nullable = false;
                        break;
                    } else if (sym.type == SYM_NONTERMINAL) {
                        if (!nullable[sym.value.non_terminal]) {
                            all_nullable = false;
                            break;
                        }
                    }
                }
                
                if (all_nullable) {
                    nullable[left] = true;
                    changed = true;
                    printf("  Iteration %d: %s can derive ε (all symbols nullable)\n", 
                           iteration, nonTerminalToString(left));
                }
            }
        }
    }
    
    printf("[FIRST/FOLLOW] Nullable computation complete after %d iterations\n", iteration);
}

// Compute FIRST sets
void computeFirst(Grammar* grammar, FirstFollowTable* table, bool* nullable) {
    printf("\n[FIRST/FOLLOW] Computing FIRST sets...\n");
    
    // Initialize all FIRST sets
    for (int i = 0; i < NT_COUNT; i++) {
        table->first_sets[i].count = 0;
        table->first_sets[i].has_epsilon = false;
    }
    
    // Iterate until no changes
    bool changed = true;
    int iteration = 0;
    
    while (changed) {
        changed = false;
        iteration++;
        
        for (int i = 0; i < grammar->production_count; i++) {
            Production* prod = &grammar->productions[i];
            NonTerminal left = prod->left_side;
            SymbolSet* first_left = &table->first_sets[left];
            
            // If production is A -> ε
            if (prod->right_side_length == 0 || prod->right_side[0].type == SYM_EPSILON) {
                if (!first_left->has_epsilon) {
                    first_left->has_epsilon = true;
                    changed = true;
                }
                continue;
            }
            
            // For A -> X1 X2 ... Xn
            for (int j = 0; j < prod->right_side_length; j++) {
                GrammarSymbol sym = prod->right_side[j];
                
                if (sym.type == SYM_TERMINAL) {
                    // Add terminal to FIRST(A)
                    int old_count = first_left->count;
                    addToSet(first_left, sym.value.terminal);
                    if (first_left->count > old_count) changed = true;
                    break;  // Stop here
                } else if (sym.type == SYM_NONTERMINAL) {
                    // Add FIRST(Xi) - {ε} to FIRST(A)
                    SymbolSet* first_xi = &table->first_sets[sym.value.non_terminal];
                    int old_count = first_left->count;
                    unionSets(first_left, first_xi);
                    if (first_left->count > old_count) changed = true;
                    
                    // If Xi cannot derive ε, stop
                    if (!nullable[sym.value.non_terminal]) {
                        break;
                    }
                    
                    // If this is the last symbol and all can derive ε
                    if (j == prod->right_side_length - 1) {
                        if (!first_left->has_epsilon) {
                            first_left->has_epsilon = true;
                            changed = true;
                        }
                    }
                }
            }
        }
    }
    
    printf("[FIRST/FOLLOW] FIRST sets computed after %d iterations\n", iteration);
}

// Compute FOLLOW sets
void computeFollow(Grammar* grammar, FirstFollowTable* table, bool* nullable) {
    printf("\n[FIRST/FOLLOW] Computing FOLLOW sets...\n");
    
    // Initialize all FOLLOW sets
    for (int i = 0; i < NT_COUNT; i++) {
        table->follow_sets[i].count = 0;
        table->follow_sets[i].has_epsilon = false;
    }
    
    // Add $ to FOLLOW(Start)
    addToSet(&table->follow_sets[grammar->start_symbol], END_OF_FILE);
    
    // Iterate until no changes
    bool changed = true;
    int iteration = 0;
    
    while (changed) {
        changed = false;
        iteration++;
        
        for (int i = 0; i < grammar->production_count; i++) {
            Production* prod = &grammar->productions[i];
            NonTerminal left = prod->left_side;
            
            // For each symbol in the production
            for (int j = 0; j < prod->right_side_length; j++) {
                GrammarSymbol sym = prod->right_side[j];
                
                // Only interested in non-terminals
                if (sym.type != SYM_NONTERMINAL) continue;
                
                NonTerminal B = sym.value.non_terminal;
                SymbolSet* follow_B = &table->follow_sets[B];
                int old_count = follow_B->count;
                
                // Look at what follows B
                bool all_nullable = true;
                
                for (int k = j + 1; k < prod->right_side_length; k++) {
                    GrammarSymbol next = prod->right_side[k];
                    
                    if (next.type == SYM_TERMINAL) {
                        // Add terminal to FOLLOW(B)
                        addToSet(follow_B, next.value.terminal);
                        all_nullable = false;
                        break;
                    } else if (next.type == SYM_NONTERMINAL) {
                        // Add FIRST(next) - {ε} to FOLLOW(B)
                        SymbolSet* first_next = &table->first_sets[next.value.non_terminal];
                        unionSets(follow_B, first_next);
                        
                        // If next cannot derive ε, stop
                        if (!nullable[next.value.non_terminal]) {
                            all_nullable = false;
                            break;
                        }
                    }
                }
                
                // If all symbols after B are nullable (or there are none)
                // Add FOLLOW(A) to FOLLOW(B)
                if (all_nullable) {
                    SymbolSet* follow_left = &table->follow_sets[left];
                    unionSets(follow_B, follow_left);
                }
                
                if (follow_B->count > old_count) changed = true;
            }
        }
    }
    
    printf("[FIRST/FOLLOW] FOLLOW sets computed after %d iterations\n", iteration);
}

// Main function to compute FIRST and FOLLOW
FirstFollowTable* computeFirstFollow(Grammar* grammar) {
    printf("\n========== COMPUTING FIRST AND FOLLOW SETS ==========\n");
    
    FirstFollowTable* table = (FirstFollowTable*)malloc(sizeof(FirstFollowTable));
    
    // Compute nullable non-terminals (epsilon closure)
    bool nullable[NT_COUNT];
    computeNullable(grammar, nullable);
    
    // Compute FIRST sets
    computeFirst(grammar, table, nullable);
    
    // Compute FOLLOW sets
    computeFollow(grammar, table, nullable);
    
    printf("\n========== FIRST/FOLLOW COMPUTATION COMPLETE ==========\n");
    
    return table;
}

void freeFirstFollowTable(FirstFollowTable* table) {
    free(table);
}

void printFirstFollowTable(FirstFollowTable* table) {
    printf("\n========== FIRST SETS ==========\n");
    for (int i = 0; i < NT_COUNT; i++) {
        printf("FIRST(%s) = ", nonTerminalToString((NonTerminal)i));
        printSymbolSet(&table->first_sets[i]);
        printf("\n");
    }
    
    printf("\n========== FOLLOW SETS ==========\n");
    for (int i = 0; i < NT_COUNT; i++) {
        printf("FOLLOW(%s) = ", nonTerminalToString((NonTerminal)i));
        printSymbolSet(&table->follow_sets[i]);
        printf("\n");
    }
    printf("====================================\n\n");
}
