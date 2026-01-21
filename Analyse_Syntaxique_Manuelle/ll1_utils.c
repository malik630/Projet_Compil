#include "ll1_parser.h"
#include <stdio.h>
#include <string.h>

const char* nonTerminalToString(NonTerminal nt) {
    switch(nt) {
        case NT_PROGRAM: return "Program";
        case NT_DECLS: return "Decls";
        case NT_DECL: return "Decl";
        case NT_TYPE: return "Type";
        case NT_OPTINIT: return "OptInit";
        case NT_INSTRS: return "Instrs";
        case NT_INSTR: return "Instr";
        case NT_ASSIGN: return "Assign";
        case NT_PRINT: return "Print";
        case NT_WHEN: return "WHEN";
        case NT_OPTOTHERWISE: return "OptOTHERWISE";
        case NT_EXPR: return "Expr";
        case NT_EXPRPRIME: return "ExprPrime";
        case NT_TERM: return "Term";
        case NT_TERMPRIME: return "TermPrime";
        case NT_FACTOR: return "Factor";
        case NT_COND: return "Cond";
        case NT_RELOP: return "RelOp";
        default: return "UNKNOWN";
    }
}

TokenType stringToTokenType(const char* str) {
    if (strcmp(str, "KW_BEGIN") == 0) return KW_BEGIN;
    if (strcmp(str, "KW_PROGRAM") == 0) return KW_PROGRAM;
    if (strcmp(str, "KW_END") == 0) return KW_END;
    if (strcmp(str, "KW_SET") == 0) return KW_SET;
    if (strcmp(str, "KW_INTEGER") == 0) return KW_INTEGER;
    if (strcmp(str, "KW_STRING") == 0) return KW_STRING;
    if (strcmp(str, "KW_FLOAT") == 0) return KW_FLOAT;
    if (strcmp(str, "KW_BOOLEAN") == 0) return KW_BOOLEAN;
    if (strcmp(str, "KW_PRINT") == 0) return KW_PRINT;
    if (strcmp(str, "KW_WHEN") == 0) return KW_WHEN;
    if (strcmp(str, "KW_THEN") == 0) return KW_THEN;
    if (strcmp(str, "KW_OTHERWISE") == 0) return KW_OTHERWISE;
    if (strcmp(str, "IDENTIFIER") == 0) return IDENTIFIER;
    if (strcmp(str, "INT_LITERAL") == 0) return INT_LITERAL;
    if (strcmp(str, "FLOAT_LITERAL") == 0) return FLOAT_LITERAL;
    if (strcmp(str, "STRING_LITERAL") == 0) return STRING_LITERAL;
    if (strcmp(str, "OP_EQ_TOK") == 0) return OP_EQ_TOK;
    if (strcmp(str, "OP_NEQ_TOK") == 0) return OP_NEQ_TOK;
    if (strcmp(str, "OP_LT_TOK") == 0) return OP_LT_TOK;
    if (strcmp(str, "OP_GT_TOK") == 0) return OP_GT_TOK;
    if (strcmp(str, "OP_LTE_TOK") == 0) return OP_LTE_TOK;
    if (strcmp(str, "OP_GTE_TOK") == 0) return OP_GTE_TOK;
    if (strcmp(str, "OP_PLUS") == 0) return OP_PLUS;
    if (strcmp(str, "OP_MINUS") == 0) return OP_MINUS;
    if (strcmp(str, "OP_MULT") == 0) return OP_MULT;
    if (strcmp(str, "OP_DIV") == 0) return OP_DIV;
    if (strcmp(str, "SEP_SEMICOLON") == 0) return SEP_SEMICOLON;
    if (strcmp(str, "SEP_LPAREN") == 0) return SEP_LPAREN;
    if (strcmp(str, "SEP_RPAREN") == 0) return SEP_RPAREN;
    if (strcmp(str, "OP_EQ") == 0) return OP_EQ_TOK; 
    if (strcmp(str, "OP_NEQ") == 0) return OP_NEQ_TOK;
    return ERROR_TOK;
}

NonTerminal stringToNonTerminal(const char* str) {
    if (strcmp(str, "Program") == 0) return NT_PROGRAM;
    if (strcmp(str, "Decls") == 0) return NT_DECLS;
    if (strcmp(str, "Decl") == 0) return NT_DECL;
    if (strcmp(str, "Type") == 0) return NT_TYPE;
    if (strcmp(str, "OptInit") == 0) return NT_OPTINIT;
    if (strcmp(str, "Instrs") == 0) return NT_INSTRS;
    if (strcmp(str, "Instr") == 0) return NT_INSTR;
    if (strcmp(str, "Assign") == 0) return NT_ASSIGN;
    if (strcmp(str, "Print") == 0) return NT_PRINT;
    if (strcmp(str, "WHEN") == 0) return NT_WHEN;
    if (strcmp(str, "OptOTHERWISE") == 0) return NT_OPTOTHERWISE;
    if (strcmp(str, "Expr") == 0) return NT_EXPR;
    if (strcmp(str, "ExprPrime") == 0) return NT_EXPRPRIME;
    if (strcmp(str, "Term") == 0) return NT_TERM;
    if (strcmp(str, "TermPrime") == 0) return NT_TERMPRIME;
    if (strcmp(str, "Factor") == 0) return NT_FACTOR;
    if (strcmp(str, "Cond") == 0) return NT_COND;
    if (strcmp(str, "RelOp") == 0) return NT_RELOP;
    return NT_PROGRAM;
}

void reportSyntaxError(LL1Parser* parser, const char* message) {
    Token current = parser->tokens[parser->current_token];
    fprintf(stderr, "File \"source.ql\", line %d, col %d: Syntax error: %s\n",
            current.line, current.column, message);
    parser->parse_errors++;
}

void pushProduction(ParseStack* stack, const char* production) {
    if (strcmp(production, "ε") == 0 || strcmp(production, "epsilon") == 0) {
        // Si epsilon on n'empile rien
        return;
    }

    char prod_copy[512];
    strncpy(prod_copy, production, 511);
    prod_copy[511] = '\0';

    char* tokens[50]; 
    int token_count = 0;
    
    char* token = strtok(prod_copy, " ");
    while (token != NULL && token_count < 50) {
        if (strcmp(token, "ε") != 0 && strcmp(token, "epsilon") != 0) {
            tokens[token_count++] = token;
        }
        token = strtok(NULL, " ");
    }

    for (int i = token_count - 1; i >= 0; i--) {
        StackSymbol sym = stringToSymbol(tokens[i]);
        pushStack(stack, sym);
    }
}

StackSymbol stringToSymbol(const char* str) {
    StackSymbol sym;
    
    if (strcmp(str, "ε") == 0 || strcmp(str, "epsilon") == 0) {
        sym.kind = SYMBOL_EOF;
        return sym;
    }

    TokenType terminal = stringToTokenType(str);
    if (terminal != ERROR_TOK) {
        sym.kind = SYMBOL_TERMINAL;
        sym.value.terminal = terminal;
        return sym;
    }

    NonTerminal nt = stringToNonTerminal(str);
    sym.kind = SYMBOL_NONTERMINAL;
    sym.value.non_terminal = nt;
    return sym;
}
