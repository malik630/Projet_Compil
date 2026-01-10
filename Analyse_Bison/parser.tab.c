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
#include "table_symboles_enrichie.h"  //  AJOUTÉ

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern int line_num;
extern int col_num;

void yyerror(const char* s);

ASTNode* root = NULL;

//  AJOUTÉ : Table des symboles globale
TableSymboles tableGlobale;
int adresseMemoire = 0;

#line 93 "parser.tab.c"

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
  YYSYMBOL_KW_THEN = 22,                   /* KW_THEN  */
  YYSYMBOL_KW_OTHERWISE = 23,              /* KW_OTHERWISE  */
  YYSYMBOL_KW_CASE = 24,                   /* KW_CASE  */
  YYSYMBOL_KW_ELSE = 25,                   /* KW_ELSE  */
  YYSYMBOL_KW_LOOP = 26,                   /* KW_LOOP  */
  YYSYMBOL_KW_ITERATE = 27,                /* KW_ITERATE  */
  YYSYMBOL_KW_FROM = 28,                   /* KW_FROM  */
  YYSYMBOL_KW_TO = 29,                     /* KW_TO  */
  YYSYMBOL_KW_PRINT = 30,                  /* KW_PRINT  */
  YYSYMBOL_KW_INPUT = 31,                  /* KW_INPUT  */
  YYSYMBOL_OP_AND = 32,                    /* OP_AND  */
  YYSYMBOL_OP_OR = 33,                     /* OP_OR  */
  YYSYMBOL_OP_NOT = 34,                    /* OP_NOT  */
  YYSYMBOL_OP_EQ = 35,                     /* OP_EQ  */
  YYSYMBOL_OP_NEQ = 36,                    /* OP_NEQ  */
  YYSYMBOL_OP_LT = 37,                     /* OP_LT  */
  YYSYMBOL_OP_GT = 38,                     /* OP_GT  */
  YYSYMBOL_OP_LTE = 39,                    /* OP_LTE  */
  YYSYMBOL_OP_GTE = 40,                    /* OP_GTE  */
  YYSYMBOL_OP_PLUS = 41,                   /* OP_PLUS  */
  YYSYMBOL_OP_MINUS = 42,                  /* OP_MINUS  */
  YYSYMBOL_OP_MULT = 43,                   /* OP_MULT  */
  YYSYMBOL_OP_DIV = 44,                    /* OP_DIV  */
  YYSYMBOL_OP_MOD = 45,                    /* OP_MOD  */
  YYSYMBOL_SEP_LPAREN = 46,                /* SEP_LPAREN  */
  YYSYMBOL_SEP_RPAREN = 47,                /* SEP_RPAREN  */
  YYSYMBOL_SEP_LBRACKET = 48,              /* SEP_LBRACKET  */
  YYSYMBOL_SEP_RBRACKET = 49,              /* SEP_RBRACKET  */
  YYSYMBOL_SEP_LBRACE = 50,                /* SEP_LBRACE  */
  YYSYMBOL_SEP_RBRACE = 51,                /* SEP_RBRACE  */
  YYSYMBOL_SEP_COMMA = 52,                 /* SEP_COMMA  */
  YYSYMBOL_SEP_SEMICOLON = 53,             /* SEP_SEMICOLON  */
  YYSYMBOL_SEP_DOT = 54,                   /* SEP_DOT  */
  YYSYMBOL_UMINUS = 55,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 56,                  /* $accept  */
  YYSYMBOL_Program = 57,                   /* Program  */
  YYSYMBOL_58_1 = 58,                      /* $@1  */
  YYSYMBOL_Decls = 59,                     /* Decls  */
  YYSYMBOL_Decl = 60,                      /* Decl  */
  YYSYMBOL_OptInit = 61,                   /* OptInit  */
  YYSYMBOL_Type = 62,                      /* Type  */
  YYSYMBOL_Instrs = 63,                    /* Instrs  */
  YYSYMBOL_Instr = 64,                     /* Instr  */
  YYSYMBOL_Assign = 65,                    /* Assign  */
  YYSYMBOL_Print = 66,                     /* Print  */
  YYSYMBOL_If = 67,                        /* If  */
  YYSYMBOL_68_2 = 68,                      /* $@2  */
  YYSYMBOL_OptElse = 69,                   /* OptElse  */
  YYSYMBOL_Expr = 70,                      /* Expr  */
  YYSYMBOL_Term = 71,                      /* Term  */
  YYSYMBOL_Factor = 72,                    /* Factor  */
  YYSYMBOL_Cond = 73                       /* Cond  */
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
typedef yytype_int8 yy_state_t;

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
#define YYLAST   76

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  40
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  77

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   310


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
      55
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    64,    64,    63,    82,    87,    93,   139,   144,   150,
     151,   152,   153,   157,   162,   168,   169,   170,   174,   198,
     206,   205,   220,   225,   231,   235,   239,   246,   250,   254,
     261,   265,   269,   274,   291,   298,   302,   306,   310,   314,
     318
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
  "KW_TRUE", "KW_FALSE", "KW_WHEN", "KW_THEN", "KW_OTHERWISE", "KW_CASE",
  "KW_ELSE", "KW_LOOP", "KW_ITERATE", "KW_FROM", "KW_TO", "KW_PRINT",
  "KW_INPUT", "OP_AND", "OP_OR", "OP_NOT", "OP_EQ", "OP_NEQ", "OP_LT",
  "OP_GT", "OP_LTE", "OP_GTE", "OP_PLUS", "OP_MINUS", "OP_MULT", "OP_DIV",
  "OP_MOD", "SEP_LPAREN", "SEP_RPAREN", "SEP_LBRACKET", "SEP_RBRACKET",
  "SEP_LBRACE", "SEP_RBRACE", "SEP_COMMA", "SEP_SEMICOLON", "SEP_DOT",
  "UMINUS", "$accept", "Program", "$@1", "Decls", "Decl", "OptInit",
  "Type", "Instrs", "Instr", "Assign", "Print", "If", "$@2", "OptElse",
  "Expr", "Term", "Factor", "Cond", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-51)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -2,    -1,     9,    11,   -51,   -36,   -51,   -51,    29,    16,
     -51,     7,    33,    -8,    36,   -51,    -3,   -51,   -51,   -51,
     -51,   -51,   -51,   -51,   -51,    -6,    -3,    -7,    -3,   -51,
     -51,   -51,   -51,    -3,   -29,   -21,   -51,    -3,    13,     0,
     -51,    19,    30,    21,    -3,    -3,   -51,    -3,    -3,   -16,
     -51,   -51,    -3,    -3,    -3,    -3,    -3,    -3,   -51,   -51,
     -21,   -21,   -51,   -51,   -16,   -16,   -16,   -16,   -16,   -16,
      15,   -51,    58,    17,    50,    23,   -51
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     2,     5,    14,     0,
       4,     0,     0,     0,     0,    20,     0,    13,    15,    16,
      17,     9,    10,    11,    12,     8,     0,     0,     0,    33,
      32,    30,    31,     0,     0,    26,    29,     0,     0,     0,
       3,     0,     0,     0,     0,     0,    19,     0,     0,     7,
       6,    18,     0,     0,     0,     0,     0,     0,    14,    34,
      24,    25,    27,    28,    35,    36,    37,    38,    39,    40,
      23,    14,     0,    22,     0,     0,    21
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -51,   -51,   -51,   -51,   -51,   -51,   -51,   -50,   -51,   -51,
     -51,   -51,   -51,   -51,   -22,    20,    22,   -51
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     7,     8,    10,    38,    25,    11,    17,    18,
      19,    20,    28,    72,    34,    35,    36,    42
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      29,    30,    31,    32,    39,     1,    41,     3,    70,     4,
      13,    43,    44,    45,     5,    49,    14,     6,    13,    12,
      13,    73,    47,    48,    46,    44,    45,    26,    15,    37,
      64,    65,    66,    67,    68,    69,    15,    16,    15,     9,
      71,    44,    45,    33,    27,    16,    40,    16,    21,    22,
      23,    24,    58,    51,    52,    53,    54,    55,    56,    57,
      44,    45,    44,    45,    60,    61,    50,    74,    59,    62,
      63,    75,     0,     0,     0,     0,    76
};

