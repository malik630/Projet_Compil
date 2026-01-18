#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "parser.tab.h"
#include "semantic.h"

extern FILE* yyin;
extern int yyparse();
extern ASTNode* root;

int main(int argc, char** argv) {
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║      Compilateur QueryLang avec Analyse Sémantique            ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier '%s'\n", argv[1]);
            return 1;
        }
        printf("Fichier source : %s\n", argv[1]);
    } else {
        printf("Usage : %s <fichier_source.ql>\n", argv[0]);
        return 1;
    }
    
    printf("─────────────────────────────────────────────────────────────────\n\n");
    
    // Phase 1: Analyse lexicale et syntaxique
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
    printf("║              ARBRE SYNTAXIQUE ABSTRAIT (AST)                  ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    printAST(root, 0);
    
    // Phase 2: Analyse sémantique
    printf("\n\nPHASE 2: Analyse Sémantique\n");
    printf("═══════════════════════════\n");
    
    int semanticResult = performSemanticAnalysis(root);
    
    // Résumé final
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                    RÉSUMÉ DE LA COMPILATION                    ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    if (semanticResult) {
        printf("Compilation réussie !\n");
        printf("  • Analyse lexicale      : OK\n");
        printf("  • Analyse syntaxique    : OK\n");
        printf("  • Analyse sémantique    : OK\n");
        printf("  • Erreurs sémantiques   : 0\n");
        printf("  • Avertissements        : %d\n", semanticWarnings.count);
        printf("\nLe programme est prêt pour la génération de code.\n\n");
    } else {
        printf("Compilation échouée !\n");
        printf("  • Analyse lexicale      : OK\n");
        printf("  • Analyse syntaxique    : OK\n");
        printf("  • Analyse sémantique    : ÉCHOUÉ\n");
        printf("  • Erreurs sémantiques   : %d\n", semanticErrors.count);
        printf("  • Avertissements        : %d\n", semanticWarnings.count);
        printf("\nCorrigez les erreurs sémantiques avant de continuer.\n\n");
    }
    
    // Libérer la mémoire
    freeAST(root);
    
    if (yyin) {
        fclose(yyin);
    }
    
    return semanticResult ? 0 : 1;
}