#include "error_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ErrorManager errorMgr;

void initErrorManager() {
    errorMgr.head = NULL;
    errorMgr.count = 0;
}

void reportError(int line, int col, const char* message) {
    ErrorEntry* error = (ErrorEntry*)malloc(sizeof(ErrorEntry));
    error->line = line;
    error->column = col;
    strcpy(error->message, message);
    error->next = errorMgr.head;
    errorMgr.head = error;
    errorMgr.count++;
    
    fprintf(stderr, "File \"source.ql\", line %d, character %d: %s\n", 
            line, col, message);
}

void displayErrorSummary() {
    printf("\n========== RÉSUMÉ DES ERREURS ==========\n");
    if (errorMgr.count == 0) {
        printf("Aucune erreur détectée.\n");
    } else {
        printf("%d erreur(s) détectée(s)\n", errorMgr.count);
    }
    printf("\n");
}