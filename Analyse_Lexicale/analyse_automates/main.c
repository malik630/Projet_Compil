#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "thompson.h"
#include "afd_builder.h"
#include "symbol_table.h"
#include "error_manager.h"
#include "lexer.h"
#include "ll1_parser.h"

int main(int argc, char* argv[]) {
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║   ANALYSEUR COMPLET - QueryLang (Lexical + Syntaxique)      ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n\n");
    
    // Options de ligne de commande
    if (argc > 1 && strcmp(argv[1], "--show-construction") == 0) {
        show_construction = true;
        argc--;
        argv++;
    }
    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [--show-construction] fichier.ql\n", argv[0]);
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
    
    // Collect all tokens
    Token* tokens = (Token*)malloc(1000 * sizeof(Token));
    int token_count = 0;
    
    Token token;
    do {
        token = getNextToken();
        
        if (token.type != COMMENT && token.type != ERROR_TOK) {
            printToken(token);
            tokens[token_count++] = token;
        } else if (token.type == ERROR_TOK) {
            printToken(token);
        }
        
        if (token.type == IDENTIFIER) {
            insertSymbol(token.lexeme, "IDENTIFIER", token.line);
        }
        
    } while (token.type != END_OF_FILE);
    
    printf("\n✓ Analyse lexicale terminée: %d tokens\n", token_count);
    
    // ========================================================================
    // PHASE 4: ANALYSE SYNTAXIQUE
    // ========================================================================
    
    if (errorMgr.count == 0) {
        printf("\n═══ PHASE 4: ANALYSE SYNTAXIQUE LL(1) ═══\n\n");
        
        // Create LL(1) parser with tokens
        LL1Parser* parser = createLL1Parser(tokens, token_count);
        
        if (parser == NULL) {
            fprintf(stderr, "Erreur: Impossible de créer le parser\n");
            free(tokens);
            free(source);
            return EXIT_FAILURE;
        }
        
        // Run the parser
        bool parse_success = parseLL1(parser);
        
        // Display results
        printf("\n═══ RÉSULTATS DE L'ANALYSE SYNTAXIQUE ═══\n");
        if (parse_success) {
            printf("✓ Analyse syntaxique réussie!\n");
            printf("  Erreurs de parsing: 0\n");
        } else {
            printf("✗ Analyse syntaxique échouée\n");
            printf("  Erreurs de parsing: %d\n", parser->parse_errors);
        }
        
        // Cleanup parser
        freeLL1Parser(parser);
    } else {
        printf("\n✗ Analyse lexicale échouée - analyse syntaxique ignorée\n");
    }
    
    // ========================================================================
    // PHASE 5: AFFICHAGE DES RÉSULTATS FINAUX
    // ========================================================================
    
    printf("\n═══ PHASE 5: RÉSULTATS FINAUX ═══\n");
    
    displaySymbolTable();
    displayErrorSummary();
    
    printf("========== STATISTIQUES GLOBALES ==========\n");
    printf("Tokens analysés:  %d\n", token_count);
    printf("Symboles:         %d\n", symTable.count);
    printf("Erreurs totales:  %d\n", errorMgr.count);
    printf("Lignes de code:   %d\n\n", line_num);
    
    if (errorMgr.count == 0) {
        printf("✓ Analyse complète terminée avec succès!\n\n");
    } else {
        printf("✗ Analyse terminée avec %d erreur(s).\n\n", errorMgr.count);
    }
    
    free(tokens);
    free(source);
    
    return errorMgr.count > 0 ? 1 : 0;
}
