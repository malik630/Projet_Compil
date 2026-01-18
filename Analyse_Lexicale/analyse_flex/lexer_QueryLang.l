%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========================================================================== */
/*                         TABLE DES SYMBOLES COMPLÈTE                        */
/* ========================================================================== */

typedef enum {
    SCOPE_GLOBAL,
    SCOPE_LOCAL,
    SCOPE_BLOCK
} ScopeLevel;

typedef enum {
    CAT_VARIABLE,
    CAT_CONSTANT,
    CAT_ARRAY,
    CAT_RECORD,
    CAT_FUNCTION
} SymbolCategory;

typedef struct FieldEntry {
    char name[64];
    char type[64];
    int offset;
    struct FieldEntry* next;
} FieldEntry;

typedef struct SymbolEntry {
    char name[256];
    char type[64];
    SymbolCategory category;
    int line;
    int column;
    ScopeLevel scope;
    int scope_id;
    
    int is_array;
    int array_size;
    char element_type[64];
    
    int is_record;
    FieldEntry* fields;
    int field_count;
    
    int is_constant;
    char constant_value[256];
    
    int address;
    int size;
    int is_initialized;
    int usage_count;
    int is_used;
    
    struct SymbolEntry* next;
} SymbolEntry;

typedef struct {
    SymbolEntry* head;
    int count;
    int current_scope_id;
    int next_address;
} SymbolTable;

/* ========================================================================== */
/*                         GESTION DES ERREURS                                */
/* ========================================================================== */

typedef enum {
    ERR_LEXICAL,
    ERR_INVALID_CHAR,
    ERR_UNTERMINATED_STRING,
    ERR_UNTERMINATED_COMMENT,
    ERR_INVALID_NUMBER,
    ERR_IDENTIFIER_TOO_LONG,
    ERR_STRING_TOO_LONG
} ErrorType;

typedef struct ErrorEntry {
    ErrorType type;
    int line;
    int column;
    char message[512];
    char context[128];
    struct ErrorEntry* next;
} ErrorEntry;

typedef struct {
    ErrorEntry* head;
    int count;
    int max_errors;
    int panic_mode;
} ErrorManager;

/* Variables globales */
SymbolTable symTable = {NULL, 0, 0, 0};
ErrorManager errorMgr = {NULL, 0, 50, 0};
int line_num = 1;
int col_num = 1;

/* ========================================================================== */
/*                    FONCTIONS - TABLE DES SYMBOLES                          */
/* ========================================================================== */

void initSymbolTable() {
    symTable.head = NULL;
    symTable.count = 0;
    symTable.current_scope_id = 0;
    symTable.next_address = 0;
}

void enterScope() {
    symTable.current_scope_id++;
     printf("-----------------[Level] Enter scope → %d\n", symTable.current_scope_id);
}

void exitScope() {
    SymbolEntry* curr = symTable.head;
    while (curr != NULL) {
        if (curr->scope_id == symTable.current_scope_id && !curr->is_used) {
            fprintf(stderr, "Warning: Variable '%s' declared at line %d but never used\n", 
                    curr->name, curr->line);
        }
        curr = curr->next;
    }
    symTable.current_scope_id--;
    printf("-----------------[Level] Exit scope → %d\n", symTable.current_scope_id);
}

SymbolEntry* searchSymbol(const char* name) {
    SymbolEntry* curr = symTable.head;
    
    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0 && 
            curr->scope_id == symTable.current_scope_id) {
            return curr;
        }
        curr = curr->next;
    }
    
    curr = symTable.head;
    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0 && 
            curr->scope_id < symTable.current_scope_id) {
            return curr;
        }
        curr = curr->next;
    }
    
    return NULL;
}

