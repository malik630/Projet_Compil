BEGIN PROGRAM TestSimple;
    SET x INTEGER = 10;
    SET y INTEGER = 5;
    SET result INTEGER;
    SET message STRING = 'Calcul arithmetique';
    
    PRINT message;
    
    result = x + y;
    PRINT result;
    
    result = x * y;
    PRINT result;
    
    IF x > y THEN
        PRINT 'x est plus grand que y';
    END IF;
END PROGRAM;
