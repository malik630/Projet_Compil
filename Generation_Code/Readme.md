cd Generation_Code
flex lexer_bison.l
bison -d -v parser.y
gcc lex.yy.c parser.tab.c main.c ast.c table_symboles_enrichie.c semantic.c quads.c -o parser