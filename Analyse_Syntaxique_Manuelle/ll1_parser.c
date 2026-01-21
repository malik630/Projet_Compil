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
        free(parser);
    }
}

bool parseLL1(LL1Parser* parser) {
    printf("║        ANALYSE SYNTAXIQUE LL(1) Manuelle - QueryLang                    ║\n");
   
    StackSymbol eof_symbol;
    eof_symbol.kind = SYMBOL_EOF;
    pushStack(&parser->stack, eof_symbol);
    
    StackSymbol start_symbol;
    start_symbol.kind = SYMBOL_NONTERMINAL;
    start_symbol.value.non_terminal = NT_PROGRAM;
    pushStack(&parser->stack, start_symbol);
    
    Token current_token = parser->tokens[parser->current_token];
    Token first_error_token;
    bool has_error = false;
    int step = 0;

    printf("Début de l'analyse...\n\n");
    
    while (!isStackEmpty(&parser->stack)) {
        step++;
        
        if (step % 10 == 1 || step < 20) {  
            printf("─── Étape %d ───\n", step);
            printStack(&parser->stack);
            printf("Token courant: %s ('%s') à ligne %d, colonne %d\n", 
                   tokenTypeToString(current_token.type), current_token.lexeme, current_token.line, current_token.column);
        }
        
        StackSymbol top = peekStack(&parser->stack);
        
        if (top.kind == SYMBOL_EOF) {
            if (current_token.type == END_OF_FILE) {
                printf("\n Analyse syntaxique terminée avec succès!\n");
                printf("  Total d'étapes: %d\n", step);
                printf("  Erreurs syntaxiques: %d\n", parser->parse_errors);
                return parser->parse_errors == 0;
            } else {
                reportSyntaxError(parser, "Symboles supplémentaires après la fin du programme");
                return false;
            }
        }
        
        if (top.kind == SYMBOL_TERMINAL) {
            if (top.value.terminal == current_token.type) {
                if (step % 10 == 1 || step < 20) {
                    printf(" Match terminal: %s\n\n", tokenTypeToString(top.value.terminal));
                }
                
                popStack(&parser->stack);
                parser->current_token++;
                if (parser->current_token < parser->token_count) 
                    current_token = parser->tokens[parser->current_token];
            } else {
                if(!has_error) { first_error_token = current_token; has_error = true; }
                reportSyntaxError(parser, "Mismatch terminal");
                parser->current_token++;
                if (parser->current_token < parser->token_count) 
                    current_token = parser->tokens[parser->current_token];
            }
            continue;
        }
        
        if (top.kind == SYMBOL_NONTERMINAL) {
            NonTerminal nt = top.value.non_terminal;
            LL1TableEntry* entry = lookupLL1Table(parser, nt, current_token.type);
            
            if (!entry) {
                if(!has_error) { first_error_token = current_token; has_error = true; }
                reportSyntaxError(parser, "Pas de production");
                popStack(&parser->stack);
                continue;
            }
            
            popStack(&parser->stack);
            if (strcmp(entry->production, "ε") != 0 && strcmp(entry->production, "epsilon") != 0) {
                pushProduction(&parser->stack, entry->production);
            }
            executeSemanticAction(parser, entry->rule_number);
        }
    }
    
    printf("\n  Analyse syntaxique terminée!\n");
    printf("  Total d'étapes: %d\n", step);
    printf("  Erreurs syntaxiques: %d\n", parser->parse_errors);

    if (has_error) {
        printf("\nParsing FAILED at word '%s' (Token: %s)\n", 
               first_error_token.lexeme, 
               tokenTypeToString(first_error_token.type));
        return false;
    }

    printf("\nParsing SUCCESS\n");
    return true; 
}
