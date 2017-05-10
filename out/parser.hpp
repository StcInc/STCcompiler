/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
/* Line 1529 of yacc.c.  */
#line 152 "parser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

