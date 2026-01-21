#include "grammar.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Grammar* createGrammar() {
    Grammar* grammar = (Grammar*)malloc(sizeof(Grammar));
    grammar->max_productions = 100;
    grammar->productions = (Production*)malloc(sizeof(Production) * grammar->max_productions);
    grammar->production_count = 0;
    grammar->start_symbol = NT_PROGRAM;
    return grammar;
}

void addProduction(Grammar* grammar, NonTerminal left, GrammarSymbol* right, int length) {
    if (grammar->production_count >= grammar->max_productions) {
        fprintf(stderr, "Error: Too many productions\n");
        return;
    }
    
    Production* prod = &grammar->productions[grammar->production_count];
    prod->left_side = left;
    prod->right_side = (GrammarSymbol*)malloc(sizeof(GrammarSymbol) * length);
    memcpy(prod->right_side, right, sizeof(GrammarSymbol) * length);
    prod->right_side_length = length;
    prod->rule_number = grammar->production_count + 1;
    
    grammar->production_count++;
}

void freeGrammar(Grammar* grammar) {
    for (int i = 0; i < grammar->production_count; i++) {
        free(grammar->productions[i].right_side);
    }
    free(grammar->productions);
    free(grammar);
}

// Helper: Create a terminal symbol
GrammarSymbol makeTerminal(TokenType token) {
    GrammarSymbol sym;
    sym.type = SYM_TERMINAL;
    sym.value.terminal = token;
    return sym;
}

// Helper: Create a non-terminal symbol
GrammarSymbol makeNonTerminal(NonTerminal nt) {
    GrammarSymbol sym;
    sym.type = SYM_NONTERMINAL;
    sym.value.non_terminal = nt;
    return sym;
}

// Helper: Create epsilon symbol
GrammarSymbol makeEpsilon() {
    GrammarSymbol sym;
    sym.type = SYM_EPSILON;
    return sym;
}

void printGrammar(Grammar* grammar) {
    printf("\n========== GRAMMAR RULES ==========\n");
    for (int i = 0; i < grammar->production_count; i++) {
        Production* prod = &grammar->productions[i];
        printf("Rule %d: %s -> ", prod->rule_number, nonTerminalToString(prod->left_side));
        
        if (prod->right_side_length == 0 || prod->right_side[0].type == SYM_EPSILON) {
            printf("ε");
        } else {
            for (int j = 0; j < prod->right_side_length; j++) {
                GrammarSymbol sym = prod->right_side[j];
                if (sym.type == SYM_TERMINAL) {
                    printf("%s ", tokenTypeToString(sym.value.terminal));
                } else if (sym.type == SYM_NONTERMINAL) {
                    printf("%s ", nonTerminalToString(sym.value.non_terminal));
                } else {
                    printf("ε ");
                }
            }
        }
        printf("\n");
    }
    printf("===================================\n\n");
}

