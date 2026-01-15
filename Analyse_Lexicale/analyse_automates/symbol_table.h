#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "structures.h"

// Table des symboles globale
extern SymbolTable symTable;

// Fonctions de gestion
void initSymbolTable();
void insertSymbol(const char* name, const char* type, int line);
void displaySymbolTable();
bool symbolExists(const char* name);
const char* getSymbolType(const char* name);
void updateSymbolType(const char* name, const char* new_type);

#endif // SYMBOL_TABLE_H