void insertSymbol(const char* name, const char* type, SymbolCategory category) {
    SymbolEntry* existing = searchSymbol(name);
    if (existing && existing->scope_id == symTable.current_scope_id) {
        fprintf(stderr, "File \"source.ql\", line %d, col %d: Symbol '%s' already declared at line %d\n",
                line_num, col_num, name, existing->line);
        errorMgr.count++;
        return;
    }
    
    SymbolEntry* newEntry = (SymbolEntry*)malloc(sizeof(SymbolEntry));
    strcpy(newEntry->name, name);
    strcpy(newEntry->type, type);
    newEntry->category = category;
    newEntry->line = line_num;
    newEntry->column = col_num;
    newEntry->scope = (symTable.current_scope_id == 0) ? SCOPE_GLOBAL : SCOPE_LOCAL;
    newEntry->scope_id = symTable.current_scope_id;
    
    newEntry->is_array = 0;
    newEntry->array_size = 0;
    newEntry->element_type[0] = '\0';
    newEntry->is_record = 0;
    newEntry->fields = NULL;
    newEntry->field_count = 0;
    newEntry->is_constant = 0;
    newEntry->constant_value[0] = '\0';
    
    newEntry->address = symTable.next_address;
    newEntry->size = 1;
    symTable.next_address += newEntry->size;
    
    newEntry->is_initialized = 0;
    newEntry->usage_count = 0;
    newEntry->is_used = 0;
    
    newEntry->next = symTable.head;
    symTable.head = newEntry;
    symTable.count++;
}

void markSymbolUsed(const char* name) {
    SymbolEntry* symbol = searchSymbol(name);
    if (symbol) {
        symbol->is_used = 1;
        symbol->usage_count++;
    }
}

void addArrayInfo(const char* name, const char* elem_type, int size) {
    SymbolEntry* symbol = searchSymbol(name);
    if (symbol) {
        symbol->is_array = 1;
        strcpy(symbol->element_type, elem_type);
        symbol->array_size = size;
        symbol->size = size;
    }
}

void displaySymbolTable() {
    printf("\n╔════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              TABLE DES SYMBOLES                                    ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n\n");
    printf("%-20s %-12s %-10s %-8s %-6s %-8s %-6s\n", 
           "Nom", "Type", "Catégorie", "Portée", "Ligne", "Adresse", "Utilisé");
    printf("─────────────────────────────────────────────────────────────────────────────────────\n");
    
    SymbolEntry* curr = symTable.head;
    while (curr != NULL) {
        const char* category_str = "";
        switch(curr->category) {
            case CAT_VARIABLE: category_str = "Variable"; break;
            case CAT_CONSTANT: category_str = "Constante"; break;
            case CAT_ARRAY: category_str = "Tableau"; break;
            case CAT_RECORD: category_str = "Record"; break;
            case CAT_FUNCTION: category_str = "Fonction"; break;
        }
        
        const char* scope_str = (curr->scope == SCOPE_GLOBAL) ? "Globale" : "Locale";
        const char* used_str = curr->is_used ? "Oui" : "Non";
        
        printf("%-20s %-12s %-10s %-8s %-6d %-8d %-6s", 
               curr->name, curr->type, category_str, scope_str, 
               curr->line, curr->address, used_str);
        
        if (curr->is_array) {
            printf("  [%d]", curr->array_size);
        }
        if (curr->is_record) {
            printf("  {%d champs}", curr->field_count);
        }
        printf("\n");
        
        if (curr->is_record && curr->fields) {
            FieldEntry* field = curr->fields;
            while (field != NULL) {
                printf("    └─ %-16s %-12s (offset: %d)\n", 
                       field->name, field->type, field->offset);
                field = field->next;
            }
        }
        
        curr = curr->next;
    }
    
    printf("─────────────────────────────────────────────────────────────────────────────────────\n");
    printf("Total: %d symbole(s) | Adresse mémoire suivante: %d\n\n", 
           symTable.count, symTable.next_address);
}

/* ========================================================================== */
/*                    FONCTIONS - GESTION DES ERREURS                         */
/* ========================================================================== */

