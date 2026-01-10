#ifndef TABLE_SYMBOLES_H
#define TABLE_SYMBOLES_H

// Types de symboles
typedef enum {
    TYPE_VARIABLE,
    TYPE_CONSTANTE,
    TYPE_TABLEAU
} TypeSymbole;

// Types de données
typedef enum {
    DATA_ENTIER,
    DATA_REEL,
    DATA_CHAINE,
    DATA_BOOLEEN
} TypeDonnee;

// Portée
typedef enum {
    PORTEE_GLOBALE,
    PORTEE_LOCALE
} Portee;

// Structure d'un symbole
typedef struct {
    char nom[50];
    TypeSymbole typeSymbole;    // Variable, Constante ou Tableau
    TypeDonnee typeDonnee;      // Entier, Réel, Chaîne, Booléen
    Portee portee;              // Globale ou Locale
    int adresse;                // Adresse mémoire
    int initialise;             // 0 = non, 1 = oui
    
    // Pour les constantes uniquement
    union {
        int valeurInt;
        float valeurReel;
        char valeurChaine[100];
        int valeurBool;
    } valeur;
    
    // Pour les tableaux uniquement
    int taille;                 // Taille du tableau
    
} Symbole;

// Table des symboles
typedef struct {
    Symbole symboles[1000];
    int nbSymboles;
    int niveauPortee;
} TableSymboles;

// Fonctions
void initTable(TableSymboles* table);
int insererSymbole(TableSymboles* table, Symbole sym);
Symbole* obtenirSymbole(TableSymboles* table, char* nom);
void afficherTable(TableSymboles* table);
void entrerPortee(TableSymboles* table);
void sortirPortee(TableSymboles* table);

#endif