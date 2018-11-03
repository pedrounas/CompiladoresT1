// Tokens
%token
INT
STR
VAR
PLUS
MINUS
MULT
DIV
MOD
EQUAL
DIFF
LESS
GREATER
LESSEQ
GREATEREQ
CICLO
FAZ
IGUAL
SE
ENTAO
PV
CHESQ
CHDIR
PESQ
PDIR
SCAN
PRINT
INTEIRO
MAIN
VIRGULA
TRUE
FALSE

// Operator associativity & precedence
%left PLUS MINUS
%left DIV MULT
%left MOD

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
int intValue;
Expr* exprValue;
BoolExpr* boolValue;
Cmd* command;
}

%type <intValue> INT
%type <exprValue> expr
//%type <boolValue> boolexpr
%type <command> cmd;

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
//Expr* root;
lcmd* root;
}

%%
program: INTEIRO MAIN PESQ PDIR CHESQ lcmd CHDIR { root = $6; }
//program: expr { root = $1; }
expr:
INT {
$$ = ast_integer($1);
}
|
expr PLUS expr {
$$ = ast_operation(PLUS, $1, $3);
}
;
|
expr MINUS expr {
$$ = ast_operation(MINUS, $1, $3);
}
;
|
expr MULT expr {
$$ = ast_operation(MULT, $1, $3);
}
;
|
expr DIV expr{
$$ = ast_operation(DIV, $1, $3);
}
;
|
expr MOD expr {
$$ = ast_operation(MOD, $1, $3);
}
;
|
expr EQUAL expr {
$$ = ast_operation(EQUAL,$1, $3);
}
;
|
expr DIFF expr {
$$ = ast_operation(DIFF,$1, $3);
}
;
|
expr LESS expr {
$$ = ast_operation(LESS,$1, $3);
}
;
|
expr GREATER expr {
$$ = ast_operation(GREATER,$1, $3);
}
;
|
expr LESSEQ expr {
$$ = ast_operation(LESSEQ,$1, $3);
}
;
|
expr GREATEREQ expr {
$$ = ast_operation(GREATEREQ,$1,$3);
}
;
|
TRUE {
$$=ast_integer(1);
}
;
|
FALSE {
$$=ast_integer(0);
}

lcmd:
cmd PV{
$$= lista_comandos($1,NULL);
}
;
|
cmd PV lcmd {
$$=lista_comandos($1,$3);
}
;


cmd:
E_IF{
$$=$1;
}
;
|
E_IF_ELSE{
$$=$1;
}
;
|
E_CICLO{
$$=$1;
}
;
|
E_ATTR{
$$=$1;
}
;
|
E_PRINT{
$$=$1;
}
;
|
E_SCAN {
$$=$1;
}
;
|
E_DECL {
$$=$1;
}
;

E_IF:
SE PESQ cond PDIR CHESQ lcmd CHDIR{
$$=ast_if($3,$6);
}
;

E_IF_ELSE:
SE PESQ cond PDIR CHESQ lcmd CHDIR{
$$=ast_ifthenelse($3,$6);
}
;

E_CICLO:
CICLO PESQ cond PDIR CHESQ lcmd CHDIR{
$$=ast_ciclos($3,$6);
}
;

E_ATTR:
VAR IGUAL INT{
$$=ast_attrib($1,$3);
}
;

E_PRINT:
PRINT PESQ STR VIRGULA lvar PDIR{
$$=ast_print($5);
}
;

E_SCAN:
SCAN PESQ STR VIRGULA lvar PDIR{
$$=ast_scan($5);
}
;

E_DECL:
INTEIRO ldecl{
$$=ast_decl($2);
}
;

cond:
expr{
//////////???
}
;
|
expr EQUAL expr {
$$= ast_operation(EQUAL, $1,$3);
}
;
|
expr DIFF expr {
$$ = ast_operation(DIFF, $1, $3);
}
;
|
expr LESS expr {
$$ = ast_operation(LESS, $1, $3);
}
;
|
expr GREATER expr {
$$= ast_operation(GREATER, $1, $3);
}
;
|
expr LESSEQ expr {
$$= ast_operation(LESSEQ, $1, $3);
}
;
|
expr GREATEREQ expr {
$$= ast_operation(GREATEREQ, $1, $3);
}
;

lvar:
VAR {
$$=ast_var($1);
}
;
|
VAR VIRGULA lvar{
$$=ast_lvar($1,$3);
}
;

ldecl:
VAR {
$$=$1;///?
}
;
VAR IGUAL expr {
$$= ast_ldecl_var($1,$3);
}
;
|
VAR VIRGULA ldecl {
$$=ast_ldecl_decl($1,$3);
}
;
|
VAR IGUAL expr VIRGULA ldecl {
$$= ast_ldecl_decl($3,$5);
}
;




void yyerror(const char* err) {
printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
