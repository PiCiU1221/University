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
#line 6 "def.yy"


#include "def.tab.hh"
#include "def_globals.h"
#include "def_utils.h"

#include <string.h>
#include <stdio.h>
#include <stack>
#include <string>
#include <fstream>
#include <map>
#include <iostream>

extern "C" int yyerror(const char *msg);
extern "C" int yylex();

using namespace std;

stack<Symbol> basicStack;
ofstream threesFile;
map<string, Symbol> symbolTable;


#line 96 "def.tab.cc"

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

#include "def.tab.hh"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT_LITERAL = 3,                /* INT_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 4,              /* FLOAT_LITERAL  */
  YYSYMBOL_BOOL_LITERAL = 5,               /* BOOL_LITERAL  */
  YYSYMBOL_CHAR_LITERAL = 6,               /* CHAR_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 7,             /* STRING_LITERAL  */
  YYSYMBOL_ID = 8,                         /* ID  */
  YYSYMBOL_INT = 9,                        /* INT  */
  YYSYMBOL_FLOAT = 10,                     /* FLOAT  */
  YYSYMBOL_BOOL = 11,                      /* BOOL  */
  YYSYMBOL_CHAR = 12,                      /* CHAR  */
  YYSYMBOL_STRING = 13,                    /* STRING  */
  YYSYMBOL_PTR_INT = 14,                   /* PTR_INT  */
  YYSYMBOL_PTR_FLOAT = 15,                 /* PTR_FLOAT  */
  YYSYMBOL_IF = 16,                        /* IF  */
  YYSYMBOL_ELSE = 17,                      /* ELSE  */
  YYSYMBOL_WHILE = 18,                     /* WHILE  */
  YYSYMBOL_FOR = 19,                       /* FOR  */
  YYSYMBOL_BREAK = 20,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 21,                  /* CONTINUE  */
  YYSYMBOL_PRINT = 22,                     /* PRINT  */
  YYSYMBOL_INPUT = 23,                     /* INPUT  */
  YYSYMBOL_EQ = 24,                        /* EQ  */
  YYSYMBOL_NEQ = 25,                       /* NEQ  */
  YYSYMBOL_LT = 26,                        /* LT  */
  YYSYMBOL_LEQ = 27,                       /* LEQ  */
  YYSYMBOL_GT = 28,                        /* GT  */
  YYSYMBOL_GEQ = 29,                       /* GEQ  */
  YYSYMBOL_AND = 30,                       /* AND  */
  YYSYMBOL_OR = 31,                        /* OR  */
  YYSYMBOL_NOT = 32,                       /* NOT  */
  YYSYMBOL_INC = 33,                       /* INC  */
  YYSYMBOL_DEC = 34,                       /* DEC  */
  YYSYMBOL_ADD_ASSIGN = 35,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 36,                /* SUB_ASSIGN  */
  YYSYMBOL_MUL_ASSIGN = 37,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 38,                /* DIV_ASSIGN  */
  YYSYMBOL_NEW = 39,                       /* NEW  */
  YYSYMBOL_40_ = 40,                       /* '+'  */
  YYSYMBOL_41_ = 41,                       /* '-'  */
  YYSYMBOL_42_ = 42,                       /* '*'  */
  YYSYMBOL_43_ = 43,                       /* '/'  */
  YYSYMBOL_44_ = 44,                       /* '%'  */
  YYSYMBOL_45_ = 45,                       /* '='  */
  YYSYMBOL_46_ = 46,                       /* ';'  */
  YYSYMBOL_47_ = 47,                       /* '['  */
  YYSYMBOL_48_ = 48,                       /* ']'  */
  YYSYMBOL_49_ = 49,                       /* '('  */
  YYSYMBOL_50_ = 50,                       /* ')'  */
  YYSYMBOL_51_ = 51,                       /* '{'  */
  YYSYMBOL_52_ = 52,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 53,                  /* $accept  */
  YYSYMBOL_program = 54,                   /* program  */
  YYSYMBOL_stmt_list = 55,                 /* stmt_list  */
  YYSYMBOL_stmt = 56,                      /* stmt  */
  YYSYMBOL_dimensions = 57,                /* dimensions  */
  YYSYMBOL_for_init = 58,                  /* for_init  */
  YYSYMBOL_for_assignment = 59,            /* for_assignment  */
  YYSYMBOL_for_expr = 60,                  /* for_expr  */
  YYSYMBOL_61_1 = 61,                      /* $@1  */
  YYSYMBOL_for_stmt = 62,                  /* for_stmt  */
  YYSYMBOL_if_stmt = 63,                   /* if_stmt  */
  YYSYMBOL_64_2 = 64,                      /* $@2  */
  YYSYMBOL_optional_else = 65,             /* optional_else  */
  YYSYMBOL_66_3 = 66,                      /* $@3  */
  YYSYMBOL_block = 67,                     /* block  */
  YYSYMBOL_type = 68,                      /* type  */
  YYSYMBOL_declaration = 69,               /* declaration  */
  YYSYMBOL_declaration_for_init = 70,      /* declaration_for_init  */
  YYSYMBOL_index_list = 71,                /* index_list  */
  YYSYMBOL_assignment = 72,                /* assignment  */
  YYSYMBOL_print_stmt = 73,                /* print_stmt  */
  YYSYMBOL_input_stmt = 74,                /* input_stmt  */
  YYSYMBOL_expr = 75,                      /* expr  */
  YYSYMBOL_term = 76,                      /* term  */
  YYSYMBOL_factor = 77                     /* factor  */
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
#define YYFINAL  42
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   320

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  137

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


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
       2,     2,     2,     2,     2,     2,     2,    44,     2,     2,
      49,    50,    42,    40,     2,    41,     2,    43,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    46,
       2,    45,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    47,     2,    48,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,    52,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    75,    75,    81,    82,    86,    87,    88,    89,    90,
      91,    92,    96,   100,   107,   108,   112,   113,   119,   119,
     123,   129,   128,   137,   136,   139,   143,   144,   148,   149,
     150,   151,   152,   153,   154,   158,   161,   165,   175,   181,
     186,   194,   197,   203,   207,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   228,   229,   230,   231,
     235,   238,   243,   247,   250,   253,   256,   260,   265
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
  "\"end of file\"", "error", "\"invalid token\"", "INT_LITERAL",
  "FLOAT_LITERAL", "BOOL_LITERAL", "CHAR_LITERAL", "STRING_LITERAL", "ID",
  "INT", "FLOAT", "BOOL", "CHAR", "STRING", "PTR_INT", "PTR_FLOAT", "IF",
  "ELSE", "WHILE", "FOR", "BREAK", "CONTINUE", "PRINT", "INPUT", "EQ",
  "NEQ", "LT", "LEQ", "GT", "GEQ", "AND", "OR", "NOT", "INC", "DEC",
  "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "NEW", "'+'",
  "'-'", "'*'", "'/'", "'%'", "'='", "';'", "'['", "']'", "'('", "')'",
  "'{'", "'}'", "$accept", "program", "stmt_list", "stmt", "dimensions",
  "for_init", "for_assignment", "for_expr", "$@1", "for_stmt", "if_stmt",
  "$@2", "optional_else", "$@3", "block", "type", "declaration",
  "declaration_for_init", "index_list", "assignment", "print_stmt",
  "input_stmt", "expr", "term", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-128)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     123,  -128,  -128,  -128,  -128,  -128,     8,  -128,  -128,  -128,
    -128,  -128,  -128,  -128,   -45,   -27,   -11,    -3,     9,    54,
     123,  -128,  -128,  -128,    48,    11,    18,    19,    22,   261,
      32,  -128,  -128,     9,     9,     2,     9,    98,     9,    64,
      12,   124,  -128,  -128,    16,  -128,  -128,  -128,  -128,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,  -128,
       9,     9,     9,   269,   186,     9,     9,   151,    24,    45,
      84,  -128,  -128,   159,    65,    73,  -128,     3,   118,    77,
      32,    32,    32,    32,    32,    32,    32,    32,    32,    32,
    -128,  -128,  -128,  -128,   269,   211,  -128,     2,  -128,    95,
    -128,  -128,    89,   269,    93,   140,  -128,    74,   101,     9,
       9,    97,  -128,   108,   123,  -128,   141,   149,   269,   269,
       9,  -128,    21,  -128,  -128,    15,   109,   236,  -128,    74,
    -128,     9,    74,  -128,  -128,   269,  -128
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    63,    65,    64,    66,    67,    62,    28,    29,    30,
      31,    32,    33,    34,     0,     0,     0,     0,     0,     0,
       2,     4,    11,    10,     0,     0,     0,     0,     0,     0,
      55,    59,    61,     0,     0,    60,     0,     0,     0,     0,
      62,     0,     1,     3,     0,     5,     6,     8,     9,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     7,
       0,     0,     0,    41,     0,     0,     0,     0,     0,     0,
       0,    14,    15,     0,     0,    60,    68,     0,     0,    36,
      47,    48,    49,    50,    51,    52,    53,    54,    45,    46,
      56,    57,    58,    40,    42,     0,    21,     0,    18,     0,
      43,    44,     0,    35,     0,     0,    39,     0,     0,     0,
       0,     0,    13,     0,     0,    27,    25,     0,    19,    38,
       0,    12,     0,    23,    22,     0,     0,     0,    26,     0,
      17,     0,     0,    37,    24,    16,    20
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -128,  -128,    46,     0,  -128,  -128,  -128,  -128,  -128,  -128,
    -128,  -128,  -128,  -128,  -127,   -36,  -128,  -128,    -1,   125,
    -128,  -128,   -15,   262,    57
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    19,    20,   115,    79,    69,   126,   108,   109,    22,
      23,   107,   124,   129,   116,    24,    25,    71,    35,    26,
      27,    28,    29,    30,    31
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      21,    70,   134,    41,    36,   136,     1,     2,     3,     4,
       5,    40,     1,     2,     3,     4,     5,    40,    63,    64,
      43,    67,    37,    73,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    38,    75,
      15,    32,   102,    16,    17,    32,    39,    65,   130,    66,
      94,    95,    18,    33,    42,    34,    44,    45,    18,    34,
     131,    77,   103,    78,    46,    47,   111,    97,    48,    33,
      18,    34,    74,   128,    60,    61,    62,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    98,    99,    15,   118,   119,    16,    17,     7,     8,
       9,    10,    11,    12,    13,   127,    68,     7,     8,     9,
      10,    11,    12,    13,    21,   101,   135,    90,    91,    92,
      66,   104,    43,    18,   105,   114,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
     110,   112,    15,   113,   120,    16,    17,   117,    49,    50,
      51,    52,    53,    54,    55,    56,   121,   125,   123,   132,
     122,     0,    72,     0,    57,    58,     0,     0,     0,     0,
       0,     0,    18,     0,    76,    49,    50,    51,    52,    53,
      54,    55,    56,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,     0,     0,     0,     0,     0,     0,    57,
      58,    96,     0,     0,     0,     0,     0,     0,     0,   100,
      49,    50,    51,    52,    53,    54,    55,    56,     0,     0,
       0,     0,     0,     0,     0,     0,    57,    58,     0,     0,
       0,     0,     0,     0,    93,    49,    50,    51,    52,    53,
      54,    55,    56,     0,     0,     0,     0,     0,     0,     0,
       0,    57,    58,     0,     0,     0,     0,     0,     0,   106,
      49,    50,    51,    52,    53,    54,    55,    56,     0,     0,
       0,     0,     0,     0,     0,     0,    57,    58,     0,     0,
       0,     0,     0,     0,   133,    49,    50,    51,    52,    53,
      54,    55,    56,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,     0,     0,     0,     0,    59,     0,    57,
      58,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89
};

