#ifndef AST_H
#define AST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Node types */
typedef enum {
    NODE_PROGRAM, 
    NODE_DECL_LIST,
    NODE_DECL,
    NODE_RECORD_DECL,
    NODE_RECORD_INSTANCE,
    NODE_ARRAY_DECL,
    NODE_DICT_DECL,
    NODE_FIELD,
    NODE_FIELD_LIST,
    NODE_STMT_LIST,
    NODE_ASSIGN,
    NODE_RECORD_ACCESS_ASSIGN,
    NODE_ARRAY_ACCESS_ASSIGN,
    NODE_PRINT,
    NODE_INPUT,
    NODE_IF,
    NODE_WHILE,
    NODE_FOR,
    NODE_FOREACH,
    NODE_REPEAT,
    NODE_CASE,
    NODE_CASE_ITEM,
    NODE_EXPR_BINOP,
    NODE_EXPR_UNARYOP,
    NODE_EXPR_LITERAL,
    NODE_EXPR_IDENTIFIER,
    NODE_EXPR_LIST,
    NODE_RECORD_ACCESS,
    NODE_ARRAY_ACCESS,
    NODE_CONDITION
} NodeType;

/* Operator types - renamed to avoid conflicts */
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
    AST_OP_GTE,
    AST_OP_AND,
    AST_OP_OR,
    AST_OP_NOT,
    AST_OP_NEG
} OperatorType;

/* Data types */
typedef enum {
    TYPE_INTEGER,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_BOOLEAN,
    TYPE_RECORD,
    TYPE_ARRAY,
    TYPE_DICTIONARY
} DataType;

/* AST Node structure */
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
        
        /* Declaration */
        struct {
            char* identifier;
            DataType dataType;
            struct ASTNode* initializer;
            struct ASTNode* next;
        } declaration;
        
        /* Record Declaration */
        struct {
            char* name;
            struct ASTNode* fields;
        } recordDecl;
        
        /* Record Instance */
        struct {
            char* instanceName;
            char* typeName;
            struct ASTNode* initializer;
        } recordInstance;
        
        /* Array Declaration */
        struct {
            char* name;
            DataType elementType;
            int size;
            struct ASTNode* initializer;
        } arrayDecl;
        
        /* Dictionary Declaration */
        struct {
            char* name;
            DataType keyType;
            DataType valueType;
        } dictDecl;
        
        /* Field */
        struct {
            char* name;
            DataType type;
            struct ASTNode* next;
        } field;
        
        /* Assignment */
        struct {
            char* identifier;
            struct ASTNode* expression;
        } assignment;
        
        /* Record Access Assignment */
        struct {
            char* recordName;
            char* fieldName;
            struct ASTNode* expression;
        } recordAccessAssign;
        
        /* Array Access Assignment */
        struct {
            char* arrayName;
            struct ASTNode* index;
            struct ASTNode* expression;
        } arrayAccessAssign;
        
        /* Print */
        struct {
            struct ASTNode* expression;
        } print;
        
        /* Input */
        struct {
            char* identifier;
        } input;
        
        /* If statement */
        struct {
            struct ASTNode* condition;
            struct ASTNode* then_block;
            struct ASTNode* else_block;
        } ifStmt;
        
        /* While loop */
        struct {
            struct ASTNode* condition;
            struct ASTNode* body;
        } whileStmt;
        
        /* For loop */
        struct {
            char* iterator;
            struct ASTNode* from;
            struct ASTNode* to;
            struct ASTNode* body;
        } forStmt;
        
        /* ForEach loop */
        struct {
            char* iterator;
            char* collection;
            struct ASTNode* body;
        } forEachStmt;
        
        /* Repeat-Until loop */
        struct {
            struct ASTNode* body;
            struct ASTNode* condition;
        } repeatStmt;
        
        /* Case statement */
        struct {
            struct ASTNode* cases;
            struct ASTNode* else_block;
        } caseStmt;
        
        /* Case item */
        struct {
            struct ASTNode* condition;
            struct ASTNode* body;
            struct ASTNode* next;
        } caseItem;
        
        /* Binary operation */
        struct {
            OperatorType op;
            struct ASTNode* left;
            struct ASTNode* right;
        } binOp;
        
        /* Unary operation */
        struct {
            OperatorType op;
            struct ASTNode* operand;
        } unaryOp;
        
        /* Literal */
        struct {
            union {
                int intValue;
                float floatValue;
                char* stringValue;
                int boolValue;
            } value;
            DataType literalType;
        } literal;
        
        /* Identifier */
        struct {
            char* name;
        } identifier;
        
        /* Record Access */
        struct {
            char* recordName;
            char* fieldName;
        } recordAccess;
        
        /* Array Access */
        struct {
            char* arrayName;
            struct ASTNode* index;
        } arrayAccess;
        
        /* Statement List */
        struct {
            struct ASTNode* statement;
            struct ASTNode* next;
        } stmtList;
        
        /* Expression List */
        struct {
            struct ASTNode* expression;
            struct ASTNode* next;
        } exprList;
    } data;
} ASTNode;