void initErrorManager() {
    errorMgr.head = NULL;
    errorMgr.count = 0;
    errorMgr.max_errors = 50;
    errorMgr.panic_mode = 0;
}

void reportError(ErrorType type, const char* message, const char* context) {
    if (errorMgr.count >= errorMgr.max_errors) {
        if (!errorMgr.panic_mode) {
            fprintf(stderr, "\n*** Trop d'erreurs détectées. Analyse abandonnée. ***\n");
            errorMgr.panic_mode = 1;
        }
        return;
    }
    
    const char* error_type_str = "";
    switch(type) {
        case ERR_LEXICAL: error_type_str = "lexical error"; break;
        case ERR_INVALID_CHAR: error_type_str = "invalid character"; break;
        case ERR_UNTERMINATED_STRING: error_type_str = "unterminated string"; break;
        case ERR_UNTERMINATED_COMMENT: error_type_str = "unterminated comment"; break;
        case ERR_INVALID_NUMBER: error_type_str = "invalid number format"; break;
        case ERR_IDENTIFIER_TOO_LONG: error_type_str = "identifier too long"; break;
        case ERR_STRING_TOO_LONG: error_type_str = "string literal too long"; break;
    }
    
    fprintf(stderr, "File \"source.ql\", line %d, character %d: %s: %s",
            line_num, col_num, error_type_str, message);
    
    if (context && context[0] != '\0') {
        fprintf(stderr, " (near '%s')", context);
    }
    fprintf(stderr, "\n");
    
    errorMgr.count++;
}

void displayErrorSummary() {
    printf("\n╔════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              RÉSUMÉ DES ERREURS                                    ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n\n");
    
    if (errorMgr.count == 0) {
        printf("✓ Aucune erreur lexicale détectée.\n");
    } else {
        printf("✗ %d erreur(s) lexicale(s) détectée(s)\n", errorMgr.count);
    }
    printf("\n");
}

/* ========================================================================== */
/*                         FONCTIONS UTILITAIRES                              */
/* ========================================================================== */

void printToken(const char* type, const char* lexeme) {
    printf("Line %3d, Col %3d: %-20s '%s'\n", line_num, col_num, type, lexeme);
    col_num += strlen(lexeme);
}

/* Context tracking pour détection d'erreurs sémantiques simples */
char last_identifier[256] = "";
char last_type[64] = "";
int in_declaration = 0;

%}

/* Définitions */
DIGIT           [0-9]
LETTER          [a-zA-Z]
IDENTIFIER      {LETTER}({LETTER}|{DIGIT}|_)*
INTEGER         {DIGIT}+
FLOAT           {DIGIT}+\.{DIGIT}+
STRING          '([^'\n]|'')*'
WHITESPACE      [ \t\r]+
NEWLINE         \n
COMMENT_LINE    --[^\n]*
COMMENT_MULTI   \/\*([^*]|\*+[^*/])*\*+\/

%%

    /* Commentaires */
{COMMENT_LINE}      { printToken("COMMENT", "-- ..."); }
{COMMENT_MULTI}     { 
                        printToken("COMMENT", "/* ... */");
                        for (int i = 0; i < yyleng; i++) {
                            if (yytext[i] == '\n') {
                                line_num++;
                                col_num = 1;
                            }
                        }
                    }

    /* Mots-clés du programme */
"BEGIN"             { printToken("KW_BEGIN", yytext); }
"PROGRAM"           { printToken("KW_PROGRAM", yytext); }
"END"               { printToken("KW_END", yytext); }

    /* Mots-clés de déclaration */
"SET"               { printToken("KW_SET", yytext); in_declaration = 1; }
"CREATE"            { printToken("KW_CREATE", yytext); }
"RECORD"            { printToken("KW_RECORD", yytext); }
"ARRAY"             { printToken("KW_ARRAY", yytext); }
"DICTIONARY"        { printToken("KW_DICTIONARY", yytext); }

    /* Types */
