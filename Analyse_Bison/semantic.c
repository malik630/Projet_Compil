#include "semantic.h"
#include <stdio.h>
#include <string.h>
#include "global.h"

SemanticErrorList semanticErrors;
SemanticWarningList semanticWarnings;
int semanticErrorCount = 0;

// Initialisation
void initSemanticAnalysis() {
    semanticErrors.count = 0;
    semanticWarnings.count = 0;
    semanticErrorCount = 0;
}

// Reporter une erreur sémantique
void reportSemanticError(SemanticErrorType type, const char* message, int line, int col) {
    if (semanticErrors.count < 100) {
        semanticErrors.errors[semanticErrors.count].type = type;
        strncpy(semanticErrors.errors[semanticErrors.count].message, message, 255);
        semanticErrors.errors[semanticErrors.count].line = line;
        semanticErrors.errors[semanticErrors.count].column = col;
        semanticErrors.count++;
        semanticErrorCount++;
    }
}

// Reporter un avertissement sémantique
void reportSemanticWarning(SemanticWarningType type, const char* message, int line, int col) {
    if (semanticWarnings.count < 100) {
        semanticWarnings.warnings[semanticWarnings.count].type = type;
        strncpy(semanticWarnings.warnings[semanticWarnings.count].message, message, 255);
        semanticWarnings.warnings[semanticWarnings.count].line = line;
        semanticWarnings.warnings[semanticWarnings.count].column = col;
        semanticWarnings.count++;
    }
}

// Conversion de type d'erreur en chaîne
const char* semanticErrorTypeToString(SemanticErrorType type) {
    switch(type) {
        case SEM_ERROR_UNDECLARED: return "VARIABLE_NON_DECLAREE";
        case SEM_ERROR_REDECLARED: return "DOUBLE_DECLARATION";
        case SEM_ERROR_TYPE_MISMATCH: return "INCOMPATIBILITE_TYPE";
        case SEM_ERROR_DIV_BY_ZERO: return "DIVISION_PAR_ZERO";
        case SEM_ERROR_ARRAY_INDEX: return "INDICE_INVALIDE";
        case SEM_ERROR_UNINITIALIZED: return "VARIABLE_NON_INITIALISEE";
        case SEM_ERROR_CONST_ASSIGNMENT: return "MODIFICATION_CONSTANTE";
        default: return "ERREUR_INCONNUE";
    }
}

// Conversion de type d'avertissement en chaîne
const char* semanticWarningTypeToString(SemanticWarningType type) {
    switch(type) {
        case SEM_WARNING_UNUSED_VAR: return "VARIABLE_NON_UTILISEE";
        case SEM_WARNING_UNINIT_USE: return "UTILISATION_NON_INITIALISEE";
        default: return "AVERTISSEMENT_INCONNU";
    }
}

// Afficher les erreurs sémantiques
void printSemanticErrors() {
    if (semanticErrors.count == 0) {
        printf("\nAucune erreur sémantique détectée !\n");
        return;
    }
    
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║              ERREURS SÉMANTIQUES DÉTECTÉES                     ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    for (int i = 0; i < semanticErrors.count; i++) {
        SemanticError err = semanticErrors.errors[i];
        fprintf(stderr, "File \"%s\", line %d, character %d: semantic error\n", 
                current_filename, err.line, err.column);
        // Optionnel : afficher aussi le message détaillé
        fprintf(stderr, "  %s\n", err.message);
    }
    
    printf("Total: %d erreur(s) sémantique(s)\n", semanticErrors.count);
}

// Afficher les avertissements sémantiques
void printSemanticWarnings() {
    if (semanticWarnings.count == 0) {
        return;
    }
    
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║              AVERTISSEMENTS (Non Bloquants)                    ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    for (int i = 0; i < semanticWarnings.count; i++) {
        SemanticWarning warn = semanticWarnings.warnings[i];
        printf("  [%s] Ligne %d, Col %d:\n   %s\n\n", 
               semanticWarningTypeToString(warn.type),
               warn.line, warn.column, warn.message);
    }
    
    printf("Total: %d avertissement(s)\n", semanticWarnings.count);
}

// Vérifier la compatibilité des types
int areTypesCompatible(DataType type1, DataType type2) {
    if (type1 == type2) return 1;
    
    // INTEGER et FLOAT sont compatibles
    if ((type1 == TYPE_INTEGER && type2 == TYPE_FLOAT) ||
        (type1 == TYPE_FLOAT && type2 == TYPE_INTEGER)) {
        return 1;
    }
    
    return 0;
}

