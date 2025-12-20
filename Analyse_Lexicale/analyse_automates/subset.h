#ifndef SUBSET_H
#define SUBSET_H

#include "structures.h"

// Fonctions utilitaires pour ensembles d'états
StateSet epsilonClosure(AFN* afn, StateSet states);
StateSet move(AFN* afn, StateSet states, int symbol);
bool stateSetEqual(StateSet s1, StateSet s2);
int findStateSet(AFD* afd, StateSet set);

// Construction par sous-ensembles
AFD subsetConstruction(AFN* afn);

#endif // SUBSET_H