"INTEGER"           { 
                        printToken("KW_INTEGER", yytext); 
                        if (in_declaration && last_identifier[0] != '\0') {
                            insertSymbol(last_identifier, "INTEGER", CAT_VARIABLE);
                            last_identifier[0] = '\0';
                            in_declaration = 0;
                        }
                        strcpy(last_type, "INTEGER");
                    }
"STRING"            { 
                        printToken("KW_STRING", yytext); 
                        if (in_declaration && last_identifier[0] != '\0') {
                            insertSymbol(last_identifier, "STRING", CAT_VARIABLE);
                            last_identifier[0] = '\0';
                            in_declaration = 0;
                        }
                        strcpy(last_type, "STRING");
                    }
"FLOAT"             { 
                        printToken("KW_FLOAT", yytext); 
                        if (in_declaration && last_identifier[0] != '\0') {
                            insertSymbol(last_identifier, "FLOAT", CAT_VARIABLE);
                            last_identifier[0] = '\0';
                            in_declaration = 0;
                        }
                        strcpy(last_type, "FLOAT");
                    }
"BOOLEAN"           { 
                        printToken("KW_BOOLEAN", yytext); 
                        if (in_declaration && last_identifier[0] != '\0') {
                            insertSymbol(last_identifier, "BOOLEAN", CAT_VARIABLE);
                            last_identifier[0] = '\0';
                            in_declaration = 0;
                        }
                        strcpy(last_type, "BOOLEAN");
                    }

    /* Valeurs booléennes */
"true"              { printToken("KW_TRUE", yytext); }
"false"             { printToken("KW_FALSE", yytext); }

    /* Structures de contrôle */
 "LOOP WHEN"              { printToken("KW_LOOP KW_WHEN", yytext); enterScope(); }
    
"WHEN"              { printToken("KW_WHEN", yytext); enterScope();}
"THEN"              { printToken("KW_THEN", yytext);  }
"OTHERWISE"         { printToken("KW_OTHERWISE", yytext); }


"CASE"              { printToken("KW_CASE", yytext); enterScope(); }
"CASEWHEN"              { printToken("KW_CASE_WHEN", yytext);}
"ELSE"              { printToken("KW_ELSE", yytext); }


    /* Boucles */
"LOOP"              { printToken("KW_LOOP", yytext); enterScope(); }
"ITERATE"           { printToken("KW_ITERATE", yytext); }
"FROM"              { printToken("KW_FROM", yytext); }
"TO"                { printToken("KW_TO", yytext); }

"END LOOP"   { printToken("KW_END_LOOP", yytext); exitScope(); }
"END CASE"   { printToken("KW_END_CASE", yytext); exitScope(); }
"END WHEN"   { printToken("KW_END_CASE", yytext); exitScope(); }

    /* Entrée/Sortie */
"PRINT"             { printToken("KW_PRINT", yytext); }
"INPUT"             { printToken("KW_INPUT", yytext); }

    /* Opérateurs logiques */
"AND"               { printToken("OP_AND", yytext); }
"OR"                { printToken("OP_OR", yytext); }
"NOT"               { printToken("OP_NOT", yytext); }

    /* Opérateurs de comparaison */
"="                 { printToken("OP_EQ", yytext); }
"<>"                { printToken("OP_NEQ", yytext); }
"<"                 { printToken("OP_LT", yytext); }
">"                 { printToken("OP_GT", yytext); }
"<="                { printToken("OP_LTE", yytext); }
">="                { printToken("OP_GTE", yytext); }

    /* Opérateurs arithmétiques */
"+"                 { printToken("OP_PLUS", yytext); }
"-"                 { printToken("OP_MINUS", yytext); }
"*"                 { printToken("OP_MULT", yytext); }
"/"                 { printToken("OP_DIV", yytext); }
"%"                 { printToken("OP_MOD", yytext); }

    /* Séparateurs */
