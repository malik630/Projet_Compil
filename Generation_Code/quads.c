#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quads.h"

Quadruplet tabQuad[2000];
int nextQuad = 0;
int tempCount = 0;


void generer_quad(const char* op, char* a1, char* a2, char* res) {
    if (nextQuad >= 2000) return;

    // PROTECTION RADICALE : On ne teste QUE la présence du pointeur
    // On ne touche pas au contenu (strlen) avant d'être sûr qu'il existe
    const char* s_op  = (op)  ? op  : "UNKNOWN";
    const char* s_a1  = (a1)  ? a1  : "";
    const char* s_a2  = (a2)  ? a2  : "";
    const char* s_res = (res) ? res : "";

    tabQuad[nextQuad].op   = strdup(s_op);
    tabQuad[nextQuad].arg1 = strdup(s_a1);
    tabQuad[nextQuad].arg2 = strdup(s_a2);
    tabQuad[nextQuad].res  = strdup(s_res);
    
    nextQuad++;
}

char* creer_temp() {
    char* t = malloc(15);
    sprintf(t, "T%d", tempCount++);
    return t;
}

void afficher_quads() {
    printf("\n--- TABLE DES QUADRUPLETS ---\n");
    for(int i = 0; i < nextQuad; i++) {
        printf("%d: (%s, %s, %s, %s)\n", i, tabQuad[i].op, 
               tabQuad[i].arg1, tabQuad[i].arg2, tabQuad[i].res);
    }
}