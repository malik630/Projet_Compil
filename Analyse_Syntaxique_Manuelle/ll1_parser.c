#include "ll1_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LL1Parser* createLL1Parser(Token* tokens, int count) {
    LL1Parser* parser = (LL1Parser*)malloc(sizeof(LL1Parser));
    if (!parser) return NULL;
    
    parser->tokens = tokens;
    parser->token_count = count;
    parser->current_token = 0;
    
    initLL1Table(parser);
    initStack(&parser->stack);
    
    parser->ast_root = NULL;
    parser->symbol_table = &symTable;    
    parser->error_manager = &errorMgr;  
    
    parser->current_identifier[0] = '\0';
    parser->current_type[0] = '\0';
    parser->in_declaration = false;
    
    parser->parse_errors = 0;
    parser->semantic_errors = 0;
    
    return parser;
}

void freeLL1Parser(LL1Parser* parser) {
    if (parser) {
        // L'AST sera libéré séparément si nécessaire
        free(parser);
    }
}

bool parseLL1(LL1Parser* parser) {
    
    printf("║       ANALYSE SYNTAXIQUE LL(1) Manuelle - QueryLang                   ║\n");
   
    
    
    StackSymbol eof_symbol;
    eof_symbol.kind = SYMBOL_EOF;
    pushStack(&parser->stack, eof_symbol);
    
    StackSymbol start_symbol;
    start_symbol.kind = SYMBOL_NONTERMINAL;
    start_symbol.value.non_terminal = NT_PROGRAM;
    pushStack(&parser->stack, start_symbol);
    
    Token current_token = parser->tokens[parser->current_token];
    
    printf("Début de l'analyse...\n\n");
    
    int step = 0;
    
    while (!isStackEmpty(&parser->stack)) {
        step++;
        
        // Affichage pour débogage
        if (step % 10 == 1 || step < 20) {  // Afficher les premiers pas et tous les 10 pas
            printf("─── Étape %d ───\n", step);
            printStack(&parser->stack);
            printf("Token courant: %s ('%s') à ligne %d, colonne %d\n", 
                   tokenTypeToString(current_token.type),
                   current_token.lexeme,
                   current_token.line,
                   current_token.column);
        }
        
        StackSymbol top = peekStack(&parser->stack);
        
        // Cas 1: Symbole de fin $
        if (top.kind == SYMBOL_EOF) {
            if (current_token.type == END_OF_FILE) {
                printf("\nAnalyse syntaxique terminée avec succès!\n");
                printf("  Total d'étapes: %d\n", step);
                printf("  Erreurs syntaxiques: %d\n", parser->parse_errors);
                return parser->parse_errors == 0;
            } else {
                reportSyntaxError(parser, "Symboles supplémentaires après la fin du programme");
                return false;
            }
        }
        
        // Cas 2: Terminal sur la pile
        if (top.kind == SYMBOL_TERMINAL) {
            if (top.value.terminal == current_token.type) {
                // Match!
                if (step % 10 == 1 || step < 20) {
                    printf("Match terminal: %s\n\n", tokenTypeToString(top.value.terminal));
                }
                
                popStack(&parser->stack);
                
                // Avancer au token suivant
                parser->current_token++;
                if (parser->current_token < parser->token_count) {
                    current_token = parser->tokens[parser->current_token];
                }
            } else {
                // Erreur: terminal attendu différent du token courant
                char error_msg[512];
                snprintf(error_msg, sizeof(error_msg),
                        "Token inattendu. Attendu: %s, Reçu: %s",
                        tokenTypeToString(top.value.terminal),
                        tokenTypeToString(current_token.type));
                reportSyntaxError(parser, error_msg);
                
                // Récupération d'erreur simple: sauter le token
                parser->current_token++;
                if (parser->current_token < parser->token_count) {
                    current_token = parser->tokens[parser->current_token];
                }
            }
            continue;
        }
        
        // Cas 3: Non-terminal sur la pile
        if (top.kind == SYMBOL_NONTERMINAL) {
            NonTerminal nt = top.value.non_terminal;
            
            // Consulter la table LL(1)
            LL1TableEntry* entry = lookupLL1Table(parser, nt, current_token.type);
            
            if (!entry) {
                // Erreur: pas de production dans la table
                char error_msg[512];
                snprintf(error_msg, sizeof(error_msg),
                        "Erreur syntaxique au non-terminal %s avec token %s",
                        nonTerminalToString(nt),
                        tokenTypeToString(current_token.type));
                reportSyntaxError(parser, error_msg);
                
                // Récupération: dépiler le non-terminal
                popStack(&parser->stack);
                continue;
            }
            
            // Appliquer la production
            if (step % 10 == 1 || step < 20) {
                printf("→ Applique règle (%d): %s → %s\n\n",
                       entry->rule_number,
                       nonTerminalToString(nt),
                       entry->production);
            }
            
            popStack(&parser->stack);
            
            // Empiler la partie droite de la production (en ordre inverse)
            // Sauf si c'est epsilon
            if (strcmp(entry->production, "ε") != 0) {
                // Parser la production et empiler les symboles
                pushProduction(&parser->stack, entry->production);
            }
            
            // Exécuter l'action sémantique associée
            executeSemanticAction(parser, entry->rule_number);
        }
    }
    
    return false;  // Ne devrait pas arriver ici
}

// empiler une production
void pushProduction(ParseStack* stack, const char* production) {
    // Parser la chaîne de production et empiler en ordre inverse
    char prod_copy[256];
    strncpy(prod_copy, production, sizeof(prod_copy) - 1);
    
    // Diviser par espaces
    char* symbols[50];
    int symbol_count = 0;
    
    char* token = strtok(prod_copy, " ");
    while (token != NULL && symbol_count < 50) {
        symbols[symbol_count++] = token;
        token = strtok(NULL, " ");
    }
    
    // Empiler en ordre inverse
    for (int i = symbol_count - 1; i >= 0; i--) {
        StackSymbol sym = stringToSymbol(symbols[i]);
        pushStack(stack, sym);
    }
}

StackSymbol stringToSymbol(const char* str) {
    StackSymbol sym;
    
    // Verifier si c'est un terminal
    if (strncmp(str, "KW_", 3) == 0 || strncmp(str, "OP_", 3) == 0 ||
        strncmp(str, "SEP_", 4) == 0 || strcmp(str, "IDENTIFIER") == 0 ||
        strcmp(str, "INT_LITERAL") == 0 || strcmp(str, "FLOAT_LITERAL") == 0 ||
        strcmp(str, "STRING_LITERAL") == 0) {
        sym.kind = SYMBOL_TERMINAL;
        sym.value.terminal = stringToTokenType(str);
    } else {
        // C'est un non-terminal
        sym.kind = SYMBOL_NONTERMINAL;
        sym.value.non_terminal = stringToNonTerminal(str);
    }
    
    return sym;
}