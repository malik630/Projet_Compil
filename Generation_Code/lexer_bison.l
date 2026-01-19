%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "parser.tab.h"
#include "global.h"
#include "table_symboles_enrichie.h"

int line_num = 1;
int col_num = 1;

int nb_identifiers_found = 0;
int nb_keywords_found = 0;
int nb_literals_found = 0;

// Variable pour tracker le contexte
int after_program_keyword = 0;   // Pour ignorer le nom du programme
int after_record_keyword = 0;    // Pour ignorer le nom du type de record
int inside_record_decl = 0;      // Pour ignorer les champs du record

// Compteur pour générer des noms uniques pour les constantes
int constant_counter = 0;

// Fonction pour insérer un identificateur dans la table des symboles
void lexer_insert_identifier(char* name) {
    if (after_program_keyword) {
        printf("[LEXER] '%s' est le nom du programme (non ajouté à la table)\n", name);
        after_program_keyword = 0;
        return;
    }

    if (after_record_keyword) {
        printf("[LEXER] '%s' est un type RECORD (non ajouté à la table)\n", name);
        after_record_keyword = 0;
        inside_record_decl = 1;  // On entre dans la déclaration
        return;
    }
    
    if (inside_record_decl) {
        printf("[LEXER] '%s' est un champ de record (non ajouté à la table)\n", name);
        return;
    }

    Symbole* existing = obtenirSymbole(&tableGlobale, name);
    
    if (existing == NULL) {
        Symbole sym;
        strcpy(sym.nom, name);
        sym.typeSymbole = TYPE_VARIABLE;
        sym.typeDonnee = DATA_ENTIER;
        sym.portee = tableGlobale.niveauPortee;
        sym.adresse = -1;
        sym.initialise = 0;
        sym.line = line_num;
        sym.column = col_num;
        sym.taille = 0;
        
        int result = insererSymbole(&tableGlobale, sym);
        if (result != -1) {
            printf("[LEXER] Nouvel identificateur '%s' ajouté à la table (L%d:C%d)\n", 
                   name, line_num, col_num);
        }
    } else {
        printf("[LEXER] Identificateur '%s' déjà dans la table (déclaré L%d)\n", 
               name, existing->line);
    }
}

// Fonction pour insérer une constante dans la table des symboles
void lexer_insert_constant(char* name, TypeDonnee type, void* value) {
    Symbole sym;
    
    // Générer un nom unique pour la constante
    sprintf(sym.nom, "_const_%d", constant_counter++);
    
    sym.typeSymbole = TYPE_CONSTANTE;
    sym.typeDonnee = type;
    sym.portee = PORTEE_GLOBALE;  // Les constantes sont globales
    sym.adresse = obtenirProchaineAdresse(&tableGlobale); ;
    sym.initialise = 1;  // Une constante est toujours initialisée
    sym.line = line_num;
    sym.column = col_num;
    sym.taille = 0;
    
    // Stocker la valeur selon le type
    switch(type) {
        case DATA_ENTIER:
            sym.valeur.valeurInt = *((int*)value);
            break;
        case DATA_REEL:
            sym.valeur.valeurReel = *((float*)value);
            break;
        case DATA_CHAINE:
            // Retirer les guillemets si présents
            if (strlen((char*)value) > 0 && ((char*)value)[0] == '\'') {
                char temp[100];
                strncpy(temp, (char*)value + 1, strlen((char*)value) - 2);
                temp[strlen((char*)value) - 2] = '\0';
                strcpy(sym.valeur.valeurChaine, temp);
            } else {
                strcpy(sym.valeur.valeurChaine, (char*)value);
            }
            break;
        case DATA_BOOLEEN:
            sym.valeur.valeurBool = *((int*)value);
            break;
        default:
            break;
    }
    
    int result = insererSymbole(&tableGlobale, sym);
    if (result != -1) {
        printf("[LEXER] Constante '%s' (valeur: %s) ajoutée à la table (L%d:C%d)\n", 
               name, name, line_num, col_num);
    }
}
%}

%option noyywrap

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

{COMMENT_LINE}   { /* ignore */ }
{COMMENT_MULTI}  { 
                    for (int i = 0; i < yyleng; i++) {
                        if (yytext[i] == '\n') {
                            line_num++;
                            col_num = 1;
                        } else {
                            col_num++;
                        }
                    }
                }

"BEGIN"          { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: BEGIN\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_BEGIN; 
                }

"PROGRAM"        { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: PROGRAM\n", line_num, col_num);
                    after_program_keyword = 1;  // Activer le flag
                    col_num += yyleng; 
                    return KW_PROGRAM; 
                }

"END"            { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: END\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_END; 
                }

"SET"            { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: SET\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_SET; 
                }

"CREATE"         { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: CREATE\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_CREATE; 
                }

"RECORD"         { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: RECORD\n", line_num, col_num);
                    after_record_keyword = 1;  // Activer le flag
                    col_num += yyleng; 
                    return KW_RECORD; 
                }

"ARRAY"          { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: ARRAY\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_ARRAY; 
                }

"DICTIONARY"     { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: DICTIONARY\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_DICTIONARY; 
                }

"INTEGER"        { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Type: INTEGER\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_INTEGER; 
                }

"STRING"         { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Type: STRING\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_STRING; 
                }

"FLOAT"          { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Type: FLOAT\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_FLOAT; 
                }

