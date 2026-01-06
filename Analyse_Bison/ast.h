#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*les types des noeuds*/

typedef enum {
    NODE_PROGRAM, 
    NODE_DECL_LIST,
    NODE_DECL,
    NODE_STMT_LIST,
    NODE_ASSIGN,
    NODE_PRINT,
    NODE_IF,
    NODE_EXPR_BINOP,
    NODE_EXPR_LITERAL,
    NODE_EXPR_IDENTIFIER,
    NODE_CONDITION
} NodeType;

/* Renomer pour eviter les conflicts */
typedef enum {
    AST_OP_ADD,
    AST_OP_SUB,
    AST_OP_MUL,
    AST_OP_DIV,
    AST_OP_MOD,
    AST_OP_EQ,
    AST_OP_NEQ,
    AST_OP_LT,
    AST_OP_GT,
    AST_OP_LTE,
    AST_OP_GTE
} OperatorType;

typedef enum {
    TYPE_INTEGER,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_BOOLEAN
} DataType;

/*La structure des noeuds sur l'arbre*/

typedef struct ASTNode {
    NodeType type;
    int line;
    int column;
    
    union {
        /* Program */
        struct {
            char* name;
            struct ASTNode* declarations;
            struct ASTNode* statements;
        } program;
        
        /* Declaration  */
        struct {
            char* identifier;
            DataType dataType;
            struct ASTNode* initializer;  /* NULL if not initialized */
            struct ASTNode* next;         /* Next declaration in list */
        } declaration;
        
        /* Assignment  */
        struct {
            char* identifier;
            struct ASTNode* expression;
        } assignment;
        
        /* Print  */
        struct {
            struct ASTNode* expression;
        } print;
        
        /* If */
        struct {
            struct ASTNode* condition;
            struct ASTNode* then_block;
            struct ASTNode* else_block;  /* NULL if no else */
        } ifStmt;
        
        /* Binary operation */
        struct {
            OperatorType op;
            struct ASTNode* left;
            struct ASTNode* right;
        } binOp;
        
        /* Literal  */
        struct {
            union {
                int intValue;
                float floatValue;
                char* stringValue;
            } value;
            DataType literalType;
        } literal;
        
        /* Identifier  */
        struct {
            char* name;
        } identifier;
        
        /* Statement  */
        struct {
            struct ASTNode* statement;
            struct ASTNode* next;
        } stmtList;
    } data;
} ASTNode;

/*Creation des fonctions de creation des noeuds*/

/* Program */
ASTNode* createProgramNode(char* name, ASTNode* decls, ASTNode* stmts);

/* Declarations */
ASTNode* createDeclNode(char* identifier, DataType type, ASTNode* initializer);
ASTNode* createDeclListNode(ASTNode* decl, ASTNode* next);

/* Statements */
ASTNode* createAssignNode(char* identifier, ASTNode* expr);
ASTNode* createPrintNode(ASTNode* expr);
ASTNode* createIfNode(ASTNode* condition, ASTNode* thenBlock, ASTNode* elseBlock);
ASTNode* createStmtListNode(ASTNode* stmt, ASTNode* next);

/* Expressions */
ASTNode* createBinOpNode(OperatorType op, ASTNode* left, ASTNode* right);
ASTNode* createIntLiteralNode(int value);
ASTNode* createFloatLiteralNode(float value);
ASTNode* createStringLiteralNode(char* value);
ASTNode* createIdentifierNode(char* name);

/* AST UTILITY FUNCTIONS  */

void printAST(ASTNode* node, int indent);
void freeAST(ASTNode* node);
const char* nodeTypeToString(NodeType type);
const char* dataTypeToString(DataType type);
const char* operatorToString(OperatorType op);

#endif /* AST_H */