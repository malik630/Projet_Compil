#include "lexer.h"
#include "afd_builder.h"
#include "error_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* source = NULL;
int pos = 0;
int line_num = 1;
int col_num = 1;

char peek() {
    return source[pos];
}

char advance() {
    char ch = source[pos++];
    if (ch == '\n') {
        line_num++;
        col_num = 1;
    } else {
        col_num++;
    }
    return ch;
}

void skipWhitespace() {
    while (isspace(peek())) advance();
}

TokenType checkKeyword(const char* str) {
    struct { const char* kw; TokenType type; } keywords[] = {
        {"BEGIN", KW_BEGIN}, {"PROGRAM", KW_PROGRAM}, {"END", KW_END},
        {"SET", KW_SET}, {"INTEGER", KW_INTEGER}, {"STRING", KW_STRING},
        {"FLOAT", KW_FLOAT}, {"BOOLEAN", KW_BOOLEAN},
        {"true", KW_TRUE}, {"false", KW_FALSE},
        {"CREATE", KW_CREATE}, {"RECORD", KW_RECORD},
        {"ARRAY", KW_ARRAY}, {"DICTIONARY", KW_DICTIONARY},
        {"WHEN", KW_WHEN}, {"THEN", KW_THEN}, {"OTHERWISE", KW_OTHERWISE},
        {"CASE", KW_CASE}, {"ELSE", KW_ELSE},
        {"LOOP", KW_LOOP}, {"ITERATE", KW_ITERATE},
        {"FROM", KW_FROM}, {"TO", KW_TO},
        {"PRINT", KW_PRINT}, {"INPUT", KW_INPUT},
        {"AND", KW_AND}, {"OR", KW_OR}, {"NOT", KW_NOT},
        {NULL, IDENTIFIER}
    };
    
    for (int i = 0; keywords[i].kw != NULL; i++) {
        if (strcmp(str, keywords[i].kw) == 0)
            return keywords[i].type;
    }
    return IDENTIFIER;
}

Token scanWithAFD(AFD* afd, TokenType default_type) {
    Token token;
    token.line = line_num;
    token.column = col_num;
    int i = 0;
    
    int current_state = afd->start_state;
    int last_accept_state = -1;
    int last_accept_pos = 0;
    
    int start_pos = pos;
    
    while (peek() != '\0' && i < 255) {
        char ch = peek();
        int next_state = afd->transitions[current_state][(unsigned char)ch];
        
        if (next_state == -1) break;
        
        token.lexeme[i++] = advance();
        current_state = next_state;
        
        if (afd->final_states[current_state]) {
            last_accept_state = current_state;
            last_accept_pos = i;
        }
    }
    
    if (last_accept_state != -1) {
        token.lexeme[last_accept_pos] = '\0';
        token.type = (default_type == IDENTIFIER) ? 
                     checkKeyword(token.lexeme) : default_type;
        
        pos = start_pos + last_accept_pos;
        return token;
    }
    
    token.type = ERROR_TOK;
    strcpy(token.lexeme, "ERROR");
    return token;
}

Token scanString() {
    Token token;
    token.line = line_num;
    token.column = col_num;
    int i = 0;
    
    if (peek() != '\'') {
        token.type = ERROR_TOK;
        return token;
    }
    
    advance();
    
    while (peek() != '\'' && peek() != '\n' && peek() != '\0' && i < 255) {
        token.lexeme[i++] = advance();
    }
    
    if (peek() == '\'') {
        advance();
        token.lexeme[i] = '\0';
        token.type = STRING_LITERAL;
    } else {
        reportError(line_num, col_num, "unterminated string");
        token.type = ERROR_TOK;
    }
    
    return token;
}

Token scanComment() {
    Token token;
    token.line = line_num;
    token.column = col_num;
    token.type = COMMENT;
    
    if (peek() == '-' && source[pos+1] == '-') {
        advance(); advance();
        while (peek() != '\n' && peek() != '\0') advance();
        strcpy(token.lexeme, "-- comment");
    } else if (peek() == '/' && source[pos+1] == '*') {
        advance(); advance();
        while (1) {
            if (peek() == '\0') {
                reportError(line_num, col_num, "unterminated comment");
                token.type = ERROR_TOK;
                break;
            }
            if (peek() == '*' && source[pos+1] == '/') {
                advance(); advance();
                break;
            }
            advance();
        }
        strcpy(token.lexeme, "/* comment */");
    }
    
    return token;
}