// Vérifier si une conversion est possible
int canConvert(DataType from, DataType to) {
    if (from == to) return 1;
    
    // INTEGER -> FLOAT OK
    if (from == TYPE_INTEGER && to == TYPE_FLOAT) return 1;
    
    // FLOAT -> INTEGER (perte de précision mais possible)
    if (from == TYPE_FLOAT && to == TYPE_INTEGER) return 1;
    
    return 0;
}

// Vérifier si un nœud est un zéro littéral
int isLiteralZero(ASTNode* node) {
    if (node == NULL) return 0;
    
    if (node->type == NODE_EXPR_LITERAL) {
        if (node->data.literal.literalType == TYPE_INTEGER) {
            return node->data.literal.value.intValue == 0;
        } else if (node->data.literal.literalType == TYPE_FLOAT) {
            return node->data.literal.value.floatValue == 0.0;
        }
    }
    
    return 0;
}

// Obtenir le type d'une expression
DataType getExpressionType(ASTNode* node) {
    if (node == NULL) return TYPE_INTEGER;
    
    switch(node->type) {
        case NODE_EXPR_LITERAL:
            return node->data.literal.literalType;
            
        case NODE_EXPR_IDENTIFIER: {
            Symbole* sym = obtenirSymbole(&tableGlobale, node->data.identifier.name);
            if (sym != NULL) {
                // Convertir TypeDonnee en DataType
                switch(sym->typeDonnee) {
                    case DATA_ENTIER: return TYPE_INTEGER;
                    case DATA_REEL: return TYPE_FLOAT;
                    case DATA_CHAINE: return TYPE_STRING;
                    case DATA_BOOLEEN: return TYPE_BOOLEAN;
                    default: return TYPE_INTEGER;
                }
            }
            return TYPE_INTEGER;
        }
        
        case NODE_EXPR_BINOP: {
            DataType leftType = getExpressionType(node->data.binOp.left);
            DataType rightType = getExpressionType(node->data.binOp.right);
            
            // Si l'un est FLOAT, le résultat est FLOAT
            if (leftType == TYPE_FLOAT || rightType == TYPE_FLOAT) {
                return TYPE_FLOAT;
            }
            
            // Pour les comparaisons, retourner BOOLEAN
            if (node->data.binOp.op >= AST_OP_EQ && node->data.binOp.op <= AST_OP_GTE) {
                return TYPE_BOOLEAN;
            }
            
            return leftType;
        }
        
        default:
            return TYPE_INTEGER;
    }
}

// Convertir DataType en TypeDonnee
TypeDonnee dataTypeToTypeDonnee(DataType dt) {
    switch(dt) {
        case TYPE_INTEGER: return DATA_ENTIER;
        case TYPE_FLOAT: return DATA_REEL;
        case TYPE_STRING: return DATA_CHAINE;
        case TYPE_BOOLEAN: return DATA_BOOLEEN;
        default: return DATA_ENTIER;
    }
}

int checkArrayIndex(ASTNode* node) {
    if (node == NULL) return 1;
    
    // Vérifier si c'est un accès à un tableau
    if (node->type == NODE_ARRAY_ACCESS || node->type == NODE_ARRAY_ACCESS_ASSIGN) {
        char* arrayName = (node->type == NODE_ARRAY_ACCESS) ? 
                          node->data.arrayAccess.arrayName : 
                          node->data.arrayAccessAssign.arrayName;
        
        ASTNode* indexExpr = (node->type == NODE_ARRAY_ACCESS) ? 
                             node->data.arrayAccess.index : 
                             node->data.arrayAccessAssign.index;
        
        // Vérifier que le tableau existe
        Symbole* arraySym = obtenirSymbole(&tableGlobale, arrayName);
        if (arraySym == NULL) {
            char msg[256];
            sprintf(msg, "Tableau '%s' non déclaré", arrayName);
            reportSemanticError(SEM_ERROR_UNDECLARED, msg, node->line, node->column);
            return 0;
        }
        
        // Vérifier que c'est bien un tableau
        if (arraySym->typeDonnee != DATA_TABLEAU) {
            char msg[256];
            sprintf(msg, "'%s' n'est pas un tableau", arrayName);
            reportSemanticError(SEM_ERROR_TYPE_MISMATCH, msg, node->line, node->column);
            return 0;
        }
        
        // Vérifier le type de l'index
        DataType indexType;
        if (!checkExpression(indexExpr, &indexType)) {
            return 0;
        }
        
        // L'index doit être un entier
        if (indexType != TYPE_INTEGER) {
            char msg[256];
            sprintf(msg, "Index de tableau doit être ENTIER, pas %s", 
                    dataTypeToString(indexType));
            reportSemanticError(SEM_ERROR_TYPE_MISMATCH, msg, node->line, node->column);
            return 0;
        }
        
        // Vérifier le dépassement de limites (si l'index est une constante)
        int constIndexValue;
        if (evaluateConstantInt(indexExpr, &constIndexValue)) {
            if (constIndexValue < 0) {
                char msg[256];
                sprintf(msg, "Index négatif non autorisé: %d", constIndexValue);
                reportSemanticError(SEM_ERROR_ARRAY_INDEX, msg, node->line, node->column);
                return 0;
            }
            
            if (constIndexValue >= arraySym->taille) {
                char msg[256];
                sprintf(msg, "Index %d hors limites (taille du tableau = %d)", 
                        constIndexValue, arraySym->taille);
                reportSemanticError(SEM_ERROR_ARRAY_INDEX, msg, node->line, node->column);
                return 0;
            }
        }
        
        return 1;
    }
    
    return 1;
}

