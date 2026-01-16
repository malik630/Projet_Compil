#include "ast.h"

extern int line_num;
extern int col_num;

/* ======== NEW NODE CREATION FUNCTIONS ======== */

/* Record Declaration */
ASTNode* createRecordDeclNode(char* name, ASTNode* fields) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_RECORD_DECL;
    node->line = line_num;
    node->column = col_num;
    node->data.recordDecl.name = strdup(name);
    node->data.recordDecl.fields = fields;
    return node;
}
/* Record Instance */
ASTNode* createRecordInstanceNode(char* instanceName, char* typeName, ASTNode* initializer) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_RECORD_INSTANCE;
    node->line = line_num;
    node->column = col_num;
    node->data.recordInstance.instanceName = strdup(instanceName);
    node->data.recordInstance.typeName = strdup(typeName);
    node->data.recordInstance.initializer = initializer;
    return node;
}

/* Array Declaration */
ASTNode* createArrayDeclNode(char* name, DataType elementType, int size, ASTNode* initializer) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_DECL;
    node->line = line_num;
    node->column = col_num;
    node->data.arrayDecl.name = strdup(name);
    node->data.arrayDecl.elementType = elementType;
    node->data.arrayDecl.size = size;
    node->data.arrayDecl.initializer = initializer;
    return node;
}

/* Dictionary Declaration */
ASTNode* createDictDeclNode(char* name, DataType keyType, DataType valueType) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_DICT_DECL;
    node->line = line_num;
    node->column = col_num;
    node->data.dictDecl.name = strdup(name);
    node->data.dictDecl.keyType = keyType;
    node->data.dictDecl.valueType = valueType;
    return node;
}

/* Field Node */
ASTNode* createFieldNode(char* name, DataType type) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_FIELD;
    node->line = line_num;
    node->column = col_num;
    node->data.field.name = strdup(name);
    node->data.field.type = type;
    node->data.field.next = NULL;
    return node;
}

/* Field List Node */
ASTNode* createFieldListNode(ASTNode* field, ASTNode* next) {
    if (field == NULL) return next;
    field->data.field.next = next;
    return field;
}

/* Record Access Assignment */
ASTNode* createRecordAccessAssignNode(char* recordName, char* fieldName, ASTNode* expr) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_RECORD_ACCESS_ASSIGN;
    node->line = line_num;
    node->column = col_num;
    node->data.recordAccessAssign.recordName = strdup(recordName);
    node->data.recordAccessAssign.fieldName = strdup(fieldName);
    node->data.recordAccessAssign.expression = expr;
    return node;
}

/* Array Access Assignment */
ASTNode* createArrayAccessAssignNode(char* arrayName, ASTNode* index, ASTNode* expr) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_ACCESS_ASSIGN;
    node->line = line_num;
    node->column = col_num;
    node->data.arrayAccessAssign.arrayName = strdup(arrayName);
    node->data.arrayAccessAssign.index = index;
    node->data.arrayAccessAssign.expression = expr;
    return node;
}

/* Input Node */
ASTNode* createInputNode(char* identifier) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_INPUT;
    node->line = line_num;
    node->column = col_num;
    node->data.input.identifier = strdup(identifier);
    return node;
}

/* While Node */
ASTNode* createWhileNode(ASTNode* condition, ASTNode* body) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_WHILE;
    node->line = line_num;
    node->column = col_num;
    node->data.whileStmt.condition = condition;
    node->data.whileStmt.body = body;
    return node;
}

/* For Node */
ASTNode* createForNode(char* iterator, ASTNode* from, ASTNode* to, ASTNode* body) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_FOR;
    node->line = line_num;
    node->column = col_num;
    node->data.forStmt.iterator = strdup(iterator);
    node->data.forStmt.from = from;
    node->data.forStmt.to = to;
    node->data.forStmt.body = body;
    return node;
}

/* ForEach Node */
ASTNode* createForEachNode(char* iterator, char* collection, ASTNode* body) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_FOREACH;
    node->line = line_num;
    node->column = col_num;
    node->data.forEachStmt.iterator = strdup(iterator);
    node->data.forEachStmt.collection = strdup(collection);
    node->data.forEachStmt.body = body;
    return node;
}

/* Repeat Node */
ASTNode* createRepeatNode(ASTNode* body, ASTNode* condition) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_REPEAT;
    node->line = line_num;
    node->column = col_num;
    node->data.repeatStmt.body = body;
    node->data.repeatStmt.condition = condition;
    return node;
}

