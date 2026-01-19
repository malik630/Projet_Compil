BEGIN PROGRAM TestTypes;

SET entier INTEGER = 42;
SET reel FLOAT = 3.14;
SET texte STRING = 'Hello';
SET flag BOOLEAN;

SET resultat1 FLOAT = entier + reel;
SET resultat2 INTEGER = entier + 5;

SET resultat3 INTEGER = texte + entier;

entier = 'texte';

texte = 123;

reel = entier;

SET mix1 FLOAT = entier * reel;
SET mix2 FLOAT = 5 + 3.14;

SET erreur STRING = texte * 2;

END PROGRAM;