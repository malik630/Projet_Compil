BEGIN PROGRAM TestErreurs;

SET x INTEGER = 10;

SET x FLOAT = 3.14;

y = 20;

SET message STRING;
message = 42;

SET result INTEGER = 100 / 0;

SET a INTEGER;
SET b INTEGER = a + 5;

PRINT z;

WHEN 'texte'
THEN
    PRINT 'test';
END WHEN;

END PROGRAM;