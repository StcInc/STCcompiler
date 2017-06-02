%{
#include <iostream>
#include <string>
#include "../src/node.cpp"
#include "parser.hpp"
#define SAVE_TOKEN yylval.stringVal = new std::string(yytext, yyleng)
//#define PRINT_TOKEN {std::string * s = new std::string(yytext, yyleng); std::cout << "Lexer:recognized:" << *s << std::endl; delete s;}
#define PRINT_TOKEN ;
#define TOKEN(t) (yylval.token = t)
void extern yyerror(char*);
void InvalidToken();

%}

D [0-9]
L [a-zA-Z]

%%

[ \t\r\v\f]      { ; }
[\n]             { yylineno++; }
"("              { PRINT_TOKEN; return TOKEN(TLPAREN); }
")"              { PRINT_TOKEN; return TOKEN(TRPAREN); }
"{"              { PRINT_TOKEN; return TOKEN(TLBRACE); }
"}"              { PRINT_TOKEN; return TOKEN(TRBRACE); }
"["              { PRINT_TOKEN; return TOKEN(TLBRACKET); }
"]"              { PRINT_TOKEN; return TOKEN(TRBRACKET); }
","              { PRINT_TOKEN; return TOKEN(TCOMMA); }
";"              { PRINT_TOKEN; return TOKEN(TSEMICOLON); }
"."              { PRINT_TOKEN; return TOKEN(TDOT); }

"int"            { PRINT_TOKEN; return TOKEN(TINT); }
"char"           { PRINT_TOKEN; return TOKEN(TCHAR); }
"bool"           { PRINT_TOKEN; return TOKEN(TBOOL); }
"float"          { PRINT_TOKEN; return TOKEN(TFLOAT); }
"string"         { PRINT_TOKEN; return TOKEN(TSTRING); }
"void"           { PRINT_TOKEN; return TOKEN(TVOID); }


"="              { PRINT_TOKEN; return TOKEN(TASG); }
"=="             { PRINT_TOKEN; return TOKEN(TEQ); }
"!="             { PRINT_TOKEN; return TOKEN(TNEQ); }
">"              { PRINT_TOKEN; return TOKEN(TGT); }
"<"              { PRINT_TOKEN; return TOKEN(TLT); }
">="             { PRINT_TOKEN; return TOKEN(TGE); }
"<="             { PRINT_TOKEN; return TOKEN(TLE); }

"if"             { PRINT_TOKEN; return TOKEN(TIF); }
"else"           { PRINT_TOKEN; return TOKEN(TELSE); }
"elif"           { PRINT_TOKEN; return TOKEN(TELIF); }
"do"             { PRINT_TOKEN; return TOKEN(TDO); }
"while"          { PRINT_TOKEN; return TOKEN(TWHILE); }
"for"            { PRINT_TOKEN; return TOKEN(TFOR); }
"++"             { PRINT_TOKEN; return TOKEN(TPLUSPLUS); }
"return"         { PRINT_TOKEN; return TOKEN(TRETURN); }
"break"          { PRINT_TOKEN; return TOKEN(TBREAK); }
"continue"       { PRINT_TOKEN; return TOKEN(TCONTINUE); }
"true"           { PRINT_TOKEN; return TOKEN(TTRUE); }
"false"          { PRINT_TOKEN; return TOKEN(TFALSE); }

"&&"             { PRINT_TOKEN; return TOKEN(TAND); }
"||"             { PRINT_TOKEN; return TOKEN(TOR); }
"!"              { PRINT_TOKEN; return TOKEN(TNOT); }

"+"              { PRINT_TOKEN; return TOKEN(TPLUS); }
"-"              { PRINT_TOKEN; return TOKEN(TMINUS); }
"*"              { PRINT_TOKEN; return TOKEN(TMULT); }
"/"              { PRINT_TOKEN; return TOKEN(TDIV); }

["].*["]        { PRINT_TOKEN; SAVE_TOKEN; return TOKEN(TSTRING_LIT); }
['].+[']        { PRINT_TOKEN; SAVE_TOKEN; return TOKEN(TCHAR_LIT); }


{L}({L}|{D})*   { PRINT_TOKEN; SAVE_TOKEN; return TID; }
{D}+            { PRINT_TOKEN; SAVE_TOKEN; return TINTV; }
{D}+([,.]{D}+)f { PRINT_TOKEN; SAVE_TOKEN; return TFLOATV; }

.               { InvalidToken(); }

%%

int yywrap(void){
    return 1;
}

void yyerror(char *s) {
    fprintf(stderr, "\nERROR ON LINE %d : \n %s\n", yylineno, s);
    exit(0);
}

void InvalidToken(){
    printf("ERROR ON LINE %d : \n Invalid Token %s\n", yylineno,yytext);
    exit(0);
}

/*
int main () {
    std::cout << terminalToStr(STRING) << std::endl;
    std::cout << "Run->\n";
    Terminal terminal;
    while((terminal = (Terminal)yylex())) {
        if (terminal != WHITE_SPACE) {
            std::cout << terminalToStr(terminal) << '\n';
        }
    }
}
*/
