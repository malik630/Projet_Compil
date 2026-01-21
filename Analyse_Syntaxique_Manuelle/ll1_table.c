#include "ll1_parser.h"
#include "grammar.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Updated initLL1Table to use automatic generation
void initLL1Table(LL1Parser* parser) {
    printf("\n[LL1 TABLE] Initializing LL(1) parse table...\n");
    
    // Create grammar
    Grammar* grammar = createGrammar();
    initializeGrammarRules(grammar);
    
    // Print grammar
    printGrammar(grammar);
    
    // Compute FIRST and FOLLOW sets
    FirstFollowTable* ff_table = computeFirstFollow(grammar);
    
    // Print FIRST and FOLLOW sets
    printFirstFollowTable(ff_table);
    
    // Generate LL(1) parse table
    generateLL1Table(grammar, ff_table, parser);
    
    // Clean up
    freeFirstFollowTable(ff_table);
    freeGrammar(grammar);
    
    printf("[LL1 TABLE] Parse table initialization complete!\n");
}

LL1TableEntry* lookupLL1Table(LL1Parser* parser, NonTerminal nt, TokenType term) {
    for (int i = 0; i < parser->table_size; i++) {
        if (parser->parse_table[i].non_terminal == nt &&
            parser->parse_table[i].terminal == term) {
            return &parser->parse_table[i];
        }
    }
    return NULL;  
}