int checkArrayDeclaration(ASTNode* node) {
    if (node == NULL || node->type != NODE_ARRAY_DECL) return 1;
    
    int valid = 1;
    
    // PAS de vérification de double déclaration
    // (déjà faite par insererSymbole() dans le parser)
    
    // Vérifier la taille
    if (node->data.arrayDecl.size <= 0) {
        char msg[256];
        sprintf(msg, "Taille du tableau '%s' doit être positive (reçu: %d)", 
                node->data.arrayDecl.name, node->data.arrayDecl.size);
        reportSemanticError(SEM_ERROR_TYPE_MISMATCH, msg, node->line, node->column);
        valid = 0;
    }
    
    // Vérifier l'initialiseur si présent
    if (node->data.arrayDecl.initializer != NULL) {
        int elemCount = 0;
        ASTNode* current = node->data.arrayDecl.initializer;
        
        while (current != NULL && current->type == NODE_EXPR_LIST) {
            elemCount++;
            
            DataType elemType;
            if (current->data.exprList.expression != NULL) {
                if (!checkExpression(current->data.exprList.expression, &elemType)) {
                    valid = 0;
                } else if (!areTypesCompatible(node->data.arrayDecl.elementType, elemType)) {
                    char msg[256];
                    sprintf(msg, "Élément %d du tableau '%s' a un type incompatible: attendu %s, reçu %s",
                            elemCount, node->data.arrayDecl.name,
                            dataTypeToString(node->data.arrayDecl.elementType),
                            dataTypeToString(elemType));
                    reportSemanticError(SEM_ERROR_TYPE_MISMATCH, msg, node->line, node->column);
                    valid = 0;
                }
            }
            
            current = current->data.exprList.next;
        }
        
        if (elemCount != node->data.arrayDecl.size) {
            char msg[256];
            sprintf(msg, "Tableau '%s': %d éléments fournis, %d attendus",
                    node->data.arrayDecl.name, elemCount, node->data.arrayDecl.size);
            reportSemanticError(SEM_ERROR_TYPE_MISMATCH, msg, node->line, node->column);
            valid = 0;
        }
    }
    
    return valid;
}

int checkArrayAccessAssignment(ASTNode* node) {
    if (node == NULL) return 1;
    
    // Vérifier l'index du tableau
    if (!checkArrayIndex(node)) {
        return 0;
    }
    
    // Vérifier l'expression d'affectation
    DataType exprType;
    if (!checkExpression(node->data.arrayAccessAssign.expression, &exprType)) {
        return 0;
    }
    
    // Obtenir le type du tableau
    char* arrayName = node->data.arrayAccessAssign.arrayName;
    Symbole* arraySym = obtenirSymbole(&tableGlobale, arrayName);
    
    if (arraySym != NULL) {
        // Convertir TypeDonnee en DataType pour comparaison
        DataType arrayElementType;
        switch(arraySym->typeDonnee) {
            case DATA_TABLEAU:
                // Pour simplifier, on considère que tous les tableaux sont d'entiers
                // Dans une version complète, il faudrait stocker le type des éléments
                arrayElementType = TYPE_INTEGER;
                break;
            default:
                arrayElementType = TYPE_INTEGER;
        }
        
        // Vérifier compatibilité des types
        if (!areTypesCompatible(arrayElementType, exprType)) {
            char msg[256];
            sprintf(msg, "Type incompatible pour l'élément de tableau: %s attendu, %s fourni",
                    dataTypeToString(arrayElementType), dataTypeToString(exprType));
            reportSemanticError(SEM_ERROR_TYPE_MISMATCH, msg, node->line, node->column);
            return 0;
        }
    }
    
    return 1;
}

