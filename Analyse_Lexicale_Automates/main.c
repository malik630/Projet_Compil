#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "thompson.h"
#include "afd_builder.h"
#include "symbol_table.h"
#include "error_manager.h"
#include "lexer.h"
#include "../Analyse_Syntaxique_Manuelle/ll1_parser.h"

int main(int argc, char* argv[]) {
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║   ANALYSEUR LEXICAL ET SYNTAXIQUE MANUEL - QueryLang          ║\n");
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
    printf("Fichier '%s' lu avec succès\n\n", argv[1]);
    
    printf("=== CODE SOURCE ===\n");
    printf("%s\n", source);
    
    // ========================================================================
    // PHASE 3: ANALYSE LEXICALE
    // ========================================================================
    
    printf("\n═══ PHASE 3: ANALYSE LEXICALE ═══\n\n");
    
    Token* tokens = (Token*)malloc(1000 * sizeof(Token));
    int token_count = 0;

    Token token;
    do {
        token = getNextToken();

        tokens[token_count] = token;
        token_count++;
    
        if (token.type != COMMENT && token.type != ERROR_TOK) {
            printToken(token);
        } else if (token.type == ERROR_TOK) {
            printToken(token);
        }
    
        if (token.type == IDENTIFIER) {
            insertSymbol(token.lexeme, "IDENTIFIER", token.line);
        }
    
    } while (token.type != END_OF_FILE && token_count < 1000);
    // ========================================================================
    // PHASE 4: ANALYSE SYNTAXIQUE
    // ========================================================================
    
    if (errorMgr.count == 0) {
        printf("\n═══ PHASE 4: ANALYSE SYNTAXIQUE LL(1) ═══\n\n");

        LL1Parser* parser = createLL1Parser(tokens, token_count);
        
        if (parser == NULL) {
            fprintf(stderr, "Erreur: Impossible de créer le parser\n");
            free(tokens);
            free(source);
            return EXIT_FAILURE;
        }

        bool parse_success = parseLL1(parser);

        printf("\n═══ RÉSULTATS DE L'ANALYSE SYNTAXIQUE ═══\n");
        if (parse_success) {
            printf("  Analyse syntaxique réussie!\n");
            printf("  Erreurs de parsing: 0\n");
        } else {
            printf("  Analyse syntaxique échouée\n");
            printf("  Erreurs de parsing: %d\n", parser->parse_errors);
        }

        freeLL1Parser(parser);
    } else {
        printf("\n✗ Analyse lexicale échouée - analyse syntaxique ignorée\n");
    }
    
    // ========================================================================
    // PHASE 5: AFFICHAGE DES RÉSULTATS
    // ========================================================================
    
    printf("\n═══ PHASE 5: RÉSULTATS ═══\n");
    
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
    
    free(tokens);
    free(source);
    
    return errorMgr.count > 0 ? 1 : 0;

}

