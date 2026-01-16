%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"         
#include "parser.tab.h"

int line_num = 1;
int col_num = 1;
%}

%option noyywrap

DIGIT           [0-9]
LETTER          [a-zA-Z]
IDENTIFIER      {LETTER}({LETTER}|{DIGIT}|_)*
INTEGER         {DIGIT}+
FLOAT           {DIGIT}+\.{DIGIT}+
STRING          '([^'\n]|'')*'
WHITESPACE      [ \t\r]+
NEWLINE         \n
COMMENT_LINE    --[^\n]*
COMMENT_MULTI   \/\*([^*]|\*+[^*/])*\*+\/

%%

{COMMENT_LINE}   { /* ignore */ }
{COMMENT_MULTI}  { 
                    for (int i = 0; i < yyleng; i++) {
                        if (yytext[i] == '\n') {
                            line_num++;
                            col_num = 1;
                        } else {
                            col_num++;
                        }
                    }
                }

"BEGIN"          { col_num += yyleng; return KW_BEGIN; }
"PROGRAM"        { col_num += yyleng; return KW_PROGRAM; }
"END"            { col_num += yyleng; return KW_END; }
"SET"            { col_num += yyleng; return KW_SET; }
"CREATE"         { col_num += yyleng; return KW_CREATE; }
"RECORD"         { col_num += yyleng; return KW_RECORD; }
"ARRAY"          { col_num += yyleng; return KW_ARRAY; }
"DICTIONARY"     { col_num += yyleng; return KW_DICTIONARY; }
"INTEGER"        { col_num += yyleng; return KW_INTEGER; }
"STRING"         { col_num += yyleng; return KW_STRING; }
"FLOAT"          { col_num += yyleng; return KW_FLOAT; }
"BOOLEAN"        { col_num += yyleng; return KW_BOOLEAN; }
"true"           { col_num += yyleng; return KW_TRUE; }
"false"          { col_num += yyleng; return KW_FALSE; }

"WHEN"           { col_num += yyleng; return KW_WHEN; }
"CASEWHEN"       { col_num += yyleng; return KW_CASE_WHEN; }
"THEN"           { col_num += yyleng; return KW_THEN; }
"OTHERWISE"      { col_num += yyleng; return KW_OTHERWISE; }
"CASE"           { col_num += yyleng; return KW_CASE; }
"ELSE"           { col_num += yyleng; return KW_ELSE; }

"LOOP"           { col_num += yyleng; return KW_LOOP; }
"ITERATE"        { col_num += yyleng; return KW_ITERATE; }
"FROM"           { col_num += yyleng; return KW_FROM; }
"TO"             { col_num += yyleng; return KW_TO; }
"FOREACH"        { col_num += yyleng; return KW_FOREACH; }
"IN"             { col_num += yyleng; return KW_IN; }

"PRINT"          { col_num += yyleng; return KW_PRINT; }
"INPUT"          { col_num += yyleng; return KW_INPUT; }

"AND"            { col_num += yyleng; return OP_AND; }
"OR"             { col_num += yyleng; return OP_OR; }
"NOT"            { col_num += yyleng; return OP_NOT; }

"<>"             { col_num += yyleng; return OP_NEQ; }
"<="             { col_num += yyleng; return OP_LTE; }
">="             { col_num += yyleng; return OP_GTE; }
"<"              { col_num += yyleng; return OP_LT; }
">"              { col_num += yyleng; return OP_GT; }
"="              { col_num += yyleng; return OP_EQ; }
"+"              { col_num += yyleng; return OP_PLUS; }
"-"              { col_num += yyleng; return OP_MINUS; }
"*"              { col_num += yyleng; return OP_MULT; }
"/"              { col_num += yyleng; return OP_DIV; }
"%"              { col_num += yyleng; return OP_MOD; }

"("              { col_num += yyleng; return SEP_LPAREN; }
")"              { col_num += yyleng; return SEP_RPAREN; }
"["              { col_num += yyleng; return SEP_LBRACKET; }
"]"              { col_num += yyleng; return SEP_RBRACKET; }
"{"              { col_num += yyleng; return SEP_LBRACE; }
"}"              { col_num += yyleng; return SEP_RBRACE; }
","              { col_num += yyleng; return SEP_COMMA; }
";"              { col_num += yyleng; return SEP_SEMICOLON; }
"."              { col_num += yyleng; return SEP_DOT; }

{IDENTIFIER}     { yylval.str = strdup(yytext); col_num += yyleng; return IDENTIFIER; }
{INTEGER}        { yylval.ival = atoi(yytext); col_num += yyleng; return INT_LITERAL; }
{FLOAT}          { yylval.fval = atof(yytext); col_num += yyleng; return FLOAT_LITERAL; }
{STRING}         { 
                   yylval.str = strdup(yytext);
                   col_num += yyleng; 
                   return STRING_LITERAL; 
                 }

{WHITESPACE}     { col_num += yyleng; }
{NEWLINE}        { line_num++; col_num = 1; }

.                { col_num++; }

 /* Lexical errors */
.                   { 
                        fprintf(stderr, "Lexical error at line %d, col %d: unexpected character '%s'\n",
                                line_num, col_num, yytext);
                        col_num++;
                    }

%%

int yywrap() {
    return 1;
}

%%