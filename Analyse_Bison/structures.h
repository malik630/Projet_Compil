#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdbool.h>

// ============================================================================
// CONSTANTES
// ============================================================================

#define MAX_STATES 100
#define MAX_TRANSITIONS 500
#define EPSILON -1

// ============================================================================
// STRUCTURES POUR AFN (Automate Fini Non-déterministe)
// ============================================================================

typedef struct {
    int from_state;
    int to_state;
    int symbol;
} Transition;

typedef struct {
    int states[MAX_STATES];
    int count;
    Transition transitions[MAX_TRANSITIONS];
    int trans_count;
    int start_state;
    int final_states[MAX_STATES];
    int final_count;
    int state_count;
} AFN;

// ============================================================================
// STRUCTURES POUR AFD (Automate Fini Déterministe)
// ============================================================================

typedef struct {
    int states[MAX_STATES];
    int count;
} StateSet;

typedef struct {
    StateSet states[MAX_STATES];
    int state_count;
    int transitions[MAX_STATES][256];
    int start_state;
    bool final_states[MAX_STATES];
} AFD;

// ============================================================================
// TYPES DE TOKENS
// ============================================================================

typedef enum {
    KW_BEGIN, KW_PROGRAM, KW_END, KW_SET, KW_INTEGER, KW_STRING,
    KW_FLOAT, KW_BOOLEAN, KW_TRUE, KW_FALSE, KW_CREATE, KW_RECORD,
    KW_ARRAY, KW_DICTIONARY, KW_WHEN, KW_THEN, KW_OTHERWISE, KW_END_WHEN,
    KW_CASE, KW_ELSE, KW_END_CASE, KW_LOOP, KW_END_LOOP, KW_ITERATE,
    KW_FROM, KW_TO, KW_PRINT, KW_INPUT, KW_AND, KW_OR, KW_NOT,
    OP_PLUS, OP_MINUS, OP_MULT, OP_DIV, OP_MOD,
    OP_EQ_TOK, OP_NEQ_TOK, OP_LT_TOK, OP_GT_TOK, OP_LTE_TOK, OP_GTE_TOK,
    SEP_LPAREN, SEP_RPAREN, SEP_LBRACKET, SEP_RBRACKET,
    SEP_LBRACE, SEP_RBRACE, SEP_COMMA, SEP_SEMICOLON, SEP_DOT,
    IDENTIFIER, INT_LITERAL, FLOAT_LITERAL, STRING_LITERAL,
    COMMENT, END_OF_FILE, ERROR_TOK
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[256];
    int line;
    int column;
} Token;

// ============================================================================
// TABLE DES SYMBOLES
// ============================================================================

typedef struct SymbolEntry {
    char name[256];
    char type[64];
    int line;
    struct SymbolEntry* next;
} SymbolEntry;

typedef struct {
    SymbolEntry* head;
    int count;
} SymbolTable;

// ============================================================================
// GESTION DES ERREURS
// ============================================================================

typedef struct ErrorEntry {
    int line;
    int column;
    char message[512];
    struct ErrorEntry* next;
} ErrorEntry;

typedef struct {
    ErrorEntry* head;
    int count;
} ErrorManager;

#endif // STRUCTURES_H