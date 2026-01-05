#include <stdio.h>
#include <stdlib.h>
#include "ast.h"           /* Include ast.h BEFORE parser.tab.h */
#include "parser.tab.h"

extern FILE* yyin;
extern int yyparse();
extern ASTNode* root;

int main(int argc, char** argv) {
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║         QueryLang Parser with AST Construction                ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Error: Cannot open file '%s'\n", argv[1]);
            return 1;
        }
        printf("Parsing file: %s\n", argv[1]);
    } else {
        printf("Usage: %s <source_file.ql>\n", argv[0]);
        return 1;
    }
    
    printf("─────────────────────────────────────────────────────────────────\n\n");
    
    int result = yyparse();
    
    if (result == 0 && root != NULL) {
        printf("\n╔════════════════════════════════════════════════════════════════╗\n");
        printf("║                    ABSTRACT SYNTAX TREE                       ║\n");
        printf("╚════════════════════════════════════════════════════════════════╝\n\n");
        
        printAST(root, 0);
        
        printf("\n─────────────────────────────────────────────────────────────────\n");
        printf("✓ AST constructed successfully!\n\n");
        
        freeAST(root);
    } else {
        printf("\n✗ Parsing failed!\n\n");
    }
    
    if (yyin) {
        fclose(yyin);
    }
    
    return result;
}