static const yytype_int16 yycheck[] =
{
       0,    37,   129,    18,    49,   132,     3,     4,     5,     6,
       7,     8,     3,     4,     5,     6,     7,     8,    33,    34,
      20,    36,    49,    38,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    49,    40,
      19,    33,    39,    22,    23,    33,    49,    45,    33,    47,
      65,    66,    49,    45,     0,    47,     8,    46,    49,    47,
      45,    45,    77,    47,    46,    46,   102,    68,    46,    45,
      49,    47,     8,    52,    42,    43,    44,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    46,     8,    19,   109,   110,    22,    23,     9,    10,
      11,    12,    13,    14,    15,   120,     8,     9,    10,    11,
      12,    13,    14,    15,   114,    50,   131,    60,    61,    62,
      47,     3,   122,    49,    47,    51,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      45,    48,    19,     3,    47,    22,    23,    46,    24,    25,
      26,    27,    28,    29,    30,    31,    48,     8,    17,    50,
     114,    -1,    37,    -1,    40,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    50,    24,    25,    26,    27,    28,
      29,    30,    31,    24,    25,    26,    27,    28,    29,    30,
      31,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      41,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    24,    25,    26,    27,    28,
      29,    30,    31,    24,    25,    26,    27,    28,    29,    30,
      31,    40,    41,    -1,    -1,    -1,    -1,    46,    -1,    40,
      41,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    19,    22,    23,    49,    54,
      55,    56,    62,    63,    68,    69,    72,    73,    74,    75,
      76,    77,    33,    45,    47,    71,    49,    49,    49,    49,
       8,    75,     0,    56,     8,    46,    46,    46,    46,    24,
      25,    26,    27,    28,    29,    30,    31,    40,    41,    46,
      42,    43,    44,    75,    75,    45,    47,    75,     8,    58,
      68,    70,    72,    75,     8,    71,    50,    45,    47,    57,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      77,    77,    77,    48,    75,    75,    50,    71,    46,     8,
      50,    50,    39,    75,     3,    47,    48,    64,    60,    61,
      45,    68,    48,     3,    51,    56,    67,    46,    75,    75,
      47,    48,    55,    17,    65,     8,    59,    75,    52,    66,
      33,    45,    50,    48,    67,    75,    67
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    55,    56,    56,    56,    56,    56,
      56,    56,    57,    57,    58,    58,    59,    59,    61,    60,
      62,    64,    63,    66,    65,    65,    67,    67,    68,    68,
      68,    68,    68,    68,    68,    69,    69,    69,    70,    71,
      71,    72,    72,    73,    74,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    76,    76,    76,    76,
      77,    77,    77,    77,    77,    77,    77,    77,    77
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     2,     2,     2,     2,
       1,     1,     4,     3,     1,     1,     3,     2,     0,     2,
       9,     0,     7,     0,     3,     0,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     8,     4,     4,
       3,     3,     4,     4,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     3,     3,     3,     1,
       2,     2,     1,     1,     1,     1,     1,     1,     3
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
  case 2: /* program: stmt_list  */
#line 75 "def.yy"
                    {
            printf("\nCompilation complete!\n\n");
        }
#line 1287 "def.tab.cc"
    break;

  case 12: /* dimensions: dimensions '[' INT_LITERAL ']'  */
#line 96 "def.yy"
                                     {
            (yyval.vec_int) = (yyvsp[-3].vec_int);
            (yyval.vec_int)->push_back((yyvsp[-1].ival));
        }
#line 1296 "def.tab.cc"
    break;

  case 13: /* dimensions: '[' INT_LITERAL ']'  */
#line 100 "def.yy"
                          {
            (yyval.vec_int) = new vector<int>();
            (yyval.vec_int)->push_back((yyvsp[-1].ival));
        }
#line 1305 "def.tab.cc"
    break;

  case 16: /* for_assignment: ID '=' expr  */
#line 112 "def.yy"
                      { basicStack.push({(yyvsp[-2].sval)}); }
#line 1311 "def.tab.cc"
    break;

  case 17: /* for_assignment: ID INC  */
#line 113 "def.yy"
             {
            handle_increment((yyvsp[-1].sval));
        }
#line 1319 "def.tab.cc"
    break;

  case 18: /* $@1: %empty  */
#line 119 "def.yy"
      { write_for_label(); }
#line 1325 "def.tab.cc"
    break;

  case 19: /* for_expr: $@1 expr  */
#line 119 "def.yy"
                                  { write_for_condition(); }
#line 1331 "def.tab.cc"
    break;

  case 20: /* for_stmt: FOR '(' for_init ';' for_expr ';' for_assignment ')' block  */
#line 124 "def.yy"
        { write_for_end(); }
#line 1337 "def.tab.cc"
    break;

  case 21: /* $@2: %empty  */
#line 129 "def.yy"
        { write_if_condition(); }
#line 1343 "def.tab.cc"
    break;

  case 22: /* if_stmt: IF '(' expr ')' $@2 block optional_else  */
#line 132 "def.yy"
        { write_if_end(); }
#line 1349 "def.tab.cc"
    break;

  case 23: /* $@3: %empty  */
#line 137 "def.yy"
        { write_else_start(); }
#line 1355 "def.tab.cc"
    break;

  case 28: /* type: INT  */
#line 148 "def.yy"
                { basicStack.push({"TYPE", "INT"}); }
#line 1361 "def.tab.cc"
    break;

  case 29: /* type: FLOAT  */
#line 149 "def.yy"
                { basicStack.push({"TYPE", "FLOAT"}); }
#line 1367 "def.tab.cc"
    break;

  case 30: /* type: BOOL  */
#line 150 "def.yy"
                { basicStack.push({"TYPE", "BOOL"}); }
#line 1373 "def.tab.cc"
    break;

  case 31: /* type: CHAR  */
#line 151 "def.yy"
                { basicStack.push({"TYPE", "CHAR"}); }
#line 1379 "def.tab.cc"
    break;

  case 32: /* type: STRING  */
#line 152 "def.yy"
                { basicStack.push({"TYPE", "STRING"}); }
#line 1385 "def.tab.cc"
    break;

  case 33: /* type: PTR_INT  */
#line 153 "def.yy"
                { basicStack.push({"TYPE", "PTR_INT"}); }
#line 1391 "def.tab.cc"
    break;

  case 34: /* type: PTR_FLOAT  */
#line 154 "def.yy"
                { basicStack.push({"TYPE", "PTR_FLOAT"}); }
#line 1397 "def.tab.cc"
    break;

  case 35: /* declaration: type ID '=' expr  */
#line 158 "def.yy"
                       {
            process_declaration((yyvsp[-2].sval));
        }
#line 1405 "def.tab.cc"
    break;

  case 36: /* declaration: type ID dimensions  */
#line 161 "def.yy"
                         { 
            Symbol typeSymbol = basicStack.top(); basicStack.pop();
            process_array_declaration(typeSymbol.type, (yyvsp[-1].sval), (yyvsp[0].vec_int));
        }
#line 1414 "def.tab.cc"
    break;

  case 37: /* declaration: type ID '=' NEW type '[' expr ']'  */
#line 165 "def.yy"
                                        {
            Symbol sizeSym = basicStack.top(); basicStack.pop();
            Symbol typeRight = basicStack.top(); basicStack.pop();
            Symbol typeLeft = basicStack.top(); basicStack.pop();

            process_dynamic_array_declaration(typeLeft.type, (yyvsp[-6].sval), sizeSym);
        }
#line 1426 "def.tab.cc"
    break;

  case 38: /* declaration_for_init: type ID '=' expr  */
#line 175 "def.yy"
                       { 
            process_declaration_and_assignment((yyvsp[-2].sval));
        }
#line 1434 "def.tab.cc"
    break;

  case 39: /* index_list: index_list '[' expr ']'  */
#line 181 "def.yy"
                              {
            Symbol idx = basicStack.top(); basicStack.pop();
            (yyvsp[-3].vec_sym)->push_back(idx);
            (yyval.vec_sym) = (yyvsp[-3].vec_sym);
        }
#line 1444 "def.tab.cc"
    break;

  case 40: /* index_list: '[' expr ']'  */
#line 186 "def.yy"
                   {
            Symbol idx = basicStack.top(); basicStack.pop();
            (yyval.vec_sym) = new vector<Symbol>();
            (yyval.vec_sym)->push_back(idx);
        }
#line 1454 "def.tab.cc"
    break;

  case 41: /* assignment: ID '=' expr  */
#line 194 "def.yy"
                      {
            code_write_assignment((yyvsp[-2].sval));
        }
#line 1462 "def.tab.cc"
    break;

  case 42: /* assignment: ID index_list '=' expr  */
#line 197 "def.yy"
                             {
            code_write_array_element_assignment((yyvsp[-3].sval), (yyvsp[-2].vec_sym));
        }
#line 1470 "def.tab.cc"
    break;

  case 43: /* print_stmt: PRINT '(' expr ')'  */
#line 203 "def.yy"
                         { process_and_print_nonvariables(); }
#line 1476 "def.tab.cc"
    break;

  case 44: /* input_stmt: INPUT '(' ID ')'  */
#line 207 "def.yy"
                       {
            string varName = (yyvsp[-1].sval);
            string varType = symbolTable[varName].type;
            threesFile << "INPUT " << varName << "\n";
        }
#line 1486 "def.tab.cc"
    break;

  case 45: /* expr: expr '+' term  */
#line 214 "def.yy"
                               { code_write("+"); }
#line 1492 "def.tab.cc"
    break;

  case 46: /* expr: expr '-' term  */
#line 215 "def.yy"
                               { code_write("-"); }
#line 1498 "def.tab.cc"
    break;

  case 47: /* expr: expr EQ term  */
#line 216 "def.yy"
                               { code_write("=="); }
#line 1504 "def.tab.cc"
    break;

  case 48: /* expr: expr NEQ term  */
#line 217 "def.yy"
                               { code_write("!="); }
#line 1510 "def.tab.cc"
    break;

  case 49: /* expr: expr LT term  */
#line 218 "def.yy"
                               { code_write("<"); }
#line 1516 "def.tab.cc"
    break;

  case 50: /* expr: expr LEQ term  */
#line 219 "def.yy"
                               { code_write("<="); }
#line 1522 "def.tab.cc"
    break;

  case 51: /* expr: expr GT term  */
#line 220 "def.yy"
                               { code_write(">"); }
#line 1528 "def.tab.cc"
    break;

  case 52: /* expr: expr GEQ term  */
#line 221 "def.yy"
                               { code_write(">="); }
#line 1534 "def.tab.cc"
    break;

  case 53: /* expr: expr AND term  */
#line 222 "def.yy"
                               { code_write("&&"); }
#line 1540 "def.tab.cc"
    break;

  case 54: /* expr: expr OR term  */
#line 223 "def.yy"
                               { code_write("||"); }
#line 1546 "def.tab.cc"
    break;

  case 56: /* term: term '*' factor  */
#line 228 "def.yy"
                        { code_write("*"); }
#line 1552 "def.tab.cc"
    break;

  case 57: /* term: term '/' factor  */
#line 229 "def.yy"
                        { code_write("/"); }
#line 1558 "def.tab.cc"
    break;

  case 58: /* term: term '%' factor  */
#line 230 "def.yy"
                        { code_write("%"); }
#line 1564 "def.tab.cc"
    break;

  case 60: /* factor: ID index_list  */
#line 235 "def.yy"
                    {
            process_array_value((yyvsp[-1].sval), (yyvsp[0].vec_sym));
        }
#line 1572 "def.tab.cc"
    break;

  case 61: /* factor: ID INC  */
#line 238 "def.yy"
             {
            string varName = (yyvsp[-1].sval);
            threesFile << varName + " = " + varName + " + 1" << endl;
            basicStack.push({varName, symbolTable[varName].type});
        }
#line 1582 "def.tab.cc"
    break;

  case 62: /* factor: ID  */
#line 243 "def.yy"
         {
            string varName = (yyvsp[0].sval);
            basicStack.push({varName, symbolTable[varName].type});
        }
#line 1591 "def.tab.cc"
    break;

  case 63: /* factor: INT_LITERAL  */
#line 247 "def.yy"
                  {
            basicStack.push({to_string((yyvsp[0].ival)), "INT", (yyvsp[0].ival), 0.0f});
        }
#line 1599 "def.tab.cc"
    break;

  case 64: /* factor: BOOL_LITERAL  */
#line 250 "def.yy"
                   {
            basicStack.push({((yyvsp[0].bval) ? "true" : "false"), "BOOL", (yyvsp[0].bval), 0.0f});
        }
#line 1607 "def.tab.cc"
    break;

  case 65: /* factor: FLOAT_LITERAL  */
#line 253 "def.yy"
                    {
            basicStack.push({to_string((yyvsp[0].fval)), "FLOAT", 0, (yyvsp[0].fval)});
        }
#line 1615 "def.tab.cc"
    break;

  case 66: /* factor: CHAR_LITERAL  */
#line 256 "def.yy"
                   {
            string charStr(1, (yyvsp[0].cval));
            basicStack.push({charStr, "CHAR", 0, 0.0f, charStr});
        }
#line 1624 "def.tab.cc"
    break;

  case 67: /* factor: STRING_LITERAL  */
#line 260 "def.yy"
                     {
            string quotedStr = "\"" + string((yyvsp[0].sval)) + "\"";
            basicStack.push({quotedStr, "STRING", 0, 0.0f, quotedStr});
            free((yyvsp[0].sval));
        }
#line 1634 "def.tab.cc"
    break;


#line 1638 "def.tab.cc"

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

#line 268 "def.yy"


int main(int argc, char *argv[])
{
    threesFile.open("threes.txt");
	yyparse();
    threesFile.close();
    generateMIPS("threes.txt", "output.asm", symbolTable);
	return 0;
}