/* Case Node */
ASTNode* createCaseNode(ASTNode* cases, ASTNode* elseBlock) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_CASE;
    node->line = line_num;
    node->column = col_num;
    node->data.caseStmt.cases = cases;
    node->data.caseStmt.else_block = elseBlock;
    return node;
}

/* Case Item Node */
ASTNode* createCaseItemNode(ASTNode* condition, ASTNode* body, ASTNode* next) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_CASE_ITEM;
    node->line = line_num;
    node->column = col_num;
    node->data.caseItem.condition = condition;
    node->data.caseItem.body = body;
    node->data.caseItem.next = next;
    return node;
}

/* Unary Operation Node */
ASTNode* createUnaryOpNode(OperatorType op, ASTNode* operand) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_EXPR_UNARYOP;
    node->line = line_num;
    node->column = col_num;
    node->data.unaryOp.op = op;
    node->data.unaryOp.operand = operand;
    return node;
}

/* Boolean Literal Node */
ASTNode* createBoolLiteralNode(int value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_EXPR_LITERAL;
    node->line = line_num;
    node->column = col_num;
    node->data.literal.value.boolValue = value;
    node->data.literal.literalType = TYPE_BOOLEAN;
    return node;
}

/* Record Access Node */
ASTNode* createRecordAccessNode(char* recordName, char* fieldName) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_RECORD_ACCESS;
    node->line = line_num;
    node->column = col_num;
    node->data.recordAccess.recordName = strdup(recordName);
    node->data.recordAccess.fieldName = strdup(fieldName);
    return node;
}

/* Array Access Node */
ASTNode* createArrayAccessNode(char* arrayName, ASTNode* index) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_ACCESS;
    node->line = line_num;
    node->column = col_num;
    node->data.arrayAccess.arrayName = strdup(arrayName);
    node->data.arrayAccess.index = index;
    return node;
}

/* Expression List Node */
ASTNode* createExprListNode(ASTNode* expr, ASTNode* next) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_EXPR_LIST;
    node->line = line_num;
    node->column = col_num;
    node->data.exprList.expression = expr;
    node->data.exprList.next = next;
    return node;
}

/* ======== UPDATED UTILITY FUNCTIONS ======== */

const char* nodeTypeToString(NodeType type) {
    switch(type) {
        case NODE_PROGRAM: return "PROGRAMME";
        case NODE_DECL_LIST: return "LISTE_DECL";
        case NODE_DECL: return "DÉCLARATION";
        case NODE_RECORD_DECL: return "DÉCL_RECORD";
        case NODE_ARRAY_DECL: return "DÉCL_ARRAY";
        case NODE_DICT_DECL: return "DÉCL_DICT";
        case NODE_FIELD: return "CHAMP";
        case NODE_FIELD_LIST: return "LISTE_CHAMPS";
        case NODE_STMT_LIST: return "LISTE_INSTR";
        case NODE_ASSIGN: return "AFFECTATION";
        case NODE_RECORD_ACCESS_ASSIGN: return "AFFECTATION_RECORD";
        case NODE_ARRAY_ACCESS_ASSIGN: return "AFFECTATION_ARRAY";
        case NODE_PRINT: return "IMPRESSION";
        case NODE_INPUT: return "ENTRÉE";
        case NODE_IF: return "SI";
        case NODE_WHILE: return "TANT_QUE";
        case NODE_FOR: return "POUR";
        case NODE_FOREACH: return "POUR_CHAQUE";
        case NODE_REPEAT: return "RÉPÉTER";
        case NODE_CASE: return "CAS";
        case NODE_CASE_ITEM: return "ITEM_CAS";
        case NODE_EXPR_BINOP: return "OP_BINAIRE";
        case NODE_EXPR_UNARYOP: return "OP_UNAIRE";
        case NODE_EXPR_LITERAL: return "LITTÉRALE";
        case NODE_EXPR_IDENTIFIER: return "IDENTIFIANT";
        case NODE_EXPR_LIST: return "LISTE_EXPR";
        case NODE_RECORD_ACCESS: return "ACCÈS_RECORD";
        case NODE_ARRAY_ACCESS: return "ACCÈS_ARRAY";
        case NODE_CONDITION: return "CONDITION";
        case NODE_RECORD_INSTANCE: return "INSTANCE_RECORD";
        default: return "INCONNU";
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
        case AST_OP_AND: return "AND";
        case AST_OP_OR: return "OR";
        case AST_OP_NOT: return "NOT";
        case AST_OP_NEG: return "-";
        default: return "?";
    }
}
/*FONCTIONS DE CRÉATION D'AST - ORIGINAL FUNCTIONS */

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