Token scanOperator() {
    Token token;
    token.line = line_num;
    token.column = col_num;
    
    char ch = advance();
    token.lexeme[0] = ch;
    token.lexeme[1] = '\0';
    
    if (ch == '<') {
        if (peek() == '=') {
            token.lexeme[1] = advance();
            token.lexeme[2] = '\0';
            token.type = OP_LTE_TOK;
        } else if (peek() == '>') {
            token.lexeme[1] = advance();
            token.lexeme[2] = '\0';
            token.type = OP_NEQ_TOK;
        } else {
            token.type = OP_LT_TOK;
        }
    } else if (ch == '>') {
        if (peek() == '=') {
            token.lexeme[1] = advance();
            token.lexeme[2] = '\0';
            token.type = OP_GTE_TOK;
        } else {
            token.type = OP_GT_TOK;
        }
    } else if (ch == '=') {
        token.type = OP_EQ_TOK;
    }
    
    return token;
}

Token getNextToken() {
    skipWhitespace();
    
    Token token;
    token.line = line_num;
    token.column = col_num;
    
    char ch = peek();
    
    if (ch == '\0') {
        token.type = END_OF_FILE;
        strcpy(token.lexeme, "EOF");
        return token;
    }
    
    if (ch == '-' && source[pos+1] == '-') return scanComment();
    if (ch == '/' && source[pos+1] == '*') return scanComment();
    if (ch == '\'') return scanString();
    
    if (isalpha(ch) || ch == '_') {
        return scanWithAFD(&identifier_afd, IDENTIFIER);
    }
    
    if (isdigit(ch)) {
        Token int_token = scanWithAFD(&integer_afd, INT_LITERAL);
        if (peek() == '.') {
            int saved_pos = pos;
            advance();
            if (isdigit(peek())) {
                pos = saved_pos - strlen(int_token.lexeme);
                return scanWithAFD(&float_afd, FLOAT_LITERAL);
            } else {
                pos = saved_pos;
            }
        }
        return int_token;
    }
    
    if (ch == '<' || ch == '>' || ch == '=') {
        return scanOperator();
    }
    
    advance();
    token.lexeme[0] = ch;
    token.lexeme[1] = '\0';
    
    switch (ch) {
        case '+': token.type = OP_PLUS; break;
        case '-': token.type = OP_MINUS; break;
        case '*': token.type = OP_MULT; break;
        case '/': token.type = OP_DIV; break;
        case '%': token.type = OP_MOD; break;
        case '(': token.type = SEP_LPAREN; break;
        case ')': token.type = SEP_RPAREN; break;
        case '[': token.type = SEP_LBRACKET; break;
        case ']': token.type = SEP_RBRACKET; break;
        case '{': token.type = SEP_LBRACE; break;
        case '}': token.type = SEP_RBRACE; break;
        case ',': token.type = SEP_COMMA; break;
        case ';': token.type = SEP_SEMICOLON; break;
        case '.': token.type = SEP_DOT; break;
        default: 
            reportError(line_num, col_num, "invalid character");
            token.type = ERROR_TOK;
            break;
    }
    
    return token;
}

const char* tokenTypeToString(TokenType type) {
    switch (type) {
        case KW_BEGIN: return "KW_BEGIN";
        case KW_PROGRAM: return "KW_PROGRAM";
        case KW_END: return "KW_END";
        case KW_SET: return "KW_SET";
        case KW_INTEGER: return "KW_INTEGER";
        case KW_STRING: return "KW_STRING";
        case KW_FLOAT: return "KW_FLOAT";
        case KW_PRINT: return "KW_PRINT";
        case IDENTIFIER: return "IDENTIFIER";
        case INT_LITERAL: return "INT_LITERAL";
        case FLOAT_LITERAL: return "FLOAT_LITERAL";
        case STRING_LITERAL: return "STRING_LITERAL";
        case OP_EQ_TOK: return "OP_EQ";
        case OP_PLUS: return "OP_PLUS";
        case SEP_SEMICOLON: return "SEP_SEMICOLON";
        case COMMENT: return "COMMENT";
        case END_OF_FILE: return "END_OF_FILE";
        case ERROR_TOK: return "ERROR";
        default: return "UNKNOWN";
    }
}

void printToken(Token token) {
    printf("Line %3d, Col %3d: %-20s '%s'\n", 
           token.line, token.column, 
           tokenTypeToString(token.type), 
           token.lexeme);
}

char* readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erreur ouverture fichier");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(size + 1);
    if (!buffer) {
        perror("Erreur allocation mémoire");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, size, file);
    buffer[size] = '\0';

    fclose(file);
    return buffer;
}