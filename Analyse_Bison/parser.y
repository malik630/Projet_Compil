%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern int line_num;
extern int col_num;

void yyerror(const char* s);

ASTNode* root = NULL;
%}

%union {
    int ival;
    float fval;
    char* str;
    ASTNode* node;
    DataType dtype;
}

%token <str> IDENTIFIER STRING_LITERAL
%token <ival> INT_LITERAL
%token <fval> FLOAT_LITERAL

%type <node> Program Decls Decl OptInit Instrs Instr Assign Print If OptElse
%type <node> Expr Term Factor Cond
%type <dtype> Type

%token KW_BEGIN KW_PROGRAM KW_END
%token KW_SET KW_CREATE KW_RECORD KW_ARRAY KW_DICTIONARY
%token KW_INTEGER KW_STRING KW_FLOAT KW_BOOLEAN
%token KW_TRUE KW_FALSE
%token KW_WHEN KW_THEN KW_OTHERWISE KW_CASE KW_ELSE
%token KW_LOOP KW_ITERATE KW_FROM KW_TO
%token KW_PRINT KW_INPUT
%token OP_AND OP_OR OP_NOT
%token OP_EQ OP_NEQ OP_LT OP_GT OP_LTE OP_GTE
%token OP_PLUS OP_MINUS OP_MULT OP_DIV OP_MOD
%token SEP_LPAREN SEP_RPAREN SEP_LBRACKET SEP_RBRACKET
%token SEP_LBRACE SEP_RBRACE SEP_COMMA SEP_SEMICOLON SEP_DOT

%left OP_OR
%left OP_AND
%right OP_NOT
%left OP_EQ OP_NEQ OP_LT OP_GT OP_LTE OP_GTE
%left OP_PLUS OP_MINUS
%left OP_MULT OP_DIV OP_MOD
%right UMINUS

%%

Program:
    KW_BEGIN KW_PROGRAM IDENTIFIER SEP_SEMICOLON Decls Instrs KW_END KW_PROGRAM SEP_SEMICOLON
    {
        $$ = createProgramNode($3, $5, $6);
        root = $$;
        printf("\n✓ Program '%s' parsed successfully!\n", $3);
        free($3);
    }
    ;

Decls:
    Decls Decl
    {
        $$ = createDeclListNode($2, $1);
    }
    | /* empty */
    {
        $$ = NULL;
    }
    ;

Decl:
    KW_SET IDENTIFIER Type OptInit SEP_SEMICOLON
    {
        $$ = createDeclNode($2, $3, $4);
        free($2);
    }
    ;

OptInit:
    OP_EQ Expr
    {
        $$ = $2;
    }
    | /* empty */
    {
        $$ = NULL;
    }
    ;

Type:
    KW_INTEGER  { $$ = TYPE_INTEGER; }
    | KW_STRING { $$ = TYPE_STRING; }
    | KW_FLOAT  { $$ = TYPE_FLOAT; }
    | KW_BOOLEAN { $$ = TYPE_BOOLEAN; }
    ;

Instrs:
    Instrs Instr
    {
        $$ = createStmtListNode($2, $1);
    }
    | /* empty */
    {
        $$ = NULL;
    }
    ;

Instr:
    Assign  { $$ = $1; }
    | Print { $$ = $1; }
    | If    { $$ = $1; }
    ;

Assign:
    IDENTIFIER OP_EQ Expr SEP_SEMICOLON
    {
        $$ = createAssignNode($1, $3);
        free($1);
    }
    ;

Print:
    KW_PRINT Expr SEP_SEMICOLON
    {
        $$ = createPrintNode($2);
    }
    ;

If:
    KW_WHEN Cond KW_THEN Instrs OptElse KW_END KW_WHEN SEP_SEMICOLON
    {
        $$ = createIfNode($2, $4, $5);
    }
    ;

OptElse:
    KW_ELSE Instrs
    {
        $$ = $2;
    }
    | /* empty */
    {
        $$ = NULL;
    }
    ;

Expr:
    Expr OP_PLUS Term
    {
        $$ = createBinOpNode(AST_OP_ADD, $1, $3);
    }
    | Expr OP_MINUS Term
    {
        $$ = createBinOpNode(AST_OP_SUB, $1, $3);
    }
    | Term
    {
        $$ = $1;
    }
    ;

Term:
    Term OP_MULT Factor
    {
        $$ = createBinOpNode(AST_OP_MUL, $1, $3);
    }
    | Term OP_DIV Factor
    {
        $$ = createBinOpNode(AST_OP_DIV, $1, $3);
    }
    | Factor
    {
        $$ = $1;
    }
    ;

Factor:
    INT_LITERAL
    {
        $$ = createIntLiteralNode($1);
    }
    | FLOAT_LITERAL
    {
        $$ = createFloatLiteralNode($1);
    }
    | STRING_LITERAL
    {
        $$ = createStringLiteralNode($1);
        free($1);
    }
    | IDENTIFIER
    {
        $$ = createIdentifierNode($1);
        free($1);
    }
    | SEP_LPAREN Expr SEP_RPAREN
    {
        $$ = $2;
    }
    ;

Cond:
    Expr OP_EQ Expr
    {
        $$ = createBinOpNode(AST_OP_EQ, $1, $3);
    }
    | Expr OP_NEQ Expr
    {
        $$ = createBinOpNode(AST_OP_NEQ, $1, $3);
    }
    | Expr OP_LT Expr
    {
        $$ = createBinOpNode(AST_OP_LT, $1, $3);
    }
    | Expr OP_GT Expr
    {
        $$ = createBinOpNode(AST_OP_GT, $1, $3);
    }
    | Expr OP_LTE Expr
    {
        $$ = createBinOpNode(AST_OP_LTE, $1, $3);
    }
    | Expr OP_GTE Expr
    {
        $$ = createBinOpNode(AST_OP_GTE, $1, $3);
    }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error at line %d, col %d: %s\n", line_num, col_num, s);
}