const char* dataTypeToString(DataType type) {
    switch(type) {
        case TYPE_INTEGER: return "ENTIER";
        case TYPE_FLOAT: return "RÉEL";
        case TYPE_STRING: return "CHAÎNE";
        case TYPE_BOOLEAN: return "BOOLÉEN";
        default: return "INCONNU";
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
        printf("(nul)\n");
        return;
    }
    
    printIndent(indent);
    
    switch(node->type) {
        case NODE_PROGRAM:
            printf("PROGRAMME: %s\n", node->data.program.name);
            printIndent(indent);
            printf("├─ Déclarations:\n");
            printAST(node->data.program.declarations, indent + 1);
            printIndent(indent);
            printf("└─ Instructions:\n");
            printAST(node->data.program.statements, indent + 1);
            break;
            
        case NODE_DECL:
            printf("DÉCL: %s : %s\n", 
                   node->data.declaration.identifier,
                   dataTypeToString(node->data.declaration.dataType));
            if (node->data.declaration.initializer) {
                printIndent(indent);
                printf("└─ Initialiseur:\n");
                printAST(node->data.declaration.initializer, indent + 1);
            }
            if (node->data.declaration.next) {
                printAST(node->data.declaration.next, indent);
            }
            break;
            
        case NODE_ASSIGN:
            printf("AFFECTATION: %s\n", node->data.assignment.identifier);
            printIndent(indent);
            printf("└─ Expression:\n");
            printAST(node->data.assignment.expression, indent + 1);
            break;
            
        case NODE_PRINT:
            printf("IMPRESSION\n");
            printIndent(indent);
            printf("└─ Expression:\n");
            printAST(node->data.print.expression, indent + 1);
            break;
            
        case NODE_IF:
            printf("SI\n");
            printIndent(indent);
            printf("├─ Condition:\n");
            printAST(node->data.ifStmt.condition, indent + 1);
            printIndent(indent);
            printf("├─ Alors:\n");
            printAST(node->data.ifStmt.then_block, indent + 1);
            if (node->data.ifStmt.else_block) {
                printIndent(indent);
                printf("└─ Sinon:\n");
                printAST(node->data.ifStmt.else_block, indent + 1);
            }
            break;
            
        case NODE_EXPR_BINOP:
            printf("OP_BINAIRE: %s\n", operatorToString(node->data.binOp.op));
            printIndent(indent);
            printf("├─ Gauche:\n");
            printAST(node->data.binOp.left, indent + 1);
            printIndent(indent);
            printf("└─ Droite:\n");
            printAST(node->data.binOp.right, indent + 1);
            break;
            
        case NODE_EXPR_LITERAL:
            printf("LITTÉRALE: ");
            if (node->data.literal.literalType == TYPE_INTEGER) {
                printf("%d (ENTIER)\n", node->data.literal.value.intValue);
            } else if (node->data.literal.literalType == TYPE_FLOAT) {
                printf("%f (RÉEL)\n", node->data.literal.value.floatValue);
            } else if (node->data.literal.literalType == TYPE_STRING) {
                printf("%s (CHAÎNE)\n", node->data.literal.value.stringValue);
            }
            break;
            
        case NODE_EXPR_IDENTIFIER:
            printf("IDENTIFIANT: %s\n", node->data.identifier.name);
            break;
            
        case NODE_STMT_LIST:
            if (node->data.stmtList.statement) {
                printAST(node->data.stmtList.statement, indent);
            }
            if (node->data.stmtList.next) {
                printAST(node->data.stmtList.next, indent);
            }
            break;
        case NODE_RECORD_INSTANCE:
            printf("INSTANCE_RECORD: %s de type %s\n", 
                node->data.recordInstance.instanceName,
                node->data.recordInstance.typeName);
            if (node->data.recordInstance.initializer) {
                printIndent(indent);
                printf("└─ Initialiseur:\n");
                printAST(node->data.recordInstance.initializer, indent + 1);
            }
            break;
            
        default:
            printf("TYPE DE NŒUD: %s\n", nodeTypeToString(node->type));
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
        case NODE_RECORD_INSTANCE:
            free(node->data.recordInstance.instanceName);
            free(node->data.recordInstance.typeName);
            freeAST(node->data.recordInstance.initializer);
            break;
    }
    
    free(node);
}