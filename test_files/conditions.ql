-- testing conditoinal structs

BEGIN PROGRAM TestConditions;
    SET x INTEGER = 15;
    SET y INTEGER = 10;
    
    IF x > y THEN
        PRINT 'x est superieur a y';
    ELSE
        PRINT 'x est inferieur ou egal a y';
    END IF;
    
    IF x = 15 THEN
        PRINT 'x vaut 15';
    END IF;
    
    IF y <> x THEN
        PRINT 'y est different de x';
    END IF;
END PROGRAM;