"("                 { printToken("SEP_LPAREN", yytext); }
")"                 { printToken("SEP_RPAREN", yytext); }
"["                 { printToken("SEP_LBRACKET", yytext); }
"]"                 { printToken("SEP_RBRACKET", yytext); }
"{"                 { printToken("SEP_LBRACE", yytext); }
"}"                 { printToken("SEP_RBRACE", yytext); }
","                 { printToken("SEP_COMMA", yytext); }
";"                 { printToken("SEP_SEMICOLON", yytext); in_declaration = 0; }
"."                 { printToken("SEP_DOT", yytext); }

    /* Identificateurs */
{IDENTIFIER}        { 
                        if (yyleng > 255) {
                            reportError(ERR_IDENTIFIER_TOO_LONG, 
                                      "Identifier exceeds maximum length (255)", yytext);
                        } else {
                            printToken("IDENTIFIER", yytext);
                            if (in_declaration) {
                                strcpy(last_identifier, yytext);
                            } else {
                                markSymbolUsed(yytext);
                            }
                        }
                    }

    /* Littéraux numériques */
{INTEGER}           { 
                        printToken("INT_LITERAL", yytext); 
                    }

{FLOAT}             { 
                        printToken("FLOAT_LITERAL", yytext); 
                    }

    /* Chaînes de caractères */
{STRING}            { 
                        if (yyleng > 257) {  /* 255 + 2 quotes */
                            reportError(ERR_STRING_TOO_LONG,
                                      "String literal exceeds maximum length (255)", NULL);
                        } else {
                            printToken("STRING_LITERAL", yytext); 
                        }
                    }

    /* Chaîne non terminée */
'[^\n']*$           {
                        reportError(ERR_UNTERMINATED_STRING,
                                  "String literal not terminated before end of line", yytext);
                    }

    /* Commentaire multi-ligne non terminé */
\/\*([^*]|\*+[^*/])*$  {
                        reportError(ERR_UNTERMINATED_COMMENT,
                                  "Multi-line comment not terminated", "/* ...");
                    }

    /* Espaces blancs */
{WHITESPACE}        { col_num += yyleng; }
{NEWLINE}           { line_num++; col_num = 1; }

    /* Erreurs lexicales */
.                   { 
                        char error_msg[256];
                        sprintf(error_msg, "Unexpected character '%s'", yytext);
                        reportError(ERR_INVALID_CHAR, error_msg, yytext);
                        col_num++;
                    }

%%

int yywrap() {
    return 1;
}

int main(int argc, char** argv) {
    FILE* input_file = NULL;
    
    printf("╔════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║           ANALYSEUR LEXICAL COMPLET - QueryLang (Version FLEX)                    ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n\n");
    
    if (argc > 1) {
        input_file = fopen(argv[1], "r");
        if (!input_file) {
            fprintf(stderr, "Erreur: Impossible d'ouvrir le fichier '%s'\n", argv[1]);
            return 1;
        }
        yyin = input_file;
        printf("Analyse du fichier: %s\n\n", argv[1]);
    } else {
        printf("Usage: %s <fichier_source.ql>\n", argv[0]);
        printf("Mode interactif: Entrez votre code (Ctrl+D pour terminer)\n\n");
    }
    
    initSymbolTable();
    initErrorManager();
    
    printf("╔════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                    TOKENS                                          ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n\n");
    
    yylex();
    
    if (input_file) {
        fclose(input_file);
    }
    
    // Affichage des résultats
    displaySymbolTable();
    displayErrorSummary();
    
    printf("╔════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                  STATISTIQUES                                      ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n\n");
    printf("Lignes analysées: %d\n", line_num);
    printf("Symboles dans la table: %d\n", symTable.count);
    printf("Erreurs lexicales: %d\n\n", errorMgr.count);
    
    if (errorMgr.count == 0) {
        printf("nalyse lexicale terminée avec succès!\n\n");
        return 0;
    } else {
        printf("Analyse lexicale terminée avec %d erreur(s).\n\n", errorMgr.count);
        return 1;
    }
}