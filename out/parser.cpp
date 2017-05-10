/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TLPAREN = 258,
     TRPAREN = 259,
     TLBRACE = 260,
     TRBRACE = 261,
     TLBRACKET = 262,
     TRBRACKET = 263,
     TCOMMA = 264,
     TSEMICOLON = 265,
     TDOT = 266,
     TINT = 267,
     TCHAR = 268,
     TBOOL = 269,
     TFLOAT = 270,
     TSTRING = 271,
     TVOID = 272,
     TASG = 273,
     TEQ = 274,
     TNEQ = 275,
     TGT = 276,
     TLT = 277,
     TGE = 278,
     TLE = 279,
     TIF = 280,
     TELSE = 281,
     TELIF = 282,
     TWHILE = 283,
     TFOR = 284,
     TDO = 285,
     TPLUSPLUS = 286,
     TRETURN = 287,
     TBREAK = 288,
     TCONTINUE = 289,
     TAND = 290,
     TOR = 291,
     TNOT = 292,
     TPLUS = 293,
     TMINUS = 294,
     TMULT = 295,
     TDIV = 296,
     TSTRING_LIT = 297,
     TCHAR_LIT = 298,
     WHITE_SPACE = 299,
     TID = 300,
     TNUM = 301
   };
#endif
/* Tokens.  */
#define TLPAREN 258
#define TRPAREN 259
#define TLBRACE 260
#define TRBRACE 261
#define TLBRACKET 262
#define TRBRACKET 263
#define TCOMMA 264
#define TSEMICOLON 265
#define TDOT 266
#define TINT 267
#define TCHAR 268
#define TBOOL 269
#define TFLOAT 270
#define TSTRING 271
#define TVOID 272
#define TASG 273
#define TEQ 274
#define TNEQ 275
#define TGT 276
#define TLT 277
#define TGE 278
#define TLE 279
#define TIF 280
#define TELSE 281
#define TELIF 282
#define TWHILE 283
#define TFOR 284
#define TDO 285
#define TPLUSPLUS 286
#define TRETURN 287
#define TBREAK 288
#define TCONTINUE 289
#define TAND 290
#define TOR 291
#define TNOT 292
#define TPLUS 293
#define TMINUS 294
#define TMULT 295
#define TDIV 296
#define TSTRING_LIT 297
#define TCHAR_LIT 298
#define WHITE_SPACE 299
#define TID 300
#define TNUM 301




/* Copy the first part of user declarations.  */
#line 1 "parser.y"


#include <cstdio>
#include <iostream>
#include <string>
#include "node.cpp"
#include "nodevalue.h"


Program * program;

