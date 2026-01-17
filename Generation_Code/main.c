#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "parser.tab.h"
#include "semantic.h"
#include "quads.h" 
#include "table_symboles_enrichie.h" 

extern FILE* yyin;
extern int yyparse();
extern ASTNode* root;
void mettre_a_jour_res(int index, char* valeur) {
    if (index >= 0 && index < nextQuad) {
        if (tabQuad[index].res) free(tabQuad[index].res); // Libère l'ancien ""
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

        case NODE_DECL_LIST:
            if (node->data.declaration.next) generer_code(node->data.declaration.next);
            return "";

        case NODE_DECL:
            if (node->data.declaration.initializer != NULL) {
                char* val = generer_code(node->data.declaration.initializer);
                generer_quad("=", val, "", node->data.declaration.identifier);
            }
            if (node->data.declaration.next != NULL) {
                generer_code(node->data.declaration.next);
            }
            return "";

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
            char* cond = generer_code(node->data.ifStmt.condition);
            int posBZ = nextQuad;
            generer_quad("BZ", cond, "", ""); 
            generer_code(node->data.ifStmt.then_block);

            if (node->data.ifStmt.else_block) {
                int posBR = nextQuad;
                generer_quad("BR", "", "", ""); 
                char labelElse[15];
                sprintf(labelElse, "%d", nextQuad);
                mettre_a_jour_res(posBZ, labelElse);
                generer_code(node->data.ifStmt.else_block);
                char labelFin[15];
                sprintf(labelFin, "%d", nextQuad);
                mettre_a_jour_res(posBR, labelFin);
            } else {
                char labelFin[15];
                sprintf(labelFin, "%d", nextQuad);
                mettre_a_jour_res(posBZ, labelFin);
            }
            return "";
        }

        case NODE_WHILE: {
            int debutWhile = nextQuad;
            char* cond = generer_code(node->data.whileStmt.condition);
            int posBZ = nextQuad;
            generer_quad("BZ", cond, "", "");
            generer_code(node->data.whileStmt.body);
            char labelRet[15];
            sprintf(labelRet, "%d", debutWhile);
            generer_quad("BR", labelRet, "", "");
            char labelSortie[15];
            sprintf(labelSortie, "%d", nextQuad);
            mettre_a_jour_res(posBZ, labelSortie);
            return "";
        }

        case NODE_FOR: {
            char* start_val = generer_code(node->data.forStmt.from);
            generer_quad("=", start_val, "", node->data.forStmt.iterator);
            int debutFor = nextQuad;
            char* end_val = generer_code(node->data.forStmt.to);
            char* cond = creer_temp();
            generer_quad("<", node->data.forStmt.iterator, end_val, cond);
            int posBZ = nextQuad;
            generer_quad("BZ", cond, "", "");
            generer_code(node->data.forStmt.body);
            char* t_inc = creer_temp();
            generer_quad("+", node->data.forStmt.iterator, "1", t_inc);
            generer_quad("=", t_inc, "", node->data.forStmt.iterator);
            char labelRet[15];
            sprintf(labelRet, "%d", debutFor);
            generer_quad("BR", labelRet, "", "");
            char labelSortie[15];
            sprintf(labelSortie, "%d", nextQuad);
            mettre_a_jour_res(posBZ, labelSortie);
            return "";
        }

        case NODE_ARRAY_ACCESS_ASSIGN: {
            char* idx = generer_code(node->data.arrayAccessAssign.index);
            char* val = generer_code(node->data.arrayAccessAssign.expression);
            generer_quad("[]=", val, idx, node->data.arrayAccessAssign.arrayName);
            return node->data.arrayAccessAssign.arrayName;
        }

        case NODE_ARRAY_ACCESS: {
            char* idx = generer_code(node->data.arrayAccess.index);
            char* res = creer_temp();
            generer_quad("=[]", node->data.arrayAccess.arrayName, idx, res);
            return res;
        }

        case NODE_RECORD_ACCESS_ASSIGN: {
            char* val = generer_code(node->data.recordAccessAssign.expression);
            char path[128];
            sprintf(path, "%s.%s", node->data.recordAccessAssign.recordName, node->data.recordAccessAssign.fieldName);
            generer_quad("=", val, "", path);
            return strdup(path); // Corrigé : utilise strdup pour éviter le warning
        }

        case NODE_RECORD_ACCESS: {
            char path[128];
            sprintf(path, "%s.%s", node->data.recordAccess.recordName, node->data.recordAccess.fieldName);
            return strdup(path); // Corrigé
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
            else sprintf(val, "0");
            return val;
        }
        case NODE_ARRAY_DECL: {
            // 1. Allouer l'espace pour le tableau
            char size_str[16];
            sprintf(size_str, "%d", node->data.arrayDecl.size);
            generer_quad("BOUNDS", node->data.arrayDecl.name, size_str, "");

            // 2. Si on a des valeurs initiales {15, 18, ...}
            if (node->data.arrayDecl.initializer) {
                // On passe le nom du tableau pour savoir où stocker les éléments
                // Dans ton AST, l'initializer est souvent un NODE_EXPR_LIST
                ASTNode* current = node->data.arrayDecl.initializer;
                int index = 0;
                while (current != NULL) {
                    ASTNode* expr = (current->type == NODE_EXPR_LIST) ? current->data.exprList.expression : current;
                    char* val = generer_code(expr);
                    
                    char idx_str[16];
                    sprintf(idx_str, "%d", index);
                    generer_quad("[]=", val, idx_str, node->data.arrayDecl.name);
                    
                    if (current->type == NODE_EXPR_LIST) current = current->data.exprList.next;
                    else break;
                    index++;
                }
            }
            return node->data.arrayDecl.name;
        }

        case NODE_EXPR_LIST: {
           
            if (node->data.exprList.next) generer_code(node->data.exprList.next);
            return generer_code(node->data.exprList.expression);
        }

        case NODE_EXPR_IDENTIFIER:
            return node->data.identifier.name;

        default: return "";
    }
}

