%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "table_symboles_enrichie.h"  /**** ADDED ****/

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern int line_num;
extern int col_num;

void yyerror(const char* s);

ASTNode* root = NULL;

/**** ADDED - START ****/
TableSymboles tableGlobale;
int adresseMemoire = 0;
/**** ADDED - END ****/
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

%type <node> Program Decl OptInit Instrs Instr Assign Print If OptElse
%type <node> Expr Term Factor Cond While For Case CaseList CaseItem Input
%type <node> RecordDecl FieldList Field ArrayDecl DictDecl ExprList ArrayInit
%type <node> ForEach
%type <dtype> Type

%token KW_BEGIN KW_PROGRAM KW_END
%token KW_SET KW_CREATE KW_RECORD KW_ARRAY KW_DICTIONARY
%token KW_INTEGER KW_STRING KW_FLOAT KW_BOOLEAN
%token KW_TRUE KW_FALSE
%token KW_WHEN KW_CASE_WHEN KW_THEN KW_OTHERWISE KW_CASE KW_ELSE
%token KW_LOOP KW_ITERATE KW_FROM KW_TO
%token KW_FOREACH KW_IN
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
    KW_BEGIN KW_PROGRAM IDENTIFIER SEP_SEMICOLON 
    {
        /**** ADDED - START ****/
        initTable(&tableGlobale);
        /**** ADDED - END ****/
    }
    Instrs KW_END KW_PROGRAM SEP_SEMICOLON
    {
        $$ = createProgramNode($3, NULL, $6); 
        root = $$;
        printf("\n✓ Program '%s' parsed successfully!\n", $3);
        
        /**** ADDED - START ****/
        afficherTable(&tableGlobale);
        /**** ADDED - END ****/
        
        free($3);
    }
    ;

Decl:
    KW_SET IDENTIFIER Type OptInit SEP_SEMICOLON
    {
        /**** ADDED - START ****/
        Symbole sym;
        strcpy(sym.nom, $2);
        sym.typeSymbole = TYPE_VARIABLE;
        
        switch($3) {
            case TYPE_INTEGER:
                sym.typeDonnee = DATA_ENTIER;
                break;
            case TYPE_FLOAT:
                sym.typeDonnee = DATA_REEL;
                break;
            case TYPE_STRING:
                sym.typeDonnee = DATA_CHAINE;
                break;
            case TYPE_BOOLEAN:
                sym.typeDonnee = DATA_BOOLEEN;
                break;
        }
        
        sym.portee = tableGlobale.niveauPortee;
        sym.adresse = adresseMemoire++;
        sym.initialise = ($4 != NULL) ? 1 : 0;
        
        if (insererSymbole(&tableGlobale, sym) == -1) {
            char msg[100];
            sprintf(msg, "Variable '%s' déjà déclarée", $2);
            yyerror(msg);
        }
        /**** ADDED - END ****/
        
        $$ = createDeclNode($2, $3, $4);
        free($2);
    }
    | KW_SET IDENTIFIER IDENTIFIER OptInit SEP_SEMICOLON
    {
        /**** ADDED - START ****/
        Symbole sym;
        strcpy(sym.nom, $2);
        sym.typeSymbole = TYPE_VARIABLE;
        sym.typeDonnee = DATA_ENREGISTREMENT;
        sym.portee = tableGlobale.niveauPortee;
        sym.adresse = adresseMemoire++;
        sym.initialise = ($4 != NULL) ? 1 : 0;
        
        if (insererSymbole(&tableGlobale, sym) == -1) {
            char msg[100];
            sprintf(msg, "Variable '%s' déjà déclarée", $2);
            yyerror(msg);
        }
        /**** ADDED - END ****/
        
        $$ = createRecordInstanceNode($2, $3, $4);
        free($2); free($3);
    }
    | RecordDecl { $$ = $1; }
    | ArrayDecl  { $$ = $1; }
    | DictDecl   { $$ = $1; }
    ;

