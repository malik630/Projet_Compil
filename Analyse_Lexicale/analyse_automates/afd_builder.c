#include "afd_builder.h"
#include "thompson.h"
#include "subset.h"
#include <stdio.h>

AFD identifier_afd;
AFD integer_afd;
AFD float_afd;

AFD buildIdentifierAFD() {
    if (show_construction) {
        printf("\n=== Construction AFD IDENTIFICATEUR: [a-zA-Z_][a-zA-Z0-9_]* ===\n");
    }
    
    next_state_id = 0;
    
    AFN letter = thompsonRange('a', 'z');
    AFN upper = thompsonRange('A', 'Z');
    AFN underscore = thompsonSymbol('_');
    
    AFN first_part = thompsonUnion(letter, upper);
    first_part = thompsonUnion(first_part, underscore);
    
    AFN letter2 = thompsonRange('a', 'z');
    AFN upper2 = thompsonRange('A', 'Z');
    AFN digit = thompsonRange('0', '9');
    AFN underscore2 = thompsonSymbol('_');
    
    AFN second_part = thompsonUnion(letter2, upper2);
    second_part = thompsonUnion(second_part, digit);
    second_part = thompsonUnion(second_part, underscore2);
    second_part = thompsonStar(second_part);
    
    AFN final_afn = thompsonConcat(first_part, second_part);
    
    AFD afd = subsetConstruction(&final_afn);
    
    if (show_construction) {
        printf("    AFD: %d états générés\n", afd.state_count);
    }
    
    return afd;
}

AFD buildIntegerAFD() {
    if (show_construction) {
        printf("\n=== Construction AFD ENTIER: [0-9]+ ===\n");
    }
    
    next_state_id = 0;
    
    AFN digit = thompsonRange('0', '9');
    AFN final_afn = thompsonPlus(digit);
    
    AFD afd = subsetConstruction(&final_afn);
    
    if (show_construction) {
        printf("    AFD: %d états générés\n", afd.state_count);
    }
    
    return afd;
}

AFD buildFloatAFD() {
    if (show_construction) {
        printf("\n=== Construction AFD RÉEL: [0-9]+\\.[0-9]+ ===\n");
    }
    
    next_state_id = 0;
    
    AFN digit1 = thompsonRange('0', '9');
    AFN int_part = thompsonPlus(digit1);
    
    AFN dot = thompsonSymbol('.');
    
    AFN digit2 = thompsonRange('0', '9');
    AFN frac_part = thompsonPlus(digit2);
    
    AFN temp = thompsonConcat(int_part, dot);
    AFN final_afn = thompsonConcat(temp, frac_part);
    
    AFD afd = subsetConstruction(&final_afn);
    
    if (show_construction) {
        printf("    AFD: %d états générés\n", afd.state_count);
    }
    
    return afd;
}

void initializeAFDs() {
    printf("═══ PHASE 1: CONSTRUCTION DES AFD ═══\n");
    
    identifier_afd = buildIdentifierAFD();
    printf("✓ AFD Identificateurs construit (%d états)\n", identifier_afd.state_count);
    
    integer_afd = buildIntegerAFD();
    printf("✓ AFD Entiers construit (%d états)\n", integer_afd.state_count);
    
    float_afd = buildFloatAFD();
    printf("✓ AFD Réels construit (%d états)\n", float_afd.state_count);
    
    printf("\n");
}