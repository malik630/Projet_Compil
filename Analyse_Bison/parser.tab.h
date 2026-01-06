/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    STRING_LITERAL = 259,          /* STRING_LITERAL  */
    INT_LITERAL = 260,             /* INT_LITERAL  */
    FLOAT_LITERAL = 261,           /* FLOAT_LITERAL  */
    KW_BEGIN = 262,                /* KW_BEGIN  */
    KW_PROGRAM = 263,              /* KW_PROGRAM  */
    KW_END = 264,                  /* KW_END  */
    KW_SET = 265,                  /* KW_SET  */
    KW_CREATE = 266,               /* KW_CREATE  */
    KW_RECORD = 267,               /* KW_RECORD  */
    KW_ARRAY = 268,                /* KW_ARRAY  */
    KW_DICTIONARY = 269,           /* KW_DICTIONARY  */
    KW_INTEGER = 270,              /* KW_INTEGER  */
    KW_STRING = 271,               /* KW_STRING  */
    KW_FLOAT = 272,                /* KW_FLOAT  */
    KW_BOOLEAN = 273,              /* KW_BOOLEAN  */
    KW_TRUE = 274,                 /* KW_TRUE  */
    KW_FALSE = 275,                /* KW_FALSE  */
    KW_WHEN = 276,                 /* KW_WHEN  */
    KW_THEN = 277,                 /* KW_THEN  */
    KW_OTHERWISE = 278,            /* KW_OTHERWISE  */
    KW_CASE = 279,                 /* KW_CASE  */
    KW_ELSE = 280,                 /* KW_ELSE  */
    KW_LOOP = 281,                 /* KW_LOOP  */
    KW_ITERATE = 282,              /* KW_ITERATE  */
    KW_FROM = 283,                 /* KW_FROM  */
    KW_TO = 284,                   /* KW_TO  */
    KW_PRINT = 285,                /* KW_PRINT  */
    KW_INPUT = 286,                /* KW_INPUT  */
    OP_AND = 287,                  /* OP_AND  */
    OP_OR = 288,                   /* OP_OR  */
    OP_NOT = 289,                  /* OP_NOT  */
    OP_EQ = 290,                   /* OP_EQ  */
    OP_NEQ = 291,                  /* OP_NEQ  */
    OP_LT = 292,                   /* OP_LT  */
    OP_GT = 293,                   /* OP_GT  */
    OP_LTE = 294,                  /* OP_LTE  */
    OP_GTE = 295,                  /* OP_GTE  */
    OP_PLUS = 296,                 /* OP_PLUS  */
    OP_MINUS = 297,                /* OP_MINUS  */
    OP_MULT = 298,                 /* OP_MULT  */
    OP_DIV = 299,                  /* OP_DIV  */
    OP_MOD = 300,                  /* OP_MOD  */
    SEP_LPAREN = 301,              /* SEP_LPAREN  */
    SEP_RPAREN = 302,              /* SEP_RPAREN  */
    SEP_LBRACKET = 303,            /* SEP_LBRACKET  */
    SEP_RBRACKET = 304,            /* SEP_RBRACKET  */
    SEP_LBRACE = 305,              /* SEP_LBRACE  */
    SEP_RBRACE = 306,              /* SEP_RBRACE  */
    SEP_COMMA = 307,               /* SEP_COMMA  */
    SEP_SEMICOLON = 308,           /* SEP_SEMICOLON  */
    SEP_DOT = 309,                 /* SEP_DOT  */
    UMINUS = 310                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "parser.y"

    int ival;
    float fval;
    char* str;
    ASTNode* node;
    DataType dtype;

#line 127 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
