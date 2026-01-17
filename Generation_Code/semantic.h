#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"
#include "table_symboles_enrichie.h"

// Types d'erreurs sémantiques
typedef enum {
    SEM_ERROR_NONE,
    SEM_ERROR_UNDECLARED,
    SEM_ERROR_REDECLARED,
    SEM_ERROR_TYPE_MISMATCH,
    SEM_ERROR_DIV_BY_ZERO,
    SEM_ERROR_ARRAY_INDEX,
    SEM_ERROR_UNINITIALIZED,
    SEM_ERROR_CONST_ASSIGNMENT
} SemanticErrorType;

// Types d'avertissements (warnings)
typedef enum {
    SEM_WARNING_NONE,
    SEM_WARNING_UNUSED_VAR,
    SEM_WARNING_UNINIT_USE
} SemanticWarningType;

// Structure pour gérer les erreurs
typedef struct {
    SemanticErrorType type;
    char message[256];
    int line;
    int column;
} SemanticError;

// Structure pour gérer les avertissements
typedef struct {
    SemanticWarningType type;
    char message[256];
    int line;
    int column;
} SemanticWarning;

// Liste des erreurs
typedef struct {
    SemanticError errors[100];
    int count;
} SemanticErrorList;

// Liste des avertissements
typedef struct {
    SemanticWarning warnings[100];
    int count;
} SemanticWarningList;

// Variables globales
extern TableSymboles tableGlobale;
extern SemanticErrorList semanticErrors;
extern SemanticWarningList semanticWarnings;
extern int semanticErrorCount;

// Fonctions principales d'analyse sémantique
void initSemanticAnalysis();
int performSemanticAnalysis(ASTNode* root);
void reportSemanticError(SemanticErrorType type, const char* message, int line, int col);
void reportSemanticWarning(SemanticWarningType type, const char* message, int line, int col);
void printSemanticErrors();
void printSemanticWarnings();

// Fonctions de vérification
int checkDeclaration(ASTNode* node);
int checkAssignment(ASTNode* node);
int checkExpression(ASTNode* node, DataType* resultType);
int checkCondition(ASTNode* node);
int checkPrint(ASTNode* node);
int checkIfStatement(ASTNode* node);
int checkStatements(ASTNode* node);

// Fonctions utilitaires
int areTypesCompatible(DataType type1, DataType type2);
int canConvert(DataType from, DataType to);
int isLiteralZero(ASTNode* node);
DataType getExpressionType(ASTNode* node);
const char* semanticErrorTypeToString(SemanticErrorType type);
const char* semanticWarningTypeToString(SemanticWarningType type);
void checkUnusedVariables();

#endif /* SEMANTIC_H */