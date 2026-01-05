BEGIN PROGRAM TestError;

SET x INTEGER;
SET y = 20;           
SET z FLOAT;

x = 5 + ;             
y = x * 2

PRINT x + y;          

WHEN x < y THEN
    PRINT x;
    PRINT y;
END IF;               

END PROGRAM;