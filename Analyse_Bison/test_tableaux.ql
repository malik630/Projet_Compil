BEGIN PROGRAM Test;
SET arr ARRAY[INTEGER, 5] = {1, 2, 3, 4, 5};

arr[10] = 20;          -- ERREUR: index hors limites (taille=5)
arr[-1] = 30;          -- ERREUR: index négatif
arr['hello'] = 40;     -- ERREUR: index doit être entier
arr[0] = 'string';     -- ERREUR: type incompatible (entier attendu)
arr[2] = 3.14;

END PROGRAM;