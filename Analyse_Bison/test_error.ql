-- ============================================
-- ERROR TEST 1: Missing semicolon
-- ============================================
BEGIN PROGRAM ErrorTest1;

SET x INTEGER = 10
SET y INTEGER = 20;

END PROGRAM;

-- ============================================
-- ERROR TEST 2: Undeclared variable usage
-- ============================================
BEGIN PROGRAM ErrorTest2;

SET x INTEGER = 10;
y = x + 5;  -- y not declared

END PROGRAM;

-- ============================================
-- ERROR TEST 3: Type mismatch
-- ============================================
BEGIN PROGRAM ErrorTest3;

SET x INTEGER = 10;
SET name STRING = 'Test';
x = name;  -- Type mismatch

END PROGRAM;

-- ============================================
-- ERROR TEST 4: Missing END statement
-- ============================================
BEGIN PROGRAM ErrorTest4;

SET x INTEGER = 10;

WHEN x > 5
THEN
    PRINT 'Greater';
-- Missing END WHEN;

END PROGRAM;

-- ============================================
-- ERROR TEST 5: Invalid identifier
-- ============================================
BEGIN PROGRAM ErrorTest5;

SET 123invalid INTEGER = 10;  -- Identifier cannot start with digit

END PROGRAM;

-- ============================================
-- ERROR TEST 6: Mismatched parentheses
-- ============================================
BEGIN PROGRAM ErrorTest6;

SET x INTEGER = 10;
SET result INTEGER = (x + 5 * 2;  -- Missing closing parenthesis

END PROGRAM;

-- ============================================
-- ERROR TEST 7: Invalid keyword usage
-- ============================================
BEGIN PROGRAM ErrorTest7;

SET x INTEGER = 10;
LOOP  -- Missing WHEN condition
    x = x + 1;
END LOOP;

END PROGRAM;

-- ============================================
-- ERROR TEST 8: Array out of bounds (semantic)
-- ============================================
BEGIN PROGRAM ErrorTest8;

SET arr ARRAY[INTEGER, 5] = {1, 2, 3, 4, 5};
arr[10] = 100;  -- Index out of bounds

END PROGRAM;

-- ============================================
-- ERROR TEST 9: Missing THEN keyword
-- ============================================
BEGIN PROGRAM ErrorTest9;

SET x INTEGER = 10;

WHEN x > 5
    PRINT 'Greater';  -- Missing THEN
END WHEN;

END PROGRAM;

-- ============================================
-- ERROR TEST 10: Invalid expression
-- ============================================
BEGIN PROGRAM ErrorTest10;

SET x INTEGER = 10;
SET y INTEGER = + * 5;  -- Invalid expression syntax

END PROGRAM;

-- ============================================
-- ERROR TEST 11: Missing program name
-- ============================================
BEGIN PROGRAM;

SET x INTEGER = 10;

END PROGRAM;

-- ============================================
-- ERROR TEST 12: Unterminated string
-- ============================================
BEGIN PROGRAM ErrorTest12;

SET message STRING = 'Hello World;  -- Missing closing quote

END PROGRAM;

-- ============================================
-- ERROR TEST 13: Record field access before initialization
-- ============================================
BEGIN PROGRAM ErrorTest13;

CREATE RECORD Person (
    name STRING,
    age INTEGER
);

SET p Person;
PRINT p.name;  -- p fields not initialized

END PROGRAM;

-- ============================================
-- ERROR TEST 14: Invalid loop syntax
-- ============================================
BEGIN PROGRAM ErrorTest14;

LOOP ITERATE i FROM 10 TO 0  -- Missing decrement, should be FROM 0 TO 10
    PRINT i;
END LOOP;

END PROGRAM;

-- ============================================
-- ERROR TEST 15: Multiple declarations same identifier
-- ============================================
BEGIN PROGRAM ErrorTest15;

SET x INTEGER = 10;
SET x FLOAT = 5.5;  -- Redeclaration error

END PROGRAM;