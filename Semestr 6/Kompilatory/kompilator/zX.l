%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "def.tab.hh"

int yyparse();
extern "C" int yylex();
extern int yylineno;
extern "C" int yyerror(const char *msg);
%}

%%

[ \t]+    ;

"new"        { return NEW; }

"int"        { return INT; }
"float"      { return FLOAT; }
"bool"       { return BOOL; }
"char"       { return CHAR; }
"string"     { return STRING; }

"int *"      { return PTR_INT; }
"float *"    { return PTR_FLOAT; }

"if"         { return IF; }
"else"       { return ELSE; }
"while"      { return WHILE; }
"for"        { return FOR; }
"break"      { return BREAK; }
"continue"   { return CONTINUE; }
"print"      { return PRINT; }
"input"      { return INPUT; }

"true"       { yylval.bval = 1; return BOOL_LITERAL; }
"false"      { yylval.bval = 0; return BOOL_LITERAL; }

[0-9]+           { yylval.ival = atoi(yytext); return INT_LITERAL; }
[0-9]+\.[0-9]+   { yylval.fval = atof(yytext); return FLOAT_LITERAL; }

\"[^\"]*\"   { yylval.sval = strdup(yytext + 1); yylval.sval[strlen(yylval.sval) - 1] = '\0'; return STRING_LITERAL; }

\'[^\n\']\'  { yylval.cval = yytext[1]; return CHAR_LITERAL; }

[A-Za-z_][A-Za-z0-9_]* { yylval.sval = strdup(yytext); return ID; }

"="          { return '='; }

"=="         { return EQ; }
"!="         { return NEQ; }
"<"          { return LT; }
"<="         { return LEQ; }
">"          { return GT; }
">="         { return GEQ; }
"&&"         { return AND; }
"||"         { return OR; }

"+"          { return '+'; }
"-"          { return '-'; }
"*"          { return '*'; }
"/"          { return '/'; }
"%"          { return '%'; }

"("          { return '('; }
")"          { return ')'; }
"{"          { return '{'; }
"}"          { return '}'; }
"["          { return '['; }
"]"          { return ']'; }
";"          { return ';'; }
","          { return ','; }

"++"         { return INC; }
"--"         { return DEC; }
"+="         { return ADD_ASSIGN; }
"-="         { return SUB_ASSIGN; }
"*="         { return MUL_ASSIGN; }
"/="         { return DIV_ASSIGN; }

"//".*       { /* Do nothing */ ; }

\n			{yylineno++;}

.			{yyerror("Lexical error\n");}

%%

int yyerror(const char *msg) {
    fprintf(stderr, "Error on line %d: %s\n", yylineno, msg);
    exit(1);
}
