#ifndef LL1_PARSER_H
#define LL1_PARSER_H

#include "structures.h"
#include "lexer.h"
#include "symbol_table.h"
#include "error_manager.h"

// Non-terminals enumeration
typedef enum {
    NT_PROGRAM,
    NT_DECLS,
    NT_DECL,
    NT_TYPE,
    NT_OPTINIT,
    NT_INSTRS,
    NT_INSTR,
    NT_ASSIGN,
    NT_PRINT,
    NT_WHEN,
    NT_OPTOTHERWISE,
    NT_EXPR,
    NT_EXPRPRIME,
    NT_TERM,
    NT_TERMPRIME,
    NT_FACTOR,
    NT_COND,
    NT_RELOP,
    NT_COUNT
} NonTerminal;

// LL(1) table entry
typedef struct {
    NonTerminal non_terminal;
    TokenType terminal;
    int rule_number;
    char production[256];
} LL1TableEntry;

// Stack structures
#define MAX_STACK_SIZE 1000

typedef enum {
    SYMBOL_TERMINAL,
    SYMBOL_NONTERMINAL,
    SYMBOL_EOF
} SymbolKind;

typedef struct {
    SymbolKind kind;
    union {
        TokenType terminal;
        NonTerminal non_terminal;
    } value;
} StackSymbol;

typedef struct {
    StackSymbol symbols[MAX_STACK_SIZE];
    int top;
} ParseStack;

// AST Node
typedef struct ASTNode {
    NonTerminal type;
    Token token;
    struct ASTNode** children;
    int child_count;
    int capacity;
} ASTNode;

// LL(1) Parser structure
typedef struct {
    Token* tokens;
    int token_count;
    int current_token;
    
    LL1TableEntry* parse_table;
    int table_size;
    
    ParseStack stack;
    ASTNode* ast_root;
    
    SymbolTable* symbol_table;
    ErrorManager* error_manager;
    
    char current_identifier[256];
    char current_type[64];
    bool in_declaration;
    
    int parse_errors;
    int semantic_errors;
} LL1Parser;

// Main parser functions
LL1Parser* createLL1Parser(Token* tokens, int count);
void freeLL1Parser(LL1Parser* parser);
bool parseLL1(LL1Parser* parser);

// Stack operations
void initStack(ParseStack* stack);
void pushStack(ParseStack* stack, StackSymbol symbol);
StackSymbol popStack(ParseStack* stack);
StackSymbol peekStack(ParseStack* stack);
bool isStackEmpty(ParseStack* stack);
void printStack(ParseStack* stack);

// Table operations
void initLL1Table(LL1Parser* parser);
LL1TableEntry* lookupLL1Table(LL1Parser* parser, NonTerminal nt, TokenType term);

// Utility functions
const char* nonTerminalToString(NonTerminal nt);
const char* tokenTypeToString(TokenType type);
TokenType stringToTokenType(const char* str);
NonTerminal stringToNonTerminal(const char* str);

// Semantic actions
void executeSemanticAction(LL1Parser* parser, int rule_number);

// Error handling
void reportSyntaxError(LL1Parser* parser, const char* message);

// Production handling
void pushProduction(ParseStack* stack, const char* production);
StackSymbol stringToSymbol(const char* str);

#endif
