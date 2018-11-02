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
Expr* root; // MUDAR PARA LISTA DE COMANDOS !!!!!!
}

%%
//program: INTEIRO MAIN PESQ PDIR CHESQ lcmd CHDIR { root = $6; }
program: expr { root = $1; }
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

lcmd:
cmd PV{

}





%%

void yyerror(const char* err) {
printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