// Initialize all grammar rules for your language
void initializeGrammarRules(Grammar* grammar) {
    printf("[GRAMMAR] Initializing grammar rules...\n");
    
    // Rule 1: Program -> KW_BEGIN KW_PROGRAM IDENTIFIER SEP_SEMICOLON Decls Instrs KW_END KW_PROGRAM SEP_SEMICOLON
    {
        GrammarSymbol rhs[] = {
            makeTerminal(KW_BEGIN),
            makeTerminal(KW_PROGRAM),
            makeTerminal(IDENTIFIER),
            makeTerminal(SEP_SEMICOLON),
            makeNonTerminal(NT_DECLS),
            makeNonTerminal(NT_INSTRS),
            makeTerminal(KW_END),
            makeTerminal(KW_PROGRAM),
            makeTerminal(SEP_SEMICOLON)
        };
        addProduction(grammar, NT_PROGRAM, rhs, 9);
    }
    
    // Rule 2: Decls -> Decl Decls
    {
        GrammarSymbol rhs[] = {
            makeNonTerminal(NT_DECL),
            makeNonTerminal(NT_DECLS)
        };
        addProduction(grammar, NT_DECLS, rhs, 2);
    }
    
    // Rule 3: Decls -> ε
    {
        GrammarSymbol rhs[] = { makeEpsilon() };
        addProduction(grammar, NT_DECLS, rhs, 1);
    }
    
    // Rule 4: Decl -> KW_SET IDENTIFIER Type OptInit SEP_SEMICOLON
    {
        GrammarSymbol rhs[] = {
            makeTerminal(KW_SET),
            makeTerminal(IDENTIFIER),
            makeNonTerminal(NT_TYPE),
            makeNonTerminal(NT_OPTINIT),
            makeTerminal(SEP_SEMICOLON)
        };
        addProduction(grammar, NT_DECL, rhs, 5);
    }
    
    // Rule 5: OptInit -> OP_EQ_TOK Expr
    {
        GrammarSymbol rhs[] = {
            makeTerminal(OP_EQ_TOK),
            makeNonTerminal(NT_EXPR)
        };
        addProduction(grammar, NT_OPTINIT, rhs, 2);
    }
    
    // Rule 6: OptInit -> ε
    {
        GrammarSymbol rhs[] = { makeEpsilon() };
        addProduction(grammar, NT_OPTINIT, rhs, 1);
    }
    
    // Rule 7: Type -> KW_INTEGER
    {
        GrammarSymbol rhs[] = { makeTerminal(KW_INTEGER) };
        addProduction(grammar, NT_TYPE, rhs, 1);
    }
    
    // Rule 8: Type -> KW_STRING
    {
        GrammarSymbol rhs[] = { makeTerminal(KW_STRING) };
        addProduction(grammar, NT_TYPE, rhs, 1);
    }
    
    // Rule 9: Type -> KW_FLOAT
    {
        GrammarSymbol rhs[] = { makeTerminal(KW_FLOAT) };
        addProduction(grammar, NT_TYPE, rhs, 1);
    }
    
    // Rule 10: Type -> KW_BOOLEAN
    {
        GrammarSymbol rhs[] = { makeTerminal(KW_BOOLEAN) };
        addProduction(grammar, NT_TYPE, rhs, 1);
    }
    
    // Rule 11: Instrs -> Instr Instrs
    {
        GrammarSymbol rhs[] = {
            makeNonTerminal(NT_INSTR),
            makeNonTerminal(NT_INSTRS)
        };
        addProduction(grammar, NT_INSTRS, rhs, 2);
    }
    
    // Rule 12: Instrs -> ε
    {
        GrammarSymbol rhs[] = { makeEpsilon() };
        addProduction(grammar, NT_INSTRS, rhs, 1);
    }
    
    // Rule 13: Instr -> Assign
    {
        GrammarSymbol rhs[] = { makeNonTerminal(NT_ASSIGN) };
        addProduction(grammar, NT_INSTR, rhs, 1);
    }
    
    // Rule 14: Instr -> Print
    {
        GrammarSymbol rhs[] = { makeNonTerminal(NT_PRINT) };
        addProduction(grammar, NT_INSTR, rhs, 1);
    }
    
    // Rule 15: Instr -> WHEN
    {
        GrammarSymbol rhs[] = { makeNonTerminal(NT_WHEN) };
        addProduction(grammar, NT_INSTR, rhs, 1);
    }
    
    // Rule 16: Assign -> IDENTIFIER OP_EQ_TOK Expr SEP_SEMICOLON
    {
        GrammarSymbol rhs[] = {
            makeTerminal(IDENTIFIER),
            makeTerminal(OP_EQ_TOK),
            makeNonTerminal(NT_EXPR),
            makeTerminal(SEP_SEMICOLON)
        };
        addProduction(grammar, NT_ASSIGN, rhs, 4);
    }
    
    // Rule 17: Print -> KW_PRINT Expr SEP_SEMICOLON
    {
        GrammarSymbol rhs[] = {
            makeTerminal(KW_PRINT),
            makeNonTerminal(NT_EXPR),
            makeTerminal(SEP_SEMICOLON)
        };
        addProduction(grammar, NT_PRINT, rhs, 3);
    }
    
    // Rule 18: WHEN -> KW_WHEN Cond KW_THEN Instrs OptOTHERWISE KW_END KW_WHEN SEP_SEMICOLON
    {
        GrammarSymbol rhs[] = {
            makeTerminal(KW_WHEN),
            makeNonTerminal(NT_COND),
            makeTerminal(KW_THEN),
            makeNonTerminal(NT_INSTRS),
            makeNonTerminal(NT_OPTOTHERWISE),
            makeTerminal(KW_END),
            makeTerminal(KW_WHEN),
            makeTerminal(SEP_SEMICOLON)
        };
        addProduction(grammar, NT_WHEN, rhs, 8);
    }
    
    // Rule 19: OptOTHERWISE -> KW_OTHERWISE Instrs
    {
        GrammarSymbol rhs[] = {
            makeTerminal(KW_OTHERWISE),
            makeNonTerminal(NT_INSTRS)
        };
        addProduction(grammar, NT_OPTOTHERWISE, rhs, 2);
    }
    
    // Rule 20: OptOTHERWISE -> ε
    {
        GrammarSymbol rhs[] = { makeEpsilon() };
        addProduction(grammar, NT_OPTOTHERWISE, rhs, 1);
    }
    
    // Rule 21: Expr -> Term ExprPrime
    {
        GrammarSymbol rhs[] = {
            makeNonTerminal(NT_TERM),
            makeNonTerminal(NT_EXPRPRIME)
        };
        addProduction(grammar, NT_EXPR, rhs, 2);
    }
    
    // Rule 22: ExprPrime -> OP_PLUS Term ExprPrime
    {
        GrammarSymbol rhs[] = {
            makeTerminal(OP_PLUS),
            makeNonTerminal(NT_TERM),
            makeNonTerminal(NT_EXPRPRIME)
        };
        addProduction(grammar, NT_EXPRPRIME, rhs, 3);
    }
    
    // Rule 23: ExprPrime -> OP_MINUS Term ExprPrime
    {
        GrammarSymbol rhs[] = {
            makeTerminal(OP_MINUS),
            makeNonTerminal(NT_TERM),
            makeNonTerminal(NT_EXPRPRIME)
        };
        addProduction(grammar, NT_EXPRPRIME, rhs, 3);
    }
    
    // Rule 24: ExprPrime -> ε
    {
        GrammarSymbol rhs[] = { makeEpsilon() };
        addProduction(grammar, NT_EXPRPRIME, rhs, 1);
    }
    
    // Rule 25: Term -> Factor TermPrime
    {
        GrammarSymbol rhs[] = {
            makeNonTerminal(NT_FACTOR),
            makeNonTerminal(NT_TERMPRIME)
        };
        addProduction(grammar, NT_TERM, rhs, 2);
    }
    
    // Rule 26: TermPrime -> OP_MULT Factor TermPrime
    {
        GrammarSymbol rhs[] = {
            makeTerminal(OP_MULT),
            makeNonTerminal(NT_FACTOR),
            makeNonTerminal(NT_TERMPRIME)
        };
        addProduction(grammar, NT_TERMPRIME, rhs, 3);
    }
    
    // Rule 27: TermPrime -> OP_DIV Factor TermPrime
    {
        GrammarSymbol rhs[] = {
            makeTerminal(OP_DIV),
            makeNonTerminal(NT_FACTOR),
            makeNonTerminal(NT_TERMPRIME)
        };
        addProduction(grammar, NT_TERMPRIME, rhs, 3);
    }
    
    // Rule 28: TermPrime -> ε
    {
        GrammarSymbol rhs[] = { makeEpsilon() };
        addProduction(grammar, NT_TERMPRIME, rhs, 1);
    }
    
    // Rule 29: Factor -> INT_LITERAL
    {
        GrammarSymbol rhs[] = { makeTerminal(INT_LITERAL) };
        addProduction(grammar, NT_FACTOR, rhs, 1);
    }
    
    // Rule 30: Factor -> FLOAT_LITERAL
    {
        GrammarSymbol rhs[] = { makeTerminal(FLOAT_LITERAL) };
        addProduction(grammar, NT_FACTOR, rhs, 1);
    }
    
    // Rule 31: Factor -> STRING_LITERAL
    {
        GrammarSymbol rhs[] = { makeTerminal(STRING_LITERAL) };
        addProduction(grammar, NT_FACTOR, rhs, 1);
    }
    
    // Rule 32: Factor -> IDENTIFIER
    {
        GrammarSymbol rhs[] = { makeTerminal(IDENTIFIER) };
        addProduction(grammar, NT_FACTOR, rhs, 1);
    }
    
    // Rule 33: Factor -> SEP_LPAREN Expr SEP_RPAREN
    {
        GrammarSymbol rhs[] = {
            makeTerminal(SEP_LPAREN),
            makeNonTerminal(NT_EXPR),
            makeTerminal(SEP_RPAREN)
        };
        addProduction(grammar, NT_FACTOR, rhs, 3);
    }
    
    // Rule 34: Cond -> Expr RelOp Expr
    {
        GrammarSymbol rhs[] = {
            makeNonTerminal(NT_EXPR),
            makeNonTerminal(NT_RELOP),
            makeNonTerminal(NT_EXPR)
        };
        addProduction(grammar, NT_COND, rhs, 3);
    }
    
    // Rule 35: RelOp -> OP_EQ_TOK
    {
        GrammarSymbol rhs[] = { makeTerminal(OP_EQ_TOK) };
        addProduction(grammar, NT_RELOP, rhs, 1);
    }
    
    // Rule 36: RelOp -> OP_NEQ_TOK
    {
        GrammarSymbol rhs[] = { makeTerminal(OP_NEQ_TOK) };
        addProduction(grammar, NT_RELOP, rhs, 1);
    }
    
    // Rule 37: RelOp -> OP_LT_TOK
    {
        GrammarSymbol rhs[] = { makeTerminal(OP_LT_TOK) };
        addProduction(grammar, NT_RELOP, rhs, 1);
    }
    
    // Rule 38: RelOp -> OP_GT_TOK
    {
        GrammarSymbol rhs[] = { makeTerminal(OP_GT_TOK) };
        addProduction(grammar, NT_RELOP, rhs, 1);
    }
    
    // Rule 39: RelOp -> OP_LTE_TOK
    {
        GrammarSymbol rhs[] = { makeTerminal(OP_LTE_TOK) };
        addProduction(grammar, NT_RELOP, rhs, 1);
    }
    
    // Rule 40: RelOp -> OP_GTE_TOK
    {
        GrammarSymbol rhs[] = { makeTerminal(OP_GTE_TOK) };
        addProduction(grammar, NT_RELOP, rhs, 1);
    }
    
    printf("[GRAMMAR] Total rules added: %d\n", grammar->production_count);
}
