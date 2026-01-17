/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "table_symboles_enrichie.h"  /**** ADDED ****/
#include "semantic.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern int line_num;
extern int col_num;

void yyerror(const char* s);

ASTNode* root = NULL;

/**** ADDED - START ****/
TableSymboles tableGlobale;
int adresseMemoire = 0;
/**** ADDED - END ****/

#line 95 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_STRING_LITERAL = 4,             /* STRING_LITERAL  */
  YYSYMBOL_INT_LITERAL = 5,                /* INT_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 6,              /* FLOAT_LITERAL  */
  YYSYMBOL_KW_BEGIN = 7,                   /* KW_BEGIN  */
  YYSYMBOL_KW_PROGRAM = 8,                 /* KW_PROGRAM  */
  YYSYMBOL_KW_END = 9,                     /* KW_END  */
  YYSYMBOL_KW_SET = 10,                    /* KW_SET  */
  YYSYMBOL_KW_CREATE = 11,                 /* KW_CREATE  */
  YYSYMBOL_KW_RECORD = 12,                 /* KW_RECORD  */
  YYSYMBOL_KW_ARRAY = 13,                  /* KW_ARRAY  */
  YYSYMBOL_KW_DICTIONARY = 14,             /* KW_DICTIONARY  */
  YYSYMBOL_KW_INTEGER = 15,                /* KW_INTEGER  */
  YYSYMBOL_KW_STRING = 16,                 /* KW_STRING  */
  YYSYMBOL_KW_FLOAT = 17,                  /* KW_FLOAT  */
  YYSYMBOL_KW_BOOLEAN = 18,                /* KW_BOOLEAN  */
  YYSYMBOL_KW_TRUE = 19,                   /* KW_TRUE  */
  YYSYMBOL_KW_FALSE = 20,                  /* KW_FALSE  */
  YYSYMBOL_KW_WHEN = 21,                   /* KW_WHEN  */
  YYSYMBOL_KW_CASE_WHEN = 22,              /* KW_CASE_WHEN  */
  YYSYMBOL_KW_THEN = 23,                   /* KW_THEN  */
  YYSYMBOL_KW_OTHERWISE = 24,              /* KW_OTHERWISE  */
  YYSYMBOL_KW_CASE = 25,                   /* KW_CASE  */
  YYSYMBOL_KW_ELSE = 26,                   /* KW_ELSE  */
  YYSYMBOL_KW_LOOP = 27,                   /* KW_LOOP  */
  YYSYMBOL_KW_ITERATE = 28,                /* KW_ITERATE  */
  YYSYMBOL_KW_FROM = 29,                   /* KW_FROM  */
  YYSYMBOL_KW_TO = 30,                     /* KW_TO  */
  YYSYMBOL_KW_FOREACH = 31,                /* KW_FOREACH  */
  YYSYMBOL_KW_IN = 32,                     /* KW_IN  */
  YYSYMBOL_KW_PRINT = 33,                  /* KW_PRINT  */
  YYSYMBOL_KW_INPUT = 34,                  /* KW_INPUT  */
  YYSYMBOL_OP_AND = 35,                    /* OP_AND  */
  YYSYMBOL_OP_OR = 36,                     /* OP_OR  */
  YYSYMBOL_OP_NOT = 37,                    /* OP_NOT  */
  YYSYMBOL_OP_EQ = 38,                     /* OP_EQ  */
  YYSYMBOL_OP_NEQ = 39,                    /* OP_NEQ  */
  YYSYMBOL_OP_LT = 40,                     /* OP_LT  */
  YYSYMBOL_OP_GT = 41,                     /* OP_GT  */
  YYSYMBOL_OP_LTE = 42,                    /* OP_LTE  */
  YYSYMBOL_OP_GTE = 43,                    /* OP_GTE  */
  YYSYMBOL_OP_PLUS = 44,                   /* OP_PLUS  */
  YYSYMBOL_OP_MINUS = 45,                  /* OP_MINUS  */
  YYSYMBOL_OP_MULT = 46,                   /* OP_MULT  */
  YYSYMBOL_OP_DIV = 47,                    /* OP_DIV  */
  YYSYMBOL_OP_MOD = 48,                    /* OP_MOD  */
  YYSYMBOL_SEP_LPAREN = 49,                /* SEP_LPAREN  */
  YYSYMBOL_SEP_RPAREN = 50,                /* SEP_RPAREN  */
  YYSYMBOL_SEP_LBRACKET = 51,              /* SEP_LBRACKET  */
  YYSYMBOL_SEP_RBRACKET = 52,              /* SEP_RBRACKET  */
  YYSYMBOL_SEP_LBRACE = 53,                /* SEP_LBRACE  */
  YYSYMBOL_SEP_RBRACE = 54,                /* SEP_RBRACE  */
  YYSYMBOL_SEP_COMMA = 55,                 /* SEP_COMMA  */
  YYSYMBOL_SEP_SEMICOLON = 56,             /* SEP_SEMICOLON  */
  YYSYMBOL_SEP_DOT = 57,                   /* SEP_DOT  */
  YYSYMBOL_UMINUS = 58,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 59,                  /* $accept  */
  YYSYMBOL_Program = 60,                   /* Program  */
  YYSYMBOL_61_1 = 61,                      /* $@1  */
  YYSYMBOL_Decl = 62,                      /* Decl  */
  YYSYMBOL_Type = 63,                      /* Type  */
  YYSYMBOL_RecordDecl = 64,                /* RecordDecl  */
  YYSYMBOL_FieldList = 65,                 /* FieldList  */
  YYSYMBOL_Field = 66,                     /* Field  */
  YYSYMBOL_ArrayDecl = 67,                 /* ArrayDecl  */
  YYSYMBOL_ArrayInit = 68,                 /* ArrayInit  */
  YYSYMBOL_DictDecl = 69,                  /* DictDecl  */
  YYSYMBOL_OptInit = 70,                   /* OptInit  */
  YYSYMBOL_ExprList = 71,                  /* ExprList  */
  YYSYMBOL_Instrs = 72,                    /* Instrs  */
  YYSYMBOL_Instr = 73,                     /* Instr  */
  YYSYMBOL_Assign = 74,                    /* Assign  */
  YYSYMBOL_Print = 75,                     /* Print  */
  YYSYMBOL_Input = 76,                     /* Input  */
  YYSYMBOL_If = 77,                        /* If  */
  YYSYMBOL_78_2 = 78,                      /* $@2  */
  YYSYMBOL_79_3 = 79,                      /* $@3  */
  YYSYMBOL_OptElse = 80,                   /* OptElse  */
  YYSYMBOL_While = 81,                     /* While  */
  YYSYMBOL_82_4 = 82,                      /* $@4  */
  YYSYMBOL_83_5 = 83,                      /* $@5  */
  YYSYMBOL_For = 84,                       /* For  */
  YYSYMBOL_85_6 = 85,                      /* $@6  */
  YYSYMBOL_86_7 = 86,                      /* $@7  */
  YYSYMBOL_ForEach = 87,                   /* ForEach  */
  YYSYMBOL_88_8 = 88,                      /* $@8  */
  YYSYMBOL_89_9 = 89,                      /* $@9  */
  YYSYMBOL_Case = 90,                      /* Case  */
  YYSYMBOL_91_10 = 91,                     /* $@10  */
  YYSYMBOL_92_11 = 92,                     /* $@11  */
  YYSYMBOL_93_12 = 93,                     /* $@12  */
  YYSYMBOL_94_13 = 94,                     /* $@13  */
  YYSYMBOL_CaseList = 95,                  /* CaseList  */
  YYSYMBOL_CaseItem = 96,                  /* CaseItem  */
  YYSYMBOL_Expr = 97,                      /* Expr  */
  YYSYMBOL_Term = 98,                      /* Term  */
  YYSYMBOL_Factor = 99,                    /* Factor  */
  YYSYMBOL_Cond = 100                      /* Cond  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   250

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  92
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  210

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   313


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    69,    69,    68,    89,   127,   148,   149,   150,   154,
     155,   156,   157,   161,   185,   186,   190,   194,   218,   219,
     220,   224,   248,   249,   253,   254,   258,   259,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   275,   296,   311,
     329,   333,   354,   360,   353,   372,   373,   374,   379,   385,
     378,   398,   418,   397,   432,   459,   431,   473,   479,   472,
     489,   495,   488,   507,   508,   520,   527,   528,   529,   533,
     534,   535,   536,   540,   541,   542,   543,   544,   545,   563,
     578,   593,   594,   598,   599,   600,   601,   602,   603,   604,
     605,   606,   607
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "STRING_LITERAL", "INT_LITERAL", "FLOAT_LITERAL", "KW_BEGIN",
  "KW_PROGRAM", "KW_END", "KW_SET", "KW_CREATE", "KW_RECORD", "KW_ARRAY",
  "KW_DICTIONARY", "KW_INTEGER", "KW_STRING", "KW_FLOAT", "KW_BOOLEAN",
  "KW_TRUE", "KW_FALSE", "KW_WHEN", "KW_CASE_WHEN", "KW_THEN",
  "KW_OTHERWISE", "KW_CASE", "KW_ELSE", "KW_LOOP", "KW_ITERATE", "KW_FROM",
  "KW_TO", "KW_FOREACH", "KW_IN", "KW_PRINT", "KW_INPUT", "OP_AND",
  "OP_OR", "OP_NOT", "OP_EQ", "OP_NEQ", "OP_LT", "OP_GT", "OP_LTE",
  "OP_GTE", "OP_PLUS", "OP_MINUS", "OP_MULT", "OP_DIV", "OP_MOD",
  "SEP_LPAREN", "SEP_RPAREN", "SEP_LBRACKET", "SEP_RBRACKET", "SEP_LBRACE",
  "SEP_RBRACE", "SEP_COMMA", "SEP_SEMICOLON", "SEP_DOT", "UMINUS",
  "$accept", "Program", "$@1", "Decl", "Type", "RecordDecl", "FieldList",
  "Field", "ArrayDecl", "ArrayInit", "DictDecl", "OptInit", "ExprList",
  "Instrs", "Instr", "Assign", "Print", "Input", "If", "$@2", "$@3",
  "OptElse", "While", "$@4", "$@5", "For", "$@6", "$@7", "ForEach", "$@8",
  "$@9", "Case", "$@10", "$@11", "$@12", "$@13", "CaseList", "CaseItem",
  "Expr", "Term", "Factor", "Cond", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-127)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      21,    33,    13,    46,  -127,    -4,  -127,  -127,   115,   -12,
      49,    72,    78,    65,    83,     6,   112,    27,   128,  -127,
    -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,
    -127,  -127,    27,    27,   144,    55,    80,   148,    22,  -127,
    -127,  -127,  -127,  -127,    65,    27,    65,   173,   110,  -127,
      51,    65,   106,  -127,    65,   151,    81,    27,    -1,   104,
      56,    64,   124,  -127,   145,   118,   147,  -127,  -127,  -127,
    -127,   145,   126,    27,   188,  -127,  -127,   160,    42,    27,
      27,    27,    27,    27,    27,    27,    27,    27,    27,    27,
    -127,    65,    65,    68,  -127,   186,  -127,   135,  -127,   203,
     -27,  -127,  -127,  -127,   169,    27,    27,   152,   161,   161,
     153,   216,    89,  -127,  -127,  -127,   137,   137,   137,   137,
     137,   137,   110,   110,  -127,  -127,  -127,  -127,  -127,   185,
    -127,  -127,   196,  -127,   193,  -127,    27,    94,   137,  -127,
     168,   170,  -127,   161,    -2,  -127,  -127,    96,   163,   134,
    -127,   163,    27,   171,   108,  -127,   221,   161,  -127,   172,
     216,  -127,  -127,  -127,   202,   174,   220,   -24,  -127,  -127,
     179,   191,  -127,  -127,   163,   163,   224,  -127,  -127,   207,
      27,   163,   197,   180,   217,   181,   183,   137,   187,     5,
     184,  -127,   189,  -127,  -127,   163,  -127,    27,   137,  -127,
    -127,   233,   131,   137,   219,  -127,    27,   192,   137,  -127
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     2,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
       6,     7,     8,    27,    28,    29,    34,    30,    31,    32,
      35,    33,     0,     0,     0,     0,     0,     0,    78,    75,
      73,    74,    76,    77,     0,     0,     0,     0,    68,    72,
       0,     0,    57,    63,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     3,    23,     0,     0,     9,    10,    11,
      12,    23,     0,     0,     0,    85,    82,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      42,     0,     0,     0,    60,     0,    64,    48,    51,     0,
       0,    40,    41,    37,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,    81,    92,    86,    87,    88,    89,
      90,    91,    66,    67,    69,    70,    71,    26,    83,    84,
      26,    26,     0,    26,     0,    54,     0,     0,    22,     5,
       0,     0,     4,     0,     0,    14,    80,    47,    65,     0,
      58,    49,     0,     0,     0,    38,     0,     0,    16,     0,
       0,    26,    26,    43,     0,     0,     0,     0,    26,    39,
       0,     0,    13,    15,    46,    45,     0,    61,    59,     0,
       0,    55,    20,     0,     0,     0,     0,    26,     0,     0,
       0,    21,     0,    62,    50,    52,    56,     0,    19,    17,
      44,     0,     0,    24,     0,    18,     0,     0,    25,    53
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -127,  -127,  -127,  -127,  -106,  -127,  -127,    84,  -127,  -127,
    -127,   176,  -127,  -126,  -127,  -127,  -127,  -127,  -127,  -127,
    -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,
    -127,  -127,  -127,  -127,  -127,  -127,  -127,   198,   -17,   107,
      -7,   -32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     7,    19,    71,    20,   144,   145,    21,   190,
      22,   107,   202,     8,    23,    24,    25,    26,    27,   127,
     176,   163,    28,   133,   166,    29,   134,   201,    30,   153,
     188,    31,    95,   165,   131,   185,    52,    53,    47,    48,
      49,    50
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      58,   147,   140,   141,   148,   149,   180,   151,    38,    39,
      40,    41,    75,     4,    78,    60,    61,    85,    86,    93,
      85,    86,    97,   114,    42,    43,    32,    54,     1,    77,
      38,    39,    40,    41,    55,   174,   175,   158,    76,    33,
     100,     3,   181,    85,    86,    34,    42,    43,   159,     5,
      45,   171,     6,   160,    57,   101,   112,    35,   197,   128,
     129,   195,   116,   117,   118,   119,   120,   121,    38,    39,
      40,    41,    45,    73,    90,    36,    57,    91,    92,    74,
     124,   125,   126,    64,    42,    43,    91,    92,   137,   138,
      37,   130,   115,    65,    66,    67,    68,    69,    70,     9,
      85,    86,    44,    91,    92,    51,    11,    12,    85,    86,
      45,    63,   103,    99,    46,    56,   104,    13,     9,   154,
     161,    14,   162,    15,    10,    11,    12,    16,    51,    17,
      18,    59,    94,    85,    86,   167,    13,     9,    85,    86,
      14,   146,    15,   164,    11,    12,    16,    62,    17,    18,
     155,    72,    85,    86,    98,    13,    87,    88,    89,    14,
     102,    15,   105,   187,   169,    16,     9,    17,    18,   108,
      91,    92,   198,    11,    12,   111,    67,    68,    69,    70,
     203,    85,    86,   106,    13,   205,   206,   109,    14,   208,
      15,   113,   122,   123,    16,   132,    17,    18,    79,    80,
      81,    82,    83,    84,    85,    86,   135,   136,   139,   142,
     114,    79,    80,    81,    82,    83,    84,    85,    86,   143,
      91,   150,   152,   156,   168,   157,   170,   177,   172,   179,
     178,   182,   183,   184,   186,   189,   191,   193,   192,   194,
     199,   196,   204,     0,   173,   200,   207,   110,   209,     0,
      96
};

static const yytype_int16 yycheck[] =
{
      17,   127,   108,   109,   130,   131,    30,   133,     3,     4,
       5,     6,    44,     0,    46,    32,    33,    44,    45,    51,
      44,    45,    54,    50,    19,    20,    38,    21,     7,    46,
       3,     4,     5,     6,    28,   161,   162,   143,    45,    51,
      57,     8,   168,    44,    45,    57,    19,    20,    50,     3,
      45,   157,    56,    55,    49,    56,    73,     8,    53,    91,
      92,   187,    79,    80,    81,    82,    83,    84,     3,     4,
       5,     6,    45,    51,    23,     3,    49,    35,    36,    57,
      87,    88,    89,     3,    19,    20,    35,    36,   105,   106,
      12,    23,    50,    13,    14,    15,    16,    17,    18,     3,
      44,    45,    37,    35,    36,    22,    10,    11,    44,    45,
      45,    56,    56,    32,    49,     3,    52,    21,     3,   136,
      24,    25,    26,    27,     9,    10,    11,    31,    22,    33,
      34,     3,    26,    44,    45,   152,    21,     3,    44,    45,
      25,    52,    27,     9,    10,    11,    31,     3,    33,    34,
      56,     3,    44,    45,     3,    21,    46,    47,    48,    25,
      56,    27,    38,   180,    56,    31,     3,    33,    34,    51,
      35,    36,   189,    10,    11,    49,    15,    16,    17,    18,
     197,    44,    45,    38,    21,    54,    55,    40,    25,   206,
      27,     3,    85,    86,    31,     9,    33,    34,    38,    39,
      40,    41,    42,    43,    44,    45,     3,    38,    56,    56,
      50,    38,    39,    40,    41,    42,    43,    44,    45,     3,
      35,    25,    29,    55,    53,    55,     5,    25,    56,     9,
      56,    52,    41,     9,    27,    38,    56,    56,    21,    56,
      56,    54,     9,    -1,   160,    56,    27,    71,    56,    -1,
      52
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,    60,     8,     0,     3,    56,    61,    72,     3,
       9,    10,    11,    21,    25,    27,    31,    33,    34,    62,
      64,    67,    69,    73,    74,    75,    76,    77,    81,    84,
      87,    90,    38,    51,    57,     8,     3,    12,     3,     4,
       5,     6,    19,    20,    37,    45,    49,    97,    98,    99,
     100,    22,    95,    96,    21,    28,     3,    49,    97,     3,
      97,    97,     3,    56,     3,    13,    14,    15,    16,    17,
      18,    63,     3,    51,    57,   100,    99,    97,   100,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      23,    35,    36,   100,    26,    91,    96,   100,     3,    32,
      97,    56,    56,    56,    52,    38,    38,    70,    51,    40,
      70,    49,    97,     3,    50,    50,    97,    97,    97,    97,
      97,    97,    98,    98,    99,    99,    99,    78,   100,   100,
      23,    93,     9,    82,    85,     3,    38,    97,    97,    56,
      63,    63,    56,     3,    65,    66,    52,    72,    72,    72,
      25,    72,    29,    88,    97,    56,    55,    55,    63,    50,
      55,    24,    26,    80,     9,    92,    83,    97,    53,    56,
       5,    63,    56,    66,    72,    72,    79,    25,    56,     9,
      30,    72,    52,    41,     9,    94,    27,    97,    89,    38,
      68,    56,    21,    56,    56,    72,    54,    53,    97,    56,
      56,    86,    71,    97,     9,    54,    55,    27,    97,    56
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    59,    61,    60,    62,    62,    62,    62,    62,    63,
      63,    63,    63,    64,    65,    65,    66,    67,    68,    68,
      68,    69,    70,    70,    71,    71,    72,    72,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    74,    74,    74,
      75,    76,    78,    79,    77,    80,    80,    80,    82,    83,
      81,    85,    86,    84,    88,    89,    87,    91,    92,    90,
      93,    94,    90,    95,    95,    96,    97,    97,    97,    98,
      98,    98,    98,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     9,     5,     5,     1,     1,     1,     1,
       1,     1,     1,     7,     1,     3,     2,    10,     4,     2,
       0,     9,     2,     0,     1,     3,     0,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     6,     7,
       3,     3,     0,     0,    10,     2,     2,     0,     0,     0,
       9,     0,     0,    13,     0,     0,     9,     0,     0,     7,
       0,     0,     9,     1,     2,     4,     3,     3,     1,     3,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       4,     3,     2,     3,     3,     2,     3,     3,     3,     3,
       3,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 69 "parser.y"
    {
        /**** ADDED - START ****/
        initTable(&tableGlobale);
        /**** ADDED - END ****/
    }
