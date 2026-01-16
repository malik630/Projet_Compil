#include "semantic.h"
#include <stdio.h>
#include <string.h>

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
        printf("\n✓ Aucune erreur sémantique détectée !\n");
        return;
    }
    
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║              ERREURS SÉMANTIQUES DÉTECTÉES                     ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    for (int i = 0; i < semanticErrors.count; i++) {
        SemanticError err = semanticErrors.errors[i];
        printf(" [%s] Ligne %d, Col %d:\n   %s\n\n", 
               semanticErrorTypeToString(err.type),
               err.line, err.column, err.message);
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
        
        default:
            *resultType = TYPE_INTEGER;
            return 1;
    }
}

// Fonction auxiliaire pour collecter tous les noms de variables déclarées
void collectDeclaredNames(ASTNode* node, char names[][50], int* count) {
    if (node == NULL) return;
    
    if (node->type == NODE_DECL) {
        strcpy(names[*count], node->data.declaration.identifier);
        (*count)++;
        
        // Traiter le suivant
        if (node->data.declaration.next != NULL) {
            collectDeclaredNames(node->data.declaration.next, names, count);
        }
    }
}

// Vérifier les doubles déclarations AVANT d'analyser les déclarations
int checkForDuplicateDeclarations(ASTNode* node) {
    if (node == NULL) return 1;
    
    char names[100][50];
    int count = 0;
    
    // Collecter tous les noms
    collectDeclaredNames(node, names, &count);
    
    // Vérifier les doublons
    int valid = 1;
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(names[i], names[j]) == 0) {
                char msg[256];
                sprintf(msg, "Variable '%s' déclarée plusieurs fois", names[i]);
                reportSemanticError(SEM_ERROR_REDECLARED, msg, 0, 0);
                valid = 0;
            }
        }
    }
    
    return valid;
}

// Vérifier une déclaration
int checkDeclaration(ASTNode* node) {
    if (node == NULL) return 1;
    
    int valid = 1;  // Continuer même en cas d'erreur
    
    if (node->type == NODE_DECL) {
        // Vérifier l'initialiseur si présent
        if (node->data.declaration.initializer != NULL) {
            DataType exprType;
            
            // Vérifier l'expression de l'initialiseur
            if (!checkExpression(node->data.declaration.initializer, &exprType)) {
                valid = 0;  // Marquer comme invalide mais continuer
            }
            
            // Vérifier compatibilité des types (même si erreur dans l'expression)
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

// Vérifier une instruction if
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
    } else if (node->type == NODE_ASSIGN) {
        if (!checkAssignment(node)) valid = 0;
    } else if (node->type == NODE_PRINT) {
        if (!checkPrint(node)) valid = 0;
    } else if (node->type == NODE_IF) {
        if (!checkIfStatement(node)) valid = 0;
    }
    
    return valid;
}

// Marquer une variable comme utilisée (récursif)
void markVariableAsUsed(ASTNode* node) {
    if (node == NULL) return;
    
    if (node->type == NODE_EXPR_IDENTIFIER) {
        Symbole* sym = obtenirSymbole(&tableGlobale, node->data.identifier.name);
        if (sym != NULL) {
            sym->initialise = 2; // 2 = utilisée
        }
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
            reportSemanticWarning(SEM_WARNING_UNUSED_VAR, msg, 0, 0);
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
        // Vérifier d'abord les doubles déclarations
        printf("→ Vérification des doubles déclarations...\n");
        if (!checkForDuplicateDeclarations(root->data.program.declarations)) {
            valid = 0;
        }
        
        // Vérifier les déclarations (initialiseurs, types)
        printf("→ Vérification des déclarations...\n");
        if (!checkDeclaration(root->data.program.declarations)) {
            valid = 0;
        }
        
        // Vérifier les instructions
        printf("→ Vérification des instructions...\n");
        if (!checkStatements(root->data.program.statements)) {
            valid = 0;
        }
        
        // Marquer les variables utilisées
        printf("→ Analyse de l'utilisation des variables...\n");
        markVariableAsUsed(root->data.program.statements);
        
        // Vérifier les variables non utilisées
        checkUnusedVariables();
    }
    
    // Afficher les erreurs
    printSemanticErrors();
    
    // Afficher les avertissements
    printSemanticWarnings();
    
    if (valid && semanticErrors.count == 0) {
        printf("\n✓ Analyse sémantique réussie !\n");
        if (semanticWarnings.count > 0) {
            printf("  (avec %d avertissement(s) non bloquant(s))\n", semanticWarnings.count);
        }
        return 1;
    } else {
        printf("\n✗ Analyse sémantique échouée avec %d erreur(s)\n", semanticErrors.count);
        return 0;
    }
}