// Fonction pour évaluer une expression constante (si possible)
int evaluateConstantInt(ASTNode* node, int* result) {
    if (node == NULL) return 0;
    
    // Cas d'un nombre négatif (unary minus)
    if (node->type == NODE_EXPR_UNARYOP && node->data.unaryOp.op == AST_OP_NEG) {
        int innerValue;
        if (evaluateConstantInt(node->data.unaryOp.operand, &innerValue)) {
            *result = -innerValue;
            return 1;
        }
        return 0;
    }
    
    if (node->type == NODE_EXPR_LITERAL) {
        if (node->data.literal.literalType == TYPE_INTEGER) {
            *result = node->data.literal.value.intValue;
            return 1;
        }
        // Pour les floats entiers
        if (node->data.literal.literalType == TYPE_FLOAT) {
            float fval = node->data.literal.value.floatValue;
            if (fval == (int)fval) { // Vérifier si c'est un entier
                *result = (int)fval;
                return 1;
            }
        }
    }
    
    // Pour les identifiants constants
    if (node->type == NODE_EXPR_IDENTIFIER) {
        Symbole* sym = obtenirSymbole(&tableGlobale, node->data.identifier.name);
        if (sym != NULL && sym->typeSymbole == TYPE_CONSTANTE) {
            if (sym->typeDonnee == DATA_ENTIER) {
                *result = sym->valeur.valeurInt;
                return 1;
            } else if (sym->typeDonnee == DATA_REEL) {
                float fval = sym->valeur.valeurReel;
                if (fval == (int)fval) {
                    *result = (int)fval;
                    return 1;
                }
            }
        }
    }
    
    // Pour les opérations binaires
    if (node->type == NODE_EXPR_BINOP) {
        int leftVal, rightVal;
        if (evaluateConstantInt(node->data.binOp.left, &leftVal) &&
            evaluateConstantInt(node->data.binOp.right, &rightVal)) {
            
            switch(node->data.binOp.op) {
                case AST_OP_ADD: *result = leftVal + rightVal; return 1;
                case AST_OP_SUB: *result = leftVal - rightVal; return 1;
                case AST_OP_MUL: *result = leftVal * rightVal; return 1;
                case AST_OP_DIV: 
                    if (rightVal != 0) {
                        *result = leftVal / rightVal; 
                        return 1;
                    }
                    break;
                default: break;
            }
        }
    }
    
    return 0;
}

int checkRecordInstance(ASTNode* node) {
    if (node == NULL || node->type != NODE_RECORD_INSTANCE) return 1;
    
    // PAS de vérification de double déclaration
    // (déjà faite par insererSymbole() dans le parser)
    
    // TODO: Vérifier que le type de record existe
    
    return 1;
}

int checkRecordDeclaration(ASTNode* node) {
    if (node == NULL || node->type != NODE_RECORD_DECL) return 1;
    
    // Pour l'instant, on accepte tout
    return 1;
}

int checkDictDeclaration(ASTNode* node) {
    if (node == NULL || node->type != NODE_DICT_DECL) return 1;
    
    // PAS de vérification de double déclaration
    // (déjà faite par insererSymbole() dans le parser)
    
    return 1;
}

int checkInput(ASTNode* node) {
    if (node == NULL) return 1;
    
    // Vérifier que la variable existe
    Symbole* sym = obtenirSymbole(&tableGlobale, node->data.input.identifier);
    if (sym == NULL) {
        char msg[256];
        sprintf(msg, "Variable '%s' non déclarée", node->data.input.identifier);
        reportSemanticError(SEM_ERROR_UNDECLARED, msg, node->line, node->column);
        return 0;
    }
    
    // Marquer comme initialisée
    sym->initialise = 1;
    
    return 1;
}

int checkWhileStatement(ASTNode* node) {
    if (node == NULL) return 1;
    
    int valid = 1;
    
    if (!checkCondition(node->data.whileStmt.condition)) {
        valid = 0;
    }
    
    entrerPortee(&tableGlobale);
    if (!checkStatements(node->data.whileStmt.body)) {
        valid = 0;
    }
    sortirPortee(&tableGlobale);
    
    return valid;
}

