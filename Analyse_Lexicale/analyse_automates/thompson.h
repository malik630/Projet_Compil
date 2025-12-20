#ifndef THOMPSON_H
#define THOMPSON_H

#include "structures.h"

// Variables globales pour la construction
extern int next_state_id;
extern bool show_construction;

// Fonctions de base pour AFN
void initAFN(AFN* afn);
int newState(AFN* afn);
void addTransition(AFN* afn, int from, int to, int symbol);

// Construction de Thompson
AFN thompsonSymbol(char c);
AFN thompsonRange(char start_char, char end_char);
AFN thompsonConcat(AFN afn1, AFN afn2);
AFN thompsonUnion(AFN afn1, AFN afn2);
AFN thompsonStar(AFN afn);
AFN thompsonPlus(AFN afn);

#endif // THOMPSON_H