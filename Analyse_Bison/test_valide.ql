BEGIN PROGRAM TestValide;

SET x INTEGER = 10;
SET y FLOAT = 3.14;
SET message STRING = 'Bonjour';
SET actif BOOLEAN;
SET result INTEGER = 5;

x = 20;
y = x + 5;
message = 'Hello World';

PRINT x;
PRINT 'Valeur: ';

WHEN x > 5
THEN
    PRINT 'x est grand';
    x = x + 1;
OTHERWISE
    PRINT 'x est petit';
END WHEN;

END PROGRAM;