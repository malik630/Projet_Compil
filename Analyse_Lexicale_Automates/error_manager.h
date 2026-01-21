#ifndef ERROR_MANAGER_H
#define ERROR_MANAGER_H

#include "structures.h"

// Gestionnaire d'erreurs global
extern ErrorManager errorMgr;

// Fonctions de gestion
void initErrorManager();
void reportError(int line, int col, const char* message);
void displayErrorSummary();

#endif // ERROR_MANAGER_H