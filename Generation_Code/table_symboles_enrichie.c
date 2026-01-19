#include <stdio.h>
#include <string.h>
#include "table_symboles_enrichie.h"

// Initialiser la table
void initTable(TableSymboles* table) {
    table->nbSymboles = 0;
    table->niveauPortee = 0;
}

// Insérer un symbole
int insererSymbole(TableSymboles* table, Symbole sym) {
    // Vérifier si déjà déclaré dans la même portée
    for (int i = table->nbSymboles - 1; i >= 0; i--) {
        if (strcmp(table->symboles[i].nom, sym.nom) == 0 &&
            table->symboles[i].portee == sym.portee) {
            printf("Erreur sémantique : '%s' déjà déclaré\n", sym.nom);
            return -1;
        }
    }
    
    // Ajouter le symbole
    table->symboles[table->nbSymboles] = sym;
    table->nbSymboles++;
    return table->nbSymboles - 1;
}



// Entrer dans une nouvelle portée
void entrerPortee(TableSymboles* table) {
    table->niveauPortee++;
}

// Sortir d'une portée 
void sortirPortee(TableSymboles* table) {
    
    // On baisse juste le niveau pour les prochaines insertions
    if (table->niveauPortee > 0) {
        table->niveauPortee--;
    }
}

// Obtenir un symbole :
Symbole* obtenirSymbole(TableSymboles* table, char* nom) {
    // On cherche du plus récent au plus ancien
    for (int i = table->nbSymboles - 1; i >= 0; i--) {
        if (strcmp(table->symboles[i].nom, nom) == 0) {
            
            // On ne peut utiliser la variable que si sa portée est <= portée actuelle
            if (table->symboles[i].portee <= table->niveauPortee) {
                return &table->symboles[i];
            }
        }
    }
    return NULL;
}

// Afficher la table
void afficherTable(TableSymboles* table) {
    printf("\n========== TABLE DES SYMBOLES ==========\n");
    printf("%-15s %-12s %-15s %-8s %-8s %-10s %-15s\n", 
           "Nom", "Type Sym", "Type Data", "Portée", "Adresse", "Init", "Info");
    printf("----------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < table->nbSymboles; i++) {
        Symbole s = table->symboles[i];
        
        // Type symbole
        char* typeSym;
        if (s.typeSymbole == TYPE_VARIABLE) typeSym = "Variable";
        else if (s.typeSymbole == TYPE_CONSTANTE) typeSym = "Constante";
        else typeSym = "Tableau";
        
        // Type donnée
        char* typeData;
        if (s.typeDonnee == DATA_ENTIER) typeData = "Entier";
        else if (s.typeDonnee == DATA_REEL) typeData = "Réel";
        else if (s.typeDonnee == DATA_CHAINE) typeData = "Chaîne";
        else if (s.typeDonnee == DATA_BOOLEEN) typeData = "Booléen";
        else if (s.typeDonnee == DATA_ENREGISTREMENT) typeData = "Enregistrement";
        else if (s.typeDonnee == DATA_TABLEAU) typeData = "Tableau";
        else if (s.typeDonnee == DATA_DICTIONNAIRE) typeData = "Dictionnaire";
        else typeData = "Inconnu";
        
        // Portée
        char porteeStr[10];
        sprintf(porteeStr, "%d", s.portee);
        
        // Initialisé
        char* init = s.initialise ? "Oui" : "Non";
        
        printf("%-15s %-12s %-15s %-8s %-8d %-10s ", 
               s.nom, typeSym, typeData, porteeStr, s.adresse, init);
        
        // Info supplémentaire
        if (s.typeSymbole == TYPE_CONSTANTE) {
            if (s.typeDonnee == DATA_ENTIER) {
                printf("Valeur=%d", s.valeur.valeurInt);
            } else if (s.typeDonnee == DATA_REEL) {
                printf("Valeur=%.2f", s.valeur.valeurReel);
            }
        } else if (s.typeSymbole == TYPE_TABLEAU || s.typeDonnee == DATA_TABLEAU) {
            printf("Taille=%d", s.taille);
        }
        
        printf("\n");
    }
    printf("========================================================================================\n\n");
}

// Rechercher un symbole uniquement dans la portée actuelle
Symbole* rechercherSymbolePorteeActuelle(TableSymboles* table, char* nom) {
    // Parcourir du plus récent au plus ancien
    for (int i = table->nbSymboles - 1; i >= 0; i--) {
        // Vérifier la portée exacte
        if (table->symboles[i].portee == table->niveauPortee) {
            if (strcmp(table->symboles[i].nom, nom) == 0) {
                return &table->symboles[i];
            }
        }
        // Si on trouve un symbole d'une portée inférieure, on arrête
        else if (table->symboles[i].portee < table->niveauPortee) {
            break;
        }
    }
    return NULL;
}