/* AST Creation Functions */

/* Program */
ASTNode* createProgramNode(char* name, ASTNode* decls, ASTNode* stmts);

/* Declarations */
ASTNode* createDeclNode(char* identifier, DataType type, ASTNode* initializer);
ASTNode* createDeclListNode(ASTNode* decl, ASTNode* next);
ASTNode* createRecordDeclNode(char* name, ASTNode* fields);
ASTNode* createRecordInstanceNode(char* instanceName, char* typeName, ASTNode* initializer);
ASTNode* createArrayDeclNode(char* name, DataType elementType, int size, ASTNode* initializer);
ASTNode* createDictDeclNode(char* name, DataType keyType, DataType valueType);
ASTNode* createFieldNode(char* name, DataType type);
ASTNode* createFieldListNode(ASTNode* field, ASTNode* next);

/* Statements */
ASTNode* createAssignNode(char* identifier, ASTNode* expr);
ASTNode* createRecordAccessAssignNode(char* recordName, char* fieldName, ASTNode* expr);
ASTNode* createArrayAccessAssignNode(char* arrayName, ASTNode* index, ASTNode* expr);
ASTNode* createPrintNode(ASTNode* expr);
ASTNode* createInputNode(char* identifier);
ASTNode* createIfNode(ASTNode* condition, ASTNode* thenBlock, ASTNode* elseBlock);
ASTNode* createWhileNode(ASTNode* condition, ASTNode* body);
ASTNode* createForNode(char* iterator, ASTNode* from, ASTNode* to, ASTNode* body);
ASTNode* createForEachNode(char* iterator, char* collection, ASTNode* body);
ASTNode* createRepeatNode(ASTNode* body, ASTNode* condition);
ASTNode* createCaseNode(ASTNode* cases, ASTNode* elseBlock);
ASTNode* createCaseItemNode(ASTNode* condition, ASTNode* body, ASTNode* next);
ASTNode* createStmtListNode(ASTNode* stmt, ASTNode* next);

/* Expressions */
ASTNode* createBinOpNode(OperatorType op, ASTNode* left, ASTNode* right);
ASTNode* createUnaryOpNode(OperatorType op, ASTNode* operand);
ASTNode* createIntLiteralNode(int value);
ASTNode* createFloatLiteralNode(float value);
ASTNode* createStringLiteralNode(char* value);
ASTNode* createBoolLiteralNode(int value);
ASTNode* createIdentifierNode(char* name);
ASTNode* createRecordAccessNode(char* recordName, char* fieldName);
ASTNode* createArrayAccessNode(char* arrayName, ASTNode* index);
ASTNode* createExprListNode(ASTNode* expr, ASTNode* next);

/* Utility Functions */
void printAST(ASTNode* node, int indent);
void freeAST(ASTNode* node);
const char* nodeTypeToString(NodeType type);
const char* dataTypeToString(DataType type);
const char* operatorToString(OperatorType op);
char* generer_code(ASTNode* node);

#endif /* AST_H */