Type:
    KW_INTEGER   { $$ = TYPE_INTEGER; }
    | KW_STRING  { $$ = TYPE_STRING; }
    | KW_FLOAT   { $$ = TYPE_FLOAT; }
    | KW_BOOLEAN { $$ = TYPE_BOOLEAN; }
    ;

RecordDecl:
    KW_CREATE KW_RECORD IDENTIFIER SEP_LPAREN FieldList SEP_RPAREN SEP_SEMICOLON
    {
        /**** ADDED - START ****/
        Symbole sym;
        strcpy(sym.nom, $3);
        sym.typeSymbole = TYPE_CONSTANTE;
        sym.typeDonnee = DATA_ENREGISTREMENT;
        sym.portee = tableGlobale.niveauPortee;
        sym.adresse = adresseMemoire++;
        sym.initialise = 1;
        
        if (insererSymbole(&tableGlobale, sym) == -1) {
            char msg[100];
            sprintf(msg, "Record '%s' déjà déclaré", $3);
            yyerror(msg);
        }
        /**** ADDED - END ****/
        
        $$ = createRecordDeclNode($3, $5);
        free($3);
    }
    ;

FieldList:
    Field                       { $$ = $1; }
    | FieldList SEP_COMMA Field { $$ = createFieldListNode($3, $1); }
    ;

Field:
    IDENTIFIER Type { $$ = createFieldNode($1, $2); free($1); }
    ;

ArrayDecl:
    KW_SET IDENTIFIER KW_ARRAY SEP_LBRACKET Type SEP_COMMA INT_LITERAL SEP_RBRACKET ArrayInit SEP_SEMICOLON
    {
        /**** ADDED - START ****/
        Symbole sym;
        strcpy(sym.nom, $2);
        sym.typeSymbole = TYPE_VARIABLE;
        sym.typeDonnee = DATA_TABLEAU;
        sym.portee = tableGlobale.niveauPortee;
        sym.adresse = adresseMemoire++;
        sym.initialise = ($9 != NULL) ? 1 : 0;
        
        if (insererSymbole(&tableGlobale, sym) == -1) {
            char msg[100];
            sprintf(msg, "Array '%s' déjà déclaré", $2);
            yyerror(msg);
        }
        /**** ADDED - END ****/
        
        $$ = createArrayDeclNode($2, $5, $7, $9);
        free($2);
    }
    ;

ArrayInit:
    OP_EQ SEP_LBRACE ExprList SEP_RBRACE { $$ = $3; }
    | OP_EQ Expr                         { $$ = $2; }
    | /* empty */                        { $$ = NULL; }
    ;

DictDecl:
    KW_SET IDENTIFIER KW_DICTIONARY OP_LT Type SEP_COMMA Type OP_GT SEP_SEMICOLON
    {
        /**** ADDED - START ****/
        Symbole sym;
        strcpy(sym.nom, $2);
        sym.typeSymbole = TYPE_VARIABLE;
        sym.typeDonnee = DATA_DICTIONNAIRE;
        sym.portee = tableGlobale.niveauPortee;
        sym.adresse = adresseMemoire++;
        sym.initialise = 0;
        
        if (insererSymbole(&tableGlobale, sym) == -1) {
            char msg[100];
            sprintf(msg, "Dictionary '%s' déjà déclaré", $2);
            yyerror(msg);
        }
        /**** ADDED - END ****/
        
        $$ = createDictDeclNode($2, $5, $7);
        free($2);
    }
    ;

OptInit:
    OP_EQ Expr    { $$ = $2; }
    | /* empty */ { $$ = NULL; }
    ;

ExprList:
    Expr                        { $$ = createExprListNode($1, NULL); }
    | ExprList SEP_COMMA Expr   { $$ = createExprListNode($3, $1); }
    ;

Instrs:
    /* empty */     { $$ = NULL; }
    | Instrs Instr  { $$ = createStmtListNode($2, $1); }
    ;

