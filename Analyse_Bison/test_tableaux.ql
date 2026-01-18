BEGIN PROGRAM TestTableaux;

SET notes ARRAY[INTEGER,10];

-- Test 2: Accès valide
notes[0] = 10;
notes[4] = 20;

-- Test 3: ERREUR - Indice négatif
notes[-1] = 5;

-- Test 4: ERREUR - Indice hors limites (> taille)
notes[10] = 15;
END PROGRAM;