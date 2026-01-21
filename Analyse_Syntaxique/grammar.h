#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "ll1_parser.h"
#include <stdbool.h>

// Represent a grammar symbol (terminal or non-terminal)
typedef enum {
    SYM_TERMINAL,
    SYM_NONTERMINAL,
    SYM_EPSILON
} SymbolType;

typedef struct {
    SymbolType type;
    union {
        TokenType terminal;
        NonTerminal non_terminal;
    } value;
} GrammarSymbol;

// Represent a single production rule
typedef struct {
    NonTerminal left_side;           // Left-hand side (A)
    GrammarSymbol* right_side;       // Right-hand side (α)
    int right_side_length;           // Number of symbols in α
    int rule_number;                 // Rule number for identification
} Production;

// Complete grammar
typedef struct {
    Production* productions;         // All production rules
    int production_count;            // Number of productions
    int max_productions;             // Capacity
    NonTerminal start_symbol;        // Starting non-terminal
} Grammar;

// Set of symbols (for FIRST and FOLLOW)
typedef struct {
    TokenType terminals[100];        // Terminal symbols
    int count;                       // Number of terminals
    bool has_epsilon;                // Whether ε is in the set
} SymbolSet;

// FIRST and FOLLOW tables
typedef struct {
    SymbolSet first_sets[NT_COUNT];
    SymbolSet follow_sets[NT_COUNT];
} FirstFollowTable;

// Functions
Grammar* createGrammar();
void addProduction(Grammar* grammar, NonTerminal left, GrammarSymbol* right, int length);
void freeGrammar(Grammar* grammar);
void printGrammar(Grammar* grammar);

// Helper functions to create symbols
GrammarSymbol makeTerminal(TokenType token);
GrammarSymbol makeNonTerminal(NonTerminal nt);
GrammarSymbol makeEpsilon();

// Initialize grammar with rules
void initializeGrammarRules(Grammar* grammar);

// FIRST and FOLLOW computation
FirstFollowTable* computeFirstFollow(Grammar* grammar);
void freeFirstFollowTable(FirstFollowTable* table);
void printFirstFollowTable(FirstFollowTable* table);

// Check if a symbol/production can derive epsilon
bool canDeriveEpsilon(Grammar* grammar, GrammarSymbol symbol, bool* nullable);
bool canProductionDeriveEpsilon(Grammar* grammar, GrammarSymbol* symbols, int length, bool* nullable);

// LL(1) table generation
void generateLL1Table(Grammar* grammar, FirstFollowTable* ff_table, LL1Parser* parser);

// Helper: Add symbol to set
void addToSet(SymbolSet* set, TokenType terminal);
bool isInSet(SymbolSet* set, TokenType terminal);
void unionSets(SymbolSet* dest, SymbolSet* src);
void printSymbolSet(SymbolSet* set);

#endif
