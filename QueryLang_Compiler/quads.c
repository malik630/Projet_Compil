#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quads.h"
#include "ast.h"

Quadruplet tabQuad[2000];
int nextQuad = 0;
int tempCount = 0;


void generer_quad(const char* op, char* a1, char* a2, char* res) {
    if (nextQuad >= 2000) return;

    const char* s_op  = (op)  ? op  : "UNKNOWN";
    const char* s_a1  = (a1)  ? a1  : "";
    const char* s_a2  = (a2)  ? a2  : "";
    const char* s_res = (res) ? res : "";

    tabQuad[nextQuad].op   = strdup(s_op);
    tabQuad[nextQuad].arg1 = strdup(s_a1);
    tabQuad[nextQuad].arg2 = strdup(s_a2);
    tabQuad[nextQuad].res  = strdup(s_res);
    
    nextQuad++;
}

char* creer_temp() {
    char* t = malloc(15);
    sprintf(t, "T%d", tempCount++);
    return t;
}

void afficher_quads() {
    printf("\n--- TABLE DES QUADRUPLETS ---\n");
    for(int i = 0; i < nextQuad; i++) {
        printf("%d: (%s, %s, %s, %s)\n", i, tabQuad[i].op, 
               tabQuad[i].arg1, tabQuad[i].arg2, tabQuad[i].res);
    }
}

// Helper function to check if operator is relational
int is_relational_op(OperatorType op) {
    return (op == AST_OP_GT || op == AST_OP_LT || op == AST_OP_GTE || 
            op == AST_OP_LTE || op == AST_OP_EQ || op == AST_OP_NEQ);
}

void mettre_a_jour_res(int index, char* valeur) {
    if (index >= 0 && index < nextQuad) {
        if (tabQuad[index].res) free(tabQuad[index].res);
        tabQuad[index].res = strdup(valeur ? valeur : "");
    }
}

