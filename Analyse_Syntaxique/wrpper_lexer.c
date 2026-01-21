#include "lexer.h"
#include "afd_builder.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Tokenizes a source file by initializing the required AFDs and 
 * running the lexer's getNextToken loop.
 */
Token* tokenizeFile(const char* filename, int* count) {
    printf("[WRAPPER] Reading file: %s\n", filename);
    
    // Read the source code from the file
    source = readFile(filename);
    if (!source) {
        fprintf(stderr, "[WRAPPER] Error: Cannot read file %s\n", filename);
        *count = 0;
        return NULL;
    }
    
    printf("[WRAPPER] File loaded, size: %zu bytes\n", strlen(source));
    
    // CRITICAL: Initialize global AFD objects (identifier_afd, integer_afd, float_afd)
    // defined in afd_builder.c. This prevents the segfault from uninitialized pointers.
    printf("[WRAPPER] Building AFDs...\n");
    initializeAFDs();
    printf("[WRAPPER] AFDs built successfully\n");
    
    // Reset lexer positioning
    pos = 0;
    line_num = 1;
    col_num = 1;
    
    // Allocate memory for tokens
    int capacity = 1000;
    Token* tokens = malloc(sizeof(Token) * capacity);
    int token_count = 0;
    
    if (!tokens) {
        fprintf(stderr, "[WRAPPER] Memory allocation failed for tokens\n");
        *count = 0;
        return NULL;
    }
    
    Token tok;
    do {
        // Fetch the next token using the lexer logic
        tok = getNextToken();
        
        // Fix: Changed tok.col to tok.column to match your struct definition
        printf("[WRAPPER] Token %d: %s ('%s') at Line %d, Col %d\n", 
               token_count, tokenTypeToString(tok.type), tok.lexeme, tok.line, tok.column);
        
        tokens[token_count++] = tok;
        
        // Stop if we encounter a lexical error
        if (tok.type == ERROR_TOK) {
            fprintf(stderr, "[WRAPPER] Lexical error encountered near line %d\n", tok.line);
            break;
        }
        
        // Dynamic resizing
        if (token_count >= capacity) {
            capacity *= 2;
            tokens = realloc(tokens, sizeof(Token) * capacity);
            if (!tokens) {
                fprintf(stderr, "[WRAPPER] Realloc failed\n");
                break;
            }
        }
        
    } while (tok.type != END_OF_FILE);
    
    *count = token_count;
    printf("[WRAPPER] Total tokens generated: %d\n", token_count);
    
    return tokens;
}
