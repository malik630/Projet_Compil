-- testing for arithmetic problems

BEGIN PROGRAM TestExpressions;
    SET a INTEGER = 10;
    SET b INTEGER = 20;
    SET c INTEGER = 5;
    SET result INTEGER;
    
    result = a + b * c;
    PRINT result;
    
    result = (a + b) * c;
    PRINT result;
    
    result = a / c + b;
    PRINT result;
    
    result = (a + b) / (c + c);
    PRINT result;
END PROGRAM;
