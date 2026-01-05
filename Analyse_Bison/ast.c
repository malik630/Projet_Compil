#include "ast.h"

extern int line_num;
extern int col_num;

/* ========================================================================== */
/*                         AST CREATION FUNCTIONS                             */
/* ========================================================================== */

ASTNode* createProgramNode(char* name, ASTNode* decls, ASTNode* stmts) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_PROGRAM;
    node->line = line_num;
    node->column = col_num;
    node->data.program.name = strdup(name);
    node->data.program.declarations = decls;
    node->data.program.statements = stmts;
    return node;
}

ASTNode* createDeclNode(char* identifier, DataType type, ASTNode* initializer) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_DECL;
    node->line = line_num;
    node->column = col_num;
    node->data.declaration.identifier = strdup(identifier);
    node->data.declaration.dataType = type;
    node->data.declaration.initializer = initializer;
    node->data.declaration.next = NULL;
    return node;
}

ASTNode* createDeclListNode(ASTNode* decl, ASTNode* next) {
    if (decl == NULL) return next;
    decl->data.declaration.next = next;
    return decl;
}

ASTNode* createAssignNode(char* identifier, ASTNode* expr) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_ASSIGN;
    node->line = line_num;
    node->column = col_num;
    node->data.assignment.identifier = strdup(identifier);
    node->data.assignment.expression = expr;
    return node;
}

ASTNode* createPrintNode(ASTNode* expr) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_PRINT;
    node->line = line_num;
    node->column = col_num;
    node->data.print.expression = expr;
    return node;
}

ASTNode* createIfNode(ASTNode* condition, ASTNode* thenBlock, ASTNode* elseBlock) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_IF;
    node->line = line_num;
    node->column = col_num;
    node->data.ifStmt.condition = condition;
    node->data.ifStmt.then_block = thenBlock;
    node->data.ifStmt.else_block = elseBlock;
    return node;
}

ASTNode* createStmtListNode(ASTNode* stmt, ASTNode* next) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_STMT_LIST;
    node->line = line_num;
    node->column = col_num;
    node->data.stmtList.statement = stmt;
    node->data.stmtList.next = next;
    return node;
}

ASTNode* createBinOpNode(OperatorType op, ASTNode* left, ASTNode* right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_EXPR_BINOP;
    node->line = line_num;
    node->column = col_num;
    node->data.binOp.op = op;
    node->data.binOp.left = left;
    node->data.binOp.right = right;
    return node;
}

ASTNode* createIntLiteralNode(int value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_EXPR_LITERAL;
    node->line = line_num;
    node->column = col_num;
    node->data.literal.value.intValue = value;
    node->data.literal.literalType = TYPE_INTEGER;
    return node;
}

ASTNode* createFloatLiteralNode(float value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_EXPR_LITERAL;
    node->line = line_num;
    node->column = col_num;
    node->data.literal.value.floatValue = value;
    node->data.literal.literalType = TYPE_FLOAT;
    return node;
}

ASTNode* createStringLiteralNode(char* value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_EXPR_LITERAL;
    node->line = line_num;
    node->column = col_num;
    node->data.literal.value.stringValue = strdup(value);
    node->data.literal.literalType = TYPE_STRING;
    return node;
}

ASTNode* createIdentifierNode(char* name) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_EXPR_IDENTIFIER;
    node->line = line_num;
    node->column = col_num;
    node->data.identifier.name = strdup(name);
    return node;
}

/* ========================================================================== */
/*                         AST UTILITY FUNCTIONS                              */
/* ========================================================================== */

const char* nodeTypeToString(NodeType type) {
    switch(type) {
        case NODE_PROGRAM: return "PROGRAM";
        case NODE_DECL_LIST: return "DECL_LIST";
        case NODE_DECL: return "DECLARATION";
        case NODE_STMT_LIST: return "STMT_LIST";
        case NODE_ASSIGN: return "ASSIGNMENT";
        case NODE_PRINT: return "PRINT";
        case NODE_IF: return "IF";
        case NODE_EXPR_BINOP: return "BINARY_OP";
        case NODE_EXPR_LITERAL: return "LITERAL";
        case NODE_EXPR_IDENTIFIER: return "IDENTIFIER";
        case NODE_CONDITION: return "CONDITION";
        default: return "UNKNOWN";
    }
}

const char* dataTypeToString(DataType type) {
    switch(type) {
        case TYPE_INTEGER: return "INTEGER";
        case TYPE_FLOAT: return "FLOAT";
        case TYPE_STRING: return "STRING";
        case TYPE_BOOLEAN: return "BOOLEAN";
        default: return "UNKNOWN";
    }
}

const char* operatorToString(OperatorType op) {
    switch(op) {
        case AST_OP_ADD: return "+";
        case AST_OP_SUB: return "-";
        case AST_OP_MUL: return "*";
        case AST_OP_DIV: return "/";
        case AST_OP_MOD: return "%";
        case AST_OP_EQ: return "=";
        case AST_OP_NEQ: return "<>";
        case AST_OP_LT: return "<";
        case AST_OP_GT: return ">";
        case AST_OP_LTE: return "<=";
        case AST_OP_GTE: return ">=";
        default: return "?";
    }
}

