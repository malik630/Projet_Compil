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





// Helper for tree visualization
void printBranch(const char* prefix, int isLast, const char* label, const char* info) {
    printf("%s", prefix);
    if (isLast) printf("└── ");
    else printf("├── ");
    
    if (label) printf("\033[1;33m%s\033[0m: ", label);
    printf("%s\033[0m\n", info);
}

// Recursive function for pretty printing
void printASTRecursive(ASTNode* node, char* prefix, int isLast, const char* label) {
    if (node == NULL) return;

    char displayStr[1024] = "";
    char childPrefix[2048];
    strcpy(childPrefix, prefix);
    if (isLast) strcat(childPrefix, "    ");
    else strcat(childPrefix, "│   ");

    // Formatter le nœud courant
    switch(node->type) {
        case NODE_PROGRAM:
            sprintf(displayStr, "\033[1;36mPROGRAMME\033[0m \033[1m%s\033[0m", node->data.program.name);
            printBranch(prefix, isLast, label, displayStr);
            
            printASTRecursive(node->data.program.declarations, childPrefix, 0, "Déclarations");
            printASTRecursive(node->data.program.statements, childPrefix, 1, "Instructions");
            break;

        case NODE_DECL:
            sprintf(displayStr, "\033[1;32mDÉCL\033[0m \033[1m%s\033[0m (%s)", 
                    node->data.declaration.identifier, 
                    dataTypeToString(node->data.declaration.dataType));
            printBranch(prefix, isLast, label, displayStr);
            
            int hasNextDecl = (node->data.declaration.next != NULL);
            int hasInit = (node->data.declaration.initializer != NULL);
            
            if (hasInit) {
                printASTRecursive(node->data.declaration.initializer, childPrefix, !hasNextDecl, "Init");
            }
            if (hasNextDecl) {
                printASTRecursive(node->data.declaration.next, childPrefix, 1, NULL);
            }
            break;

        case NODE_ASSIGN:
            sprintf(displayStr, "\033[1;32mAFFECTATION\033[0m \033[1m%s\033[0m", node->data.assignment.identifier);
            printBranch(prefix, isLast, label, displayStr);
            printASTRecursive(node->data.assignment.expression, childPrefix, 1, "Expr");
            break;

        case NODE_PRINT:
            sprintf(displayStr, "\033[1;35mIMPRESSION\033[0m");
            printBranch(prefix, isLast, label, displayStr);
            printASTRecursive(node->data.print.expression, childPrefix, 1, "Expr");
            break;
            
        case NODE_INPUT:
            sprintf(displayStr, "\033[1;35mENTRÉE\033[0m dans \033[1m%s\033[0m", node->data.input.identifier);
            printBranch(prefix, isLast, label, displayStr);
            break;

        case NODE_IF:
            sprintf(displayStr, "\033[1;35mSI\033[0m");
            printBranch(prefix, isLast, label, displayStr);
            int hasElse = (node->data.ifStmt.else_block != NULL);
            printASTRecursive(node->data.ifStmt.condition, childPrefix, 0, "Cond");
            printASTRecursive(node->data.ifStmt.then_block, childPrefix, hasElse ? 0 : 1, "Alors");
            if (hasElse) printASTRecursive(node->data.ifStmt.else_block, childPrefix, 1, "Sinon");
            break;
            
        case NODE_WHILE:
            sprintf(displayStr, "\033[1;35mTANT_QUE\033[0m");
            printBranch(prefix, isLast, label, displayStr);
            printASTRecursive(node->data.whileStmt.condition, childPrefix, 0, "Cond");
            printASTRecursive(node->data.whileStmt.body, childPrefix, 1, "Faire");
            break;

        case NODE_FOR:
            sprintf(displayStr, "\033[1;35mPOUR\033[0m \033[1m%s\033[0m", node->data.forStmt.iterator);
            printBranch(prefix, isLast, label, displayStr);
            printASTRecursive(node->data.forStmt.from, childPrefix, 0, "De");
            printASTRecursive(node->data.forStmt.to, childPrefix, 0, "À");
            printASTRecursive(node->data.forStmt.body, childPrefix, 1, "Faire");
            break;
            
        case NODE_STMT_LIST:
            // Pour les listes, on n'affiche pas le nœud conteneur pour alléger, 
            // ou on l'affiche simplement comme "SEQ"
            // Ici on va 'transparently' afficher le statement, puis le next
            // Mais pour préserver l'indentation structurelle, mieux vaut l'afficher si c'est un bloc.
            // Sauf si c'est juste un lien.
            // Affichons un indicateur '.' pour la séquence ou rien.
            // Option choisie: afficher "Instruction"
            
            // Correction: Si on est dans un "bloc" (alors/sinon), on veut voir la liste.
            // Mais afficher "LISTE_INSTR" à chaque ligne est lourd.
            // On va afficher le contenu.
            
            if (node->data.stmtList.statement) {
                int hasNext = (node->data.stmtList.next != NULL);
                // On affiche le statement courant
                printASTRecursive(node->data.stmtList.statement, prefix, isLast && !hasNext, label);
                // Et on enchaîne sur le suivant (même niveau d'indentation si c'est une liste linéaire)
                if (hasNext) {
                    printASTRecursive(node->data.stmtList.next, prefix, isLast, NULL);
                }
            } else {
                // Cas liste vide ou fin
                if (node->data.stmtList.next) {
                     printASTRecursive(node->data.stmtList.next, prefix, isLast, NULL);
                }
            }
            // NOTE: This logic for LIST flattens the list visually (siblings), which is nicer.
            // The 'label' is only applied to the distinct head if passed.
            break;

        case NODE_EXPR_BINOP:
            sprintf(displayStr, "\033[1m%s\033[0m", operatorToString(node->data.binOp.op));
            printBranch(prefix, isLast, label, displayStr);
            printASTRecursive(node->data.binOp.left, childPrefix, 0, NULL);
            printASTRecursive(node->data.binOp.right, childPrefix, 1, NULL);
            break;

        case NODE_EXPR_UNARYOP:
            sprintf(displayStr, "UNAIRE \033[1m%s\033[0m", operatorToString(node->data.unaryOp.op));
            printBranch(prefix, isLast, label, displayStr);
            printASTRecursive(node->data.unaryOp.operand, childPrefix, 1, NULL);
            break;

        case NODE_EXPR_LITERAL:
            if (node->data.literal.literalType == TYPE_INTEGER)
                sprintf(displayStr, "\033[36m%d\033[0m", node->data.literal.value.intValue);
            else if (node->data.literal.literalType == TYPE_FLOAT)
                sprintf(displayStr, "\033[36m%.2f\033[0m", node->data.literal.value.floatValue);
            else if (node->data.literal.literalType == TYPE_STRING)
                sprintf(displayStr, "\033[32m\"%s\"\033[0m", node->data.literal.value.stringValue);
            else if (node->data.literal.literalType == TYPE_BOOLEAN)
                sprintf(displayStr, "\033[36m%s\033[0m", node->data.literal.value.boolValue ? "true" : "false");
            
            printBranch(prefix, isLast, label, displayStr);
            break;

        case NODE_EXPR_IDENTIFIER:
            sprintf(displayStr, "ID: \033[33m%s\033[0m", node->data.identifier.name);
            printBranch(prefix, isLast, label, displayStr);
            break;

        case NODE_RECORD_INSTANCE:
            sprintf(displayStr, "INSTANCE \033[1m%s\033[0m : %s", node->data.recordInstance.instanceName, node->data.recordInstance.typeName);
            printBranch(prefix, isLast, label, displayStr);
            if (node->data.recordInstance.initializer) {
                printASTRecursive(node->data.recordInstance.initializer, childPrefix, 1, "Init");
            }
            break;
            
        case NODE_FIELD_LIST:
             // Similar layout to STMT_LIST
            {
                int hasNext = (node->data.field.next != NULL);
                char fieldStr[256];
                sprintf(fieldStr, "CHAMP \033[1m%s\033[0m : %s", node->data.field.name, dataTypeToString(node->data.field.type));
                printBranch(prefix, isLast && !hasNext, label, fieldStr);
                if (hasNext) {
                    printASTRecursive(node->data.field.next, prefix, isLast, NULL);
                }
            }
            break;
            
        case NODE_RECORD_DECL:
            sprintf(displayStr, "RECORD \033[1m%s\033[0m", node->data.recordDecl.name);
            printBranch(prefix, isLast, label, displayStr);
            printASTRecursive(node->data.recordDecl.fields, childPrefix, 1, "Champs");
            break;

        case NODE_ARRAY_DECL:
            sprintf(displayStr, "ARRAY \033[1m%s\033[0m [%d] of %s", 
                    node->data.arrayDecl.name,
                    node->data.arrayDecl.size,
                    dataTypeToString(node->data.arrayDecl.elementType));
            printBranch(prefix, isLast, label, displayStr);
            if (node->data.arrayDecl.initializer) {
                printASTRecursive(node->data.arrayDecl.initializer, childPrefix, 1, "Init");
            }
            break;
            
        case NODE_REPEAT:
            sprintf(displayStr, "\033[1;35mRÉPÉTER\033[0m");
            printBranch(prefix, isLast, label, displayStr);
            printASTRecursive(node->data.repeatStmt.body, childPrefix, 0, "Faire");
            printASTRecursive(node->data.repeatStmt.condition, childPrefix, 1, "Jusqu'à");
            break;
            
        case NODE_CASE:
            sprintf(displayStr, "\033[1;35mCAS\033[0m");
            printBranch(prefix, isLast, label, displayStr);
            int hasElseBlock = (node->data.caseStmt.else_block != NULL);
            printASTRecursive(node->data.caseStmt.cases, childPrefix, hasElseBlock ? 0 : 1, NULL);
            if (hasElseBlock) 
                printASTRecursive(node->data.caseStmt.else_block, childPrefix, 1, "Sinon");
            break;
            
        case NODE_CASE_ITEM:
             // Similar list logic
            {
                int hasNext = (node->data.caseItem.next != NULL);
                printBranch(prefix, isLast && !hasNext, label, "OPTION");
                
                // Need a sub-child-prefix since we printed a branch for OPTION
                // Using 'childPrefix' which includes indentation for current level children
                
                // Wait, if I print "OPTION", I introduce a node.
                // Its children are Condition and Body.
                printASTRecursive(node->data.caseItem.condition, childPrefix, 0, "Si");
                printASTRecursive(node->data.caseItem.body, childPrefix, 1, "Alors");
                
                // And print next item at SAME level as OPTION
                if (hasNext) {
                    printASTRecursive(node->data.caseItem.next, prefix, isLast, NULL);
                }
            }
            break;

        default:
            sprintf(displayStr, "NODE [%s]", nodeTypeToString(node->type));
            printBranch(prefix, isLast, label, displayStr);
            break;
    }
}

void printAST(ASTNode* node, int indent) {
    // Ignore indent parameter, always start fresh
    if (node == NULL) {
        printf("(Arbre vide)\n");
        return;
    }
    printf("\n"); // Spacing before tree
    printASTRecursive(node, "", 1, NULL);
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