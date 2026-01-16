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

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern int line_num;
extern int col_num;

void yyerror(const char* s);

ASTNode* root = NULL;

#line 88 "parser.tab.c"

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
  YYSYMBOL_Decl = 61,                      /* Decl  */
  YYSYMBOL_BasicType = 62,                 /* BasicType  */
  YYSYMBOL_RecordDecl = 63,                /* RecordDecl  */
  YYSYMBOL_FieldList = 64,                 /* FieldList  */
  YYSYMBOL_Field = 65,                     /* Field  */
  YYSYMBOL_ArrayDecl = 66,                 /* ArrayDecl  */
  YYSYMBOL_ArrayInit = 67,                 /* ArrayInit  */
  YYSYMBOL_DictDecl = 68,                  /* DictDecl  */
  YYSYMBOL_OptInit = 69,                   /* OptInit  */
  YYSYMBOL_ExprList = 70,                  /* ExprList  */
  YYSYMBOL_Type = 71,                      /* Type  */
  YYSYMBOL_Instrs = 72,                    /* Instrs  */
  YYSYMBOL_Instr = 73,                     /* Instr  */
  YYSYMBOL_Assign = 74,                    /* Assign  */
  YYSYMBOL_Print = 75,                     /* Print  */
  YYSYMBOL_Input = 76,                     /* Input  */
  YYSYMBOL_If = 77,                        /* If  */
  YYSYMBOL_OptElse = 78,                   /* OptElse  */
  YYSYMBOL_While = 79,                     /* While  */
  YYSYMBOL_For = 80,                       /* For  */
  YYSYMBOL_ForEach = 81,                   /* ForEach  */
  YYSYMBOL_Case = 82,                      /* Case  */
  YYSYMBOL_CaseList = 83,                  /* CaseList  */
  YYSYMBOL_CaseItem = 84,                  /* CaseItem  */
  YYSYMBOL_Expr = 85,                      /* Expr  */
  YYSYMBOL_Term = 86,                      /* Term  */
  YYSYMBOL_Factor = 87,                    /* Factor  */
  YYSYMBOL_Cond = 88                       /* Cond  */
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
#define YYLAST   275

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  201

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
       0,    62,    62,    74,    79,    84,    85,    86,    90,    91,
      92,    93,    97,   105,   106,   110,   114,   122,   123,   124,
     128,   136,   137,   141,   142,   146,   147,   148,   149,   153,
     154,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     170,   175,   180,   188,   192,   196,   203,   204,   205,   209,
     216,   224,   232,   236,   243,   244,   256,   263,   264,   265,
     269,   270,   271,   272,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298
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
  "$accept", "Program", "Decl", "BasicType", "RecordDecl", "FieldList",
  "Field", "ArrayDecl", "ArrayInit", "DictDecl", "OptInit", "ExprList",
  "Type", "Instrs", "Instr", "Assign", "Print", "Input", "If", "OptElse",
  "While", "For", "ForEach", "Case", "CaseList", "CaseItem", "Expr",
  "Term", "Factor", "Cond", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-108)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -2,    11,    22,    41,  -108,    27,  -108,   119,   -34,    46,
      97,    86,    67,    83,     6,   115,    87,   120,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,    87,    87,   132,    89,   231,   136,   -26,  -108,  -108,
    -108,  -108,  -108,    67,    87,    67,   225,    95,  -108,    59,
      67,    19,  -108,    67,   148,   126,    87,    57,   107,    64,
     112,   127,  -108,   139,   145,   130,  -108,  -108,  -108,  -108,
     139,   141,    87,   199,  -108,  -108,   212,     7,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,  -108,
      67,    67,    61,   180,  -108,  -108,    43,   177,   204,    30,
    -108,  -108,  -108,   174,    87,    87,   152,   171,   171,   153,
     210,   122,  -108,  -108,  -108,    70,    70,    70,    70,    70,
      70,    95,    95,  -108,  -108,  -108,   100,  -108,   182,  -108,
     159,   151,   170,    87,   168,    87,    93,    70,  -108,  -108,
    -108,  -108,  -108,   169,   172,  -108,   171,   -47,  -108,  -108,
    -108,  -108,   216,   208,  -108,   201,   203,    16,  -108,   103,
    -108,   223,   171,  -108,   175,   210,   208,   208,   211,   181,
     184,    87,    -1,  -108,   186,   195,  -108,  -108,   187,  -108,
    -108,    70,  -108,   220,   205,  -108,   189,    32,   215,  -108,
     232,    87,    70,  -108,   217,   114,    70,  -108,  -108,    87,
      70
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,    29,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,     5,
       6,     7,    30,    31,    32,    37,    33,    34,    35,    38,
      36,     0,     0,     0,     0,     0,     0,    69,    66,    64,
      65,    67,    68,     0,     0,     0,     0,    59,    63,     0,
       0,     0,    54,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,    22,     0,     0,     8,     9,    10,    11,
      22,     0,     0,     0,    76,    73,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    29,
       0,     0,     0,     0,    29,    55,    29,     0,     0,     0,
      43,    44,    40,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    70,    72,    83,    77,    78,    79,    80,    81,
      82,    57,    58,    60,    61,    62,    48,    74,    75,    29,
       0,     0,     0,     0,     0,     0,     0,    21,     4,    25,
      26,    27,    28,     0,     0,     3,     0,     0,    13,    71,
      29,    29,     0,    56,    52,     0,     0,     0,    29,     0,
      41,     0,     0,    15,     0,     0,    47,    46,     0,     0,
       0,     0,     0,    42,     0,     0,    12,    14,     0,    53,
      49,    29,    51,    19,     0,    45,     0,     0,     0,    20,
       0,     0,    18,    16,     0,     0,    23,    50,    17,     0,
      24
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -108,  -108,  -108,  -108,  -108,  -108,   110,  -108,  -108,  -108,
     190,  -108,  -107,   -82,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,   221,   -16,   109,   -38,   -32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,    18,    70,    19,   147,   148,    20,   188,    21,
     106,   195,   143,     7,    22,    23,    24,    25,    26,   152,
      27,    28,    29,    30,    51,    52,    46,    47,    48,    49
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      57,   144,     8,   164,    31,     1,    75,   126,   165,    10,
      11,    74,   131,    77,   132,    59,    60,    32,    92,     3,
      12,    96,     4,    33,    13,    72,    14,    53,    93,    76,
      15,    73,    16,    17,    54,    37,    38,    39,    40,   163,
      99,    50,    90,    91,     5,    94,   171,   153,   123,   124,
     125,    41,    42,   182,    34,   175,   111,   114,   127,   128,
      84,    85,   115,   116,   117,   118,   119,   120,   166,   167,
      37,    38,    39,    40,    84,    85,   172,    44,    90,    91,
     113,    56,    89,     6,   129,   191,    41,    42,   136,   137,
      37,    38,    39,    40,    90,    91,    90,    91,    36,   186,
      35,    84,    85,     8,    43,    50,    41,    42,    84,    85,
      10,    11,    44,   100,    84,    85,    45,   157,    55,   159,
     102,    12,     8,    58,   150,    13,   151,    14,     9,    10,
      11,    15,    44,    16,    17,    61,    56,    84,    85,    71,
      12,    86,    87,    88,    13,    62,    14,    84,    85,   160,
      15,    97,    16,    17,     8,   181,    84,    85,    98,   173,
     155,    10,    11,   101,   103,   104,    84,    85,   198,   199,
     108,   192,    12,     8,   149,   196,    13,   105,    14,   156,
      10,    11,    15,   200,    16,    17,   139,   140,   141,   142,
     110,    12,     8,   121,   122,    13,   107,    14,   190,    10,
      11,    15,   112,    16,    17,   130,   133,   134,   138,   145,
      12,     8,   135,   146,    13,   154,    14,    90,    10,    11,
      15,   158,    16,    17,   161,   168,   169,   162,   174,    12,
     170,   176,   178,    13,    63,    14,   184,   179,   183,    15,
     180,    16,    17,   185,    64,    65,    66,    67,    68,    69,
      78,    79,    80,    81,    82,    83,    84,    85,   187,   194,
     109,   189,   113,    78,    79,    80,    81,    82,    83,    84,
      85,   193,    95,   197,     0,   177
};

