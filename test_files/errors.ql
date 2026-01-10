-- program with intentionala errors to test

BEGIN PROGRAM TestErrors
    -- ERREUR 1: Point-virgule manquant après TestErrors
    
    SET x INTEGER = 10;
    SET y   -- ERREUR 2: Type manquant
    
    PRINT x  -- ERREUR 3: Point-virgule manquant
    
    z = 5;   -- ERREUR 4: Variable non déclarée
    
    IF x > THEN  -- ERREUR 5: Expression manquante
        PRINT 'Test';
    END IF;
    
    x = * 5;  -- ERREUR 6: Opérande manquant
