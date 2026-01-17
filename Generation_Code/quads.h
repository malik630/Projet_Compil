#ifndef QUADS_H
#define QUADS_H

typedef struct {
    char* op;    // Opérateur
    char* arg1;  // Premier argument
    char* arg2;  // Deuxième argument
    char* res;   // Résultat ou étiquette
} Quadruplet;

extern Quadruplet tabQuad[2000];
extern int nextQuad;


void generer_quad(const char* op, char* a1, char* a2, char* res);
char* creer_temp();
void afficher_quads();

#endif