Instr:
    Assign      { $$ = $1; }
    | Print     { $$ = $1; }
    | If        { $$ = $1; }
    | While     { $$ = $1; }
    | For       { $$ = $1; }
    | Case      { $$ = $1; }
    | Input     { $$ = $1; }
    | ForEach   { $$ = $1; }
    | Decl      { $$ = $1; }
    ;

Assign:
    IDENTIFIER OP_EQ Expr SEP_SEMICOLON
    {
        /**** ADDED - START ****/
        Symbole* sym = obtenirSymbole(&tableGlobale, $1);
        
        if (sym == NULL) {
            char msg[100];
            sprintf(msg, "Variable '%s' non déclarée", $1);
            yyerror(msg);
        } else if (sym->typeSymbole == TYPE_CONSTANTE) {
            char msg[100];
            sprintf(msg, "Impossible de modifier la constante '%s'", $1);
            yyerror(msg);
        } else {
            sym->initialise = 1;
        }
        /**** ADDED - END ****/
        
        $$ = createAssignNode($1, $3);
        free($1);
    }
    | IDENTIFIER SEP_DOT IDENTIFIER OP_EQ Expr SEP_SEMICOLON
    {
        /**** ADDED - START ****/
        Symbole* sym = obtenirSymbole(&tableGlobale, $1);
        
        if (sym == NULL) {
            char msg[100];
            sprintf(msg, "Record '%s' non déclaré", $1);
            yyerror(msg);
        }
        /**** ADDED - END ****/
        
        $$ = createRecordAccessAssignNode($1, $3, $5);
        free($1); free($3);
    }
    | IDENTIFIER SEP_LBRACKET Expr SEP_RBRACKET OP_EQ Expr SEP_SEMICOLON
    {
        /**** ADDED - START ****/
        Symbole* sym = obtenirSymbole(&tableGlobale, $1);
        
        if (sym == NULL) {
            char msg[100];
            sprintf(msg, "Array '%s' non déclaré", $1);
            yyerror(msg);
        }
        /**** ADDED - END ****/
        
        $$ = createArrayAccessAssignNode($1, $3, $6);
        free($1);
    }
    ;

Print:
    KW_PRINT Expr SEP_SEMICOLON { $$ = createPrintNode($2); }
    ;

Input:
    KW_INPUT IDENTIFIER SEP_SEMICOLON 
    { 
        /**** ADDED - START ****/
        Symbole* sym = obtenirSymbole(&tableGlobale, $2);
        
        if (sym == NULL) {
            char msg[100];
            sprintf(msg, "Variable '%s' non déclarée", $2);
            yyerror(msg);
        } else {
            sym->initialise = 1;
        }
        /**** ADDED - END ****/
        
        $$ = createInputNode($2); 
        free($2); 
    }
    ;

If:
    KW_WHEN Cond KW_THEN 
    {
        /**** ADDED - START ****/
        entrerPortee(&tableGlobale);
        /**** ADDED - END ****/
    }
    Instrs OptElse 
    {
        /**** ADDED - START ****/
        sortirPortee(&tableGlobale);
        /**** ADDED - END ****/
    }
    KW_END KW_WHEN SEP_SEMICOLON
    {
        $$ = createIfNode($2, $5, $6);
    }
    ;

OptElse:
    KW_ELSE Instrs        { $$ = $2; }
    | KW_OTHERWISE Instrs { $$ = $2; }
    | /* empty */         { $$ = NULL; }
    ;

While:
    KW_LOOP KW_WHEN Cond 
    {
        /**** ADDED - START ****/
        entrerPortee(&tableGlobale);
        /**** ADDED - END ****/
    }
    Instrs 
    {
        /**** ADDED - START ****/
        sortirPortee(&tableGlobale);
        /**** ADDED - END ****/
    }
    KW_END KW_LOOP SEP_SEMICOLON
    {
        $$ = createWhileNode($3, $5);
    }
    ;

