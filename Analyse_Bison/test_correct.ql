BEGIN PROGRAM TestCorrect;

SET x INTEGER;
SET y INTEGER = 10;
SET name STRING;

x = 5 + 3;
y = x * 2;
PRINT x + y;

WHEN x < y THEN
    PRINT x;
END WHEN;

END PROGRAM;