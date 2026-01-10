// handling la pile syntaxique
#include "ll1_parser.h"
#include <stdio.h>
#include <stdlib.h>

void initStack(ParseStack* stack) {
    stack->top = -1;
}

void pushStack(ParseStack* stack, StackSymbol symbol) {
    if (stack->top >= MAX_STACK_SIZE - 1) {
        fprintf(stderr, "ERREUR: Débordement de pile\n");
        exit(EXIT_FAILURE);
    }
    stack->symbols[++stack->top] = symbol;
}

StackSymbol popStack(ParseStack* stack) {
    if (stack->top < 0) {
        fprintf(stderr, "ERREUR: Pile vide\n");
        exit(EXIT_FAILURE);
    }
    return stack->symbols[stack->top--];
}

StackSymbol peekStack(ParseStack* stack) {
    if (stack->top < 0) {
        StackSymbol eof;
        eof.kind = SYMBOL_EOF;
        return eof;
    }
    return stack->symbols[stack->top];
}

bool isStackEmpty(ParseStack* stack) {
    return stack->top < 0;
}

void printStack(ParseStack* stack) {
    printf("Pile: [");
    for (int i = 0; i <= stack->top; i++) {
        StackSymbol sym = stack->symbols[i];
        if (sym.kind == SYMBOL_TERMINAL) {
            printf("%s", tokenTypeToString(sym.value.terminal));
        } else if (sym.kind == SYMBOL_NONTERMINAL) {
            printf("%s", nonTerminalToString(sym.value.non_terminal));
        } else {
            printf("$");
        }
        if (i < stack->top) printf(", ");
    }
    printf("]\n");
}