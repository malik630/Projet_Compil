#include <stdio.h>
#include <string.h>
#include "table_symboles_enrichie.h"
#include "ast.h"

// Définition de la variable globale
TableSymboles tableGlobale;

// Initialiser la table
void initTable(TableSymboles* table) {
    table->nbSymboles = 0;
    table->niveauPortee = 0;
    printf("\n[TABLE SYMBOLES] Initialisation de la table des symboles\n");
}

// Insérer un symbole
int insererSymbole(TableSymboles* table, Symbole sym) {
    // Vérifier si déjà déclaré dans la même portée
    for (int i = table->nbSymboles - 1; i >= 0; i--) {
        if (strcmp(table->symboles[i].nom, sym.nom) == 0 &&
            table->symboles[i].portee == sym.portee) {
            printf("[TABLE SYMBOLES] '%s' déjà dans la table (ligne %d)\n", 
                   sym.nom, table->symboles[i].line);
            return i;  // Retourner l'index existant au lieu de -1
        }
    }
    
    // Ajouter le symbole
    table->symboles[table->nbSymboles] = sym;
    printf("[TABLE SYMBOLES] Insertion : '%s' (type=%d, portée=%d, ligne=%d, col=%d)\n", 
           sym.nom, sym.typeDonnee, sym.portee, sym.line, sym.column);
    table->nbSymboles++;
    return table->nbSymboles - 1;
}


// Supprimer un symbole de la table
int supprimerSymbole(TableSymboles* table, char* nom) {
    for (int i = 0; i < table->nbSymboles; i++) {
        if (strcmp(table->symboles[i].nom, nom) == 0) {
            printf("[TABLE SYMBOLES] Suppression : '%s'\n", nom);
            
            // Décaler tous les symboles suivants
            for (int j = i; j < table->nbSymboles - 1; j++) {
                table->symboles[j] = table->symboles[j + 1];
            }
            
            table->nbSymboles--;
            return 1; // Succès
        }
    }
    return 0; // Non trouvé
}

// Nettoyer les noms de types de records de la table
void nettoyerTypesRecords(TableSymboles* table, char** nomsTypes, int nbTypes) {
    printf("\n[TABLE SYMBOLES] Nettoyage des types de records...\n");
    
    for (int i = 0; i < nbTypes; i++) {
        supprimerSymbole(table, nomsTypes[i]);
    }
    
    printf("[TABLE SYMBOLES] %d types de records supprimés\n", nbTypes);
}

// Nettoyer les champs d'un record
void nettoyerChampsRecord(TableSymboles* table, ASTNode* champs) {
    ASTNode* current = champs;
    
    while (current != NULL) {
        if (current->type == NODE_FIELD) {
            supprimerSymbole(table, current->data.field.name);
            current = current->data.field.next;
        } else {
            break;
        }
    }
}

// Mettre à jour un symbole existant (pour le parser)
int mettreAJourSymbole(TableSymboles* table, char* nom, TypeSymbole typeSymbole, 
                       TypeDonnee typeDonnee, int initialise, int taille) {
    // Chercher le symbole
    for (int i = table->nbSymboles - 1; i >= 0; i--) {
        if (strcmp(table->symboles[i].nom, nom) == 0) {
            // Mettre à jour les informations
            table->symboles[i].typeSymbole = typeSymbole;
            table->symboles[i].typeDonnee = typeDonnee;
            table->symboles[i].initialise = initialise;
            if (taille > 0) {
                table->symboles[i].taille = taille;
            }
            
            printf("[TABLE SYMBOLES] Mise à jour : '%s' ", nom);
            printf("(type symbole=%d, type donnée=%d, init=%d)\n", 
                   typeSymbole, typeDonnee, initialise);
            
            return i;
        }
    }
    
    printf("[TABLE SYMBOLES] Symbole '%s' non trouvé pour mise à jour\n", nom);
    return -1;
}

// Entrer dans une nouvelle portée
void entrerPortee(TableSymboles* table) {
    table->niveauPortee++;
    printf("[TABLE SYMBOLES] Entrée dans portée niveau %d\n", table->niveauPortee);
}

// Sortir d'une portée 
void sortirPortee(TableSymboles* table) {
    if (table->niveauPortee > 0) {
        printf("[TABLE SYMBOLES] Sortie de portée niveau %d\n", table->niveauPortee);
        table->niveauPortee--;
    }
}

// Obtenir un symbole
Symbole* obtenirSymbole(TableSymboles* table, char* nom) {
    for (int i = table->nbSymboles - 1; i >= 0; i--) {
        if (strcmp(table->symboles[i].nom, nom) == 0) {
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
        
        char* typeSym;
        if (s.typeSymbole == TYPE_VARIABLE) typeSym = "Variable";
        else if (s.typeSymbole == TYPE_CONSTANTE) typeSym = "Constante";
        else typeSym = "Tableau";
        
        char* typeData;
        if (s.typeDonnee == DATA_ENTIER) typeData = "Entier";
        else if (s.typeDonnee == DATA_REEL) typeData = "Réel";
        else if (s.typeDonnee == DATA_CHAINE) typeData = "Chaîne";
        else if (s.typeDonnee == DATA_BOOLEEN) typeData = "Booléen";
        else if (s.typeDonnee == DATA_ENREGISTREMENT) typeData = "Enregistrement";
        else if (s.typeDonnee == DATA_TABLEAU) typeData = "Tableau";
        else if (s.typeDonnee == DATA_DICTIONNAIRE) typeData = "Dictionnaire";
        else typeData = "Inconnu";
        
        char porteeStr[10];
        sprintf(porteeStr, "%d", s.portee);
        
        char* init = s.initialise ? "Oui" : "Non";
        
        printf("%-15s %-12s %-15s %-8s %-8d %-10s ", 
               s.nom, typeSym, typeData, porteeStr, s.adresse, init);
        
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
    for (int i = table->nbSymboles - 1; i >= 0; i--) {
        if (table->symboles[i].portee == table->niveauPortee) {
            if (strcmp(table->symboles[i].nom, nom) == 0) {
                return &table->symboles[i];
            }
        } else if (table->symboles[i].portee < table->niveauPortee) {
            break;
        }
    }
    return NULL;
}