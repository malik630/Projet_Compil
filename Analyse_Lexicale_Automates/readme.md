#Fichier             #Description
structures.h        Définitions des structures (AFN, AFD, Token, etc.)
thompson.{h,c}      Construction de Thompson (Regex → AFN)
subset.{h,c}        Construction par sous-ensembles (AFN → AFD)
afd_builder.{h,c}   Construction des AFD pour QueryLang
symbol_table.{h,c}  Gestion de la table des symboles
error_manager.{h,c} Gestion des erreurs lexicales
lexer.{h,c}         Analyseur lexical principal
main.c              Programme principal

##Pour compiler l'analyseur lexical/syntaxique qui construit un AFD à partir d'une expression régulière : 
Se déplacer d'abord dans le dossier Analyse_Syntaxique_Manuelle pour compiler les fichiers de l'analyse syntaxique et exécuter cette commande :

gcc -c ll1_parser.c deb_suiv.c grammar.c ll1_generator.c ll1_stack.c ll1_table.c ll1_utils.c wrpper_lexer.c


Puis, se déplacer vers le dossier Analyse_Lexicale_Automates
Exécuter ces commandes : 

gcc -Wall -g -c *.c

gcc -o lexer *.o ../Analyse_Syntaxique_Manuelle/*.o

Tester sur le programme du fichier test.ql : 
./lexer test.ql

#Remarque : Le fichier test.ql est un programme de test écrit dans notre langage QueryLang.