extern int yylex();
void yyerror(const char *s) { printf("ERROR: %sn", s); }


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 17 "parser.y"
{
    int token;
    int intVal;
    char charVal;
    double floatVal;
    std::string* stringVal;
    bool boolVal;
    Node * node;
    NodeValue * nodeVal;
}
/* Line 193 of yacc.c.  */
#line 214 "parser.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 227 "parser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   214

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNRULES -- Number of states.  */
#define YYNSTATES  164

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      45,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    10,    12,    19,    21,    23,
      25,    27,    29,    31,    35,    36,    39,    40,    44,    46,
      48,    52,    55,    56,    58,    60,    62,    64,    66,    68,
      70,    72,    74,    76,    78,    81,    84,    89,    94,    95,
      97,    99,   102,   103,   105,   107,   109,   111,   113,   116,
     120,   123,   125,   127,   130,   131,   135,   139,   141,   143,
     145,   147,   149,   151,   153,   155,   157,   162,   163,   168,
     171,   174,   175,   179,   186,   189,   196,   197,   199,   203,
     207,   210,   214,   216,   218,   222,   224,   226,   228,   230,
     232,   234,   237,   242,   248,   254,   258,   261,   263
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    50,    49,    -1,    50,    49,    -1,    -1,
      51,    -1,    52,    45,     3,    53,     4,    56,    -1,    12,
      -1,    13,    -1,    14,    -1,    15,    -1,    16,    -1,    17,
      -1,    52,    45,    54,    -1,    -1,     9,    53,    -1,    -1,
       5,    57,     6,    -1,    55,    -1,    10,    -1,    58,    10,
      57,    -1,    59,    57,    -1,    -1,    61,    -1,    78,    -1,
      88,    -1,    89,    -1,    60,    -1,    75,    -1,    33,    -1,
      34,    -1,    79,    -1,    84,    -1,    86,    -1,    66,    31,
      -1,    31,    66,    -1,    52,    45,    62,    64,    -1,     7,
      63,     8,    62,    -1,    -1,    46,    -1,    71,    -1,    18,
      65,    -1,    -1,    71,    -1,    67,    -1,    81,    -1,    42,
      -1,    43,    -1,    45,    74,    -1,     5,    68,     6,    -1,
      69,    70,    -1,    71,    -1,    67,    -1,     9,    68,    -1,
      -1,    71,    73,    71,    -1,     3,    71,     4,    -1,    72,
      -1,    66,    -1,    75,    -1,    46,    -1,    60,    -1,    38,
      -1,    39,    -1,    40,    -1,    41,    -1,     7,    63,     8,
      74,    -1,    -1,    45,     3,    76,     4,    -1,    65,    77,
      -1,     9,    76,    -1,    -1,    66,    18,    65,    -1,    25,
       3,    81,     4,    55,    80,    -1,    26,    55,    -1,    27,
       3,    81,     4,    55,    80,    -1,    -1,    82,    -1,    81,
      35,    81,    -1,    81,    36,    81,    -1,    37,    81,    -1,
       3,    81,     4,    -1,    66,    -1,    75,    -1,    71,    83,
      71,    -1,    19,    -1,    20,    -1,    21,    -1,    22,    -1,
      23,    -1,    24,    -1,    85,    56,    -1,    28,     3,    81,
       4,    -1,    29,     3,    87,     4,    56,    -1,    61,    10,
      81,    10,    71,    -1,    30,    55,    85,    -1,    32,    90,
      -1,    71,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   132,   132,   140,   145,   150,   156,   165,   168,   171,
     174,   177,   180,   186,   194,   199,   202,   207,   212,   215,
     220,   226,   231,   236,   239,   242,   245,   248,   251,   254,
     257,   262,   265,   268,   273,   277,   283,   292,   297,   302,
     306,   311,   314,   319,   322,   325,   328,   331,   336,   343,
     348,   355,   358,   363,   366,   371,   376,   379,   384,   385,
     386,   387,   391,   392,   393,   394,   397,   402,   407,   414,
     421,   424,   429,   436,   444,   447,   453,   458,   461,   466,
     471,   476,   479,   482,   487,   494,   495,   496,   497,   498,
     499,   502,   509,   514,   521,   529,   536,   542,   545
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TLPAREN", "TRPAREN", "TLBRACE",
  "TRBRACE", "TLBRACKET", "TRBRACKET", "TCOMMA", "TSEMICOLON", "TDOT",
  "TINT", "TCHAR", "TBOOL", "TFLOAT", "TSTRING", "TVOID", "TASG", "TEQ",
  "TNEQ", "TGT", "TLT", "TGE", "TLE", "TIF", "TELSE", "TELIF", "TWHILE",
  "TFOR", "TDO", "TPLUSPLUS", "TRETURN", "TBREAK", "TCONTINUE", "TAND",
  "TOR", "TNOT", "TPLUS", "TMINUS", "TMULT", "TDIV", "TSTRING_LIT",
  "TCHAR_LIT", "WHITE_SPACE", "TID", "TNUM", "$accept", "program",
  "otherDeclarations", "declaration", "function", "typeId", "argList",
  "otherArgs", "body", "bodyOrSemi", "operatorBlock", "operatorSC",
  "moperator", "increment", "varDecl", "arrayDim", "dim", "init",
  "rightPartExpr", "leftPartExpr", "arrayConst", "arrayItems", "arrayItem",
  "otherArrayItems", "expr", "term", "arithOp", "indexing", "funCall",
  "paramList", "otherParams", "assignment", "conditional", "elseBlock",
  "condition", "comparison", "compare", "whileLoop", "whileHeader",
  "forLoop", "forInit", "postLoop", "mreturn", "exprOrNothing", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    49,    49,    50,    51,    52,    52,    52,
      52,    52,    52,    53,    53,    54,    54,    55,    56,    56,
      57,    57,    57,    58,    58,    58,    58,    58,    58,    58,
      58,    59,    59,    59,    60,    60,    61,    62,    62,    63,
      63,    64,    64,    65,    65,    65,    65,    65,    66,    67,
      68,    69,    69,    70,    70,    71,    71,    71,    72,    72,
      72,    72,    73,    73,    73,    73,    74,    74,    75,    76,
      77,    77,    78,    79,    80,    80,    80,    81,    81,    81,
      81,    81,    81,    81,    82,    83,    83,    83,    83,    83,
      83,    84,    85,    86,    87,    88,    89,    90,    90
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     0,     1,     6,     1,     1,     1,
       1,     1,     1,     3,     0,     2,     0,     3,     1,     1,
       3,     2,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     4,     4,     0,     1,
       1,     2,     0,     1,     1,     1,     1,     1,     2,     3,
       2,     1,     1,     2,     0,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     0,     4,     2,
       2,     0,     3,     6,     2,     6,     0,     1,     3,     3,
       2,     3,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     2,     4,     5,     5,     3,     2,     1,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     7,     8,     9,    10,    11,    12,     0,     4,     5,
       0,     1,     2,     4,     0,     3,    14,     0,     0,    16,
       0,    14,    13,    22,    19,    18,     6,    15,     0,     0,
       0,     0,     0,    98,    29,    30,    67,     0,     0,     0,
      22,    27,    23,     0,    28,    24,    31,    32,     0,    33,
      25,    26,     0,     0,     0,     0,    67,    35,     0,    60,
      61,    58,    97,    57,    59,    96,     0,     0,    48,    38,
      17,    22,    21,     0,    34,    91,     0,     0,    58,     0,
      59,     0,    77,     0,     0,     0,    95,     0,    62,    63,
      64,    65,     0,     0,    46,    47,    71,    44,    43,     0,
      45,    60,     0,    40,     0,    42,    20,    72,     0,     0,
      80,    85,    86,    87,    88,    89,    90,     0,     0,     0,
       0,    92,     0,     0,    56,    55,    52,     0,    54,    51,
       0,    69,    68,    67,     0,     0,    36,    81,    84,    76,
      78,    79,     0,    93,    49,     0,    50,    70,    66,    38,
      41,     0,     0,    73,     0,    53,    37,    74,     0,    94,
       0,     0,    76,    75
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,    12,    13,     9,    37,    18,    22,    25,    26,
      38,    39,    40,    60,    42,   105,   102,   136,    96,    78,
      97,   127,   128,   146,    79,    63,    92,    68,    80,    99,
     131,    45,    46,   153,   100,    82,   117,    47,    48,    49,
      85,    50,    51,    65
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -91
static const yytype_int16 yypact[] =
{
     185,   -91,   -91,   -91,   -91,   -91,   -91,    21,   185,   -91,
      -9,   -91,   -91,   185,    31,   -91,   185,    -7,    37,    36,
      10,   185,   -91,   140,   -91,   -91,   -91,   -91,    44,    46,
      61,    63,    35,    82,   -91,   -91,    20,    39,    60,    87,
     140,   -91,   -91,    -5,   -91,   -91,   -91,   -91,    10,   -91,
     -91,   -91,    72,    72,   185,    54,    91,   -91,    82,   -91,
     -91,    75,   165,   -91,   -91,   -91,    62,    92,   -91,   103,
     -91,   140,   -91,    62,   -91,   -91,    72,    72,    55,   172,
      -3,     4,   -91,    18,   101,   112,   -91,   110,   -91,   -91,
     -91,   -91,    82,    11,   -91,   -91,   120,   -91,   172,   115,
      65,   113,   124,   165,    92,   116,   -91,   -91,   122,   143,
      65,   -91,   -91,   -91,   -91,   -91,   -91,    82,    63,    72,
      72,   -91,    72,    10,   -91,   165,   -91,   130,   131,   165,
      62,   -91,   -91,    91,   151,    62,   -91,   -91,   165,    -2,
      65,    65,    52,   -91,   -91,    11,   -91,   -91,   -91,   103,
     -91,    63,   161,   -91,    82,   -91,   -91,   -91,    72,   165,
     154,    63,    -2,   -91
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -91,   -91,   153,   176,   -91,   167,   156,   -91,   -26,   -44,
     -11,   -91,   -91,   -12,   127,    33,    80,   -91,   -72,   -23,
     -90,    41,   -91,   -91,   -15,   -91,   -91,    74,   -21,    57,
     -91,   -91,   -91,    47,   -46,   -91,   -91,   -91,   159,   -91,
     -91,   -91,   -91,   -91
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -84
static const yytype_int16 yytable[] =
{
      43,   107,    44,   126,    75,    55,    81,    83,   118,    57,
      61,    41,    64,    73,    58,    23,    93,    43,    62,    44,
      24,    11,   121,    66,   151,   152,    74,    67,    41,    72,
     109,   110,   -83,   -83,    16,    61,    14,    64,    19,   119,
     120,    20,    32,    87,    61,    21,    64,    52,    43,    53,
      44,    98,   103,   119,   120,   126,    36,    59,    98,    41,
     106,   108,   154,   150,    54,    76,    70,    93,    23,    61,
      61,    64,    64,   140,   141,    76,   142,   125,   129,   143,
      56,    61,    29,    64,    69,    58,    74,   119,   120,   103,
     -82,   -82,   139,    32,    61,    58,    64,    71,    67,    77,
     119,   120,   138,    32,    94,    95,    74,    36,    59,    77,
     104,   122,   160,    32,   124,    98,   123,    36,    59,   132,
      98,   -39,    61,    32,    64,   157,   124,    36,    59,   130,
     129,    61,   133,    64,   135,   162,   144,    36,   101,   159,
     145,   111,   112,   113,   114,   115,   116,   137,    88,    89,
      90,    91,     1,     2,     3,     4,     5,     6,   161,   149,
      88,    89,    90,    91,   158,    28,    15,    10,    29,    30,
      31,    32,    33,    34,    35,    10,     8,    27,   119,   120,
      10,    84,   156,    17,   134,    36,   155,   147,    17,   119,
     120,   111,   112,   113,   114,   115,   116,     1,     2,     3,
       4,     5,     6,    88,    89,    90,    91,   148,     0,   163,
      88,    89,    90,    91,    86
};

static const yytype_int16 yycheck[] =
{
      23,    73,    23,    93,    48,    31,    52,    53,     4,    32,
      33,    23,    33,    18,     3,     5,     5,    40,    33,    40,
      10,     0,     4,     3,    26,    27,    31,     7,    40,    40,
      76,    77,    35,    36,     3,    58,    45,    58,    45,    35,
      36,     4,    31,    58,    67,     9,    67,     3,    71,     3,
      71,    66,    67,    35,    36,   145,    45,    46,    73,    71,
      71,    76,    10,   135,     3,     3,     6,     5,     5,    92,
      93,    92,    93,   119,   120,     3,   122,    92,    93,   123,
      45,   104,    28,   104,    45,     3,    31,    35,    36,   104,
      35,    36,   118,    31,   117,     3,   117,    10,     7,    37,
      35,    36,   117,    31,    42,    43,    31,    45,    46,    37,
       7,    10,   158,    31,     4,   130,     4,    45,    46,     4,
     135,     8,   145,    31,   145,   151,     4,    45,    46,     9,
     145,   154,     8,   154,    18,   161,     6,    45,    46,   154,
       9,    19,    20,    21,    22,    23,    24,     4,    38,    39,
      40,    41,    12,    13,    14,    15,    16,    17,     4,     8,
      38,    39,    40,    41,     3,    25,    13,     0,    28,    29,
      30,    31,    32,    33,    34,     8,     0,    21,    35,    36,
      13,    54,   149,    16,   104,    45,   145,   130,    21,    35,
      36,    19,    20,    21,    22,    23,    24,    12,    13,    14,
      15,    16,    17,    38,    39,    40,    41,   133,    -1,   162,
      38,    39,    40,    41,    55
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    12,    13,    14,    15,    16,    17,    48,    50,    51,
      52,     0,    49,    50,    45,    49,     3,    52,    53,    45,
       4,     9,    54,     5,    10,    55,    56,    53,    25,    28,
      29,    30,    31,    32,    33,    34,    45,    52,    57,    58,
      59,    60,    61,    66,    75,    78,    79,    84,    85,    86,
      88,    89,     3,     3,     3,    55,    45,    66,     3,    46,
      60,    66,    71,    72,    75,    90,     3,     7,    74,    45,
       6,    10,    57,    18,    31,    56,     3,    37,    66,    71,
      75,    81,    82,    81,    61,    87,    85,    71,    38,    39,
      40,    41,    73,     5,    42,    43,    65,    67,    71,    76,
      81,    46,    63,    71,     7,    62,    57,    65,    71,    81,
      81,    19,    20,    21,    22,    23,    24,    83,     4,    35,
      36,     4,    10,     4,     4,    71,    67,    68,    69,    71,
       9,    77,     4,     8,    63,    18,    64,     4,    71,    55,
      81,    81,    81,    56,     6,     9,    70,    76,    74,     8,
      65,    26,    27,    80,    10,    68,    62,    55,     3,    71,
      81,     4,    55,    80
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 132 "parser.y"
    {
    program = new Program();
        (yyval.node) = program;
        (yyval.node)->addChild((yyvsp[(1) - (2)].node));
        (yyval.node)->addChild((yyvsp[(2) - (2)].node));
    ;}
    break;

  case 3:
#line 140 "parser.y"
    {
        (yyval.node) = new Program();
        (yyval.node)->addChild((yyvsp[(1) - (2)].node));
        (yyval.node)->addChild((yyvsp[(2) - (2)].node));
    ;}
    break;

  case 4:
#line 145 "parser.y"
    { /*EPS*/
        (yyval.node) = NULL;
    ;}
    break;

  case 5:
#line 150 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 6:
#line 156 "parser.y"
    {
    (yyval.node) = new FunctionDecl();
    (yyval.node)->addChild((yyvsp[(1) - (6)].node));
    (yyval.node)->addChild(new Identifier(new StringValue((yyvsp[(2) - (6)].stringVal))));
    (yyval.node)->addChild((yyvsp[(4) - (6)].node));
    (yyval.node)->addChild((yyvsp[(6) - (6)].node));
;}
    break;

  case 7:
#line 165 "parser.y"
    {
        (yyval.node) = new TypeNode(T_INT);
    ;}
    break;

  case 8:
#line 168 "parser.y"
    {
        (yyval.node) = new TypeNode(T_CHAR);
    ;}
    break;

  case 9:
#line 171 "parser.y"
    {
        (yyval.node) = new TypeNode(T_BOOL);
    ;}
    break;

  case 10:
#line 174 "parser.y"
    {
        (yyval.node) = new TypeNode(T_FLOAT);
    ;}
    break;

  case 11:
#line 177 "parser.y"
    {
        (yyval.node) = new TypeNode(T_STRING);
    ;}
    break;

  case 12:
#line 180 "parser.y"
    {
        (yyval.node) = new TypeNode(T_VOID);
    ;}
    break;

  case 13:
#line 186 "parser.y"
    {
        (yyval.node) = new ArgList();
        Arg * arg = new Arg();
        arg->addChild((yyvsp[(1) - (3)].node));
        arg->addChild(new Identifier(new StringValue((yyvsp[(2) - (3)].stringVal))));
        (yyval.node)->addChild(arg);
        (yyval.node)->addChild((yyvsp[(3) - (3)].node));
    ;}
    break;

  case 14:
#line 194 "parser.y"
    { /*EPS*/
        (yyval.node) = NULL;
    ;}
    break;

  case 15:
#line 199 "parser.y"
    {
        (yyval.node) = (yyvsp[(2) - (2)].node);
    ;}
    break;

  case 16:
#line 202 "parser.y"
    { /*EPS*/
        (yyval.node) = NULL;
    ;}
    break;

  case 17:
#line 207 "parser.y"
    {
        (yyval.node) = (yyvsp[(2) - (3)].node);
    ;}
    break;

  case 18:
#line 212 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 19:
#line 215 "parser.y"
    {
        (yyval.node) = NULL;
    ;}
    break;

  case 20:
#line 220 "parser.y"
    {
        (yyval.node) = new OperatorBlock();
        (yyval.node)->addChild((yyvsp[(1) - (3)].node));
        (yyval.node)->addChild((yyvsp[(3) - (3)].node));

    ;}
    break;

  case 21:
#line 226 "parser.y"
    {
        (yyval.node) = new OperatorBlock();
        (yyval.node)->addChild((yyvsp[(1) - (2)].node));
        (yyval.node)->addChild((yyvsp[(2) - (2)].node));
    ;}
    break;

  case 22:
#line 231 "parser.y"
    { /*EPS*/
        (yyval.node) = NULL;
    ;}
    break;

  case 23:
#line 236 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 24:
#line 239 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 25:
#line 242 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 26:
#line 245 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 27:
#line 248 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 28:
#line 251 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 29:
#line 254 "parser.y"
    {
        (yyval.node) = new Break();
    ;}
    break;

  case 30:
#line 257 "parser.y"
    {
        (yyval.node) = new Continue();
    ;}
    break;

  case 31:
#line 262 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 32:
#line 265 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 33:
#line 268 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 34:
#line 273 "parser.y"
    {
        (yyval.node) = new Increment();
        (yyval.node)->addChild((yyvsp[(1) - (2)].node));
    ;}
    break;

  case 35:
#line 277 "parser.y"
    {
        (yyval.node) = new Increment();
        (yyval.node)->addChild((yyvsp[(2) - (2)].node));
    ;}
    break;

  case 36:
#line 283 "parser.y"
    {
        (yyval.node) = new VariableDecl();
        (yyval.node)->addChild((yyvsp[(1) - (4)].node));
        (yyval.node)->addChild(new Identifier(new StringValue((yyvsp[(2) - (4)].stringVal))));
        (yyval.node)->addChild((yyvsp[(3) - (4)].node));
        (yyval.node)->addChild((yyvsp[(4) - (4)].node));
    ;}
    break;

  case 37:
#line 292 "parser.y"
    {
        (yyval.node) = new ArrayDim();
        (yyval.node)->addChild((yyvsp[(2) - (4)].node));
        (yyval.node)->addChild((yyvsp[(4) - (4)].node));
    ;}
    break;

  case 38:
#line 297 "parser.y"
    { /*EPS*/
        (yyval.node) = NULL;
    ;}
    break;

  case 39:
#line 302 "parser.y"
    {
        // parse value from stringVal
        (yyval.node) = new Literal(new StringValue((yyvsp[(1) - (1)].stringVal)));
    ;}
    break;

  case 40:
#line 306 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 41:
#line 311 "parser.y"
    {
        (yyval.node) = (yyvsp[(2) - (2)].node);
    ;}
    break;

  case 42:
#line 314 "parser.y"
    { /*EPS*/
        (yyval.node) = NULL;
    ;}
    break;

  case 43:
#line 319 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 44:
#line 322 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 45:
#line 325 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 46:
#line 328 "parser.y"
    {
        (yyval.node) = new Literal(new StringValue((yyvsp[(1) - (1)].stringVal)));
    ;}
    break;

  case 47:
#line 331 "parser.y"
    {
        (yyval.node) = new Literal(new CharValue((yyvsp[(1) - (1)].charVal)));
    ;}
    break;

  case 48:
#line 336 "parser.y"
    {
        (yyval.node) = new LeftPartExpr();
        (yyval.node)->addChild(new Identifier(new StringValue((yyvsp[(1) - (2)].stringVal))));
        (yyval.node)->addChild((yyvsp[(2) - (2)].node));
    ;}
    break;

  case 49:
#line 343 "parser.y"
    {
        (yyval.node) = (yyvsp[(2) - (3)].node);
    ;}
    break;

  case 50:
#line 348 "parser.y"
    {
        (yyval.node) = new ArrayItems();
        (yyval.node)->addChild((yyvsp[(1) - (2)].node));
        (yyval.node)->addChild((yyvsp[(2) - (2)].node));
    ;}
    break;

  case 51:
#line 355 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 52:
#line 358 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 53:
#line 363 "parser.y"
    {
        (yyval.node) = (yyvsp[(2) - (2)].node);
    ;}
    break;

  case 54:
#line 366 "parser.y"
    { /*EPS*/
        (yyval.node) = NULL;
    ;}
    break;

  case 55:
#line 371 "parser.y"
    {
        (yyval.node) = new BinaryExpr((yyvsp[(2) - (3)].nodeVal));
        (yyval.node)->addChild((yyvsp[(1) - (3)].node));
        (yyval.node)->addChild((yyvsp[(3) - (3)].node))
    ;}
    break;

  case 56:
#line 376 "parser.y"
    {
        (yyval.node) = (yyvsp[(2) - (3)].node);
    ;}
    break;

  case 57:
#line 379 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 58:
#line 384 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 59:
#line 385 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 60:
#line 386 "parser.y"
    { (yyval.node) = new Literal(new StringValue((yyvsp[(1) - (1)].stringVal))); ;}
    break;

  case 61:
#line 387 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 62:
#line 391 "parser.y"
    { (yyval.nodeVal) = new BinOp(TTPLUS);;}
    break;

  case 63:
#line 392 "parser.y"
    { (yyval.nodeVal) = new BinOp(TTMINUS);;}
    break;

  case 64:
#line 393 "parser.y"
    { (yyval.nodeVal) = new BinOp(TTMULT);;}
    break;

  case 65:
#line 394 "parser.y"
    { (yyval.nodeVal) = new BinOp(TTDIV);;}
    break;

  case 66:
#line 397 "parser.y"
    {
        (yyval.node) = new Indexing();
        (yyval.node)->addChild((yyvsp[(2) - (4)].node));
        (yyval.node)->addChild((yyvsp[(4) - (4)].node));
    ;}
    break;

  case 67:
#line 402 "parser.y"
    { /*EPS*/
        (yyval.node) = NULL;
    ;}
    break;

  case 68:
#line 407 "parser.y"
    {
        (yyval.node) = new FunctionCall();
        (yyval.node)->addChild(new Identifier(new StringValue((yyvsp[(1) - (4)].stringVal))));
        (yyval.node)->addChild((yyvsp[(3) - (4)].node));
    ;}
    break;

  case 69:
#line 414 "parser.y"
    {
        (yyval.node) = new ParamList();
        (yyval.node)->addChild((yyvsp[(1) - (2)].node));
        (yyval.node)->addChild((yyvsp[(2) - (2)].node));
    ;}
    break;

  case 70:
#line 421 "parser.y"
    {
        (yyval.node) = (yyvsp[(2) - (2)].node);
    ;}
    break;

  case 71:
#line 424 "parser.y"
    { /*EPS*/
        (yyval.node) = NULL;
    ;}
    break;

  case 72:
#line 429 "parser.y"
    {
        (yyval.node) = new Assignment();
        (yyval.node)->addChild((yyvsp[(1) - (3)].node));
        (yyval.node)->addChild((yyvsp[(3) - (3)].node));
    ;}
    break;

  case 73:
#line 436 "parser.y"
    {
        (yyval.node) = new Conditional();
        (yyval.node)->addChild((yyvsp[(3) - (6)].node));
        (yyval.node)->addChild((yyvsp[(5) - (6)].node));
        (yyval.node)->addChild((yyvsp[(6) - (6)].node))
    ;}
    break;

  case 74:
#line 444 "parser.y"
    {
        (yyval.node) = (yyvsp[(2) - (2)].node);
    ;}
    break;

  case 75:
#line 447 "parser.y"
    {
        (yyval.node) = new Conditional();
        (yyval.node)->addChild((yyvsp[(3) - (6)].node));
        (yyval.node)->addChild((yyvsp[(5) - (6)].node));
        (yyval.node)->addChild((yyvsp[(6) - (6)].node));
    ;}
    break;

  case 76:
#line 453 "parser.y"
    { /*EPS*/
        (yyval.node) = NULL;
    ;}
    break;

  case 77:
#line 458 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 78:
#line 461 "parser.y"
    {
        (yyval.node) = new BinaryExpr(new BinOp(TTAND));
        (yyval.node)->addChild((yyvsp[(1) - (3)].node));
        (yyval.node)->addChild((yyvsp[(3) - (3)].node));
    ;}
    break;

  case 79:
#line 466 "parser.y"
    {
        (yyval.node) = new BinaryExpr(new BinOp(TTOR));
        (yyval.node)->addChild((yyvsp[(1) - (3)].node));
        (yyval.node)->addChild((yyvsp[(3) - (3)].node));
    ;}
    break;

  case 80:
#line 471 "parser.y"
    {
        (yyval.node) = new UnaryExpr(new UnOp(TTNOT));
        (yyval.node)->addChild((yyvsp[(2) - (2)].node));

    ;}
    break;

  case 81:
#line 476 "parser.y"
    {
        (yyval.node) = (yyvsp[(2) - (3)].node);
    ;}
    break;

  case 82:
#line 479 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 83:
#line 482 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 84:
#line 487 "parser.y"
    {
        (yyval.node) = new BinaryExpr((yyvsp[(2) - (3)].nodeVal));
        (yyval.node)->addChild((yyvsp[(1) - (3)].node));
        (yyval.node)->addChild((yyvsp[(3) - (3)].node));
    ;}
    break;

  case 85:
#line 494 "parser.y"
    { (yyval.nodeVal) = new BinOp(TTEQ); ;}
    break;

  case 86:
#line 495 "parser.y"
    { (yyval.nodeVal) = new BinOp(TTNEQ); ;}
    break;

  case 87:
#line 496 "parser.y"
    { (yyval.nodeVal) = new BinOp(TTGT); ;}
    break;

  case 88:
#line 497 "parser.y"
    { (yyval.nodeVal) = new BinOp(TTLT); ;}
    break;

  case 89:
#line 498 "parser.y"
    { (yyval.nodeVal) = new BinOp(TTGE); ;}
    break;

  case 90:
#line 499 "parser.y"
    { (yyval.nodeVal) = new BinOp(TTLE); ;}
    break;

  case 91:
#line 502 "parser.y"
    {
        (yyval.node) = new WhileLoop();
        (yyval.node)->addChild((yyvsp[(1) - (2)].node));
        (yyval.node)->addChild((yyvsp[(2) - (2)].node));
    ;}
    break;

  case 92:
#line 509 "parser.y"
    {
        (yyval.node) = (yyvsp[(3) - (4)].node);
    ;}
    break;

  case 93:
#line 514 "parser.y"
    {
        (yyval.node) = new ForLoop();
        (yyval.node)->addChild((yyvsp[(3) - (5)].node));
        (yyval.node)->addChild((yyvsp[(5) - (5)].node));
    ;}
    break;

  case 94:
#line 521 "parser.y"
    {
        (yyval.node) = new ForInit();
        (yyval.node)->addChild((yyvsp[(1) - (5)].node));
        (yyval.node)->addChild((yyvsp[(3) - (5)].node));
        (yyval.node)->addChild((yyvsp[(5) - (5)].node));
    ;}
    break;

  case 95:
#line 529 "parser.y"
    {
        (yyval.node) = new PostLoop();
        (yyval.node)->addChild((yyvsp[(2) - (3)].node));
        (yyval.node)->addChild((yyvsp[(3) - (3)].node));
    ;}
    break;

  case 96:
#line 536 "parser.y"
    {
        (yyval.node) = new Return();
        (yyval.node)->addChild((yyvsp[(2) - (2)].node));
    ;}
    break;

  case 97:
#line 542 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 98:
#line 545 "parser.y"
    { /*EPS*/
        (yyval.node) = NULL;
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2305 "parser.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 549 "parser.y"


