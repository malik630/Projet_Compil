#ifndef LEXER_H
#define LEXER_H

#include "structures.h"

// Variables globales pour l'analyse
extern char* source;
extern int pos;
extern int line_num;
extern int col_num;

// Fonctions utilitaires
char peek();
char advance();
void skipWhitespace();
TokenType checkKeyword(const char* str);

// Fonctions de scan
Token scanWithAFD(AFD* afd, TokenType default_type);
Token scanString();
Token scanComment();
Token scanOperator();
Token getNextToken();

// Affichage
const char* tokenTypeToString(TokenType type);
void printToken(Token token);

// Lecture de fichier
char* readFile(const char* filename);

#endif // LEXER_H