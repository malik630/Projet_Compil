-- Programme de test pour QueryLang
BEGIN PROGRAM CalculNotes

-- Declaration des variables
SET nombre_etudiants INTEGER = 5;
SET moyenne FLOAT = 0.0;
SET nom_etudiant STRING = 'Ali';
SET est_valide BOOLEAN = true;

-- Tableau de notes
SET notes ARRAY[FLOAT, 5] = {12.5, 15.0, 8.5, 16.0, 14.5};

-- Record Etudiant
CREATE RECORD Etudiant (
    nom STRING,
    prenom STRING,
    age INTEGER,
    note FLOAT
);

SET etud1 Etudiant;
etud1.nom = 'Boudiaf';
etud1.prenom = 'Ahmed';
etud1.age = 21;
etud1.note = 15.5;

-- Calcul de la moyenne
SET somme FLOAT = 0.0;
SET i INTEGER = 0;

LOOP WHEN i < nombre_etudiants
    somme = somme + notes[i];
    i = i + 1;
END LOOP;

moyenne = somme / nombre_etudiants;

-- Affichage des résultats
PRINT 'Nombre d etudiants: ';
PRINT nombre_etudiants;
PRINT 'Moyenne de la classe: ';
PRINT moyenne;

-- Structure conditionnelle
WHEN moyenne >= 10.0
THEN
    PRINT 'Classe reussie!';
OTHERWISE
    PRINT 'Classe echouee!';
END WHEN;

-- Boucle FOR
PRINT 'Notes des etudiants:';
LOOP ITERATE j FROM 0 TO 4
    PRINT notes[j];
END LOOP;

-- CASE multiple
SET operation STRING = '+';
SET a INTEGER = 10;
SET b INTEGER = 5;
SET resultat INTEGER = 0;

CASE
    WHEN operation = '+' THEN
        resultat = a + b;
    WHEN operation = '-' THEN
        resultat = a - b;
    WHEN operation = '*' THEN
        resultat = a * b;
    WHEN operation = '/' AND b <> 0 THEN
        resultat = a / b;
    ELSE
        PRINT 'Operation invalide';
END CASE;

PRINT 'Resultat de l operation: ';
PRINT resultat;

/* 
   Commentaire multi-lignes
   Test des opérateurs et expressions
*/

SET x INTEGER = 100;
SET y INTEGER = 50;
SET test BOOLEAN = false;

test = (x > y) AND (x <= 200);
WHEN test
THEN
    PRINT 'Test logique reussi';
END WHEN;

-- Dictionnaire
SET contacts DICTIONARY<STRING, INTEGER>;
contacts['Ahmed'] = 0558123456;
contacts['Fatima'] = 0661234567;

END PROGRAM;