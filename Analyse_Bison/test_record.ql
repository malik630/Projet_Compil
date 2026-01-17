BEGIN PROGRAM TestRecord;

CREATE RECORD Student (
    name STRING,
    age INTEGER
);

SET student1 Student;
SET student2 Student;

student1.name = 'Ahmed';
student1.age = 21;
sutdent1.city = 'Cairo';  -- Intentional typo to test error handling

PRINT student1.name;

END PROGRAM;