static const yytype_int8 yycheck[] =
{
       3,     4,     5,     6,    26,     7,    28,     8,    58,     0,
       3,    33,    41,    42,     3,    37,     9,    53,     3,     3,
       3,    71,    43,    44,    53,    41,    42,    35,    21,    35,
      52,    53,    54,    55,    56,    57,    21,    30,    21,    10,
      25,    41,    42,    46,     8,    30,    53,    30,    15,    16,
      17,    18,    22,    53,    35,    36,    37,    38,    39,    40,
      41,    42,    41,    42,    44,    45,    53,     9,    47,    47,
      48,    21,    -1,    -1,    -1,    -1,    53
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,    57,     8,     0,     3,    53,    58,    59,    10,
      60,    63,     3,     3,     9,    21,    30,    64,    65,    66,
      67,    15,    16,    17,    18,    62,    35,     8,    68,     3,
       4,     5,     6,    46,    70,    71,    72,    35,    61,    70,
      53,    70,    73,    70,    41,    42,    53,    43,    44,    70,
      53,    53,    35,    36,    37,    38,    39,    40,    22,    47,
      71,    71,    72,    72,    70,    70,    70,    70,    70,    70,
      63,    25,    69,    63,     9,    21,    53
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    56,    58,    57,    59,    59,    60,    61,    61,    62,
      62,    62,    62,    63,    63,    64,    64,    64,    65,    66,
      68,    67,    69,    69,    70,    70,    70,    71,    71,    71,
      72,    72,    72,    72,    72,    73,    73,    73,    73,    73,
      73
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,    10,     2,     0,     5,     2,     0,     1,
       1,     1,     1,     2,     0,     1,     1,     1,     4,     3,
       0,     9,     2,     0,     3,     3,     1,     3,     3,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3
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
#line 64 "parser.y"
    {
        //  AJOUTÉ : Initialiser la table au début du programme
        initTable(&tableGlobale);
    }
#line 1208 "parser.tab.c"
    break;

  case 3: /* Program: KW_BEGIN KW_PROGRAM IDENTIFIER SEP_SEMICOLON $@1 Decls Instrs KW_END KW_PROGRAM SEP_SEMICOLON  */
#line 69 "parser.y"
    {
        (yyval.node) = createProgramNode((yyvsp[-7].str), (yyvsp[-4].node), (yyvsp[-3].node));
        root = (yyval.node);
        printf("\n✓ Program '%s' parsed successfully!\n", (yyvsp[-7].str));
        
        //  AJOUTÉ : Afficher la table des symboles à la fin
        afficherTable(&tableGlobale);
        
        free((yyvsp[-7].str));
    }
#line 1223 "parser.tab.c"
    break;

  case 4: /* Decls: Decls Decl  */
#line 83 "parser.y"
    {
        (yyval.node) = createDeclListNode((yyvsp[0].node), (yyvsp[-1].node));
    }
#line 1231 "parser.tab.c"
    break;

  case 5: /* Decls: %empty  */
#line 87 "parser.y"
    {
        (yyval.node) = NULL;
    }
#line 1239 "parser.tab.c"
    break;

  case 6: /* Decl: KW_SET IDENTIFIER Type OptInit SEP_SEMICOLON  */
#line 94 "parser.y"
    {
        //  MODIFIÉ : Ajouter le symbole à la table
        Symbole sym;
        strcpy(sym.nom, (yyvsp[-3].str));
        sym.typeSymbole = TYPE_VARIABLE;
        
        // Convertir DataType en TypeDonnee
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
        
        // Si initialisée, marquer comme telle
        if ((yyvsp[-1].node) != NULL) {
            sym.initialise = 1;
        } else {
            sym.initialise = 0;
        }
        
        // Insérer dans la table
        if (insererSymbole(&tableGlobale, sym) == -1) {
            char msg[100];
            sprintf(msg, "Variable '%s' déjà déclarée", (yyvsp[-3].str));
            yyerror(msg);
        }
        
        (yyval.node) = createDeclNode((yyvsp[-3].str), (yyvsp[-2].dtype), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1286 "parser.tab.c"
    break;

  case 7: /* OptInit: OP_EQ Expr  */
#line 140 "parser.y"
    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1294 "parser.tab.c"
    break;

  case 8: /* OptInit: %empty  */
#line 144 "parser.y"
    {
        (yyval.node) = NULL;
    }
#line 1302 "parser.tab.c"
    break;

  case 9: /* Type: KW_INTEGER  */
#line 150 "parser.y"
                { (yyval.dtype) = TYPE_INTEGER; }
#line 1308 "parser.tab.c"
    break;

  case 10: /* Type: KW_STRING  */
#line 151 "parser.y"
                { (yyval.dtype) = TYPE_STRING; }
#line 1314 "parser.tab.c"
    break;

  case 11: /* Type: KW_FLOAT  */
#line 152 "parser.y"
                { (yyval.dtype) = TYPE_FLOAT; }
#line 1320 "parser.tab.c"
    break;

  case 12: /* Type: KW_BOOLEAN  */
#line 153 "parser.y"
                 { (yyval.dtype) = TYPE_BOOLEAN; }
#line 1326 "parser.tab.c"
    break;

  case 13: /* Instrs: Instrs Instr  */
#line 158 "parser.y"
    {
        (yyval.node) = createStmtListNode((yyvsp[0].node), (yyvsp[-1].node));
    }
#line 1334 "parser.tab.c"
    break;

  case 14: /* Instrs: %empty  */
#line 162 "parser.y"
    {
        (yyval.node) = NULL;
    }
#line 1342 "parser.tab.c"
    break;

  case 15: /* Instr: Assign  */
#line 168 "parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1348 "parser.tab.c"
    break;

  case 16: /* Instr: Print  */
#line 169 "parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1354 "parser.tab.c"
    break;

  case 17: /* Instr: If  */
#line 170 "parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1360 "parser.tab.c"
    break;

  case 18: /* Assign: IDENTIFIER OP_EQ Expr SEP_SEMICOLON  */
#line 175 "parser.y"
    {
        //  AJOUTÉ : Vérifications sémantiques
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
            // Marquer comme initialisée
            sym->initialise = 1;
        }
        
        (yyval.node) = createAssignNode((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1385 "parser.tab.c"
    break;

  case 19: /* Print: KW_PRINT Expr SEP_SEMICOLON  */
#line 199 "parser.y"
    {
        (yyval.node) = createPrintNode((yyvsp[-1].node));
    }
#line 1393 "parser.tab.c"
    break;

  case 20: /* $@2: %empty  */
#line 206 "parser.y"
    {
        //  AJOUTÉ : Entrer dans une nouvelle portée
        entrerPortee(&tableGlobale);
    }
#line 1402 "parser.tab.c"
    break;

  case 21: /* If: KW_WHEN $@2 Cond KW_THEN Instrs OptElse KW_END KW_WHEN SEP_SEMICOLON  */
#line 211 "parser.y"
    {
        (yyval.node) = createIfNode((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-3].node));
        
        //  AJOUTÉ : Sortir de la portée
        sortirPortee(&tableGlobale);
    }
#line 1413 "parser.tab.c"
    break;

  case 22: /* OptElse: KW_ELSE Instrs  */
#line 221 "parser.y"
    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1421 "parser.tab.c"
    break;

  case 23: /* OptElse: %empty  */
#line 225 "parser.y"
    {
        (yyval.node) = NULL;
    }
#line 1429 "parser.tab.c"
    break;

  case 24: /* Expr: Expr OP_PLUS Term  */
#line 232 "parser.y"
    {
        (yyval.node) = createBinOpNode(AST_OP_ADD, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1437 "parser.tab.c"
    break;

  case 25: /* Expr: Expr OP_MINUS Term  */
#line 236 "parser.y"
    {
        (yyval.node) = createBinOpNode(AST_OP_SUB, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1445 "parser.tab.c"
    break;

  case 26: /* Expr: Term  */
#line 240 "parser.y"
    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1453 "parser.tab.c"
    break;

  case 27: /* Term: Term OP_MULT Factor  */
#line 247 "parser.y"
    {
        (yyval.node) = createBinOpNode(AST_OP_MUL, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1461 "parser.tab.c"
    break;

  case 28: /* Term: Term OP_DIV Factor  */
#line 251 "parser.y"
    {
        (yyval.node) = createBinOpNode(AST_OP_DIV, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1469 "parser.tab.c"
    break;

  case 29: /* Term: Factor  */
#line 255 "parser.y"
    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1477 "parser.tab.c"
    break;

  case 30: /* Factor: INT_LITERAL  */
#line 262 "parser.y"
    {
        (yyval.node) = createIntLiteralNode((yyvsp[0].ival));
    }
#line 1485 "parser.tab.c"
    break;

  case 31: /* Factor: FLOAT_LITERAL  */
#line 266 "parser.y"
    {
        (yyval.node) = createFloatLiteralNode((yyvsp[0].fval));
    }
#line 1493 "parser.tab.c"
    break;

  case 32: /* Factor: STRING_LITERAL  */
#line 270 "parser.y"
    {
        (yyval.node) = createStringLiteralNode((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1502 "parser.tab.c"
    break;

  case 33: /* Factor: IDENTIFIER  */
#line 275 "parser.y"
    {
        //  AJOUTÉ : Vérifier que la variable existe et est initialisée
        Symbole* sym = obtenirSymbole(&tableGlobale, (yyvsp[0].str));
        
        if (sym == NULL) {
            char msg[100];
            sprintf(msg, "Variable '%s' non déclarée", (yyvsp[0].str));
            yyerror(msg);
        } else if (!sym->initialise && sym->typeSymbole != TYPE_CONSTANTE) {
            printf("Attention ligne %d : variable '%s' utilisée sans initialisation\n", 
                   line_num, (yyvsp[0].str));
        }
        
        (yyval.node) = createIdentifierNode((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1523 "parser.tab.c"
    break;

  case 34: /* Factor: SEP_LPAREN Expr SEP_RPAREN  */
#line 292 "parser.y"
    {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1531 "parser.tab.c"
    break;

  case 35: /* Cond: Expr OP_EQ Expr  */
#line 299 "parser.y"
    {
        (yyval.node) = createBinOpNode(AST_OP_EQ, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1539 "parser.tab.c"
    break;

  case 36: /* Cond: Expr OP_NEQ Expr  */
#line 303 "parser.y"
    {
        (yyval.node) = createBinOpNode(AST_OP_NEQ, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1547 "parser.tab.c"
    break;

  case 37: /* Cond: Expr OP_LT Expr  */
#line 307 "parser.y"
    {
        (yyval.node) = createBinOpNode(AST_OP_LT, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1555 "parser.tab.c"
    break;

  case 38: /* Cond: Expr OP_GT Expr  */
#line 311 "parser.y"
    {
        (yyval.node) = createBinOpNode(AST_OP_GT, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1563 "parser.tab.c"
    break;

  case 39: /* Cond: Expr OP_LTE Expr  */
#line 315 "parser.y"
    {
        (yyval.node) = createBinOpNode(AST_OP_LTE, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1571 "parser.tab.c"
    break;

  case 40: /* Cond: Expr OP_GTE Expr  */
#line 319 "parser.y"
    {
        (yyval.node) = createBinOpNode(AST_OP_GTE, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1579 "parser.tab.c"
    break;


#line 1583 "parser.tab.c"

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

#line 324 "parser.y"


void yyerror(const char* s) {
    fprintf(stderr, "Erreur sémantique ligne %d, col %d: %s\n", line_num, col_num, s);
}