int main(int argc, char** argv) {
    memset(tabQuad, 0, sizeof(tabQuad));
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║      Compilateur QueryLang avec Génération de Code             ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier '%s'\n", argv[1]);
            return 1;
        }
        printf("Fichier source : %s\n", argv[1]);
    } else {
        printf("Usage : %s <fichier_source.ql>\n", argv[0]);
        return 1;
    }
    
    printf("─────────────────────────────────────────────────────────────────\n\n");
    
    // --- PHASE 1: Analyse lexicale et syntaxique ---
    printf("PHASE 1: Analyse Lexicale et Syntaxique\n");
    printf("═══════════════════════════════════════\n");
    
    int result = yyparse();
    
    if (result != 0 || root == NULL) {
        printf("\nAnalyse syntaxique échouée !\n\n");
        if (yyin) fclose(yyin);
        return 1;
    }
    
    printf("\nAnalyse syntaxique réussie !\n");
    
    // Afficher l'AST
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║               ARBRE SYNTAXIQUE ABSTRAIT (AST)                  ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    printAST(root, 0);
    
    // --- PHASE 2: Analyse sémantique ---
    printf("\n\nPHASE 2: Analyse Sémantique\n");
    printf("═══════════════════════════\n");
    
    int semanticResult = performSemanticAnalysis(root);
    
    // --- PHASE 3: Génération de Code (Quadruplets) ---
    if (semanticResult) {
        printf("\n\nPHASE 3: Génération de Code Intermédiaire\n");
        printf("════════════════════════════════════════\n");
        
        // On lance la génération récursive sur l'AST
        generer_code(root);
        
        // On affiche les quadruplets obtenus
        afficher_quads();
    }

    // --- RÉSUMÉ FINAL ---
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                    RÉSUMÉ DE LA COMPILATION                    ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    if (semanticResult) {
        printf("Compilation réussie !\n");
        printf("  • Analyse lexicale/syntaxique : OK\n");
        printf("  • Analyse sémantique          : OK\n");
        printf("  • Génération de code (Quads)  : %d instructions générées\n", nextQuad);
        printf("  • Avertissements              : %d\n", semanticWarnings.count);
        
        printf("\nAffichage de la Table des Symboles finale :\n");
        afficherTable(&tableGlobale); // Affichage de la table enrichie
        
        printf("\nLe programme a été transformé en instructions élémentaires.\n\n");
    } else {
        printf("Compilation échouée !\n");
        printf("  • Analyse sémantique          : ÉCHOUÉ\n");
        printf("  • Erreurs sémantiques         : %d\n", semanticErrors.count);
        printf("\nCorrigez les erreurs sémantiques avant la génération de code.\n\n");
    }
    
    // Libérer la mémoire
    freeAST(root);
    
    if (yyin) {
        fclose(yyin);
    }
    
    return semanticResult ? 0 : 1;
}