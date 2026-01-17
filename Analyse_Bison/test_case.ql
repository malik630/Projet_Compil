BEGIN PROGRAM TestCase;
SET x INTEGER = 15;

CASE
    CASEWHEN x < 10 THEN
        PRINT 'Small';
    CASEWHEN x < 20 THEN
        PRINT 'Medium';
    CASEWHEN x >= 20 THEN
        PRINT 'Large';
    ELSE
        PRINT 'Unknown size';
END CASE;

END PROGRAM;