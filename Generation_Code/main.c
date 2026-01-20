#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "parser.tab.h"
#include "semantic.h"
#include "quads.h" 
#include "table_symboles_enrichie.h" 
#include "global.h"

extern FILE* yyin;
extern int yyparse();
extern ASTNode* root;

char* current_filename;


int main(int argc, char** argv) {
    memset(tabQuad, 0, sizeof(tabQuad));
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║      Compilateur QueryLang avec Génération de Code             ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier '%s'\n", argv[1]);
            return 1;
        }
        printf("Fichier source : %s\n", argv[1]);
        current_filename = strdup(argv[1]);
    } else {
        printf("Usage : %s <fichier_source.ql>\n", argv[0]);
        return 1;
    }

    // --- PHASE 0: Initialisation de la Table des Symboles ---
    printf("PHASE 0: Initialisation de la Table des Symboles\n");
    printf("════════════════════════════════════════════════\n");
    
    initTable(&tableGlobale);
    printf("Table des symboles initialisée\n");
    printf("   • Nombre de symboles  : %d\n", tableGlobale.nbSymboles);
    printf("   • Niveau de portée    : %d\n\n", tableGlobale.niveauPortee);
    
    printf("─────────────────────────────────────────────────────────────────\n\n");
    
    // --- PHASE 1: Analyse Lexicale et Syntaxique ---
    printf("PHASE 1: Analyse Lexicale et Syntaxique\n");
    printf("═══════════════════════════════════════\n");
    
    int result = yyparse();
    
    if (result != 0 || root == NULL) {
        printf("\nAnalyse syntaxique échouée !\n\n");
        if (yyin) fclose(yyin);
        return 1;
    }
    
    printf("\nAnalyse syntaxique réussie !\n");
    
    // Afficher l'AST
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║               ARBRE SYNTAXIQUE ABSTRAIT (AST)                  ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    printAST(root, 0);
    
    // --- PHASE 2: Analyse sémantique ---
    printf("\n\nPHASE 2: Analyse Sémantique\n");
    printf("═══════════════════════════\n");
    
    int semanticResult = performSemanticAnalysis(root);
    
    // --- PHASE 3: Génération de Code (Quadruplets) ---
    if (semanticResult) {
        printf("\n\nPHASE 3: Génération de Code Intermédiaire\n");
        printf("════════════════════════════════════════\n");
        
        generer_code(root);
        afficher_quads();
    }

    // --- RÉSUMÉ FINAL ---
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                    RÉSUMÉ DE LA COMPILATION                    ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    if (semanticResult) {
        printf("Compilation réussie !\n");
        printf("  • Analyse lexicale/syntaxique : OK\n");
        printf("  • Analyse sémantique          : OK\n");
        printf("  • Génération de code (Quads)  : %d instructions générées\n", nextQuad);
        printf("  • Avertissements              : %d\n", semanticWarnings.count);
        
        printf("\nAffichage de la Table des Symboles finale :\n");
        afficherTable(&tableGlobale);
        
        printf("\nLe programme a été transformé en instructions élémentaires.\n\n");
    } else {
        printf("Compilation échouée !\n");
        printf("  • Analyse sémantique          : ÉCHOUÉ\n");
        printf("  • Erreurs sémantiques         : %d\n", semanticErrors.count);
        printf("\nCorrigez les erreurs sémantiques avant la génération de code.\n\n");
    }
    
    freeAST(root);
    
    if (yyin) {
        fclose(yyin);
    }
    
    return semanticResult ? 0 : 1;
}



