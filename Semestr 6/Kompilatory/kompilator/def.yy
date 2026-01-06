%code requires {
    #include <vector>
    #include "asmgen.h"
}

%{

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

%}

%union {
    int ival;         // Integer values
    float fval;       // Float values
    int bval;         // Bool values
    char cval;        // Character values
    char *sval;       // String values and identifiers
    std::vector<int>* vec_int;
    std::vector<Symbol>* vec_sym;
}

%token <ival> INT_LITERAL
%token <fval> FLOAT_LITERAL
%token <bval> BOOL_LITERAL
%token <cval> CHAR_LITERAL
%token <sval> STRING_LITERAL

%token <sval> ID

%token INT FLOAT BOOL CHAR STRING
%token PTR_INT PTR_FLOAT

%token IF ELSE WHILE FOR BREAK CONTINUE PRINT INPUT

%token EQ NEQ LT LEQ GT GEQ AND OR NOT
%token INC DEC ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN

%token NEW

%type <vec_int> dimensions
%type <vec_sym> index_list

%left OR
%left AND
%left EQ NEQ
%left LT LEQ GT GEQ
%left '+' '-'
%left '*' '/' '%'
%right INC DEC
%right ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN
%right '='

%%

program
	: stmt_list {
            printf("\nCompilation complete!\n\n");
        }
	;

stmt_list
	: stmt_list stmt
	| stmt
	;

stmt
	: declaration ';'
    | assignment ';'
	| expr ';'
    | print_stmt ';'
    | input_stmt ';'
    | if_stmt
    | for_stmt
	;

dimensions
    : dimensions '[' INT_LITERAL ']' {
            $$ = $1;
            $$->push_back($3);
        }
    | '[' INT_LITERAL ']' {
            $$ = new vector<int>();
            $$->push_back($2);
        }
    ;

for_init
    : declaration_for_init
    | assignment
    ;

for_assignment
	: ID '=' expr { basicStack.push({$1}); }
    | ID INC {
            handle_increment($1);
        }
	;

for_expr
    : { write_for_label(); } expr { write_for_condition(); }
    ;

for_stmt
    : FOR '(' for_init ';' for_expr ';' for_assignment ')' block
        { write_for_end(); }
    ;

if_stmt
    : IF '(' expr ')'
        { write_if_condition(); }
      block
      optional_else
        { write_if_end(); }
    ;

optional_else
    : ELSE
        { write_else_start(); }
      block
    |
    ;

block
    : '{' stmt_list '}'
    | stmt
    ;

type
    : INT       { basicStack.push({"TYPE", "INT"}); }
    | FLOAT     { basicStack.push({"TYPE", "FLOAT"}); }
    | BOOL      { basicStack.push({"TYPE", "BOOL"}); }
    | CHAR      { basicStack.push({"TYPE", "CHAR"}); }
    | STRING    { basicStack.push({"TYPE", "STRING"}); }
    | PTR_INT   { basicStack.push({"TYPE", "PTR_INT"}); }
    | PTR_FLOAT { basicStack.push({"TYPE", "PTR_FLOAT"}); }
    ;

declaration
    : type ID '=' expr {
            process_declaration($2);
        }
    | type ID dimensions { 
            Symbol typeSymbol = basicStack.top(); basicStack.pop();
            process_array_declaration(typeSymbol.type, $2, $3);
        }
    | type ID '=' NEW type '[' expr ']' {
            Symbol sizeSym = basicStack.top(); basicStack.pop();
            Symbol typeRight = basicStack.top(); basicStack.pop();
            Symbol typeLeft = basicStack.top(); basicStack.pop();

            process_dynamic_array_declaration(typeLeft.type, $2, sizeSym);
        }
    ;

declaration_for_init 
    : type ID '=' expr { 
            process_declaration_and_assignment($2);
        }
    ;

index_list
    : index_list '[' expr ']' {
            Symbol idx = basicStack.top(); basicStack.pop();
            $1->push_back(idx);
            $$ = $1;
        }
    | '[' expr ']' {
            Symbol idx = basicStack.top(); basicStack.pop();
            $$ = new vector<Symbol>();
            $$->push_back(idx);
        }
    ;

assignment
	: ID '=' expr {
            code_write_assignment($1);
        }
    | ID index_list '=' expr {
            code_write_array_element_assignment($1, $2);
        }
	;

print_stmt
    : PRINT '(' expr ')' { process_and_print_nonvariables(); }
    ;

input_stmt
    : INPUT '(' ID ')' {
            string varName = $3;
            string varType = symbolTable[varName].type;
            threesFile << "INPUT " << varName << "\n";
        }

expr
    : expr '+' term            { code_write("+"); }
    | expr '-' term            { code_write("-"); }
    | expr EQ term             { code_write("=="); }
    | expr NEQ term            { code_write("!="); }
    | expr LT term             { code_write("<"); }
    | expr LEQ term            { code_write("<="); }
    | expr GT term             { code_write(">"); }
    | expr GEQ term            { code_write(">="); }
    | expr AND term            { code_write("&&"); }
    | expr OR term             { code_write("||"); }
    | term
    ;

term
    : term '*' factor   { code_write("*"); }
    | term '/' factor   { code_write("/"); }
    | term '%' factor   { code_write("%"); }
    | factor
    ;

factor
    : ID index_list {
            process_array_value($1, $2);
        }
    | ID INC {
            string varName = $1;
            threesFile << varName + " = " + varName + " + 1" << endl;
            basicStack.push({varName, symbolTable[varName].type});
        }
    | ID {
            string varName = $1;
            basicStack.push({varName, symbolTable[varName].type});
        }
    | INT_LITERAL {
            basicStack.push({to_string($1), "INT", $1, 0.0f});
        }
    | BOOL_LITERAL {
            basicStack.push({($1 ? "true" : "false"), "BOOL", $1, 0.0f});
        }
    | FLOAT_LITERAL {
            basicStack.push({to_string($1), "FLOAT", 0, $1});
        }
    | CHAR_LITERAL {
            string charStr(1, $1);
            basicStack.push({charStr, "CHAR", 0, 0.0f, charStr});
        }
    | STRING_LITERAL {
            string quotedStr = "\"" + string($1) + "\"";
            basicStack.push({quotedStr, "STRING", 0, 0.0f, quotedStr});
            free($1);
        }
    | '(' expr ')'
    ;

%%

int main(int argc, char *argv[])
{
    threesFile.open("threes.txt");
	yyparse();
    threesFile.close();
    generateMIPS("threes.txt", "output.asm", symbolTable);
	return 0;
}