int checkForStatement(ASTNode* node) {
    if (node == NULL) return 1;
    
    int valid = 1;
    
    DataType fromType, toType;
    if (!checkExpression(node->data.forStmt.from, &fromType)) {
        valid = 0;
    } else if (fromType != TYPE_INTEGER) {
        char msg[256];
        sprintf(msg, "Expression FROM doit être de type INTEGER, pas %s",
                dataTypeToString(fromType));
        reportSemanticError(SEM_ERROR_TYPE_MISMATCH, msg, node->line, node->column);
        valid = 0;
    }
    
    if (!checkExpression(node->data.forStmt.to, &toType)) {
        valid = 0;
    } else if (toType != TYPE_INTEGER) {
        char msg[256];
        sprintf(msg, "Expression TO doit être de type INTEGER, pas %s",
                dataTypeToString(toType));
        reportSemanticError(SEM_ERROR_TYPE_MISMATCH, msg, node->line, node->column);
        valid = 0;
    }
    
    entrerPortee(&tableGlobale);
    if (!checkStatements(node->data.forStmt.body)) {
        valid = 0;
    }
    sortirPortee(&tableGlobale);
    
    return valid;
}

int checkRecordAccessAssignment(ASTNode* node) {
    if (node == NULL) return 1;
    
    Symbole* recordSym = obtenirSymbole(&tableGlobale, node->data.recordAccessAssign.recordName);
    if (recordSym == NULL) {
        char msg[256];
        sprintf(msg, "Record '%s' non déclaré", node->data.recordAccessAssign.recordName);
        reportSemanticError(SEM_ERROR_UNDECLARED, msg, node->line, node->column);
        return 0;
    }
    
    DataType exprType;
    if (!checkExpression(node->data.recordAccessAssign.expression, &exprType)) {
        return 0;
    }
    
    return 1;
}

// Vérifier une expression
int checkExpression(ASTNode* node, DataType* resultType) {
    if (node == NULL) return 1;
    
    int valid = 1;  // On continue même en cas d'erreur pour collecter toutes les erreurs
    
    switch(node->type) {
        case NODE_EXPR_LITERAL:
            *resultType = node->data.literal.literalType;
            return 1;
            
        case NODE_EXPR_IDENTIFIER: {
            Symbole* sym = obtenirSymbole(&tableGlobale, node->data.identifier.name);
            if (sym == NULL) {
                char msg[256];
                sprintf(msg, "Variable '%s' non déclarée", node->data.identifier.name);
                reportSemanticError(SEM_ERROR_UNDECLARED, msg, node->line, node->column);
                *resultType = TYPE_INTEGER;  // Type par défaut
                return 0;
            }
            
            if (!sym->initialise && sym->typeSymbole != TYPE_CONSTANTE) {
                char msg[256];
                sprintf(msg, "Variable '%s' utilisée sans initialisation", node->data.identifier.name);
                reportSemanticWarning(SEM_WARNING_UNINIT_USE, msg, node->line, node->column);
            }
            
            // Convertir TypeDonnee en DataType
            switch(sym->typeDonnee) {
                case DATA_ENTIER: *resultType = TYPE_INTEGER; break;
                case DATA_REEL: *resultType = TYPE_FLOAT; break;
                case DATA_CHAINE: *resultType = TYPE_STRING; break;
                case DATA_BOOLEEN: *resultType = TYPE_BOOLEAN; break;
                default: *resultType = TYPE_INTEGER;
            }
            return 1;
        }
        
        case NODE_EXPR_BINOP: {
            DataType leftType, rightType;
            
            // Vérifier les deux côtés et collecter TOUTES les erreurs
            if (!checkExpression(node->data.binOp.left, &leftType)) {
                valid = 0;
                leftType = TYPE_INTEGER;  // Type par défaut pour continuer
            }
            
            if (!checkExpression(node->data.binOp.right, &rightType)) {
                valid = 0;
                rightType = TYPE_INTEGER;  // Type par défaut pour continuer
            }
            
            // Vérification division par zéro
            if ((node->data.binOp.op == AST_OP_DIV || node->data.binOp.op == AST_OP_MOD)) {
                if (isLiteralZero(node->data.binOp.right)) {
                    char msg[256];
                    sprintf(msg, "Division par zéro détectée");
                    reportSemanticError(SEM_ERROR_DIV_BY_ZERO, msg, node->line, node->column);
                    valid = 0;
                }
            }
            
            // Vérification compatibilité des types (même si erreur avant)
            if (!areTypesCompatible(leftType, rightType)) {
                char msg[256];
                sprintf(msg, "Types incompatibles dans l'expression: %s et %s",
                        dataTypeToString(leftType), dataTypeToString(rightType));
                reportSemanticError(SEM_ERROR_TYPE_MISMATCH, msg, node->line, node->column);
                valid = 0;
            }
            
            // Déterminer le type résultat
            if (node->data.binOp.op >= AST_OP_EQ && node->data.binOp.op <= AST_OP_GTE) {
                *resultType = TYPE_BOOLEAN;
            } else if (leftType == TYPE_FLOAT || rightType == TYPE_FLOAT) {
                *resultType = TYPE_FLOAT;
            } else {
                *resultType = leftType;
            }
            
            return valid;
        }
        case NODE_ARRAY_ACCESS: {
            if (!checkArrayIndex(node)) {
                *resultType = TYPE_INTEGER;
                return 0;
            }
            
            Symbole* arraySym = obtenirSymbole(&tableGlobale, node->data.arrayAccess.arrayName);
            if (arraySym != NULL) {
                switch(arraySym->typeElement) {
                    case DATA_ENTIER: *resultType = TYPE_INTEGER; break;
                    case DATA_REEL: *resultType = TYPE_FLOAT; break;
                    case DATA_CHAINE: *resultType = TYPE_STRING; break;
                    case DATA_BOOLEEN: *resultType = TYPE_BOOLEAN; break;
                    default: *resultType = TYPE_INTEGER;
                }
            } else {
                *resultType = TYPE_INTEGER;
            }
            return 1;
        }
        
        default:
            *resultType = TYPE_INTEGER;
            return 1;
    }
}

