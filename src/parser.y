%{

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include "../src/node.cpp"
#include "../src/nodevalue.h"


Program * program;

extern int yylex();
void yyerror(const char *s) { printf("ERROR: %sn", s); }
%}


%union {
    int token;
    std::string* stringVal;
    char charVal;
    Node * node;
    NodeValue * nodeVal;
}

%token TLPAREN
%token TRPAREN
%token TLBRACE
%token TRBRACE
%token TLBRACKET
%token TRBRACKET

%token TCOMMA
%token TSEMICOLON
%token TDOT

%token TINT
%token TCHAR
%token TBOOL
%token TFLOAT
%token TSTRING
%token TVOID

%token TASG
%token TEQ
%token TNEQ
%token TGT
%token TLT
%token TGE
%token TLE

%token TIF
%token TELSE
%token TELIF
%token TWHILE
%token TFOR
%token TDO
%token TPLUSPLUS
%token TRETURN
%token TBREAK
%token TCONTINUE
%token TTRUE
%token TFALSE

%token TAND
%token TOR
%token TNOT

%token TPLUS
%token TMINUS
%token TMULT
%token TDIV

%token <stringVal> TSTRING_LIT
%token <charVal> TCHAR_LIT
%token WHITE_SPACE

%token <stringVal> TID
%token <stringVal> TINTV
%token <stringVal> TFLOATV
%token <stringVal> TBOOLV

%type <nodeVal> compare

%type <node> program
%type <node> otherDeclarations
%type <node> declaration
%type <node> function
%type <node> typeId
%type <node> argList
%type <node> otherArgs
%type <node> body
%type <node> bodyOrSemi
%type <node> operatorBlock
%type <node> operatorSC
%type <node> moperator
%type <node> increment
%type <node> varDecl
%type <node> arrayDim
%type <node> init
%type <node> leftPartExpr
%type <node> arrayConst
%type <node> arrayItems
%type <node> arrayItem
%type <node> otherArrayItems
%type <node> expr
%type <node> term

%type <node> indexing
%type <node> funCall
%type <node> paramList
%type <node> otherParams
%type <node> assignment
%type <node> conditional
%type <node> elseBlock
%type <node> condition
%type <node> comparison

%type <node> whileLoop
%type <node> whileHeader
%type <node> forLoop
%type <node> forInit
%type <node> postLoop
%type <node> mreturn
%type <node> exprOrNothing
%type <nodeVal> arithOp
%start program

%%


program : declaration otherDeclarations {
    program = new Program();
        $$ = program;
        $$->addChild($1);
        $$->addChild($2);
    }
    ;

otherDeclarations : declaration otherDeclarations {
        $$ = new Program();
        $$->addChild($1);
        $$->addChild($2);
    }
    | { /*EPS*/
        $$ = NULL;
    }
    ;

declaration : function {
        $$ = $1;
    }
    ;


function : typeId TID TLPAREN argList TRPAREN bodyOrSemi {
    $$ = new FunctionDecl();
    $$->addChild($1);
    $$->addChild(new Identifier(new StringValue($<stringVal>2)));
    $$->addChild($4);
    $$->addChild($6);
}
    ;

typeId : TINT {
        $$ = new TypeNode(T_INT);
    }
    | TCHAR {
        $$ = new TypeNode(T_CHAR);
    }
    | TBOOL {
        $$ = new TypeNode(T_BOOL);
    }
    | TFLOAT {
        $$ = new TypeNode(T_FLOAT);
    }
    | TSTRING {
        $$ = new TypeNode(T_STRING);
    }
    | TVOID {
        $$ = new TypeNode(T_VOID);
    }
    ;


argList : typeId TID otherArgs {
        $$ = new ArgList();
        Arg * arg = new Arg();
        arg->addChild($1);
        arg->addChild(new Identifier(new StringValue($<stringVal>2)));
        $$->addChild(arg);
        $$->addChild($3);
    }
    | { /*EPS*/
        $$ = NULL;
    }
    ;

otherArgs : TCOMMA argList {
        $$ = $2;
    }
    | { /*EPS*/
        $$ = NULL;
    }
    ;

body : TLBRACE operatorBlock TRBRACE {
        $$ = $2;
    }
    ;

bodyOrSemi : body {
        $$ = $1;
    }
    | TSEMICOLON {
        $$ = NULL;
    }
    ;

operatorBlock : operatorSC TSEMICOLON operatorBlock {
        $$ = new OperatorBlock();
        $$->addChild($1);
        $$->addChild($3);

    }
    | moperator operatorBlock {
        $$ = new OperatorBlock();
        $$->addChild($1);
        $$->addChild($2);
    }
    | { /*EPS*/
        $$ = NULL;
    }
    ;

operatorSC : varDecl {
        $$ = $1;
    }
    | assignment {
        $$ = $1;
    }
    | postLoop {
        $$ = $1;
    }
    | mreturn {
        $$ = $1;
    }
    | increment {
        $$ = $1;
    }
    | funCall {
        $$ = $1;
    }
    | TBREAK {
        $$ = new Break();
    }
    | TCONTINUE {
        $$ = new Continue();
    }
    ;

moperator : conditional {
        $$ = $1;
    }
    | whileLoop {
        $$ = $1;
    }
    | forLoop {
        $$ = $1;
    }
    ;

increment : leftPartExpr TPLUSPLUS {
        $$ = new Increment();
        $$->addChild($1);
    }
    | TPLUSPLUS leftPartExpr {
        $$ = new Increment();
        $$->addChild($2);
    }
    ;

varDecl : typeId TID arrayDim init {
        $$ = new VariableDecl();
        $$->addChild($1);
        $$->addChild(new Identifier(new StringValue($<stringVal>2)));
        $$->addChild($3);
        $$->addChild($4);
    }
    ;

