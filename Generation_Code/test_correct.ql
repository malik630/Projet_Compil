-- Complete Correct Test for QueryLang Compiler
BEGIN PROGRAM TestComplete;

-- SECTION 1: Declarations
SET x INTEGER = 10;
SET y INTEGER = 20;
SET message STRING = 'Hello QueryLang';
SET price FLOAT = 99.99;
SET active BOOLEAN = true;
SET inactive BOOLEAN = false;

-- SECTION 2: Arrays
SET scores ARRAY[INTEGER, 5] = {15, 18, 12, 20, 16};

-- SECTION 3: Records
CREATE RECORD Student (
    name STRING,
    age INTEGER,
    grade FLOAT
);

CREATE RECORD Point (
    x INTEGER,
    y INTEGER
);

-- SECTION 4: Instances
SET student1 Student;
SET point1 Point;

-- SECTION 5: Dictionary
SET contacts DICTIONARY<STRING, INTEGER>;

-- SECTION 6-8: Assignments
x = x + 5;
y = x * 2;
message = 'Updated message';
student1.name = 'Ahmed';
student1.age = 21;
scores[0] = 19;

-- SECTION 9-10: I/O
PRINT 'Testing QueryLang Compiler';
INPUT y;

-- SECTION 11: If-Then-Else
WHEN x > 10
THEN
    PRINT 'x is greater than 10';
ELSE
    PRINT 'x is not';
END WHEN; -- Mandatory ;


-- SECTION 12: If-Then-Otherwise
WHEN active = true
THEN
    PRINT 'Active';
OTHERWISE
    PRINT 'Inactive';
END WHEN; -- Mandatory ;

-- SECTION 14: Nested If
WHEN x > 5
THEN
    WHEN x > 15
    THEN
     
        PRINT 'Nested';
    END WHEN; -- Mandatory ;
END WHEN; -- Mandatory ;

-- SECTION 15: Case (USING CASEWHEN)
CASE
    CASEWHEN x < 10 THEN
        PRINT 'Small';
    CASEWHEN x >= 10 THEN
        PRINT 'Large';
    ELSE
        PRINT 'Unknown';
END CASE; -- Mandatory ;

-- SECTION 17: While Loop
LOOP WHEN x < 100
    x = x + 10;
END LOOP; -- Mandatory ;

-- SECTION 18: For Loop
LOOP ITERATE i FROM 0 TO 5
    PRINT i;
END LOOP; -- Mandatory ;

-- SECTION 19: Nested Loops (THIS WAS YOUR ERROR SOURCE)
LOOP ITERATE i FROM 0 TO 2
    LOOP ITERATE j FROM 0 TO 2
        PRINT i;
        PRINT j;
    END LOOP; -- Added ;
END LOOP;     -- Added ;

-- SECTION 20: Arithmetic (Line 148)
SET result INTEGER = (x + y) * 2 - 5;
SET sum FLOAT = price * 1.2;

-- SECTION 21-26: Conditions
WHEN x > 10 AND y < 50
THEN
    PRINT 'True';
END WHEN;

WHEN NOT (x < 0)
THEN
    PRINT 'Non-negative';
END WHEN;

SET negative INTEGER = -5;

PRINT 'All tests completed successfully!';

END PROGRAM; -- Mandatory ;