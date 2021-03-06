%{
// HEADERS
#include <stdlib.h>
#include "parser.h"

// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }
#.*\n { yyline++; }
\n { yyline++; }

\"(\\.|[^\\"])*\" {
yylval.textValue = strdup(yytext);
return STR;
}

\-?[0-9]+ {
yylval.intValue = atoi(yytext);
return INT;
}

"+" { return PLUS; }
"-" { return MINUS; }
"*" { return MULT; }
"/" { return DIV; }
"%" { return MOD;}
"==" {return EQUAL;}
"!=" {return DIFF;}
"<" {return LESS;}
">" {return GREATER;}
"<=" {return LESSEQ;}
">=" {return GREATEREQ;}
"while" {return CICLO;}
"if" {return SE;}
"else" {return ENTAO;}
"=" { return IGUAL;}
";" {return PV;}
"{" {return CHESQ;}
"}" {return CHDIR;}
"(" {return PESQ;}
")" {return PDIR;}
"scanf" {return SCAN;}
"printf" {return PRINT;}
"int" {return INTEIRO;}
"main" {return MAIN;}
"," {return VIRGULA;}

[a-zA-Z_][a-zA-Z0-9_]* {
yylval.textValue = strdup(yytext);
return VAR;
}



.  { yyerror("unexpected character"); }
%%