// Vérifier une déclaration
int checkDeclaration(ASTNode* node) {
    if (node == NULL) return 1;
    
    int valid = 1;
    
    if (node->type == NODE_DECL) {
        // PAS de vérification de double déclaration
        // (déjà faite par insererSymbole() dans le parser)
        
        // Vérifier l'initialiseur si présent
        if (node->data.declaration.initializer != NULL) {
            DataType exprType;
            
            if (!checkExpression(node->data.declaration.initializer, &exprType)) {
                valid = 0;
            }
            
            // Vérifier compatibilité des types
            if (!areTypesCompatible(node->data.declaration.dataType, exprType)) {
                char msg[256];
                sprintf(msg, "Type de l'initialiseur (%s) incompatible avec le type déclaré (%s) pour '%s'",
                        dataTypeToString(exprType), 
                        dataTypeToString(node->data.declaration.dataType),
                        node->data.declaration.identifier);
                reportSemanticError(SEM_ERROR_TYPE_MISMATCH, msg, node->line, node->column);
                valid = 0;
            }
        }
        
        // Vérifier la prochaine déclaration
        if (node->data.declaration.next != NULL) {
            if (!checkDeclaration(node->data.declaration.next)) {
                valid = 0;
            }
        }
    }
    
    return valid;
}

// Vérifier une affectation
int checkAssignment(ASTNode* node) {
    if (node == NULL) return 1;
    
    // Vérifier que la variable existe
    Symbole* sym = obtenirSymbole(&tableGlobale, node->data.assignment.identifier);
    if (sym == NULL) {
        char msg[256];
        sprintf(msg, "Variable '%s' non déclarée", node->data.assignment.identifier);
        reportSemanticError(SEM_ERROR_UNDECLARED, msg, node->line, node->column);
        return 0;
    }
    
    // Vérifier qu'on n'assigne pas à une constante
    if (sym->typeSymbole == TYPE_CONSTANTE) {
        char msg[256];
        sprintf(msg, "Impossible de modifier la constante '%s'", node->data.assignment.identifier);
        reportSemanticError(SEM_ERROR_CONST_ASSIGNMENT, msg, node->line, node->column);
        return 0;
    }
    
    // Vérifier l'expression
    DataType exprType;
    if (!checkExpression(node->data.assignment.expression, &exprType)) {
        return 0;
    }
    
    // Convertir TypeDonnee en DataType pour la comparaison
    DataType varType;
    switch(sym->typeDonnee) {
        case DATA_ENTIER: varType = TYPE_INTEGER; break;
        case DATA_REEL: varType = TYPE_FLOAT; break;
        case DATA_CHAINE: varType = TYPE_STRING; break;
        case DATA_BOOLEEN: varType = TYPE_BOOLEAN; break;
        default: varType = TYPE_INTEGER;
    }
    
    // Vérifier compatibilité des types
    if (!areTypesCompatible(varType, exprType)) {
        char msg[256];
        sprintf(msg, "Type de l'expression (%s) incompatible avec le type de '%s' (%s)",
                dataTypeToString(exprType), node->data.assignment.identifier,
                dataTypeToString(varType));
        reportSemanticError(SEM_ERROR_TYPE_MISMATCH, msg, node->line, node->column);
        return 0;
    }
    
    // Marquer comme initialisée
    sym->initialise = 1;
    
    return 1;
}