For:
    KW_LOOP KW_ITERATE IDENTIFIER 
    {
        /**** ADDED - START ****/
        entrerPortee(&tableGlobale);
        
        Symbole sym;
        strcpy(sym.nom, $3);
        sym.typeSymbole = TYPE_VARIABLE;
        sym.typeDonnee = DATA_ENTIER;
        sym.portee = tableGlobale.niveauPortee;
        sym.adresse = adresseMemoire++;
        sym.initialise = 1;
        
        if (insererSymbole(&tableGlobale, sym) == -1) {
            char msg[100];
            sprintf(msg, "Variable '%s' déjà déclarée", $3);
            yyerror(msg);
        }
        /**** ADDED - END ****/
    }
    KW_FROM Expr KW_TO Expr Instrs 
    {
        /**** ADDED - START ****/
        sortirPortee(&tableGlobale);
        /**** ADDED - END ****/
    }
    KW_END KW_LOOP SEP_SEMICOLON
    {
        $$ = createForNode($3, $6, $8, $9);
        free($3);
    }
    ;

ForEach:
    KW_FOREACH IDENTIFIER KW_IN IDENTIFIER 
    {
        /**** ADDED - START ****/
        entrerPortee(&tableGlobale);
        
        Symbole* arraySym = obtenirSymbole(&tableGlobale, $4);
        if (arraySym == NULL) {
            char msg[100];
            sprintf(msg, "Array '%s' non déclaré", $4);
            yyerror(msg);
        }
        
        Symbole sym;
        strcpy(sym.nom, $2);
        sym.typeSymbole = TYPE_VARIABLE;
        sym.typeDonnee = DATA_ENTIER;
        sym.portee = tableGlobale.niveauPortee;
        sym.adresse = adresseMemoire++;
        sym.initialise = 1;
        
        if (insererSymbole(&tableGlobale, sym) == -1) {
            char msg[100];
            sprintf(msg, "Variable '%s' déjà déclarée", $2);
            yyerror(msg);
        }
        /**** ADDED - END ****/
    }
    SEP_LBRACE Instrs 
    {
        /**** ADDED - START ****/
        sortirPortee(&tableGlobale);
        /**** ADDED - END ****/
    }
    SEP_RBRACE
    {
        $$ = createForEachNode($2, $4, $7);
        free($2); free($4);
    }
    ;

Case:
    KW_CASE CaseList 
    {
        /**** ADDED - START ****/
        entrerPortee(&tableGlobale);
        /**** ADDED - END ****/
    }
    KW_END KW_CASE 
    {
        /**** ADDED - START ****/
        sortirPortee(&tableGlobale);
        /**** ADDED - END ****/
    }
    SEP_SEMICOLON
    {
        $$ = createCaseNode($2, NULL);
    }
    | KW_CASE CaseList KW_ELSE 
    {
        /**** ADDED - START ****/
        entrerPortee(&tableGlobale);
        /**** ADDED - END ****/
    }
    Instrs KW_END KW_CASE 
    {
        /**** ADDED - START ****/
        sortirPortee(&tableGlobale);
        /**** ADDED - END ****/
    }
    SEP_SEMICOLON
    {
        $$ = createCaseNode($2, $5);
    }
    ;

CaseList:
    CaseItem { $$ = $1; }
    | CaseList CaseItem 
    {
        ASTNode* temp = $1;
        while (temp->data.caseItem.next != NULL) {
            temp = temp->data.caseItem.next;
        }
        temp->data.caseItem.next = $2;
        $$ = $1;
    }
    ;

CaseItem:
    KW_CASE_WHEN Cond KW_THEN Instrs
    {
        $$ = createCaseItemNode($2, $4, NULL);
    }
    ;

Expr:
    Expr OP_PLUS Term     { $$ = createBinOpNode(AST_OP_ADD, $1, $3); }
    | Expr OP_MINUS Term    { $$ = createBinOpNode(AST_OP_SUB, $1, $3); }
    | Term                  { $$ = $1; }
    ;

