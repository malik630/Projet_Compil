#ifndef AFD_BUILDER_H
#define AFD_BUILDER_H

#include "structures.h"

// AFD globaux
extern AFD identifier_afd;
extern AFD integer_afd;
extern AFD float_afd;

// Construction des AFD pour QueryLang
AFD buildIdentifierAFD();
AFD buildIntegerAFD();
AFD buildFloatAFD();

// Initialisation de tous les AFD
void initializeAFDs();

#endif // AFD_BUILDER_H