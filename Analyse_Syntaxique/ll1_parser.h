#ifndef LL1_PARSER_H
#define LL1_PARSER_H

#include "structures.h"      // struct existantes
#include "lexer.h"           // analyseur lexicla
#include "symbol_table.h"    // Table des symboles
#include "error_manager.h"   // handling errors


// enumererr les non termiveaux


typedef enum {
    NT_PROGRAM,      // Program
    NT_DECLS,        // Decls
    NT_DECL,         // Decl
    NT_TYPE,         // Type
    NT_OPTINIT,      // OptInit
    NT_INSTRS,       // Instrs
    NT_INSTR,        // Instr
    NT_ASSIGN,       // Assign
    NT_PRINT,        // Print
    NT_IF,           // If
    NT_OPTELSE,      // OptElse
    NT_EXPR,         // Expr
    NT_EXPRPRIME,    // ExprPrime
    NT_TERM,         // Term
    NT_TERMPRIME,    // TermPrime
    NT_FACTOR,       // Factor
    NT_COND,         // Cond
    NT_RELOP,        // RelOp
    NT_COUNT         // Nombre total de non-terminaux
} NonTerminal;


// struct dentre dune table ll1


typedef struct {
    NonTerminal non_terminal;    // Non-terminal (ligne)
    TokenType terminal;          // Terminal (colonne)
    int rule_number;             // Numéro de la règle (1-40)
    char production[256];        // Production 
} LL1TableEntry;


// struct pile analyse


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


// Struct arbre syntaxique


typedef struct ASTNode {
    NonTerminal type;           // Type du nœud
    Token token;                // Token feuile
    struct ASTNode** children;  // Enfants
    int child_count;            // Nombre d'enfants
    int capacity;               // Capacité du tableau d'enfants
} ASTNode;


// struct parser ll1


typedef struct {
    // Tokens d'entrée
    Token* tokens;
    int token_count;
    int current_token;
    
    // Table d'analyse LL(1)
    LL1TableEntry* parse_table;
    int table_size;
    
    // Pile 
    ParseStack stack;
    
    // Arbre syntaxique
    ASTNode* ast_root;
    
   
    SymbolTable* symbol_table;
    ErrorManager* error_manager;
    
   
    char current_identifier[256];
    char current_type[64];
    bool in_declaration;
    
    //handling errors
    int parse_errors;
    int semantic_errors;
    
} LL1Parser;

//functions
// init
LL1Parser* createLL1Parser(Token* tokens, int count);
void freeLL1Parser(LL1Parser* parser);
bool parseLL1(LL1Parser* parser);

// gest pile
void initStack(ParseStack* stack);
void pushStack(ParseStack* stack, StackSymbol symbol);
StackSymbol popStack(ParseStack* stack);
StackSymbol peekStack(ParseStack* stack);
bool isStackEmpty(ParseStack* stack);
void printStack(ParseStack* stack);

// gest table ll1
void initLL1Table(LL1Parser* parser);
LL1TableEntry* lookupLL1Table(LL1Parser* parser, NonTerminal nt, TokenType term);
const char* nonTerminalToString(NonTerminal nt);
const char* tokenTypeToString(TokenType type);
bool isTerminal(StackSymbol symbol);
bool matchTerminal(TokenType stack_term, TokenType input_term);
void executeSemanticAction(LL1Parser* parser, int rule_number);
// errors handling 
void reportSyntaxError(LL1Parser* parser, const char* message);
void recoverFromError(LL1Parser* parser);

void printParseTree(ASTNode* root, int depth);
void printLL1Table(LL1Parser* parser);

#endif 