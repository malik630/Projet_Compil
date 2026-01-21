#ifndef TABLE_SYMBOLES_H
#define TABLE_SYMBOLES_H

typedef struct ASTNode ASTNode;

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
    DATA_BOOLEEN,
    DATA_ENREGISTREMENT,
    DATA_TABLEAU,
    DATA_DICTIONNAIRE
} TypeDonnee;

// Portée
typedef enum {
    PORTEE_GLOBALE,
    PORTEE_LOCALE
} Portee;

// Structure d'un symbole
typedef struct {
    char nom[50];
    TypeSymbole typeSymbole;
    TypeDonnee typeDonnee;
    Portee portee;
    int adresse;
    int initialise;
    int line;
    int column;
    
    // Pour les constantes uniquement
    union {
        int valeurInt;
        float valeurReel;
        char valeurChaine[100];
        int valeurBool;
    } valeur;
    
    // Pour les tableaux uniquement
    int taille;
    TypeDonnee typeElement;
    
} Symbole;

// Table des symboles
typedef struct {
    Symbole symboles[1000];
    int nbSymboles;
    int niveauPortee;
    int prochaineAdresse;
} TableSymboles;

// Variable globale partagée entre toutes les phases
extern TableSymboles tableGlobale;

// Fonctions de base
void initTable(TableSymboles* table);
int insererSymbole(TableSymboles* table, Symbole sym);
int supprimerSymbole(TableSymboles* table, char* nom);
int mettreAJourSymbole(TableSymboles* table, char* nom, TypeSymbole typeSymbole, 
                       TypeDonnee typeDonnee, int initialise, int taille);
Symbole* obtenirSymbole(TableSymboles* table, char* nom);
void afficherTable(TableSymboles* table);
void entrerPortee(TableSymboles* table);
void sortirPortee(TableSymboles* table);
Symbole* rechercherSymbolePorteeActuelle(TableSymboles* table, char* nom);

// Fonction pour obtenir la prochaine adresse
int obtenirProchaineAdresse(TableSymboles* table);

#endif