void printIndent(int indent) {
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
}

void printAST(ASTNode* node, int indent) {
    if (node == NULL) {
        printIndent(indent);
        printf("(null)\n");
        return;
    }
    
    printIndent(indent);
    
    switch(node->type) {
        case NODE_PROGRAM:
            printf("PROGRAM: %s\n", node->data.program.name);
            printIndent(indent);
            printf("├─ Declarations:\n");
            printAST(node->data.program.declarations, indent + 1);
            printIndent(indent);
            printf("└─ Statements:\n");
            printAST(node->data.program.statements, indent + 1);
            break;
            
        case NODE_DECL:
            printf("DECL: %s : %s\n", 
                   node->data.declaration.identifier,
                   dataTypeToString(node->data.declaration.dataType));
            if (node->data.declaration.initializer) {
                printIndent(indent);
                printf("└─ Initializer:\n");
                printAST(node->data.declaration.initializer, indent + 1);
            }
            if (node->data.declaration.next) {
                printAST(node->data.declaration.next, indent);
            }
            break;
            
        case NODE_ASSIGN:
            printf("ASSIGN: %s\n", node->data.assignment.identifier);
            printIndent(indent);
            printf("└─ Expression:\n");
            printAST(node->data.assignment.expression, indent + 1);
            break;
            
        case NODE_PRINT:
            printf("PRINT\n");
            printIndent(indent);
            printf("└─ Expression:\n");
            printAST(node->data.print.expression, indent + 1);
            break;
            
        case NODE_IF:
            printf("IF\n");
            printIndent(indent);
            printf("├─ Condition:\n");
            printAST(node->data.ifStmt.condition, indent + 1);
            printIndent(indent);
            printf("├─ Then:\n");
            printAST(node->data.ifStmt.then_block, indent + 1);
            if (node->data.ifStmt.else_block) {
                printIndent(indent);
                printf("└─ Else:\n");
                printAST(node->data.ifStmt.else_block, indent + 1);
            }
            break;
            
        case NODE_EXPR_BINOP:
            printf("BINOP: %s\n", operatorToString(node->data.binOp.op));
            printIndent(indent);
            printf("├─ Left:\n");
            printAST(node->data.binOp.left, indent + 1);
            printIndent(indent);
            printf("└─ Right:\n");
            printAST(node->data.binOp.right, indent + 1);
            break;
            
        case NODE_EXPR_LITERAL:
            printf("LITERAL: ");
            if (node->data.literal.literalType == TYPE_INTEGER) {
                printf("%d (INTEGER)\n", node->data.literal.value.intValue);
            } else if (node->data.literal.literalType == TYPE_FLOAT) {
                printf("%f (FLOAT)\n", node->data.literal.value.floatValue);
            } else if (node->data.literal.literalType == TYPE_STRING) {
                printf("%s (STRING)\n", node->data.literal.value.stringValue);
            }
            break;
            
        case NODE_EXPR_IDENTIFIER:
            printf("IDENTIFIER: %s\n", node->data.identifier.name);
            break;
            
        case NODE_STMT_LIST:
            if (node->data.stmtList.statement) {
                printAST(node->data.stmtList.statement, indent);
            }
            if (node->data.stmtList.next) {
                printAST(node->data.stmtList.next, indent);
            }
            break;
            
        default:
            printf("UNKNOWN NODE TYPE\n");
    }
}

void freeAST(ASTNode* node) {
    if (node == NULL) return;
    
    switch(node->type) {
        case NODE_PROGRAM:
            free(node->data.program.name);
            freeAST(node->data.program.declarations);
            freeAST(node->data.program.statements);
            break;
            
        case NODE_DECL:
            free(node->data.declaration.identifier);
            freeAST(node->data.declaration.initializer);
            freeAST(node->data.declaration.next);
            break;
            
        case NODE_ASSIGN:
            free(node->data.assignment.identifier);
            freeAST(node->data.assignment.expression);
            break;
            
        case NODE_PRINT:
            freeAST(node->data.print.expression);
            break;
            
        case NODE_IF:
            freeAST(node->data.ifStmt.condition);
            freeAST(node->data.ifStmt.then_block);
            freeAST(node->data.ifStmt.else_block);
            break;
            
        case NODE_EXPR_BINOP:
            freeAST(node->data.binOp.left);
            freeAST(node->data.binOp.right);
            break;
            
        case NODE_EXPR_LITERAL:
            if (node->data.literal.literalType == TYPE_STRING) {
                free(node->data.literal.value.stringValue);
            }
            break;
            
        case NODE_EXPR_IDENTIFIER:
            free(node->data.identifier.name);
            break;
            
        case NODE_STMT_LIST:
            freeAST(node->data.stmtList.statement);
            freeAST(node->data.stmtList.next);
            break;
    }
    
    free(node);
}