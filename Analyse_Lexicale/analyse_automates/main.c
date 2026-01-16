#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "thompson.h"
#include "afd_builder.h"
#include "symbol_table.h"
#include "error_manager.h"
#include "lexer.h"

int main(int argc, char* argv[]) {
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║   ANALYSEUR LEXICAL COMPLET - QueryLang                      ║\n");
    printf("║   Avec Transformations Regex → AFN → AFD                     ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n\n");
    
    // Options de ligne de commande
    if (argc > 1 && strcmp(argv[1], "--show-construction") == 0) {
        show_construction = true;
        argc--;
        argv++;
    }
    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [--show-construction] fichier.ql\n", argv[0]);
        fprintf(stderr, "\nOptions:\n");
        fprintf(stderr, "  --show-construction  Afficher les détails de construction des AFD\n");
        return EXIT_FAILURE;
    }
    
    // ========================================================================
    // PHASE 1: CONSTRUCTION DES AFD
    // ========================================================================
    
    initializeAFDs();
    
    // ========================================================================
    // PHASE 2: LECTURE DU FICHIER SOURCE
    // ========================================================================
    
    printf("═══ PHASE 2: LECTURE DU FICHIER SOURCE ═══\n");
    
    source = readFile(argv[1]);
    printf("✓ Fichier '%s' lu avec succès\n\n", argv[1]);
    
    printf("=== CODE SOURCE ===\n");
    printf("%s\n", source);
    
    // ========================================================================
    // PHASE 3: ANALYSE LEXICALE
    // ========================================================================
    
    printf("\n═══ PHASE 3: ANALYSE LEXICALE ═══\n\n");
    
    initSymbolTable();
    initErrorManager();
    
    int token_count = 0;
    
    Token token;
    do {
        token = getNextToken();
        token_count++;
        
        if (token.type != COMMENT && token.type != ERROR_TOK) {
            printToken(token);
        } else if (token.type == ERROR_TOK) {
            printToken(token);
        }
        
        if (token.type == IDENTIFIER) {
            insertSymbol(token.lexeme, "IDENTIFIER", token.line);
        }
        
    } while (token.type != END_OF_FILE);
    
    // ========================================================================
    // PHASE 4: AFFICHAGE DES RÉSULTATS
    // ========================================================================
    
    printf("\n═══ PHASE 4: RÉSULTATS ═══\n");
    
    displaySymbolTable();
    displayErrorSummary();
    
    printf("========== STATISTIQUES ==========\n");
    printf("Tokens analysés:  %d\n", token_count);
    printf("Symboles:         %d\n", symTable.count);
    printf("Erreurs:          %d\n", errorMgr.count);
    printf("Lignes de code:   %d\n\n", line_num);
    
    if (errorMgr.count == 0) {
        printf("Analyse lexicale terminée avec succès!\n\n");
    } else {
        printf("Analyse lexicale terminée avec %d erreur(s).\n\n", errorMgr.count);
    }
    
    free(source);
    
    return errorMgr.count > 0 ? 1 : 0;

}