// Vérifier une condition
int checkCondition(ASTNode* node) {
    if (node == NULL) return 1;
    
    DataType condType;
    if (!checkExpression(node, &condType)) {
        return 0;
    }
    
    // La condition devrait être booléenne ou numérique (compatible)
    if (condType != TYPE_BOOLEAN && condType != TYPE_INTEGER && condType != TYPE_FLOAT) {
        char msg[256];
        sprintf(msg, "Type de condition invalide: %s (attendu BOOLEAN ou numérique)",
                dataTypeToString(condType));
        reportSemanticError(SEM_ERROR_TYPE_MISMATCH, msg, node->line, node->column);
        return 0;
    }
    
    return 1;
}

// Vérifier une instruction print
int checkPrint(ASTNode* node) {
    if (node == NULL) return 1;
    
    DataType exprType;
    return checkExpression(node->data.print.expression, &exprType);
}

// Vérifier une instruction WHEN
int checkIfStatement(ASTNode* node) {
    if (node == NULL) return 1;
    
    int valid = 1;
    
    // Vérifier la condition
    if (!checkCondition(node->data.ifStmt.condition)) {
        valid = 0;
    }
    
    // Entrer dans une nouvelle portée
    entrerPortee(&tableGlobale);
    
    // Vérifier le bloc then
    if (!checkStatements(node->data.ifStmt.then_block)) {
        valid = 0;
    }
    
    // Sortir de la portée
    sortirPortee(&tableGlobale);
    
    // Vérifier le bloc else si présent
    if (node->data.ifStmt.else_block != NULL) {
        entrerPortee(&tableGlobale);
        if (!checkStatements(node->data.ifStmt.else_block)) {
            valid = 0;
        }
        sortirPortee(&tableGlobale);
    }
    
    return valid;
}

// Vérifier une liste d'instructions
int checkStatements(ASTNode* node) {
    if (node == NULL) return 1;
    
    int valid = 1;
    
    if (node->type == NODE_STMT_LIST) {
        if (node->data.stmtList.statement != NULL) {
            if (!checkStatements(node->data.stmtList.statement)) {
                valid = 0;
            }
        }
        if (node->data.stmtList.next != NULL) {
            if (!checkStatements(node->data.stmtList.next)) {
                valid = 0;
            }
        }
    } 
    // DÉCLARATIONS (maintenant dans les instructions)
    else if (node->type == NODE_DECL) {
        if (!checkDeclaration(node)) valid = 0;
    }
    else if (node->type == NODE_ARRAY_DECL) {
        if (!checkArrayDeclaration(node)) valid = 0;
    }
    else if (node->type == NODE_RECORD_DECL) {
        if (!checkRecordDeclaration(node)) valid = 0;
    }
    else if (node->type == NODE_RECORD_INSTANCE) {
        if (!checkRecordInstance(node)) valid = 0;
    }
    else if (node->type == NODE_DICT_DECL) {
        if (!checkDictDeclaration(node)) valid = 0;
    }
    // AFFECTATIONS
    else if (node->type == NODE_ASSIGN) {
        if (!checkAssignment(node)) valid = 0;
    } 
    else if (node->type == NODE_ARRAY_ACCESS_ASSIGN) {
        if (!checkArrayAccessAssignment(node)) valid = 0;
    }
    else if (node->type == NODE_RECORD_ACCESS_ASSIGN) {
        if (!checkRecordAccessAssignment(node)) valid = 0;
    }
    // ENTRÉES/SORTIES
    else if (node->type == NODE_PRINT) {
        if (!checkPrint(node)) valid = 0;
    }
    else if (node->type == NODE_INPUT) {
        if (!checkInput(node)) valid = 0;
    }
    // STRUCTURES DE CONTRÔLE
    else if (node->type == NODE_IF) {
        if (!checkIfStatement(node)) valid = 0;
    }
    else if (node->type == NODE_WHILE) {
        if (!checkWhileStatement(node)) valid = 0;
    }
    else if (node->type == NODE_FOR) {
        if (!checkForStatement(node)) valid = 0;
    }
    
    return valid;
}