Term:
    Term OP_MULT Factor   { $$ = createBinOpNode(AST_OP_MUL, $1, $3); }
    | Term OP_DIV Factor    { $$ = createBinOpNode(AST_OP_DIV, $1, $3); }
    | Term OP_MOD Factor    { $$ = createBinOpNode(AST_OP_MOD, $1, $3); }
    | Factor                { $$ = $1; }
    ;

Factor:
    INT_LITERAL        { $$ = createIntLiteralNode($1); }
    | FLOAT_LITERAL    { $$ = createFloatLiteralNode($1); }
    | STRING_LITERAL   { $$ = createStringLiteralNode($1); free($1); }
    | KW_TRUE          { $$ = createBoolLiteralNode(1); }
    | KW_FALSE         { $$ = createBoolLiteralNode(0); }
    | IDENTIFIER       
    { 
        /**** ADDED - START ****/
        Symbole* sym = obtenirSymbole(&tableGlobale, $1);
        
        if (sym == NULL) {
            char msg[100];
            sprintf(msg, "Variable '%s' non déclarée", $1);
            yyerror(msg);
        } else if (!sym->initialise && sym->typeSymbole != TYPE_CONSTANTE) {
            printf("Attention ligne %d : variable '%s' utilisée sans initialisation\n", 
                   line_num, $1);
        }
        /**** ADDED - END ****/
        
        $$ = createIdentifierNode($1); 
        free($1); 
    }
    | IDENTIFIER SEP_DOT IDENTIFIER 
    { 
        /**** ADDED - START ****/
        Symbole* sym = obtenirSymbole(&tableGlobale, $1);
        
        if (sym == NULL) {
            char msg[100];
            sprintf(msg, "Record '%s' non déclaré", $1);
            yyerror(msg);
        }
        /**** ADDED - END ****/
        
        $$ = createRecordAccessNode($1, $3); 
        free($1); free($3); 
    }
    | IDENTIFIER SEP_LBRACKET Expr SEP_RBRACKET 
    { 
        /**** ADDED - START ****/
        Symbole* sym = obtenirSymbole(&tableGlobale, $1);
        
        if (sym == NULL) {
            char msg[100];
            sprintf(msg, "Array '%s' non déclaré", $1);
            yyerror(msg);
        }
        /**** ADDED - END ****/
        
        $$ = createArrayAccessNode($1, $3); 
        free($1); 
    }
    | SEP_LPAREN Expr SEP_RPAREN { $$ = $2; }
    | OP_MINUS Factor %prec UMINUS { $$ = createUnaryOpNode(AST_OP_NEG, $2); }
    ;

Cond:
    Cond OP_AND Cond    { $$ = createBinOpNode(AST_OP_AND, $1, $3); }
    | Cond OP_OR Cond     { $$ = createBinOpNode(AST_OP_OR, $1, $3); }
    | OP_NOT Cond         { $$ = createUnaryOpNode(AST_OP_NOT, $2); }
    | Expr OP_EQ Expr     { $$ = createBinOpNode(AST_OP_EQ, $1, $3); }
    | Expr OP_NEQ Expr    { $$ = createBinOpNode(AST_OP_NEQ, $1, $3); }
    | Expr OP_LT Expr     { $$ = createBinOpNode(AST_OP_LT, $1, $3); }
    | Expr OP_GT Expr     { $$ = createBinOpNode(AST_OP_GT, $1, $3); }
    | Expr OP_LTE Expr    { $$ = createBinOpNode(AST_OP_LTE, $1, $3); }
    | Expr OP_GTE Expr    { $$ = createBinOpNode(AST_OP_GTE, $1, $3); }
    | SEP_LPAREN Cond SEP_RPAREN { $$ = $2; }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error at line %d, col %d: %s\n", line_num, col_num, s);
}