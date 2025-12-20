#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SymbolTable symTable;

void initSymbolTable() {
    symTable.head = NULL;
    symTable.count = 0;
}

void insertSymbol(const char* name, const char* type, int line) {
    SymbolEntry* curr = symTable.head;
    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) return;
        curr = curr->next;
    }
    
    SymbolEntry* entry = (SymbolEntry*)malloc(sizeof(SymbolEntry));
    strcpy(entry->name, name);
    strcpy(entry->type, type);
    entry->line = line;
    entry->next = symTable.head;
    symTable.head = entry;
    symTable.count++;
}

void displaySymbolTable() {
    printf("\n========== TABLE DES SYMBOLES ==========\n");
    printf("%-25s %-15s %-10s\n", "Nom", "Type", "Ligne");
    printf("-------------------------------------------\n");
    
    SymbolEntry* curr = symTable.head;
    while (curr != NULL) {
        printf("%-25s %-15s %-10d\n", curr->name, curr->type, curr->line);
        curr = curr->next;
    }
    printf("-------------------------------------------\n");
    printf("Total: %d symboles\n\n", symTable.count);
}