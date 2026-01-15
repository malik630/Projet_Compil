%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "table_symboles_enrichie.h"  //  AJOUTÉ

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern int line_num;
extern int col_num;

void yyerror(const char* s);

ASTNode* root = NULL;

//  AJOUTÉ : Table des symboles globale
TableSymboles tableGlobale;
int adresseMemoire = 0;
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
    KW_BEGIN KW_PROGRAM IDENTIFIER SEP_SEMICOLON 
    {
        //  AJOUTÉ : Initialiser la table au début du programme
        initTable(&tableGlobale);
    }
    Decls Instrs KW_END KW_PROGRAM SEP_SEMICOLON
    {
        $$ = createProgramNode($3, $6, $7);
        root = $$;
        printf("\n✓ Program '%s' parsed successfully!\n", $3);
        
        //  AJOUTÉ : Afficher la table des symboles à la fin
        afficherTable(&tableGlobale);
        
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
        //  MODIFIÉ : Ajouter le symbole à la table
        Symbole sym;
        strcpy(sym.nom, $2);
        sym.typeSymbole = TYPE_VARIABLE;
        
        // Convertir DataType en TypeDonnee
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
        
        // Si initialisée, marquer comme telle
        if ($4 != NULL) {
            sym.initialise = 1;
        } else {
            sym.initialise = 0;
        }
        
        // Insérer dans la table
        if (insererSymbole(&tableGlobale, sym) == -1) {
            char msg[100];
            sprintf(msg, "Variable '%s' déjà déclarée", $2);
            yyerror(msg);
        }
        
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
        //  AJOUTÉ : Vérifications sémantiques
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
            // Marquer comme initialisée
            sym->initialise = 1;
        }
        
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
    KW_WHEN 
    {
        //  AJOUTÉ : Entrer dans une nouvelle portée
        entrerPortee(&tableGlobale);
    }
    Cond KW_THEN Instrs OptElse KW_END KW_WHEN SEP_SEMICOLON
    {
        $$ = createIfNode($3, $5, $6);
        
        //  AJOUTÉ : Sortir de la portée
        sortirPortee(&tableGlobale);
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
        //  AJOUTÉ : Vérifier que la variable existe et est initialisée
        Symbole* sym = obtenirSymbole(&tableGlobale, $1);
        
        if (sym == NULL) {
            char msg[100];
            sprintf(msg, "Variable '%s' non déclarée", $1);
            yyerror(msg);
        } else if (!sym->initialise && sym->typeSymbole != TYPE_CONSTANTE) {
            printf("Attention ligne %d : variable '%s' utilisée sans initialisation\n", 
                   line_num, $1);
        }
        
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
    fprintf(stderr, "Erreur sémantique ligne %d, col %d: %s\n", line_num, col_num, s);
}