arrayDim : TLBRACKET expr TRBRACKET arrayDim {
        $$ = new ArrayDim();
        $$->addChild($2);
        $$->addChild($4);
    }
    | { /*EPS*/
        $$ = NULL;
    }
    ;

init : TASG expr {
        $$ = $2;
    }
    | { /*EPS*/
        $$ = NULL;
    }
    ;

leftPartExpr : TID indexing {
        $$ = new LeftPartExpr();
        $$->addChild(new Identifier(new StringValue($<stringVal>1)));
        $$->addChild($2);
    }
    ;

arrayConst : TLBRACE arrayItems TRBRACE {
        $$ = $2;
    }
    ;

arrayItems : arrayItem otherArrayItems {
        $$ = new ArrayItems();
        $$->addChild($1);
        $$->addChild($2);
    }
    ;

arrayItem : expr {
        $$ = $1;
    }
    | arrayConst {
        $$ = $1;
    }
    ;

otherArrayItems : TCOMMA arrayItems {
        $$ = $2;
    }
    | { /*EPS*/
        $$ = NULL;
    }
    ;

expr : expr arithOp expr {
        $$ = new BinaryExpr($2);
        $$->addChild($1);
        $$->addChild($3)
    }
    | TLPAREN expr TRPAREN {
        $$ = $2;
    }
    | term {
        $$ = $1;
    }
    ;

term : leftPartExpr { $$ = $1; }
    | funCall { $$ = $1; }
    | increment { $$ = $1; }
    | arrayConst { $$ = $1; }
    | condition { $$ = $1; }
    | TINTV { $$ = new Literal(new IntValue($<stringVal>1)); }
    | TFLOATV { $$ = new Literal(new FloatValue($<stringVal>1)); }
    | TBOOLV { $$ = new Literal(new BoolValue($<stringVal>1));}
    | TSTRING_LIT { $$ = new Literal(new StringValue($<stringVal>1)); }
    | TCHAR_LIT { $$ = new Literal(new CharValue($<charVal>1)); }
    ;


arithOp : TPLUS { $$ = new BinOp(TTPLUS);}
    | TMINUS { $$ = new BinOp(TTMINUS);}
    | TMULT { $$ = new BinOp(TTMULT);}
    | TDIV { $$ = new BinOp(TTDIV);}
    ;

indexing : TLBRACKET expr TRBRACKET indexing {
        $$ = new Indexing();
        $$->addChild($2);
        $$->addChild($4);
    }
    | { /*EPS*/
        $$ = NULL;
    }
    ;

funCall : TID TLPAREN paramList TRPAREN {
        $$ = new FunctionCall();
        $$->addChild(new Identifier(new StringValue($<stringVal>1)));
        $$->addChild($3);
    }
    ;

paramList : expr otherParams {
        $$ = new ParamList();
        $$->addChild($1);
        $$->addChild($2);
    }
    ;

otherParams : TCOMMA paramList {
        $$ = $2;
    }
    | { /*EPS*/
        $$ = NULL;
    }
    ;

assignment : leftPartExpr TASG expr {
        $$ = new Assignment();
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

conditional : TIF TLPAREN condition TRPAREN body elseBlock {
        $$ = new Conditional();
        $$->addChild($3);
        $$->addChild($5);
        $$->addChild($6)
    }
    ;

elseBlock : TELSE body {
        $$ = $2;
    }
    | TELIF TLPAREN condition TRPAREN body elseBlock {
        $$ = new Conditional();
        $$->addChild($3);
        $$->addChild($5);
        $$->addChild($6);
    }
    | { /*EPS*/
        $$ = NULL;
    }
    ;

condition : comparison {
        $$ = $1;
    }
    | condition TAND condition {
        $$ = new BinaryExpr(new BinOp(TTAND));
        $$->addChild($1);
        $$->addChild($3);
    }
    | condition TOR condition {
        $$ = new BinaryExpr(new BinOp(TTOR));
        $$->addChild($1);
        $$->addChild($3);
    }
    | TNOT condition {
        $$ = new UnaryExpr(new UnOp(TTNOT));
        $$->addChild($2);

    }
    | TLPAREN condition TRPAREN {
        $$ = $2;
    }
    ;

comparison : expr compare expr {
        $$ = new BinaryExpr($2);
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

compare : TEQ { $$ = new BinOp(TTEQ); }
    | TNEQ { $$ = new BinOp(TTNEQ); }
    | TGT { $$ = new BinOp(TTGT); }
    | TLT { $$ = new BinOp(TTLT); }
    | TGE { $$ = new BinOp(TTGE); }
    | TLE { $$ = new BinOp(TTLE); }
    ;

whileLoop : whileHeader bodyOrSemi {
        $$ = new WhileLoop();
        $$->addChild($1);
        $$->addChild($2);
    }
    ;

whileHeader : TWHILE TLPAREN condition TRPAREN {
        $$ = $3;
    }
    ;

forLoop : TFOR TLPAREN forInit TRPAREN bodyOrSemi {
        $$ = new ForLoop();
        $$->addChild($3);
        $$->addChild($5);
    }
    ;

forInit : varDecl TSEMICOLON condition TSEMICOLON expr {
        $$ = new ForInit();
        $$->addChild($1);
        $$->addChild($3);
        $$->addChild($5);
    }
    ;

postLoop : TDO body whileHeader {
        $$ = new PostLoop();
        $$->addChild($2);
        $$->addChild($3);
    }
    ;

mreturn : TRETURN exprOrNothing {
        $$ = new Return();
        $$->addChild($2);
    }
    ;

exprOrNothing : expr {
        $$ = $1;
    }
    | { /*EPS*/
        $$ = NULL;
    }
    ;
%%
