#include <stdio.h>
#include <stdlib.h>
#include "ast.h"           /* Inclure ast.h AVANT parser.tab.h */
#include "parser.tab.h"

extern FILE* yyin;
extern int yyparse();
extern ASTNode* root;

int main(int argc, char** argv) {
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║         Analyseur QueryLang avec Construction d'AST           ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier '%s'\n", argv[1]);
            return 1;
        }
        printf("Analyse du fichier : %s\n", argv[1]);
    } else {
        printf("Usage : %s <fichier_source.ql>\n", argv[0]);
        return 1;
    }
    
    printf("─────────────────────────────────────────────────────────────────\n\n");
    
    int result = yyparse();
    
    if (result == 0 && root != NULL) {
        printf("\n╔════════════════════════════════════════════════════════════════╗\n");
        printf("║              ARBRE SYNTAXIQUE ABSTRAIT (AST)                  ║\n");
        printf("╚════════════════════════════════════════════════════════════════╝\n\n");
        
        printAST(root, 0);
        
        printf("\n─────────────────────────────────────────────────────────────────\n");
        printf("✓ AST construit avec succès !\n\n");
        
        freeAST(root);
    } else {
        printf("\n✗ Échec de l'analyse syntaxique !\n\n");
    }
    
    if (yyin) {
        fclose(yyin);
    }
    
    return result;
}