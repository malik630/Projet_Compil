#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "parser.tab.h"

extern FILE* yyin;
extern ASTNode* root;
extern int yyparse();
extern void yylex_destroy();

void print_banner() {
    printf("╔══════════════════════════════════════════════╗\n");
    printf("║      QueryLang Compiler - Version 1.0       ║\n");
    printf("║   A Simple Language for Data Processing     ║\n");
    printf("╚══════════════════════════════════════════════╝\n\n");
}

void print_usage(char* program_name) {
    printf("Usage: %s <source_file.ql>\n", program_name);
    printf("  source_file.ql : QueryLang source code file\n\n");
    printf("Example:\n");
    printf("  %s program.ql\n", program_name);
}

int main(int argc, char** argv) {
    print_banner();
    
    // Check command line arguments
    if (argc != 2) {
        fprintf(stderr, "Error: Invalid number of arguments\n\n");
        print_usage(argv[0]);
        return 1;
    }
    
    // Open input file
    FILE* input_file = fopen(argv[1], "r");
    if (!input_file) {
        fprintf(stderr, "Error: Cannot open file '%s'\n", argv[1]);
        return 1;
    }
    
    printf("📄 Compiling: %s\n", argv[1]);
    printf("─────────────────────────────────────────────\n\n");
    
    // Set input for lexer
    yyin = input_file;
    
    // Parse the input
    printf("🔍 Lexical and Syntax Analysis...\n");
    int parse_result = yyparse();
    
    fclose(input_file);
    
    if (parse_result == 0 && root != NULL) {
        printf("\n═══════════════════════════════════════════════\n");
        printf("          ABSTRACT SYNTAX TREE (AST)          \n");
        printf("═══════════════════════════════════════════════\n\n");
        
        printAST(root, 0);
        
        printf("\n═══════════════════════════════════════════════\n");
        printf("✓ Compilation successful!\n");
        printf("═══════════════════════════════════════════════\n");
        
        // Free AST memory
        freeAST(root);
        
        // Cleanup lexer
        yylex_destroy();
        
        return 0;
    } else {
        printf("\n═══════════════════════════════════════════════\n");
        printf("✗ Compilation failed with errors\n");
        printf("═══════════════════════════════════════════════\n");
        
        if (root != NULL) {
            freeAST(root);
        }
        
        yylex_destroy();
        
        return 1;
    }
}