static const yytype_int16 yycheck[] =
{
      16,   108,     3,    50,    38,     7,    44,    89,    55,    10,
      11,    43,    94,    45,    96,    31,    32,    51,    50,     8,
      21,    53,     0,    57,    25,    51,    27,    21,     9,    45,
      31,    57,    33,    34,    28,     3,     4,     5,     6,   146,
      56,    22,    35,    36,     3,    26,    30,   129,    86,    87,
      88,    19,    20,    54,     8,   162,    72,    50,    90,    91,
      44,    45,    78,    79,    80,    81,    82,    83,   150,   151,
       3,     4,     5,     6,    44,    45,   158,    45,    35,    36,
      50,    49,    23,    56,    23,    53,    19,    20,   104,   105,
       3,     4,     5,     6,    35,    36,    35,    36,    12,   181,
       3,    44,    45,     3,    37,    22,    19,    20,    44,    45,
      10,    11,    45,    56,    44,    45,    49,   133,     3,   135,
      56,    21,     3,     3,    24,    25,    26,    27,     9,    10,
      11,    31,    45,    33,    34,     3,    49,    44,    45,     3,
      21,    46,    47,    48,    25,    56,    27,    44,    45,    56,
      31,     3,    33,    34,     3,   171,    44,    45,    32,    56,
       9,    10,    11,    56,    52,    38,    44,    45,    54,    55,
      40,   187,    21,     3,    52,   191,    25,    38,    27,     9,
      10,    11,    31,   199,    33,    34,    15,    16,    17,    18,
      49,    21,     3,    84,    85,    25,    51,    27,     9,    10,
      11,    31,     3,    33,    34,    25,    29,     3,    56,    56,
      21,     3,    38,     3,    25,    56,    27,    35,    10,    11,
      31,    53,    33,    34,    55,     9,    25,    55,     5,    21,
      27,    56,    21,    25,     3,    27,    41,    56,    52,    31,
      56,    33,    34,    56,    13,    14,    15,    16,    17,    18,
      38,    39,    40,    41,    42,    43,    44,    45,    38,    27,
      70,    56,    50,    38,    39,    40,    41,    42,    43,    44,
      45,    56,    51,    56,    -1,   165
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,    60,     8,     0,     3,    56,    72,     3,     9,
      10,    11,    21,    25,    27,    31,    33,    34,    61,    63,
      66,    68,    73,    74,    75,    76,    77,    79,    80,    81,
      82,    38,    51,    57,     8,     3,    12,     3,     4,     5,
       6,    19,    20,    37,    45,    49,    85,    86,    87,    88,
      22,    83,    84,    21,    28,     3,    49,    85,     3,    85,
      85,     3,    56,     3,    13,    14,    15,    16,    17,    18,
      62,     3,    51,    57,    88,    87,    85,    88,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    23,
      35,    36,    88,     9,    26,    84,    88,     3,    32,    85,
      56,    56,    56,    52,    38,    38,    69,    51,    40,    69,
      49,    85,     3,    50,    50,    85,    85,    85,    85,    85,
      85,    86,    86,    87,    87,    87,    72,    88,    88,    23,
      25,    72,    72,    29,     3,    38,    85,    85,    56,    15,
      16,    17,    18,    71,    71,    56,     3,    64,    65,    52,
      24,    26,    78,    72,    56,     9,     9,    85,    53,    85,
      56,    55,    55,    71,    50,    55,    72,    72,     9,    25,
      27,    30,    72,    56,     5,    71,    56,    65,    21,    56,
      56,    85,    54,    52,    41,    56,    72,    38,    67,    56,
       9,    53,    85,    56,    27,    70,    85,    56,    54,    55,
      85
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    59,    60,    61,    61,    61,    61,    61,    62,    62,
      62,    62,    63,    64,    64,    65,    66,    67,    67,    67,
      68,    69,    69,    70,    70,    71,    71,    71,    71,    72,
      72,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      74,    74,    74,    75,    76,    77,    78,    78,    78,    79,
      80,    81,    82,    82,    83,    83,    84,    85,    85,    85,
      86,    86,    86,    86,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     8,     5,     5,     1,     1,     1,     1,     1,
       1,     1,     7,     1,     3,     2,    10,     4,     2,     0,
       9,     2,     0,     1,     3,     1,     1,     1,     1,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     6,     7,     3,     3,     8,     2,     2,     0,     7,
      11,     7,     5,     7,     1,     2,     4,     3,     3,     1,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     4,     3,     2,     3,     3,     2,     3,     3,     3,
       3,     3,     3,     3
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
  case 2: /* Program: KW_BEGIN KW_PROGRAM IDENTIFIER SEP_SEMICOLON Instrs KW_END KW_PROGRAM SEP_SEMICOLON  */
#line 63 "parser.y"
    {
        /* We pass NULL for the old Decls parameter because Declarations are now part of Instrs */
        (yyval.node) = createProgramNode((yyvsp[-5].str), NULL, (yyvsp[-3].node)); 
        root = (yyval.node);
        printf("\n✓ Program '%s' parsed successfully!\n", (yyvsp[-5].str));
        free((yyvsp[-5].str));
    }
#line 1317 "parser.tab.c"
    break;

  case 3: /* Decl: KW_SET IDENTIFIER BasicType OptInit SEP_SEMICOLON  */
#line 75 "parser.y"
    {
        (yyval.node) = createDeclNode((yyvsp[-3].str), (yyvsp[-2].dtype), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1326 "parser.tab.c"
    break;

  case 4: /* Decl: KW_SET IDENTIFIER IDENTIFIER OptInit SEP_SEMICOLON  */
#line 80 "parser.y"
    {
        (yyval.node) = createRecordInstanceNode((yyvsp[-3].str), (yyvsp[-2].str), (yyvsp[-1].node));
        free((yyvsp[-3].str)); free((yyvsp[-2].str));
    }
#line 1335 "parser.tab.c"
    break;

  case 5: /* Decl: RecordDecl  */
#line 84 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1341 "parser.tab.c"
    break;

  case 6: /* Decl: ArrayDecl  */
#line 85 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1347 "parser.tab.c"
    break;

  case 7: /* Decl: DictDecl  */
#line 86 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1353 "parser.tab.c"
    break;

  case 8: /* BasicType: KW_INTEGER  */
#line 90 "parser.y"
                 { (yyval.dtype) = TYPE_INTEGER; }
#line 1359 "parser.tab.c"
    break;

  case 9: /* BasicType: KW_STRING  */
#line 91 "parser.y"
                 { (yyval.dtype) = TYPE_STRING; }
#line 1365 "parser.tab.c"
    break;

  case 10: /* BasicType: KW_FLOAT  */
#line 92 "parser.y"
                 { (yyval.dtype) = TYPE_FLOAT; }
#line 1371 "parser.tab.c"
    break;

  case 11: /* BasicType: KW_BOOLEAN  */
#line 93 "parser.y"
                 { (yyval.dtype) = TYPE_BOOLEAN; }
#line 1377 "parser.tab.c"
    break;

  case 12: /* RecordDecl: KW_CREATE KW_RECORD IDENTIFIER SEP_LPAREN FieldList SEP_RPAREN SEP_SEMICOLON  */
#line 98 "parser.y"
    {
        (yyval.node) = createRecordDeclNode((yyvsp[-4].str), (yyvsp[-2].node));
        free((yyvsp[-4].str));
    }
#line 1386 "parser.tab.c"
    break;

  case 13: /* FieldList: Field  */
#line 105 "parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1392 "parser.tab.c"
    break;

  case 14: /* FieldList: FieldList SEP_COMMA Field  */
#line 106 "parser.y"
                                { (yyval.node) = createFieldListNode((yyvsp[0].node), (yyvsp[-2].node)); }
#line 1398 "parser.tab.c"
    break;

  case 15: /* Field: IDENTIFIER Type  */
#line 110 "parser.y"
                    { (yyval.node) = createFieldNode((yyvsp[-1].str), (yyvsp[0].dtype)); free((yyvsp[-1].str)); }
#line 1404 "parser.tab.c"
    break;

  case 16: /* ArrayDecl: KW_SET IDENTIFIER KW_ARRAY SEP_LBRACKET Type SEP_COMMA INT_LITERAL SEP_RBRACKET ArrayInit SEP_SEMICOLON  */
#line 115 "parser.y"
    {
        (yyval.node) = createArrayDeclNode((yyvsp[-8].str), (yyvsp[-5].dtype), (yyvsp[-3].ival), (yyvsp[-1].node));
        free((yyvsp[-8].str));
    }
#line 1413 "parser.tab.c"
    break;

  case 17: /* ArrayInit: OP_EQ SEP_LBRACE ExprList SEP_RBRACE  */
#line 122 "parser.y"
                                         { (yyval.node) = (yyvsp[-1].node); }
#line 1419 "parser.tab.c"
    break;

  case 18: /* ArrayInit: OP_EQ Expr  */
#line 123 "parser.y"
                                         { (yyval.node) = (yyvsp[0].node); }
#line 1425 "parser.tab.c"
    break;

  case 19: /* ArrayInit: %empty  */
#line 124 "parser.y"
                                         { (yyval.node) = NULL; }
#line 1431 "parser.tab.c"
    break;

  case 20: /* DictDecl: KW_SET IDENTIFIER KW_DICTIONARY OP_LT Type SEP_COMMA Type OP_GT SEP_SEMICOLON  */
#line 129 "parser.y"
    {
        (yyval.node) = createDictDeclNode((yyvsp[-7].str), (yyvsp[-4].dtype), (yyvsp[-2].dtype));
        free((yyvsp[-7].str));
    }
#line 1440 "parser.tab.c"
    break;

  case 21: /* OptInit: OP_EQ Expr  */
#line 136 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1446 "parser.tab.c"
    break;

  case 22: /* OptInit: %empty  */
#line 137 "parser.y"
                  { (yyval.node) = NULL; }
#line 1452 "parser.tab.c"
    break;

  case 23: /* ExprList: Expr  */
#line 141 "parser.y"
                                { (yyval.node) = createExprListNode((yyvsp[0].node), NULL); }
#line 1458 "parser.tab.c"
    break;

  case 24: /* ExprList: ExprList SEP_COMMA Expr  */
#line 142 "parser.y"
                                { (yyval.node) = createExprListNode((yyvsp[0].node), (yyvsp[-2].node)); }
#line 1464 "parser.tab.c"
    break;

  case 25: /* Type: KW_INTEGER  */
#line 146 "parser.y"
                 { (yyval.dtype) = TYPE_INTEGER; }
#line 1470 "parser.tab.c"
    break;

  case 26: /* Type: KW_STRING  */
#line 147 "parser.y"
                 { (yyval.dtype) = TYPE_STRING; }
#line 1476 "parser.tab.c"
    break;

  case 27: /* Type: KW_FLOAT  */
#line 148 "parser.y"
                 { (yyval.dtype) = TYPE_FLOAT; }
#line 1482 "parser.tab.c"
    break;

  case 28: /* Type: KW_BOOLEAN  */
#line 149 "parser.y"
                 { (yyval.dtype) = TYPE_BOOLEAN; }
#line 1488 "parser.tab.c"
    break;

  case 29: /* Instrs: %empty  */
#line 153 "parser.y"
                    { (yyval.node) = NULL; }
#line 1494 "parser.tab.c"
    break;

  case 30: /* Instrs: Instrs Instr  */
#line 154 "parser.y"
                    { (yyval.node) = createStmtListNode((yyvsp[0].node), (yyvsp[-1].node)); }
#line 1500 "parser.tab.c"
    break;

  case 31: /* Instr: Assign  */
#line 158 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1506 "parser.tab.c"
    break;

  case 32: /* Instr: Print  */
#line 159 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1512 "parser.tab.c"
    break;

  case 33: /* Instr: If  */
#line 160 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1518 "parser.tab.c"
    break;

  case 34: /* Instr: While  */
#line 161 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1524 "parser.tab.c"
    break;

  case 35: /* Instr: For  */
#line 162 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1530 "parser.tab.c"
    break;

  case 36: /* Instr: Case  */
#line 163 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1536 "parser.tab.c"
    break;

  case 37: /* Instr: Input  */
#line 164 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1542 "parser.tab.c"
    break;

  case 38: /* Instr: ForEach  */
#line 165 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1548 "parser.tab.c"
    break;

  case 39: /* Instr: Decl  */
#line 166 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1554 "parser.tab.c"
    break;

  case 40: /* Assign: IDENTIFIER OP_EQ Expr SEP_SEMICOLON  */
#line 171 "parser.y"
    {
        (yyval.node) = createAssignNode((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1563 "parser.tab.c"
    break;

  case 41: /* Assign: IDENTIFIER SEP_DOT IDENTIFIER OP_EQ Expr SEP_SEMICOLON  */
#line 176 "parser.y"
    {
        (yyval.node) = createRecordAccessAssignNode((yyvsp[-5].str), (yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-5].str)); free((yyvsp[-3].str));
    }
#line 1572 "parser.tab.c"
    break;

  case 42: /* Assign: IDENTIFIER SEP_LBRACKET Expr SEP_RBRACKET OP_EQ Expr SEP_SEMICOLON  */
#line 181 "parser.y"
    {
        (yyval.node) = createArrayAccessAssignNode((yyvsp[-6].str), (yyvsp[-4].node), (yyvsp[-1].node));
        free((yyvsp[-6].str));
    }
#line 1581 "parser.tab.c"
    break;

  case 43: /* Print: KW_PRINT Expr SEP_SEMICOLON  */
#line 188 "parser.y"
                                { (yyval.node) = createPrintNode((yyvsp[-1].node)); }
#line 1587 "parser.tab.c"
    break;

  case 44: /* Input: KW_INPUT IDENTIFIER SEP_SEMICOLON  */
#line 192 "parser.y"
                                      { (yyval.node) = createInputNode((yyvsp[-1].str)); free((yyvsp[-1].str)); }
#line 1593 "parser.tab.c"
    break;

  case 45: /* If: KW_WHEN Cond KW_THEN Instrs OptElse KW_END KW_WHEN SEP_SEMICOLON  */
#line 197 "parser.y"
    {
        (yyval.node) = createIfNode((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-3].node));
    }
#line 1601 "parser.tab.c"
    break;

  case 46: /* OptElse: KW_ELSE Instrs  */
#line 203 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1607 "parser.tab.c"
    break;

  case 47: /* OptElse: KW_OTHERWISE Instrs  */
#line 204 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1613 "parser.tab.c"
    break;

  case 48: /* OptElse: %empty  */
#line 205 "parser.y"
                          { (yyval.node) = NULL; }
#line 1619 "parser.tab.c"
    break;

  case 49: /* While: KW_LOOP KW_WHEN Cond Instrs KW_END KW_LOOP SEP_SEMICOLON  */
#line 210 "parser.y"
    {
        (yyval.node) = createWhileNode((yyvsp[-4].node), (yyvsp[-3].node));
    }
#line 1627 "parser.tab.c"
    break;

  case 50: /* For: KW_LOOP KW_ITERATE IDENTIFIER KW_FROM Expr KW_TO Expr Instrs KW_END KW_LOOP SEP_SEMICOLON  */
#line 217 "parser.y"
    {
        (yyval.node) = createForNode((yyvsp[-8].str), (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-3].node));
        free((yyvsp[-8].str));
    }
#line 1636 "parser.tab.c"
    break;

  case 51: /* ForEach: KW_FOREACH IDENTIFIER KW_IN IDENTIFIER SEP_LBRACE Instrs SEP_RBRACE  */
#line 225 "parser.y"
    {
        (yyval.node) = createForEachNode((yyvsp[-5].str), (yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-5].str)); free((yyvsp[-3].str));
    }
#line 1645 "parser.tab.c"
    break;

  case 52: /* Case: KW_CASE CaseList KW_END KW_CASE SEP_SEMICOLON  */
#line 233 "parser.y"
    {
        (yyval.node) = createCaseNode((yyvsp[-3].node), NULL);
    }
#line 1653 "parser.tab.c"
    break;

  case 53: /* Case: KW_CASE CaseList KW_ELSE Instrs KW_END KW_CASE SEP_SEMICOLON  */
#line 237 "parser.y"
    {
        (yyval.node) = createCaseNode((yyvsp[-5].node), (yyvsp[-3].node));
    }
#line 1661 "parser.tab.c"
    break;

  case 54: /* CaseList: CaseItem  */
#line 243 "parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 1667 "parser.tab.c"
    break;

  case 55: /* CaseList: CaseList CaseItem  */
#line 245 "parser.y"
    {
        ASTNode* temp = (yyvsp[-1].node);
        while (temp->data.caseItem.next != NULL) {
            temp = temp->data.caseItem.next;
        }
        temp->data.caseItem.next = (yyvsp[0].node);
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1680 "parser.tab.c"
    break;

  case 56: /* CaseItem: KW_CASE_WHEN Cond KW_THEN Instrs  */
#line 257 "parser.y"
    {
        (yyval.node) = createCaseItemNode((yyvsp[-2].node), (yyvsp[0].node), NULL);
    }
#line 1688 "parser.tab.c"
    break;

  case 57: /* Expr: Expr OP_PLUS Term  */
#line 263 "parser.y"
                          { (yyval.node) = createBinOpNode(AST_OP_ADD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1694 "parser.tab.c"
    break;

  case 58: /* Expr: Expr OP_MINUS Term  */
#line 264 "parser.y"
                            { (yyval.node) = createBinOpNode(AST_OP_SUB, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1700 "parser.tab.c"
    break;

  case 59: /* Expr: Term  */
#line 265 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1706 "parser.tab.c"
    break;

  case 60: /* Term: Term OP_MULT Factor  */
#line 269 "parser.y"
                          { (yyval.node) = createBinOpNode(AST_OP_MUL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1712 "parser.tab.c"
    break;

  case 61: /* Term: Term OP_DIV Factor  */
#line 270 "parser.y"
                            { (yyval.node) = createBinOpNode(AST_OP_DIV, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1718 "parser.tab.c"
    break;

  case 62: /* Term: Term OP_MOD Factor  */
#line 271 "parser.y"
                            { (yyval.node) = createBinOpNode(AST_OP_MOD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1724 "parser.tab.c"
    break;

  case 63: /* Term: Factor  */
#line 272 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1730 "parser.tab.c"
    break;

  case 64: /* Factor: INT_LITERAL  */
#line 276 "parser.y"
                       { (yyval.node) = createIntLiteralNode((yyvsp[0].ival)); }
#line 1736 "parser.tab.c"
    break;

  case 65: /* Factor: FLOAT_LITERAL  */
#line 277 "parser.y"
                       { (yyval.node) = createFloatLiteralNode((yyvsp[0].fval)); }
#line 1742 "parser.tab.c"
    break;

  case 66: /* Factor: STRING_LITERAL  */
#line 278 "parser.y"
                       { (yyval.node) = createStringLiteralNode((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 1748 "parser.tab.c"
    break;

  case 67: /* Factor: KW_TRUE  */
#line 279 "parser.y"
                       { (yyval.node) = createBoolLiteralNode(1); }
#line 1754 "parser.tab.c"
    break;

  case 68: /* Factor: KW_FALSE  */
#line 280 "parser.y"
                       { (yyval.node) = createBoolLiteralNode(0); }
#line 1760 "parser.tab.c"
    break;

  case 69: /* Factor: IDENTIFIER  */
#line 281 "parser.y"
                       { (yyval.node) = createIdentifierNode((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 1766 "parser.tab.c"
    break;

  case 70: /* Factor: IDENTIFIER SEP_DOT IDENTIFIER  */
#line 282 "parser.y"
                                    { (yyval.node) = createRecordAccessNode((yyvsp[-2].str), (yyvsp[0].str)); free((yyvsp[-2].str)); free((yyvsp[0].str)); }
#line 1772 "parser.tab.c"
    break;

  case 71: /* Factor: IDENTIFIER SEP_LBRACKET Expr SEP_RBRACKET  */
#line 283 "parser.y"
                                                { (yyval.node) = createArrayAccessNode((yyvsp[-3].str), (yyvsp[-1].node)); free((yyvsp[-3].str)); }
#line 1778 "parser.tab.c"
    break;

  case 72: /* Factor: SEP_LPAREN Expr SEP_RPAREN  */
#line 284 "parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 1784 "parser.tab.c"
    break;

  case 73: /* Factor: OP_MINUS Factor  */
#line 285 "parser.y"
                                   { (yyval.node) = createUnaryOpNode(AST_OP_NEG, (yyvsp[0].node)); }
#line 1790 "parser.tab.c"
    break;

  case 74: /* Cond: Cond OP_AND Cond  */
#line 289 "parser.y"
                        { (yyval.node) = createBinOpNode(AST_OP_AND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1796 "parser.tab.c"
    break;

  case 75: /* Cond: Cond OP_OR Cond  */
#line 290 "parser.y"
                          { (yyval.node) = createBinOpNode(AST_OP_OR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1802 "parser.tab.c"
    break;

  case 76: /* Cond: OP_NOT Cond  */
#line 291 "parser.y"
                          { (yyval.node) = createUnaryOpNode(AST_OP_NOT, (yyvsp[0].node)); }
#line 1808 "parser.tab.c"
    break;

  case 77: /* Cond: Expr OP_EQ Expr  */
#line 292 "parser.y"
                          { (yyval.node) = createBinOpNode(AST_OP_EQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1814 "parser.tab.c"
    break;

  case 78: /* Cond: Expr OP_NEQ Expr  */
#line 293 "parser.y"
                          { (yyval.node) = createBinOpNode(AST_OP_NEQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1820 "parser.tab.c"
    break;

  case 79: /* Cond: Expr OP_LT Expr  */
#line 294 "parser.y"
                          { (yyval.node) = createBinOpNode(AST_OP_LT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1826 "parser.tab.c"
    break;

  case 80: /* Cond: Expr OP_GT Expr  */
#line 295 "parser.y"
                          { (yyval.node) = createBinOpNode(AST_OP_GT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1832 "parser.tab.c"
    break;

  case 81: /* Cond: Expr OP_LTE Expr  */
#line 296 "parser.y"
                          { (yyval.node) = createBinOpNode(AST_OP_LTE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1838 "parser.tab.c"
    break;

  case 82: /* Cond: Expr OP_GTE Expr  */
#line 297 "parser.y"
                          { (yyval.node) = createBinOpNode(AST_OP_GTE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1844 "parser.tab.c"
    break;

  case 83: /* Cond: SEP_LPAREN Cond SEP_RPAREN  */
#line 298 "parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 1850 "parser.tab.c"
    break;


#line 1854 "parser.tab.c"

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

#line 301 "parser.y"


void yyerror(const char* s) {
    fprintf(stderr, "Parse error at line %d, col %d: %s\n", line_num, col_num, s);
}