"BOOLEAN"        { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Type: BOOLEAN\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_BOOLEAN; 
                }

"true"           { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Booléen: true\n", line_num, col_num);
                    col_num += yyleng;
                    
                    // Insérer la constante booléenne true
                    int value = 1;
                    lexer_insert_constant("true", DATA_BOOLEEN, &value);
                    
                    return KW_TRUE; 
                }

"false"          { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Booléen: false\n", line_num, col_num);
                    col_num += yyleng; 
                    
                    // Insérer la constante booléenne false
                    int value = 0;
                    lexer_insert_constant("false", DATA_BOOLEEN, &value);
                    
                    return KW_FALSE; 
                }

"WHEN"           { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: WHEN\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_WHEN; 
                }

"CASEWHEN"       { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: CASEWHEN\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_CASE_WHEN; 
                }

"THEN"           { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: THEN\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_THEN; 
                }

"OTHERWISE"      { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: OTHERWISE\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_OTHERWISE; 
                }

"CASE"           { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: CASE\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_CASE; 
                }

"ELSE"           { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: ELSE\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_ELSE; 
                }

"LOOP"           { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: LOOP\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_LOOP; 
                }

"ITERATE"        { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: ITERATE\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_ITERATE; 
                }

"FROM"           { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: FROM\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_FROM; 
                }

"TO"             { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: TO\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_TO; 
                }

"FOREACH"        { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: FOREACH\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_FOREACH; 
                }

"IN"             { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: IN\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_IN; 
                }

"PRINT"          { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: PRINT\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_PRINT; 
                }

"INPUT"          { 
                    nb_keywords_found++;
                    printf("[LEXER] L%d:C%d - Mot-clé: INPUT\n", line_num, col_num);
                    col_num += yyleng; 
                    return KW_INPUT; 
                }

"AND"            { nb_keywords_found++; col_num += yyleng; return OP_AND; }
"OR"             { nb_keywords_found++; col_num += yyleng; return OP_OR; }
"NOT"            { nb_keywords_found++; col_num += yyleng; return OP_NOT; }

"<>"             { col_num += yyleng; return OP_NEQ; }
"<="             { col_num += yyleng; return OP_LTE; }
">="             { col_num += yyleng; return OP_GTE; }
"<"              { col_num += yyleng; return OP_LT; }
">"              { col_num += yyleng; return OP_GT; }
"="              { col_num += yyleng; return OP_EQ; }
"+"              { col_num += yyleng; return OP_PLUS; }
"-"              { col_num += yyleng; return OP_MINUS; }
"*"              { col_num += yyleng; return OP_MULT; }
"/"              { col_num += yyleng; return OP_DIV; }
"%"              { col_num += yyleng; return OP_MOD; }

"("              { col_num += yyleng; return SEP_LPAREN; }

")"              { 
                    //Fin de la déclaration de record
                    if (inside_record_decl) {
                        inside_record_decl = 0;
                        printf("[LEXER] Fin de déclaration de record\n");
                    }
                    col_num += yyleng; 
                    return SEP_RPAREN; 
                }

"["              { col_num += yyleng; return SEP_LBRACKET; }
"]"              { col_num += yyleng; return SEP_RBRACKET; }
"{"              { col_num += yyleng; return SEP_LBRACE; }
"}"              { col_num += yyleng; return SEP_RBRACE; }
","              { col_num += yyleng; return SEP_COMMA; }
";"              { col_num += yyleng; return SEP_SEMICOLON; }
"."              { col_num += yyleng; return SEP_DOT; }

{IDENTIFIER}     { 
                    nb_identifiers_found++;
                    yylval.str = strdup(yytext);
                    printf("[LEXER] L%d:C%d - Identificateur: '%s'\n", 
                           line_num, col_num, yytext);
                    lexer_insert_identifier(yytext);
                    
                    col_num += yyleng; 
                    return IDENTIFIER; 
                }

{INTEGER}        { 
                    nb_literals_found++;
                    yylval.ival = atoi(yytext);
                    printf("[LEXER] L%d:C%d - Entier: %d\n", line_num, col_num, yylval.ival);
                    
                    // Insérer la constante entière
                    lexer_insert_constant(yytext, DATA_ENTIER, &yylval.ival);
                    
                    col_num += yyleng; 
                    return INT_LITERAL; 
                }

{FLOAT}          { 
                    nb_literals_found++;
                    yylval.fval = atof(yytext);
                    printf("[LEXER] L%d:C%d - Réel: %.2f\n", line_num, col_num, yylval.fval);
                    
                    // Insérer la constante réelle
                    lexer_insert_constant(yytext, DATA_REEL, &yylval.fval);
                    
                    col_num += yyleng; 
                    return FLOAT_LITERAL; 
                }

{STRING}         { 
                    nb_literals_found++;
                    yylval.str = strdup(yytext);
                    printf("[LEXER] L%d:C%d - Chaîne: %s\n", line_num, col_num, yytext);
                    
                    // Insérer la constante chaîne
                    lexer_insert_constant(yytext, DATA_CHAINE, yytext);
                    
                    col_num += yyleng; 
                    return STRING_LITERAL; 
                }

{WHITESPACE}     { col_num += yyleng; }
{NEWLINE}        { line_num++; col_num = 1; }

.                { 
                    fprintf(stderr, "File \"%s\", line %d, character %d: lexical error\n", 
                            current_filename, line_num, col_num); 
                    col_num++; 
                }

%%