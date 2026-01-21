#include "grammar.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Generate the LL(1) parsing table
void generateLL1Table(Grammar* grammar, FirstFollowTable* ff_table, LL1Parser* parser) {
    printf("\n========== GENERATING LL(1) PARSE TABLE ==========\n");
    
    // Allocate space for the table
    parser->parse_table = (LL1TableEntry*)malloc(sizeof(LL1TableEntry) * 500);
    parser->table_size = 0;
    
    // For each production A -> α
    for (int i = 0; i < grammar->production_count; i++) {
        Production* prod = &grammar->productions[i];
        NonTerminal A = prod->left_side;
        
        printf("\nProcessing Rule %d: %s -> ", prod->rule_number, nonTerminalToString(A));
        
        // Build production string
        char prod_string[256] = "";
        if (prod->right_side_length == 0 || prod->right_side[0].type == SYM_EPSILON) {
            strcpy(prod_string, "ε");
            printf("ε\n");
        } else {
            for (int j = 0; j < prod->right_side_length; j++) {
                GrammarSymbol sym = prod->right_side[j];
                if (sym.type == SYM_TERMINAL) {
                    strcat(prod_string, tokenTypeToString(sym.value.terminal));
                    printf("%s ", tokenTypeToString(sym.value.terminal));
                } else if (sym.type == SYM_NONTERMINAL) {
                    strcat(prod_string, nonTerminalToString(sym.value.non_terminal));
                    printf("%s ", nonTerminalToString(sym.value.non_terminal));
                }
                if (j < prod->right_side_length - 1) {
                    strcat(prod_string, " ");
                }
            }
            printf("\n");
        }
        
        // Compute FIRST(α)
        SymbolSet first_alpha;
        first_alpha.count = 0;
        first_alpha.has_epsilon = false;
        
        if (prod->right_side_length == 0 || prod->right_side[0].type == SYM_EPSILON) {
            // A -> ε
            first_alpha.has_epsilon = true;
        } else {
            // Compute FIRST of the production
            for (int j = 0; j < prod->right_side_length; j++) {
                GrammarSymbol sym = prod->right_side[j];
                
                if (sym.type == SYM_TERMINAL) {
                    addToSet(&first_alpha, sym.value.terminal);
                    break;
                } else if (sym.type == SYM_NONTERMINAL) {
                    SymbolSet* first_nt = &ff_table->first_sets[sym.value.non_terminal];
                    unionSets(&first_alpha, first_nt);
                    
                    // If this non-terminal can't derive epsilon, stop
                    if (!first_nt->has_epsilon) {
                        break;
                    }
                    
                    // If last symbol and can derive epsilon
                    if (j == prod->right_side_length - 1 && first_nt->has_epsilon) {
                        first_alpha.has_epsilon = true;
                    }
                }
            }
        }
        
        // For each terminal a in FIRST(α), add A -> α to Table[A, a]
        printf("  FIRST(α) = ");
        printSymbolSet(&first_alpha);
        printf("\n");
        
        for (int j = 0; j < first_alpha.count; j++) {
            TokenType terminal = first_alpha.terminals[j];
            
            // Add entry to table
            parser->parse_table[parser->table_size].non_terminal = A;
            parser->parse_table[parser->table_size].terminal = terminal;
            parser->parse_table[parser->table_size].rule_number = prod->rule_number;
            strcpy(parser->parse_table[parser->table_size].production, prod_string);
            
            printf("  Table[%s, %s] = Rule %d\n", 
                   nonTerminalToString(A), 
                   tokenTypeToString(terminal),
                   prod->rule_number);
            
            parser->table_size++;
        }
        
        // If ε in FIRST(α), for each b in FOLLOW(A), add A -> α to Table[A, b]
        if (first_alpha.has_epsilon) {
            printf("  ε in FIRST(α), using FOLLOW(%s) = ", nonTerminalToString(A));
            printSymbolSet(&ff_table->follow_sets[A]);
            printf("\n");
            
            SymbolSet* follow_A = &ff_table->follow_sets[A];
            for (int j = 0; j < follow_A->count; j++) {
                TokenType terminal = follow_A->terminals[j];
                
                // Add entry to table
                parser->parse_table[parser->table_size].non_terminal = A;
                parser->parse_table[parser->table_size].terminal = terminal;
                parser->parse_table[parser->table_size].rule_number = prod->rule_number;
                strcpy(parser->parse_table[parser->table_size].production, prod_string);
                
                printf("  Table[%s, %s] = Rule %d (via FOLLOW)\n", 
                       nonTerminalToString(A), 
                       tokenTypeToString(terminal),
                       prod->rule_number);
                
                parser->table_size++;
            }
        }
    }
    
    printf("\n========== LL(1) TABLE GENERATED ==========\n");
    printf("Total entries in parse table: %d\n", parser->table_size);
}
