#include "ll1_parser.h"
#include <stdlib.h>
#include <string.h>
//table ll1

static LL1TableEntry ll1_table_data[] = {
    // Program
    {NT_PROGRAM, KW_BEGIN, 1, "KW_BEGIN KW_PROGRAM IDENTIFIER SEP_SEMICOLON Decls Instrs KW_END KW_PROGRAM SEP_SEMICOLON"},
    
    // Decls
    {NT_DECLS, KW_SET, 2, "Decl Decls"},
    {NT_DECLS, IDENTIFIER, 3, "ε"},
    {NT_DECLS, KW_PRINT, 3, "ε"},
    {NT_DECLS, KW_IF, 3, "ε"},
    {NT_DECLS, KW_END, 3, "ε"},
    
    // Decl
    {NT_DECL, KW_SET, 4, "KW_SET IDENTIFIER Type OptInit SEP_SEMICOLON"},
    
    // OptInit
    {NT_OPTINIT, OP_EQ_TOK, 5, "OP_EQ_TOK Expr"},
    {NT_OPTINIT, SEP_SEMICOLON, 6, "ε"},
    
    // Type
    {NT_TYPE, KW_INTEGER, 7, "KW_INTEGER"},
    {NT_TYPE, KW_STRING, 8, "KW_STRING"},
    {NT_TYPE, KW_FLOAT, 9, "KW_FLOAT"},
    {NT_TYPE, KW_BOOLEAN, 10, "KW_BOOLEAN"},
    
    // Instrs
    {NT_INSTRS, IDENTIFIER, 11, "Instr Instrs"},
    {NT_INSTRS, KW_PRINT, 11, "Instr Instrs"},
    {NT_INSTRS, KW_IF, 11, "Instr Instrs"},
    {NT_INSTRS, KW_END, 12, "ε"},
    {NT_INSTRS, KW_ELSE, 12, "ε"},
    
    // Instr
    {NT_INSTR, IDENTIFIER, 13, "Assign"},
    {NT_INSTR, KW_PRINT, 14, "Print"},
    {NT_INSTR, KW_IF, 15, "If"},
    
    // Assign
    {NT_ASSIGN, IDENTIFIER, 16, "IDENTIFIER OP_EQ_TOK Expr SEP_SEMICOLON"},
    
    // Print
    {NT_PRINT, KW_PRINT, 17, "KW_PRINT Expr SEP_SEMICOLON"},
    
    // If
    {NT_IF, KW_IF, 18, "KW_IF Cond KW_THEN Instrs OptElse KW_END KW_IF SEP_SEMICOLON"},
    
    // OptElse
    {NT_OPTELSE, KW_ELSE, 19, "KW_ELSE Instrs"},
    {NT_OPTELSE, KW_END, 20, "ε"},
    
    // Expr
    {NT_EXPR, INT_LITERAL, 21, "Term ExprPrime"},
    {NT_EXPR, FLOAT_LITERAL, 21, "Term ExprPrime"},
    {NT_EXPR, STRING_LITERAL, 21, "Term ExprPrime"},
    {NT_EXPR, IDENTIFIER, 21, "Term ExprPrime"},
    {NT_EXPR, SEP_LPAREN, 21, "Term ExprPrime"},
    
    // ExprPrime
    {NT_EXPRPRIME, OP_PLUS, 22, "OP_PLUS Term ExprPrime"},
    {NT_EXPRPRIME, OP_MINUS, 23, "OP_MINUS Term ExprPrime"},
    {NT_EXPRPRIME, SEP_SEMICOLON, 24, "ε"},
    {NT_EXPRPRIME, SEP_RPAREN, 24, "ε"},
    {NT_EXPRPRIME, OP_EQ_TOK, 24, "ε"},
    {NT_EXPRPRIME, OP_NEQ_TOK, 24, "ε"},
    {NT_EXPRPRIME, OP_LT_TOK, 24, "ε"},
    {NT_EXPRPRIME, OP_GT_TOK, 24, "ε"},
    {NT_EXPRPRIME, OP_LTE_TOK, 24, "ε"},
    {NT_EXPRPRIME, OP_GTE_TOK, 24, "ε"},
    {NT_EXPRPRIME, KW_THEN, 24, "ε"},
    
    // Term
    {NT_TERM, INT_LITERAL, 25, "Factor TermPrime"},
    {NT_TERM, FLOAT_LITERAL, 25, "Factor TermPrime"},
    {NT_TERM, STRING_LITERAL, 25, "Factor TermPrime"},
    {NT_TERM, IDENTIFIER, 25, "Factor TermPrime"},
    {NT_TERM, SEP_LPAREN, 25, "Factor TermPrime"},
    
    // TermPrime
    {NT_TERMPRIME, OP_MULT, 26, "OP_MULT Factor TermPrime"},
    {NT_TERMPRIME, OP_DIV, 27, "OP_DIV Factor TermPrime"},
    {NT_TERMPRIME, OP_PLUS, 28, "ε"},
    {NT_TERMPRIME, OP_MINUS, 28, "ε"},
    {NT_TERMPRIME, SEP_SEMICOLON, 28, "ε"},
    {NT_TERMPRIME, SEP_RPAREN, 28, "ε"},
    {NT_TERMPRIME, OP_EQ_TOK, 28, "ε"},
    {NT_TERMPRIME, OP_NEQ_TOK, 28, "ε"},
    {NT_TERMPRIME, OP_LT_TOK, 28, "ε"},
    {NT_TERMPRIME, OP_GT_TOK, 28, "ε"},
    {NT_TERMPRIME, OP_LTE_TOK, 28, "ε"},
    {NT_TERMPRIME, OP_GTE_TOK, 28, "ε"},
    {NT_TERMPRIME, KW_THEN, 28, "ε"},
    
    // Factor
    {NT_FACTOR, INT_LITERAL, 29, "INT_LITERAL"},
    {NT_FACTOR, FLOAT_LITERAL, 30, "FLOAT_LITERAL"},
    {NT_FACTOR, STRING_LITERAL, 31, "STRING_LITERAL"},
    {NT_FACTOR, IDENTIFIER, 32, "IDENTIFIER"},
    {NT_FACTOR, SEP_LPAREN, 33, "SEP_LPAREN Expr SEP_RPAREN"},
    
    // Cond
    {NT_COND, INT_LITERAL, 34, "Expr RelOp Expr"},
    {NT_COND, FLOAT_LITERAL, 34, "Expr RelOp Expr"},
    {NT_COND, STRING_LITERAL, 34, "Expr RelOp Expr"},
    {NT_COND, IDENTIFIER, 34, "Expr RelOp Expr"},
    {NT_COND, SEP_LPAREN, 34, "Expr RelOp Expr"},
    
    // RelOp
    {NT_RELOP, OP_EQ_TOK, 35, "OP_EQ_TOK"},
    {NT_RELOP, OP_NEQ_TOK, 36, "OP_NEQ_TOK"},
    {NT_RELOP, OP_LT_TOK, 37, "OP_LT_TOK"},
    {NT_RELOP, OP_GT_TOK, 38, "OP_GT_TOK"},
    {NT_RELOP, OP_LTE_TOK, 39, "OP_LTE_TOK"},
    {NT_RELOP, OP_GTE_TOK, 40, "OP_GTE_TOK"},
};

void initLL1Table(LL1Parser* parser) {
    parser->table_size = sizeof(ll1_table_data) / sizeof(LL1TableEntry);
    parser->parse_table = ll1_table_data;
}

LL1TableEntry* lookupLL1Table(LL1Parser* parser, NonTerminal nt, TokenType term) {
    for (int i = 0; i < parser->table_size; i++) {
        if (parser->parse_table[i].non_terminal == nt &&
            parser->parse_table[i].terminal == term) {
            return &parser->parse_table[i];
        }
    }
    return NULL;  
}