char* generer_code(ASTNode* node) {
    if (node == NULL) return "";

    switch(node->type) {
        case NODE_PROGRAM:
            if (node->data.program.declarations) 
                generer_code(node->data.program.declarations);
            if (node->data.program.statements) 
                generer_code(node->data.program.statements);
            return "";

        case NODE_DECL: {
            char* val = NULL;
            if (node->data.declaration.initializer)
                val = generer_code(node->data.declaration.initializer);

            // Convert DataType enum to string
            char* typeStr = strdup(dataTypeToString(node->data.declaration.dataType));

            if (val)
                generer_quad("=", val, typeStr, node->data.declaration.identifier);

            return node->data.declaration.identifier;
        }

        case NODE_STMT_LIST:
            if (node->data.stmtList.next) generer_code(node->data.stmtList.next);
            if (node->data.stmtList.statement) generer_code(node->data.stmtList.statement);
            return "";

        case NODE_ASSIGN: {
            char* src = generer_code(node->data.assignment.expression);
            generer_quad("=", src, "", node->data.assignment.identifier);
            return node->data.assignment.identifier;
        }

        case NODE_EXPR_BINOP: {
            // Special handling for logical AND (short-circuit evaluation)
            if (node->data.binOp.op == AST_OP_AND) {
                char* res = creer_temp();
                
                // Evaluate left operand
                ASTNode* leftNode = node->data.binOp.left;
                if (leftNode->type == NODE_EXPR_BINOP && is_relational_op(leftNode->data.binOp.op)) {
                    // Left is relational - use direct branch
                    char* l1 = generer_code(leftNode->data.binOp.left);
                    char* l2 = generer_code(leftNode->data.binOp.right);
                    
                    // Invert the branch (jump if condition is FALSE)
                    char* branch_op;
                    switch(leftNode->data.binOp.op) {
                        case AST_OP_GT:  branch_op = "BLE"; break;
                        case AST_OP_LT:  branch_op = "BGE"; break;
                        case AST_OP_GTE: branch_op = "BL";  break;
                        case AST_OP_LTE: branch_op = "BG";  break;
                        case AST_OP_EQ:  branch_op = "BNE"; break;
                        case AST_OP_NEQ: branch_op = "BE";  break;
                        default:         branch_op = "BE";  break;
                    }
                    
                    generer_quad(branch_op, l1, l2, "0");
                } else {
                    char* left = generer_code(leftNode);
                    generer_quad("BE", left, "0", "0");
                }
                
                int falseBranch = nextQuad - 1;
                
                // Evaluate right operand
                ASTNode* rightNode = node->data.binOp.right;
                if (rightNode->type == NODE_EXPR_BINOP && is_relational_op(rightNode->data.binOp.op)) {
                    // Right is relational - use direct branch
                    char* r1 = generer_code(rightNode->data.binOp.left);
                    char* r2 = generer_code(rightNode->data.binOp.right);
                    
                    // Invert the branch (jump if condition is FALSE)
                    char* branch_op;
                    switch(rightNode->data.binOp.op) {
                        case AST_OP_GT:  branch_op = "BLE"; break;
                        case AST_OP_LT:  branch_op = "BGE"; break;
                        case AST_OP_GTE: branch_op = "BL";  break;
                        case AST_OP_LTE: branch_op = "BG";  break;
                        case AST_OP_EQ:  branch_op = "BNE"; break;
                        case AST_OP_NEQ: branch_op = "BE";  break;
                        default:         branch_op = "BE";  break;
                    }
                    
                    generer_quad(branch_op, r1, r2, "0");
                } else {
                    char* right = generer_code(rightNode);
                    generer_quad("BE", right, "0", "0");
                }
                
                int falseBranch2 = nextQuad - 1;
                
                // Both true - set result to 1
                generer_quad("=", "1", "", res);
                int posJump = nextQuad;
                generer_quad("BR", "", "", "0");
                
                // Update false branches
                char labelFalse[15];
                sprintf(labelFalse, "%d", nextQuad);
                mettre_a_jour_res(falseBranch, labelFalse);
                mettre_a_jour_res(falseBranch2, labelFalse);
                
                // Set result to false
                generer_quad("=", "0", "", res);
                
                // Update end jump
                char labelEnd[15];
                sprintf(labelEnd, "%d", nextQuad);
                mettre_a_jour_res(posJump, labelEnd);
                
                return res;
            }
            // Special handling for logical OR (short-circuit evaluation)
            else if (node->data.binOp.op == AST_OP_OR) {
                char* res = creer_temp();
                
                // Evaluate left operand
                ASTNode* leftNode = node->data.binOp.left;
                if (leftNode->type == NODE_EXPR_BINOP && is_relational_op(leftNode->data.binOp.op)) {
                    // Left is relational - use direct branch
                    char* l1 = generer_code(leftNode->data.binOp.left);
                    char* l2 = generer_code(leftNode->data.binOp.right);
                    
                    // Direct branch (jump if condition is TRUE)
                    char* branch_op;
                    switch(leftNode->data.binOp.op) {
                        case AST_OP_GT:  branch_op = "BG";  break;
                        case AST_OP_LT:  branch_op = "BL";  break;
                        case AST_OP_GTE: branch_op = "BGE"; break;
                        case AST_OP_LTE: branch_op = "BLE"; break;
                        case AST_OP_EQ:  branch_op = "BE";  break;
                        case AST_OP_NEQ: branch_op = "BNE"; break;
                        default:         branch_op = "BNE"; break;
                    }
                    
                    generer_quad(branch_op, l1, l2, "0");
                } else {
                    char* left = generer_code(leftNode);
                    generer_quad("BNE", left, "0", "0");
                }
                
                int trueBranch = nextQuad - 1;
                
                // Evaluate right operand
                ASTNode* rightNode = node->data.binOp.right;
                if (rightNode->type == NODE_EXPR_BINOP && is_relational_op(rightNode->data.binOp.op)) {
                    // Right is relational - use direct branch
                    char* r1 = generer_code(rightNode->data.binOp.left);
                    char* r2 = generer_code(rightNode->data.binOp.right);
                    
                    // Direct branch (jump if condition is TRUE)
                    char* branch_op;
                    switch(rightNode->data.binOp.op) {
                        case AST_OP_GT:  branch_op = "BG";  break;
                        case AST_OP_LT:  branch_op = "BL";  break;
                        case AST_OP_GTE: branch_op = "BGE"; break;
                        case AST_OP_LTE: branch_op = "BLE"; break;
                        case AST_OP_EQ:  branch_op = "BE";  break;
                        case AST_OP_NEQ: branch_op = "BNE"; break;
                        default:         branch_op = "BNE"; break;
                    }
                    
                    generer_quad(branch_op, r1, r2, "0");
                } else {
                    char* right = generer_code(rightNode);
                    generer_quad("BNE", right, "0", "0");
                }
                
                int trueBranch2 = nextQuad - 1;
                
                // Both false - set result to 0
                generer_quad("=", "0", "", res);
                int posJump = nextQuad;
                generer_quad("BR", "", "", "0");
                
                // Update true branches
                char labelTrue[15];
                sprintf(labelTrue, "%d", nextQuad);
                mettre_a_jour_res(trueBranch, labelTrue);
                mettre_a_jour_res(trueBranch2, labelTrue);
                
                // Set result to true
                generer_quad("=", "1", "", res);
                
                // Update end jump
                char labelEnd[15];
                sprintf(labelEnd, "%d", nextQuad);
                mettre_a_jour_res(posJump, labelEnd);
                
                return res;
            }
            
            // For relational operators, generate direct comparison
            if (is_relational_op(node->data.binOp.op)) {
                char* t1 = generer_code(node->data.binOp.left);
                char* t2 = generer_code(node->data.binOp.right);
                char* res = creer_temp();
                
                // Generate comparison with branch instructions
                char* branch_op;
                switch(node->data.binOp.op) {
                    case AST_OP_GT:  branch_op = "BG";  break;
                    case AST_OP_LT:  branch_op = "BL";  break;
                    case AST_OP_GTE: branch_op = "BGE"; break;
                    case AST_OP_LTE: branch_op = "BLE"; break;
                    case AST_OP_EQ:  branch_op = "BE";  break;
                    case AST_OP_NEQ: branch_op = "BNE"; break;
                    default:         branch_op = "BNE"; break;
                }
                
                int posBranch = nextQuad;
                generer_quad(branch_op, t1, t2, "0");
                
                // False case
                generer_quad("=", "0", "", res);
                int posJump = nextQuad;
                generer_quad("BR", "", "", "0");
                
                // True case
                char labelTrue[15];
                sprintf(labelTrue, "%d", nextQuad);
                mettre_a_jour_res(posBranch, labelTrue);
                generer_quad("=", "1", "", res);
                
                // End
                char labelEnd[15];
                sprintf(labelEnd, "%d", nextQuad);
                mettre_a_jour_res(posJump, labelEnd);
                
                return res;
            }
            
            // Regular arithmetic/logical operations
            char* t1 = generer_code(node->data.binOp.left);
            char* t2 = generer_code(node->data.binOp.right);
            char* res = creer_temp();
            generer_quad(operatorToString(node->data.binOp.op), t1, t2, res);
            return res;
        }

        case NODE_EXPR_UNARYOP: {
            char* op1 = generer_code(node->data.unaryOp.operand);
            char* res = creer_temp();
            generer_quad(operatorToString(node->data.unaryOp.op), op1, "", res);
            return res;
        }

        case NODE_PRINT: {
            char* val = generer_code(node->data.print.expression);
            generer_quad("PRINT", val, "", "");
            return "";
        }

        case NODE_INPUT:
            generer_quad("READ", "", "", node->data.input.identifier);
            return node->data.input.identifier;

        case NODE_IF: {
            ASTNode* cond = node->data.ifStmt.condition;
            int posBR;

            // Check if condition is a relational operation
            if (cond->type == NODE_EXPR_BINOP && is_relational_op(cond->data.binOp.op)) {
                // Generate operands WITHOUT generating the comparison quad
                char* left  = generer_code(cond->data.binOp.left);
                char* right = generer_code(cond->data.binOp.right);
                char* op;
                
                // Map relational operators to inverted branch instructions
                switch(cond->data.binOp.op) {
                    case AST_OP_GT:  op = "BLE"; break; // if NOT (a > b) means a <= b
                    case AST_OP_LT:  op = "BGE"; break; // if NOT (a < b) means a >= b
                    case AST_OP_GTE: op = "BL";  break; // if NOT (a >= b) means a < b
                    case AST_OP_LTE: op = "BG";  break; // if NOT (a <= b) means a > b
                    case AST_OP_EQ:  op = "BNE"; break; // if NOT (a == b) means a != b
                    case AST_OP_NEQ: op = "BE";  break; // if NOT (a != b) means a == b
                    default:         op = "BE";  break;
                }

                posBR = nextQuad;
                
                generer_quad(op, left, right, "0"); // placeholder for jump

            } else {
                // For non-relational conditions, evaluate and branch if false (0)
                char* condStr = generer_code(cond);
                posBR = nextQuad;
                generer_quad("BE", condStr, "0", "0");
            }

            // Then block
            generer_code(node->data.ifStmt.then_block);

            // Update jump target
            char labelFin[15];
            sprintf(labelFin, "%d", nextQuad);
            mettre_a_jour_res(posBR, labelFin);

            posBR=nextQuad;
            generer_quad("BR", 0, "", "");
            

            // Else block
            if (node->data.ifStmt.else_block) {
                generer_code(node->data.ifStmt.else_block);
            }

            char labelDebut[15];
            sprintf(labelDebut, "%d", nextQuad);
            mettre_a_jour_res(posBR, labelDebut);


            return "";
        }

        case NODE_WHILE: {
            int debutWhile = nextQuad;
            ASTNode* cond = node->data.whileStmt.condition;
            int posBR;

            // Check if condition is a relational operation
            if (cond->type == NODE_EXPR_BINOP && is_relational_op(cond->data.binOp.op)) {
                char* left  = generer_code(cond->data.binOp.left);
                char* right = generer_code(cond->data.binOp.right);
                char* op;

                // Map to inverted branch
                switch(cond->data.binOp.op) {
                    case AST_OP_GT:  op = "BLE"; break;
                    case AST_OP_LT:  op = "BGE"; break;
                    case AST_OP_GTE: op = "BL";  break;
                    case AST_OP_LTE: op = "BG";  break;
                    case AST_OP_EQ:  op = "BNE"; break;
                    case AST_OP_NEQ: op = "BE";  break;
                    default:         op = "BE";  break;
                }

                posBR = nextQuad;
                generer_quad(op, left, right, "0"); // placeholder

            } else {
                char* condStr = generer_code(cond);
                posBR = nextQuad;
                generer_quad("BE", condStr, "0", "0");
            }

            // Loop body
            generer_code(node->data.whileStmt.body);

            // Jump back to start
            char labelDebut[15];
            sprintf(labelDebut, "%d", debutWhile);
            generer_quad("BR", labelDebut, "", "");

            // Update branch target to exit loop
            char labelSortie[15];
            sprintf(labelSortie, "%d", nextQuad);
            mettre_a_jour_res(posBR, labelSortie);

            return "";
        }

        case NODE_FOR: {
            char* start_val = generer_code(node->data.forStmt.from);
            generer_quad("=", start_val, "", node->data.forStmt.iterator);

            int debutFor = nextQuad;
            char* end_val = generer_code(node->data.forStmt.to);
            int posBR;

            // For loop: continue while iterator <= end_val
            // So branch (exit) when iterator > end_val
            posBR = nextQuad;
            generer_quad("BG", node->data.forStmt.iterator, end_val, "0"); // placeholder

            // Loop body
            generer_code(node->data.forStmt.body);

            // Increment iterator
            char* t_inc = creer_temp();
            generer_quad("+", node->data.forStmt.iterator, "1", t_inc);
            generer_quad("=", t_inc, "", node->data.forStmt.iterator);

            // Jump back to loop start
            char labelDebut[15];
            sprintf(labelDebut, "%d", debutFor);
            generer_quad("BR", labelDebut, "", "");

            // Update branch target to exit loop
            char labelSortie[15];
            sprintf(labelSortie, "%d", nextQuad);
            mettre_a_jour_res(posBR, labelSortie);

            return "";
        }

        case NODE_ARRAY_ACCESS_ASSIGN: {
            char* idx = generer_code(node->data.arrayAccessAssign.index);
            char* val = generer_code(node->data.arrayAccessAssign.expression);

            char addr[128];
            sprintf(addr, "%s[%s]", node->data.arrayAccessAssign.arrayName, idx);

            generer_quad("=", val, "", addr);

            return node->data.arrayAccessAssign.arrayName;
        }

        case NODE_ARRAY_ACCESS: {
            char* idx = generer_code(node->data.arrayAccess.index);
            char* res = creer_temp();
            generer_quad("=[]", node->data.arrayAccess.arrayName, idx, res);
            return res;
        }

        case NODE_ARRAY_DECL: {
            int upper_bound = node->data.arrayDecl.size;

            char ub_str[16];
            sprintf(ub_str, "%d", upper_bound);
            generer_quad("BOUNDS", "0", ub_str, "");

            generer_quad("ADEC", node->data.arrayDecl.name, "", "");

            if (node->data.arrayDecl.initializer) {
                // Reverse the expression list to maintain correct order
                ASTNode* prev = NULL;
                ASTNode* curr = node->data.arrayDecl.initializer;
                while (curr) {
                    ASTNode* next = (curr->type == NODE_EXPR_LIST) 
                                        ? curr->data.exprList.next 
                                        : NULL;
                    if (curr->type == NODE_EXPR_LIST)
                        curr->data.exprList.next = prev;
                    prev = curr;
                    curr = next;
                }
                ASTNode* reversed_head = prev;

                ASTNode* current = reversed_head;
                int index = 0;

                while (current != NULL) {
                    ASTNode* expr = (current->type == NODE_EXPR_LIST)
                                      ? current->data.exprList.expression
                                      : current;

                    char* val = generer_code(expr);

                    char idx_str[16];
                    sprintf(idx_str, "%d", index);

                    char addr[128];
                    sprintf(addr, "%s[%s]", node->data.arrayDecl.name, idx_str);

                    generer_quad("=", addr, "", val);

                    if (current->type == NODE_EXPR_LIST)
                        current = current->data.exprList.next;
                    else 
                        break;

                    index++;
                }
            }

            return "";
        }

        case NODE_RECORD_ACCESS_ASSIGN: {
            char* val = generer_code(node->data.recordAccessAssign.expression);
            char path[128];
            sprintf(path, "%s.%s", node->data.recordAccessAssign.recordName, 
                    node->data.recordAccessAssign.fieldName);
            generer_quad("=", val, "", path);
            return strdup(path);
        }

        case NODE_RECORD_ACCESS: {
            char path[128];
            sprintf(path, "%s.%s", node->data.recordAccess.recordName, 
                    node->data.recordAccess.fieldName);
            return strdup(path);
        }

        case NODE_RECORD_DECL: {
            int field_count = 0;
            ASTNode* field = node->data.recordDecl.fields;
            while (field != NULL) {
                field_count++;
                field = field->data.field.next;
            }
            
            char count_str[16];
            sprintf(count_str, "%d", field_count);
            generer_quad("RDECL", node->data.recordDecl.name, count_str, "");
            
            field = node->data.recordDecl.fields;
            while (field != NULL) {
                char field_info[128];
                char type_str_buf[32];
                char* type_str = type_str_buf;
                
                switch(field->data.field.type) {
                    case TYPE_INTEGER: strcpy(type_str, "INTEGER"); break;
                    case TYPE_FLOAT:   strcpy(type_str, "FLOAT");   break;
                    case TYPE_STRING:  strcpy(type_str, "STRING");  break;
                    case TYPE_BOOLEAN: strcpy(type_str, "BOOLEAN"); break;
                    default:           strcpy(type_str, "UNKNOWN"); break;
                }
                
                sprintf(field_info, "%s.%s", node->data.recordDecl.name, field->data.field.name);
                generer_quad("FIELD", field_info, type_str, "");
                
                field = field->data.field.next;
            }
            
            return "";
        }

        case NODE_RECORD_INSTANCE: {
            generer_quad("RINST", node->data.recordInstance.instanceName, 
                        node->data.recordInstance.typeName, "");
            return "";
        }

        case NODE_DICT_DECL: {
            char type_info[64];
            char key_type_buf[32];
            char val_type_buf[32];
            
            switch(node->data.dictDecl.keyType) {
                case TYPE_INTEGER: strcpy(key_type_buf, "INTEGER"); break;
                case TYPE_FLOAT:   strcpy(key_type_buf, "FLOAT");   break;
                case TYPE_STRING:  strcpy(key_type_buf, "STRING");  break;
                case TYPE_BOOLEAN: strcpy(key_type_buf, "BOOLEAN"); break;
                default:           strcpy(key_type_buf, "UNKNOWN"); break;
            }
            
            switch(node->data.dictDecl.valueType) {
                case TYPE_INTEGER: strcpy(val_type_buf, "INTEGER"); break;
                case TYPE_FLOAT:   strcpy(val_type_buf, "FLOAT");   break;
                case TYPE_STRING:  strcpy(val_type_buf, "STRING");  break;
                case TYPE_BOOLEAN: strcpy(val_type_buf, "BOOLEAN"); break;
                default:           strcpy(val_type_buf, "UNKNOWN"); break;
            }
            
            sprintf(type_info, "%s:%s", key_type_buf, val_type_buf);
            generer_quad("DDECL", node->data.dictDecl.name, type_info, "");
            return "";
        }

        case NODE_EXPR_LIST: {
            if (node->data.exprList.next) generer_code(node->data.exprList.next);
            return generer_code(node->data.exprList.expression);
        }

        case NODE_EXPR_LITERAL: {
            char* val = malloc(64);
            if (node->data.literal.literalType == TYPE_INTEGER) 
                sprintf(val, "%d", node->data.literal.value.intValue);
            else if (node->data.literal.literalType == TYPE_FLOAT) 
                sprintf(val, "%f", node->data.literal.value.floatValue);
            else if (node->data.literal.literalType == TYPE_BOOLEAN)
                sprintf(val, "%s", node->data.literal.value.boolValue ? "TRUE" : "FALSE");
            else if (node->data.literal.literalType == TYPE_STRING)
                sprintf(val, "'%s'", node->data.literal.value.stringValue);
            else 
                sprintf(val, "0");
            return val;
        }

        case NODE_EXPR_IDENTIFIER:
            return node->data.identifier.name;

        default: 
            return "";
    }
}