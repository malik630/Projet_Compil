BEGIN PROGRAM TestRapide
SET x INTEGER = 42;
SET nom STRING = 'Ahmed';
PRINT 'Resultat: ';
PRINT x;
WHEN x > 10
THEN
    PRINT 'x est superieur a 10';
OTHERWISE
    PRINT 'x est inferieur ou egal a 10';
END WHEN;
END PROGRAM;