// Marquer une variable comme utilisée (récursif)
void markVariableAsUsed(ASTNode* node) {
    if (node == NULL) return;
    
    if (node->type == NODE_EXPR_IDENTIFIER) {
        Symbole* sym = obtenirSymbole(&tableGlobale, node->data.identifier.name);
        if (sym != NULL) {
            sym->initialise = 2;
        }
    } else if (node->type == NODE_ARRAY_ACCESS) {
        // Marquer le tableau comme utilisé
        Symbole* sym = obtenirSymbole(&tableGlobale, node->data.arrayAccess.arrayName);
        if (sym != NULL) {
            sym->initialise = 2;
        }
        // Vérifier l'index aussi
        markVariableAsUsed(node->data.arrayAccess.index);
    } else if (node->type == NODE_ARRAY_ACCESS_ASSIGN) {
        Symbole* sym = obtenirSymbole(&tableGlobale, node->data.arrayAccessAssign.arrayName);
        if (sym != NULL) {
            sym->initialise = 2;
        }
        markVariableAsUsed(node->data.arrayAccessAssign.index);
        markVariableAsUsed(node->data.arrayAccessAssign.expression);
    } else if (node->type == NODE_EXPR_BINOP) {
        markVariableAsUsed(node->data.binOp.left);
        markVariableAsUsed(node->data.binOp.right);
    } else if (node->type == NODE_ASSIGN) {
        markVariableAsUsed(node->data.assignment.expression);
    } else if (node->type == NODE_PRINT) {
        markVariableAsUsed(node->data.print.expression);
    } else if (node->type == NODE_IF) {
        markVariableAsUsed(node->data.ifStmt.condition);
        markVariableAsUsed(node->data.ifStmt.then_block);
        markVariableAsUsed(node->data.ifStmt.else_block);
    } else if (node->type == NODE_STMT_LIST) {
        markVariableAsUsed(node->data.stmtList.statement);
        markVariableAsUsed(node->data.stmtList.next);
    }
    else if (node->type == NODE_WHILE) {
        markVariableAsUsed(node->data.whileStmt.condition);
        markVariableAsUsed(node->data.whileStmt.body);
    } else if (node->type == NODE_FOR) {
        markVariableAsUsed(node->data.forStmt.from);
        markVariableAsUsed(node->data.forStmt.to);
        markVariableAsUsed(node->data.forStmt.body);
    } else if (node->type == NODE_DECL) {
        if (node->data.declaration.initializer) {
            markVariableAsUsed(node->data.declaration.initializer);
        }
        if (node->data.declaration.next) {
            markVariableAsUsed(node->data.declaration.next);
        }
    } else if (node->type == NODE_ARRAY_DECL) {
        if (node->data.arrayDecl.initializer) {
            markVariableAsUsed(node->data.arrayDecl.initializer);
        }
    }
}

// Vérifier les variables non utilisées
void checkUnusedVariables() {
    for (int i = 0; i < tableGlobale.nbSymboles; i++) {
        Symbole* sym = &tableGlobale.symboles[i];
        
        // Si initialise == 1, c'est déclaré mais pas utilisé
        // Si initialise == 2, c'est utilisé
        if (sym->initialise == 1 || sym->initialise == 0) {
            char msg[256];
            sprintf(msg, "Variable '%s' déclarée mais jamais utilisée", sym->nom);
            reportSemanticWarning(SEM_WARNING_UNUSED_VAR, msg, sym->line, sym->column);
        }
    }
}

// Analyse sémantique principale
int performSemanticAnalysis(ASTNode* root) {
    if (root == NULL) return 0;
    
    initSemanticAnalysis();
    
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║              ANALYSE SÉMANTIQUE EN COURS...                    ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    int valid = 1;
    
    if (root->type == NODE_PROGRAM) {
        // Maintenant, les déclarations sont dans la branche statements
        
        printf("Vérification des instructions (incluant les déclarations)...\n");
        if (!checkStatements(root->data.program.statements)) {
            valid = 0;
        }
        
        printf("Analyse de l'utilisation des variables...\n");
        markVariableAsUsed(root->data.program.statements);
        
        checkUnusedVariables();
    }
    
    // Afficher les erreurs
    printSemanticErrors();
    
    // Afficher les avertissements
    printSemanticWarnings();
    
    if (valid && semanticErrors.count == 0) {
        printf("\nAnalyse sémantique réussie !\n");
        if (semanticWarnings.count > 0) {
            printf("  (avec %d avertissement(s) non bloquant(s))\n", semanticWarnings.count);
        }
        return 1;
    } else {
        printf("\nAnalyse sémantique échouée avec %d erreur(s)\n", semanticErrors.count);
        return 0;
    }
}