#line 1338 "parser.tab.c"
    break;

  case 3: /* Program: KW_BEGIN KW_PROGRAM IDENTIFIER SEP_SEMICOLON $@1 Instrs KW_END KW_PROGRAM SEP_SEMICOLON  */
#line 75 "parser.y"
    {
        (yyval.node) = createProgramNode((yyvsp[-6].str), NULL, (yyvsp[-3].node)); 
        root = (yyval.node);
        printf("\n✓ Program '%s' parsed successfully!\n", (yyvsp[-6].str));
        
        /**** ADDED - START ****/
        afficherTable(&tableGlobale);
        /**** ADDED - END ****/
        
        free((yyvsp[-6].str));
    }
#line 1354 "parser.tab.c"
    break;

  case 4: /* Decl: KW_SET IDENTIFIER Type OptInit SEP_SEMICOLON  */
#line 90 "parser.y"
    {
        /**** ADDED - START ****/
        Symbole sym;
        strcpy(sym.nom, (yyvsp[-3].str));
        sym.typeSymbole = TYPE_VARIABLE;
        sym.line = line_num;      // AJOUTER
        sym.column = col_num;     // AJOUTER
        
        switch((yyvsp[-2].dtype)) {
            case TYPE_INTEGER:
                sym.typeDonnee = DATA_ENTIER;
                break;
            case TYPE_FLOAT:
                sym.typeDonnee = DATA_REEL;
                break;
            case TYPE_STRING:
                sym.typeDonnee = DATA_CHAINE;
                break;
            case TYPE_BOOLEAN:
                sym.typeDonnee = DATA_BOOLEEN;
                break;
        }
        
        sym.portee = tableGlobale.niveauPortee;
        sym.adresse = adresseMemoire++;
        sym.initialise = ((yyvsp[-1].node) != NULL) ? 1 : 0;
        
        if (insererSymbole(&tableGlobale, sym) == -1) {
            char msg[100];
            sprintf(msg, "Variable '%s' déjà déclarée", (yyvsp[-3].str));
            yyerror(msg);
        }
        /**** ADDED - END ****/
        
        (yyval.node) = createDeclNode((yyvsp[-3].str), (yyvsp[-2].dtype), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1396 "parser.tab.c"
    break;

  case 5: /* Decl: KW_SET IDENTIFIER IDENTIFIER OptInit SEP_SEMICOLON  */
#line 128 "parser.y"
    {
        /**** ADDED - START ****/
        Symbole sym;
        strcpy(sym.nom, (yyvsp[-3].str));
        sym.typeSymbole = TYPE_VARIABLE;
        sym.typeDonnee = DATA_ENREGISTREMENT;
        sym.portee = tableGlobale.niveauPortee;
        sym.adresse = adresseMemoire++;
        sym.initialise = ((yyvsp[-1].node) != NULL) ? 1 : 0;
        
        if (insererSymbole(&tableGlobale, sym) == -1) {
            char msg[100];
            sprintf(msg, "Variable '%s' déjà déclarée", (yyvsp[-3].str));
            yyerror(msg);
        }
        /**** ADDED - END ****/
        
        (yyval.node) = createRecordInstanceNode((yyvsp[-3].str), (yyvsp[-2].str), (yyvsp[-1].node));
        free((yyvsp[-3].str)); free((yyvsp[-2].str));
    }
#line 1421 "parser.tab.c"
    break;

  case 6: /* Decl: RecordDecl  */
#line 148 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1427 "parser.tab.c"
    break;

  case 7: /* Decl: ArrayDecl  */
#line 149 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1433 "parser.tab.c"
    break;

  case 8: /* Decl: DictDecl  */
#line 150 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1439 "parser.tab.c"
    break;

  case 9: /* Type: KW_INTEGER  */
#line 154 "parser.y"
                 { (yyval.dtype) = TYPE_INTEGER; }
#line 1445 "parser.tab.c"
    break;

  case 10: /* Type: KW_STRING  */
#line 155 "parser.y"
                 { (yyval.dtype) = TYPE_STRING; }
#line 1451 "parser.tab.c"
    break;

  case 11: /* Type: KW_FLOAT  */
#line 156 "parser.y"
                 { (yyval.dtype) = TYPE_FLOAT; }
#line 1457 "parser.tab.c"
    break;

  case 12: /* Type: KW_BOOLEAN  */
#line 157 "parser.y"
                 { (yyval.dtype) = TYPE_BOOLEAN; }
#line 1463 "parser.tab.c"
    break;

  case 13: /* RecordDecl: KW_CREATE KW_RECORD IDENTIFIER SEP_LPAREN FieldList SEP_RPAREN SEP_SEMICOLON  */
#line 162 "parser.y"
    {
        /**** ADDED - START ****/
        Symbole sym;
        strcpy(sym.nom, (yyvsp[-4].str));
        sym.typeSymbole = TYPE_CONSTANTE;
        sym.typeDonnee = DATA_ENREGISTREMENT;
        sym.portee = tableGlobale.niveauPortee;
        sym.adresse = adresseMemoire++;
        sym.initialise = 1;
        
        if (insererSymbole(&tableGlobale, sym) == -1) {
            char msg[100];
            sprintf(msg, "Record '%s' déjà déclaré", (yyvsp[-4].str));
            yyerror(msg);
        }
        /**** ADDED - END ****/
        
        (yyval.node) = createRecordDeclNode((yyvsp[-4].str), (yyvsp[-2].node));
        free((yyvsp[-4].str));
    }
#line 1488 "parser.tab.c"
    break;

  case 14: /* FieldList: Field  */
#line 185 "parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1494 "parser.tab.c"
    break;

  case 15: /* FieldList: FieldList SEP_COMMA Field  */
#line 186 "parser.y"
                                { (yyval.node) = createFieldListNode((yyvsp[0].node), (yyvsp[-2].node)); }
#line 1500 "parser.tab.c"
    break;

  case 16: /* Field: IDENTIFIER Type  */
#line 190 "parser.y"
                    { (yyval.node) = createFieldNode((yyvsp[-1].str), (yyvsp[0].dtype)); free((yyvsp[-1].str)); }
#line 1506 "parser.tab.c"
    break;

  case 17: /* ArrayDecl: KW_SET IDENTIFIER KW_ARRAY SEP_LBRACKET Type SEP_COMMA INT_LITERAL SEP_RBRACKET ArrayInit SEP_SEMICOLON  */
#line 195 "parser.y"
    {
        Symbole sym;
        strcpy(sym.nom, (yyvsp[-8].str));
        sym.typeSymbole = TYPE_VARIABLE;
        sym.typeDonnee = DATA_TABLEAU;
        sym.portee = tableGlobale.niveauPortee;
        sym.adresse = adresseMemoire++;
        sym.initialise = ((yyvsp[-1].node) != NULL) ? 1 : 0;
        sym.taille = (yyvsp[-3].ival);
        sym.typeElement = dataTypeToTypeDonnee((yyvsp[-5].dtype));  // AJOUTÉ
        
        if (insererSymbole(&tableGlobale, sym) == -1) {
            char msg[100];
            sprintf(msg, "Array '%s' déjà déclaré", (yyvsp[-8].str));
            yyerror(msg);
        }
        
        (yyval.node) = createArrayDeclNode((yyvsp[-8].str), (yyvsp[-5].dtype), (yyvsp[-3].ival), (yyvsp[-1].node));
        free((yyvsp[-8].str));
    }
#line 1531 "parser.tab.c"
    break;

  case 18: /* ArrayInit: OP_EQ SEP_LBRACE ExprList SEP_RBRACE  */
#line 218 "parser.y"
                                         { (yyval.node) = (yyvsp[-1].node); }
#line 1537 "parser.tab.c"
    break;

  case 19: /* ArrayInit: OP_EQ Expr  */
#line 219 "parser.y"
                                         { (yyval.node) = (yyvsp[0].node); }
#line 1543 "parser.tab.c"
    break;

  case 20: /* ArrayInit: %empty  */
#line 220 "parser.y"
                                         { (yyval.node) = NULL; }
#line 1549 "parser.tab.c"
    break;

  case 21: /* DictDecl: KW_SET IDENTIFIER KW_DICTIONARY OP_LT Type SEP_COMMA Type OP_GT SEP_SEMICOLON  */
#line 225 "parser.y"
    {
        /**** ADDED - START ****/
        Symbole sym;
        strcpy(sym.nom, (yyvsp[-7].str));
        sym.typeSymbole = TYPE_VARIABLE;
        sym.typeDonnee = DATA_DICTIONNAIRE;
        sym.portee = tableGlobale.niveauPortee;
        sym.adresse = adresseMemoire++;
        sym.initialise = 0;
        
        if (insererSymbole(&tableGlobale, sym) == -1) {
            char msg[100];
            sprintf(msg, "Dictionary '%s' déjà déclaré", (yyvsp[-7].str));
            yyerror(msg);
        }
        /**** ADDED - END ****/
        
        (yyval.node) = createDictDeclNode((yyvsp[-7].str), (yyvsp[-4].dtype), (yyvsp[-2].dtype));
        free((yyvsp[-7].str));
    }
#line 1574 "parser.tab.c"
    break;

  case 22: /* OptInit: OP_EQ Expr  */
#line 248 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1580 "parser.tab.c"
    break;

  case 23: /* OptInit: %empty  */
#line 249 "parser.y"
                  { (yyval.node) = NULL; }
#line 1586 "parser.tab.c"
    break;

  case 24: /* ExprList: Expr  */
#line 253 "parser.y"
                                { (yyval.node) = createExprListNode((yyvsp[0].node), NULL); }
#line 1592 "parser.tab.c"
    break;

  case 25: /* ExprList: ExprList SEP_COMMA Expr  */
#line 254 "parser.y"
                                { (yyval.node) = createExprListNode((yyvsp[0].node), (yyvsp[-2].node)); }
#line 1598 "parser.tab.c"
    break;

  case 26: /* Instrs: %empty  */
#line 258 "parser.y"
                    { (yyval.node) = NULL; }
#line 1604 "parser.tab.c"
    break;

  case 27: /* Instrs: Instrs Instr  */
#line 259 "parser.y"
                    { (yyval.node) = createStmtListNode((yyvsp[0].node), (yyvsp[-1].node)); }
#line 1610 "parser.tab.c"
    break;

  case 28: /* Instr: Assign  */
#line 263 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1616 "parser.tab.c"
    break;

  case 29: /* Instr: Print  */
#line 264 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1622 "parser.tab.c"
    break;

  case 30: /* Instr: If  */
#line 265 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1628 "parser.tab.c"
    break;

  case 31: /* Instr: While  */
#line 266 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1634 "parser.tab.c"
    break;

  case 32: /* Instr: For  */
#line 267 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1640 "parser.tab.c"
    break;

  case 33: /* Instr: Case  */
#line 268 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1646 "parser.tab.c"
    break;

  case 34: /* Instr: Input  */
#line 269 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1652 "parser.tab.c"
    break;

  case 35: /* Instr: ForEach  */
#line 270 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1658 "parser.tab.c"
    break;

  case 36: /* Instr: Decl  */
#line 271 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1664 "parser.tab.c"
    break;

  case 37: /* Assign: IDENTIFIER OP_EQ Expr SEP_SEMICOLON  */
#line 276 "parser.y"
    {
        /**** ADDED - START ****/
        Symbole* sym = obtenirSymbole(&tableGlobale, (yyvsp[-3].str));
        
        if (sym == NULL) {
            char msg[100];
            sprintf(msg, "Variable '%s' non déclarée", (yyvsp[-3].str));
            yyerror(msg);
        } else if (sym->typeSymbole == TYPE_CONSTANTE) {
            char msg[100];
            sprintf(msg, "Impossible de modifier la constante '%s'", (yyvsp[-3].str));
            yyerror(msg);
        } else {
            sym->initialise = 1;
        }
        /**** ADDED - END ****/
        
        (yyval.node) = createAssignNode((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1689 "parser.tab.c"
    break;

  case 38: /* Assign: IDENTIFIER SEP_DOT IDENTIFIER OP_EQ Expr SEP_SEMICOLON  */
#line 297 "parser.y"
    {
        /**** ADDED - START ****/
        Symbole* sym = obtenirSymbole(&tableGlobale, (yyvsp[-5].str));
        
        if (sym == NULL) {
            char msg[100];
            sprintf(msg, "Record '%s' non déclaré", (yyvsp[-5].str));
            yyerror(msg);
        }
        /**** ADDED - END ****/
        
        (yyval.node) = createRecordAccessAssignNode((yyvsp[-5].str), (yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-5].str)); free((yyvsp[-3].str));
    }
#line 1708 "parser.tab.c"
    break;

  case 39: /* Assign: IDENTIFIER SEP_LBRACKET Expr SEP_RBRACKET OP_EQ Expr SEP_SEMICOLON  */
#line 312 "parser.y"
    {
        /**** ADDED - START ****/
        Symbole* sym = obtenirSymbole(&tableGlobale, (yyvsp[-6].str));
        
        if (sym == NULL) {
            char msg[100];
            sprintf(msg, "Array '%s' non déclaré", (yyvsp[-6].str));
            yyerror(msg);
        }
        /**** ADDED - END ****/
        
        (yyval.node) = createArrayAccessAssignNode((yyvsp[-6].str), (yyvsp[-4].node), (yyvsp[-1].node));
        free((yyvsp[-6].str));
    }
#line 1727 "parser.tab.c"
    break;

  case 40: /* Print: KW_PRINT Expr SEP_SEMICOLON  */
#line 329 "parser.y"
                                { (yyval.node) = createPrintNode((yyvsp[-1].node)); }
#line 1733 "parser.tab.c"
    break;

  case 41: /* Input: KW_INPUT IDENTIFIER SEP_SEMICOLON  */
#line 334 "parser.y"
    { 
        /**** ADDED - START ****/
        Symbole* sym = obtenirSymbole(&tableGlobale, (yyvsp[-1].str));
        
        if (sym == NULL) {
            char msg[100];
            sprintf(msg, "Variable '%s' non déclarée", (yyvsp[-1].str));
            yyerror(msg);
        } else {
            sym->initialise = 1;
        }
        /**** ADDED - END ****/
        
        (yyval.node) = createInputNode((yyvsp[-1].str)); 
        free((yyvsp[-1].str)); 
    }
#line 1754 "parser.tab.c"
    break;

  case 42: /* $@2: %empty  */
#line 354 "parser.y"
    {
        /**** ADDED - START ****/
        entrerPortee(&tableGlobale);
        /**** ADDED - END ****/
    }
#line 1764 "parser.tab.c"
    break;

  case 43: /* $@3: %empty  */
#line 360 "parser.y"
    {
        /**** ADDED - START ****/
        sortirPortee(&tableGlobale);
        /**** ADDED - END ****/
    }
#line 1774 "parser.tab.c"
    break;

  case 44: /* If: KW_WHEN Cond KW_THEN $@2 Instrs OptElse $@3 KW_END KW_WHEN SEP_SEMICOLON  */
#line 366 "parser.y"
    {
        (yyval.node) = createIfNode((yyvsp[-8].node), (yyvsp[-5].node), (yyvsp[-4].node));
    }
#line 1782 "parser.tab.c"
    break;

  case 45: /* OptElse: KW_ELSE Instrs  */
#line 372 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1788 "parser.tab.c"
    break;

  case 46: /* OptElse: KW_OTHERWISE Instrs  */
#line 373 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1794 "parser.tab.c"
    break;

  case 47: /* OptElse: %empty  */
#line 374 "parser.y"
                          { (yyval.node) = NULL; }
#line 1800 "parser.tab.c"
    break;

  case 48: /* $@4: %empty  */
#line 379 "parser.y"
    {
        /**** ADDED - START ****/
        entrerPortee(&tableGlobale);
        /**** ADDED - END ****/
    }
#line 1810 "parser.tab.c"
    break;

  case 49: /* $@5: %empty  */
#line 385 "parser.y"
    {
        /**** ADDED - START ****/
        sortirPortee(&tableGlobale);
        /**** ADDED - END ****/
    }
#line 1820 "parser.tab.c"
    break;

  case 50: /* While: KW_LOOP KW_WHEN Cond $@4 Instrs $@5 KW_END KW_LOOP SEP_SEMICOLON  */
#line 391 "parser.y"
    {
        (yyval.node) = createWhileNode((yyvsp[-6].node), (yyvsp[-4].node));
    }
#line 1828 "parser.tab.c"
    break;

  case 51: /* $@6: %empty  */
#line 398 "parser.y"
    {
        /**** ADDED - START ****/
        entrerPortee(&tableGlobale);
        
        Symbole sym;
        strcpy(sym.nom, (yyvsp[0].str));
        sym.typeSymbole = TYPE_VARIABLE;
        sym.typeDonnee = DATA_ENTIER;
        sym.portee = tableGlobale.niveauPortee;
        sym.adresse = adresseMemoire++;
        sym.initialise = 1;
        
        if (insererSymbole(&tableGlobale, sym) == -1) {
            char msg[100];
            sprintf(msg, "Variable '%s' déjà déclarée", (yyvsp[0].str));
            yyerror(msg);
        }
        /**** ADDED - END ****/
    }
#line 1852 "parser.tab.c"
    break;

  case 52: /* $@7: %empty  */
#line 418 "parser.y"
    {
        /**** ADDED - START ****/
        sortirPortee(&tableGlobale);
        /**** ADDED - END ****/
    }
#line 1862 "parser.tab.c"
    break;

  case 53: /* For: KW_LOOP KW_ITERATE IDENTIFIER $@6 KW_FROM Expr KW_TO Expr Instrs $@7 KW_END KW_LOOP SEP_SEMICOLON  */
#line 424 "parser.y"
    {
        (yyval.node) = createForNode((yyvsp[-10].str), (yyvsp[-7].node), (yyvsp[-5].node), (yyvsp[-4].node));
        free((yyvsp[-10].str));
    }
#line 1871 "parser.tab.c"
    break;

  case 54: /* $@8: %empty  */
#line 432 "parser.y"
    {
        /**** ADDED - START ****/
        entrerPortee(&tableGlobale);
        
        Symbole* arraySym = obtenirSymbole(&tableGlobale, (yyvsp[0].str));
        if (arraySym == NULL) {
            char msg[100];
            sprintf(msg, "Array '%s' non déclaré", (yyvsp[0].str));
            yyerror(msg);
        }
        
        Symbole sym;
        strcpy(sym.nom, (yyvsp[-2].str));
        sym.typeSymbole = TYPE_VARIABLE;
        sym.typeDonnee = DATA_ENTIER;
        sym.portee = tableGlobale.niveauPortee;
        sym.adresse = adresseMemoire++;
        sym.initialise = 1;
        
        if (insererSymbole(&tableGlobale, sym) == -1) {
            char msg[100];
            sprintf(msg, "Variable '%s' déjà déclarée", (yyvsp[-2].str));
            yyerror(msg);
        }
        /**** ADDED - END ****/
    }
#line 1902 "parser.tab.c"
    break;

  case 55: /* $@9: %empty  */
#line 459 "parser.y"
    {
        /**** ADDED - START ****/
        sortirPortee(&tableGlobale);
        /**** ADDED - END ****/
    }
#line 1912 "parser.tab.c"
    break;

  case 56: /* ForEach: KW_FOREACH IDENTIFIER KW_IN IDENTIFIER $@8 SEP_LBRACE Instrs $@9 SEP_RBRACE  */
#line 465 "parser.y"
    {
        (yyval.node) = createForEachNode((yyvsp[-7].str), (yyvsp[-5].str), (yyvsp[-2].node));
        free((yyvsp[-7].str)); free((yyvsp[-5].str));
    }
#line 1921 "parser.tab.c"
    break;

  case 57: /* $@10: %empty  */
#line 473 "parser.y"
    {
        /**** ADDED - START ****/
        entrerPortee(&tableGlobale);
        /**** ADDED - END ****/
    }
#line 1931 "parser.tab.c"
    break;

  case 58: /* $@11: %empty  */
#line 479 "parser.y"
    {
        /**** ADDED - START ****/
        sortirPortee(&tableGlobale);
        /**** ADDED - END ****/
    }
#line 1941 "parser.tab.c"
    break;

  case 59: /* Case: KW_CASE CaseList $@10 KW_END KW_CASE $@11 SEP_SEMICOLON  */
#line 485 "parser.y"
    {
        (yyval.node) = createCaseNode((yyvsp[-5].node), NULL);
    }
#line 1949 "parser.tab.c"
    break;

  case 60: /* $@12: %empty  */
#line 489 "parser.y"
    {
        /**** ADDED - START ****/
        entrerPortee(&tableGlobale);
        /**** ADDED - END ****/
    }
#line 1959 "parser.tab.c"
    break;

  case 61: /* $@13: %empty  */
#line 495 "parser.y"
    {
        /**** ADDED - START ****/
        sortirPortee(&tableGlobale);
        /**** ADDED - END ****/
    }
#line 1969 "parser.tab.c"
    break;

  case 62: /* Case: KW_CASE CaseList KW_ELSE $@12 Instrs KW_END KW_CASE $@13 SEP_SEMICOLON  */
#line 501 "parser.y"
    {
        (yyval.node) = createCaseNode((yyvsp[-7].node), (yyvsp[-4].node));
    }
#line 1977 "parser.tab.c"
    break;

  case 63: /* CaseList: CaseItem  */
#line 507 "parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 1983 "parser.tab.c"
    break;

  case 64: /* CaseList: CaseList CaseItem  */
#line 509 "parser.y"
    {
        ASTNode* temp = (yyvsp[-1].node);
        while (temp->data.caseItem.next != NULL) {
            temp = temp->data.caseItem.next;
        }
        temp->data.caseItem.next = (yyvsp[0].node);
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1996 "parser.tab.c"
    break;

  case 65: /* CaseItem: KW_CASE_WHEN Cond KW_THEN Instrs  */
#line 521 "parser.y"
    {
        (yyval.node) = createCaseItemNode((yyvsp[-2].node), (yyvsp[0].node), NULL);
    }
#line 2004 "parser.tab.c"
    break;

  case 66: /* Expr: Expr OP_PLUS Term  */
#line 527 "parser.y"
                          { (yyval.node) = createBinOpNode(AST_OP_ADD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2010 "parser.tab.c"
    break;

  case 67: /* Expr: Expr OP_MINUS Term  */
#line 528 "parser.y"
                            { (yyval.node) = createBinOpNode(AST_OP_SUB, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2016 "parser.tab.c"
    break;

  case 68: /* Expr: Term  */
#line 529 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2022 "parser.tab.c"
    break;

  case 69: /* Term: Term OP_MULT Factor  */
#line 533 "parser.y"
                          { (yyval.node) = createBinOpNode(AST_OP_MUL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2028 "parser.tab.c"
    break;

  case 70: /* Term: Term OP_DIV Factor  */
#line 534 "parser.y"
                            { (yyval.node) = createBinOpNode(AST_OP_DIV, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2034 "parser.tab.c"
    break;

  case 71: /* Term: Term OP_MOD Factor  */
#line 535 "parser.y"
                            { (yyval.node) = createBinOpNode(AST_OP_MOD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2040 "parser.tab.c"
    break;

  case 72: /* Term: Factor  */
#line 536 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2046 "parser.tab.c"
    break;

  case 73: /* Factor: INT_LITERAL  */
#line 540 "parser.y"
                       { (yyval.node) = createIntLiteralNode((yyvsp[0].ival)); }
#line 2052 "parser.tab.c"
    break;

  case 74: /* Factor: FLOAT_LITERAL  */
#line 541 "parser.y"
                       { (yyval.node) = createFloatLiteralNode((yyvsp[0].fval)); }
#line 2058 "parser.tab.c"
    break;

  case 75: /* Factor: STRING_LITERAL  */
#line 542 "parser.y"
                       { (yyval.node) = createStringLiteralNode((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 2064 "parser.tab.c"
    break;

  case 76: /* Factor: KW_TRUE  */
#line 543 "parser.y"
                       { (yyval.node) = createBoolLiteralNode(1); }
#line 2070 "parser.tab.c"
    break;

  case 77: /* Factor: KW_FALSE  */
#line 544 "parser.y"
                       { (yyval.node) = createBoolLiteralNode(0); }
#line 2076 "parser.tab.c"
    break;

  case 78: /* Factor: IDENTIFIER  */
#line 546 "parser.y"
    { 
        /**** ADDED - START ****/
        Symbole* sym = obtenirSymbole(&tableGlobale, (yyvsp[0].str));
        
        if (sym == NULL) {
            char msg[100];
            sprintf(msg, "Variable '%s' non déclarée", (yyvsp[0].str));
            yyerror(msg);
        } else if (!sym->initialise && sym->typeSymbole != TYPE_CONSTANTE) {
            printf("Attention ligne %d : variable '%s' utilisée sans initialisation\n", 
                   line_num, (yyvsp[0].str));
        }
        /**** ADDED - END ****/
        
        (yyval.node) = createIdentifierNode((yyvsp[0].str)); 
        free((yyvsp[0].str)); 
    }
#line 2098 "parser.tab.c"
    break;

  case 79: /* Factor: IDENTIFIER SEP_DOT IDENTIFIER  */
#line 564 "parser.y"
    { 
        /**** ADDED - START ****/
        Symbole* sym = obtenirSymbole(&tableGlobale, (yyvsp[-2].str));
        
        if (sym == NULL) {
            char msg[100];
            sprintf(msg, "Record '%s' non déclaré", (yyvsp[-2].str));
            yyerror(msg);
        }
        /**** ADDED - END ****/
        
        (yyval.node) = createRecordAccessNode((yyvsp[-2].str), (yyvsp[0].str)); 
        free((yyvsp[-2].str)); free((yyvsp[0].str)); 
    }
#line 2117 "parser.tab.c"
    break;

  case 80: /* Factor: IDENTIFIER SEP_LBRACKET Expr SEP_RBRACKET  */
#line 579 "parser.y"
    { 
        /**** ADDED - START ****/
        Symbole* sym = obtenirSymbole(&tableGlobale, (yyvsp[-3].str));
        
        if (sym == NULL) {
            char msg[100];
            sprintf(msg, "Array '%s' non déclaré", (yyvsp[-3].str));
            yyerror(msg);
        }
        /**** ADDED - END ****/
        
        (yyval.node) = createArrayAccessNode((yyvsp[-3].str), (yyvsp[-1].node)); 
        free((yyvsp[-3].str)); 
    }
#line 2136 "parser.tab.c"
    break;

  case 81: /* Factor: SEP_LPAREN Expr SEP_RPAREN  */
#line 593 "parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 2142 "parser.tab.c"
    break;

  case 82: /* Factor: OP_MINUS Factor  */
#line 594 "parser.y"
                                   { (yyval.node) = createUnaryOpNode(AST_OP_NEG, (yyvsp[0].node)); }
#line 2148 "parser.tab.c"
    break;

  case 83: /* Cond: Cond OP_AND Cond  */
#line 598 "parser.y"
                        { (yyval.node) = createBinOpNode(AST_OP_AND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2154 "parser.tab.c"
    break;

  case 84: /* Cond: Cond OP_OR Cond  */
#line 599 "parser.y"
                          { (yyval.node) = createBinOpNode(AST_OP_OR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2160 "parser.tab.c"
    break;

  case 85: /* Cond: OP_NOT Cond  */
#line 600 "parser.y"
                          { (yyval.node) = createUnaryOpNode(AST_OP_NOT, (yyvsp[0].node)); }
#line 2166 "parser.tab.c"
    break;

  case 86: /* Cond: Expr OP_EQ Expr  */
#line 601 "parser.y"
                          { (yyval.node) = createBinOpNode(AST_OP_EQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2172 "parser.tab.c"
    break;

  case 87: /* Cond: Expr OP_NEQ Expr  */
#line 602 "parser.y"
                          { (yyval.node) = createBinOpNode(AST_OP_NEQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2178 "parser.tab.c"
    break;

  case 88: /* Cond: Expr OP_LT Expr  */
#line 603 "parser.y"
                          { (yyval.node) = createBinOpNode(AST_OP_LT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2184 "parser.tab.c"
    break;

  case 89: /* Cond: Expr OP_GT Expr  */
#line 604 "parser.y"
                          { (yyval.node) = createBinOpNode(AST_OP_GT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2190 "parser.tab.c"
    break;

  case 90: /* Cond: Expr OP_LTE Expr  */
#line 605 "parser.y"
                          { (yyval.node) = createBinOpNode(AST_OP_LTE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2196 "parser.tab.c"
    break;

  case 91: /* Cond: Expr OP_GTE Expr  */
#line 606 "parser.y"
                          { (yyval.node) = createBinOpNode(AST_OP_GTE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2202 "parser.tab.c"
    break;

  case 92: /* Cond: SEP_LPAREN Cond SEP_RPAREN  */
#line 607 "parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 2208 "parser.tab.c"
    break;


#line 2212 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 610 "parser.y"


void yyerror(const char* s) {
    fprintf(stderr, "Parse error at line %d, col %d: %s\n", line_num, col_num, s);
}
