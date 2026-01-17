BEGIN PROGRAM Test;

-- Test 1: Division par zéro dans déclaration
SET x INTEGER = 10/0;

-- Test 2: Tableau avec indice négatif
SET tab ARRAY[INTEGER, 5] = {1,2,3,4,5};
tab[-1] = 10;

-- Test 3: Accès à un champ inexistant
CREATE RECORD Personne(nom STRING, age INTEGER);
SET p Personne;
p.nom = "Test";
p.age = 20;
p.ville = "Paris";  -- Erreur: ville n'existe pas

-- Test 4: Variable non utilisée
SET y INTEGER = 5;
-- y n'est jamais utilisé

END PROGRAM;