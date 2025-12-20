#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "structures.h"

// Table des symboles globale
extern SymbolTable symTable;

// Fonctions de gestion
void initSymbolTable();
void insertSymbol(const char* name, const char* type, int line);
void displaySymbolTable();

#endif // SYMBOL_TABLE_H