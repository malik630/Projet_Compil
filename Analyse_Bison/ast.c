#include "ast.h"

extern int line_num;
extern int col_num;

/*FONCTIONS DE CRÉATION D'AST */

/*--------*/

/*Crée le nœud racine du programme. 
Prend un nom de programme, une liste de déclarations et une liste 
d'instructions. Retourne un nœud de programme complet
 qui sert de sommet de l'AST.*/
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
/*--------*/
/*Crée un nœud de déclaration de variable. 
Prend le nom de la variable, son type de données 
(int/float/string/boolean), et une expression d'initialisation optionnelle.*/

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
/*--------*/

/*Relie les nœuds de déclaration ensemble dans une liste.
 Prend une déclaration et la prochaine déclaration dans la chaîne.
  Si la première déclaration est NULL, elle retourne simplement la suivante.*/

ASTNode* createDeclListNode(ASTNode* decl, ASTNode* next) {
    if (decl == NULL) return next;
    decl->data.declaration.next = next;
    return decl;
}

/*--------*/

/*Crée un nœud d'instruction d'affectation. 
Prend un identifiant de variable et l'expression à lui affecter*/

ASTNode* createAssignNode(char* identifier, ASTNode* expr) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_ASSIGN;
    node->line = line_num;
    node->column = col_num;
    node->data.assignment.identifier = strdup(identifier);
    node->data.assignment.expression = expr;
    return node;
}
/*--------*/
/*Crée un nœud d'instruction d'impression.
 Prend une expression à afficher en sortie.*/

ASTNode* createPrintNode(ASTNode* expr) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_PRINT;
    node->line = line_num;
    node->column = col_num;
    node->data.print.expression = expr;
    return node;
}
/*--------*/
/*Crée un nœud d'instruction if. 
Prend une expression de condition, 
les instructions à exécuter si vraie (bloc then),
 et un bloc else optionnel.*/
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
/*--------*/
/*Crée une liste d'instructions en reliant les nœuds d'instruction.
 Prend une instruction et la prochaine instruction dans la liste.*/

ASTNode* createStmtListNode(ASTNode* stmt, ASTNode* next) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_STMT_LIST;
    node->line = line_num;
    node->column = col_num;
    node->data.stmtList.statement = stmt;
    node->data.stmtList.next = next;
    return node;
}
/*--------*/
/*Crée un nœud d'opération binaire pour des expressions comme 5 + 3 ou x > 10.
 Prend le type d'opérateur et les expressions des opérandes gauche et droit.*/

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
/*--------*/
/*Crée un nœud littéral pour les valeurs entières (par exemple, 42).
 Stocke la valeur entière et marque le type comme INTEGER.*/

ASTNode* createIntLiteralNode(int value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_EXPR_LITERAL;
    node->line = line_num;
    node->column = col_num;
    node->data.literal.value.intValue = value;
    node->data.literal.literalType = TYPE_INTEGER;
    return node;
}
/*--------*/
/*Crée un nœud littéral pour les valeurs à 
virgule flottante (par exemple, 3.14).
 Stocke la valeur float et marque le type comme FLOAT.*/

ASTNode* createFloatLiteralNode(float value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_EXPR_LITERAL;
    node->line = line_num;
    node->column = col_num;
    node->data.literal.value.floatValue = value;
    node->data.literal.literalType = TYPE_FLOAT;
    return node;
}
/*--------*/
/*Crée un nœud littéral pour les valeurs de chaîne (par exemple, "bonjour").
 Duplique la chaîne et marque le type comme STRING.*/

ASTNode* createStringLiteralNode(char* value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_EXPR_LITERAL;
    node->line = line_num;
    node->column = col_num;
    node->data.literal.value.stringValue = strdup(value);
    node->data.literal.literalType = TYPE_STRING;
    return node;
}
/*--------*/
/*Crée un nœud d'identifiant représentant une 
référence de variable (par exemple, 
quand vous utilisez x dans une expression). Stocke le nom de la variable*/

ASTNode* createIdentifierNode(char* name) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_EXPR_IDENTIFIER;
    node->line = line_num;
    node->column = col_num;
    node->data.identifier.name = strdup(name);
    return node;
}
/*--------*/

/*FONCTIONS UTILITAIRES D'AST*/
/*--------*/

/*Convertit une énumération de type de nœud en chaîne
 lisible. Par exemple, NODE_PROGRAM devient "PROGRAMME". 
 Utilisé pour le débogage et l'affichage de l'AST.*/

const char* nodeTypeToString(NodeType type) {
    switch(type) {
        case NODE_PROGRAM: return "PROGRAMME";
        case NODE_DECL_LIST: return "LISTE_DECL";
        case NODE_DECL: return "DÉCLARATION";
        case NODE_STMT_LIST: return "LISTE_INSTR";
        case NODE_ASSIGN: return "AFFECTATION";
        case NODE_PRINT: return "IMPRESSION";
        case NODE_IF: return "SI";
        case NODE_EXPR_BINOP: return "OP_BINAIRE";
        case NODE_EXPR_LITERAL: return "LITTÉRALE";
        case NODE_EXPR_IDENTIFIER: return "IDENTIFIANT";
        case NODE_CONDITION: return "CONDITION";
        default: return "INCONNU";
    }
}
/*--------*/
/*Convertit une énumération de type de données en chaîne. Par exemple, 
TYPE_INTEGER devient "ENTIER". Utile pour afficher les types de variables.*/

const char* dataTypeToString(DataType type) {
    switch(type) {
        case TYPE_INTEGER: return "ENTIER";
        case TYPE_FLOAT: return "RÉEL";
        case TYPE_STRING: return "CHAÎNE";
        case TYPE_BOOLEAN: return "BOOLÉEN";
        default: return "INCONNU";
    }
}
/*--------*/
/*Convertit une énumération de type d'opérateur en chaîne.
 Par exemple, AST_OP_ADD devient "+". 
 Utile pour afficher les opérations dans l'AST.*/

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
/*--------*/
/*Fonction utilitaire pour imprimer des indentations
 lors de l'affichage de l'AST.*/

void printIndent(int indent) {
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
}
/*--------*/
/*Imprime l'AST de manière lisible avec indentation.
 Utilise la récursivité pour parcourir tous les nœuds.*/

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
            
        default:
            printf("TYPE DE NŒUD INCONNU\n");
    }
}
/*--------*/
/*Libère la mémoire allouée pour l'AST de manière récursive.*/

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