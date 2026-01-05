#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========================================================================== */
/*                         AST NODE TYPES                                     */
/* ========================================================================== */

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

/* Renamed to avoid conflict with Bison tokens */
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

/* ========================================================================== */
/*                         AST NODE STRUCTURES                                */
/* ========================================================================== */

typedef struct ASTNode {
    NodeType type;
    int line;
    int column;
    
    union {
        /* Program node */
        struct {
            char* name;
            struct ASTNode* declarations;
            struct ASTNode* statements;
        } program;
        
        /* Declaration node */
        struct {
            char* identifier;
            DataType dataType;
            struct ASTNode* initializer;  /* NULL if not initialized */
            struct ASTNode* next;         /* Next declaration in list */
        } declaration;
        
        /* Assignment node */
        struct {
            char* identifier;
            struct ASTNode* expression;
        } assignment;
        
        /* Print node */
        struct {
            struct ASTNode* expression;
        } print;
        
        /* If node */
        struct {
            struct ASTNode* condition;
            struct ASTNode* then_block;
            struct ASTNode* else_block;  /* NULL if no else */
        } ifStmt;
        
        /* Binary operation node */
        struct {
            OperatorType op;
            struct ASTNode* left;
            struct ASTNode* right;
        } binOp;
        
        /* Literal node */
        struct {
            union {
                int intValue;
                float floatValue;
                char* stringValue;
            } value;
            DataType literalType;
        } literal;
        
        /* Identifier node */
        struct {
            char* name;
        } identifier;
        
        /* Statement list */
        struct {
            struct ASTNode* statement;
            struct ASTNode* next;
        } stmtList;
    } data;
} ASTNode;

/* ========================================================================== */
/*                         AST CREATION FUNCTIONS                             */
/* ========================================================================== */

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

/* ========================================================================== */
/*                         AST UTILITY FUNCTIONS                              */
/* ========================================================================== */

void printAST(ASTNode* node, int indent);
void freeAST(ASTNode* node);
const char* nodeTypeToString(NodeType type);
const char* dataTypeToString(DataType type);
const char* operatorToString(OperatorType op);

#endif /* AST_H */