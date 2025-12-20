#Fichier             #Description
structures.h        Définitions des structures (AFN, AFD, Token, etc.)
thompson.{h,c}      Construction de Thompson (Regex → AFN)
subset.{h,c}        Construction par sous-ensembles (AFN → AFD)
afd_builder.{h,c}   Construction des AFD pour QueryLang
symbol_table.{h,c}  Gestion de la table des symboles
error_manager.{h,c} Gestion des erreurs lexicales
lexer.{h,c}         Analyseur lexical principal
main.c              Programme principal

##Pour compiler l'analyseur lexical qui utilise flex : 
Se déplacer vers le dossier analyse_flex
Exécuter ces commandes : 

flex -o lexer_flex.c lexer_QueryLang.l

gcc -Wall -g -o lexer_flex lexer_flex.c -lfl

./lexer_flex test.ql

##Pour compiler l'analyseur lexical qui construit un AFD à partir d'une expression régulière : 
Se déplacer vers le dossier analyse_automates
Exécuter ces commandes : 

gcc -Wall -g -c *.c

gcc -o lexer *.o

#Remarque : Le fichier test.ql est un programme de test écrit dans notre langage QueryLang.