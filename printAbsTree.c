#include <stdio.h>
#include "parser.h"
#include "ast.h"

void printExpr(Expr* expr) {
  int result = 0;
  if (expr == 0) {
    yyerror("Null expression!!");
  }
  else if (expr->kind == E_INTEGER) {
    printf("%d",expr->attr.value);
  }
  else if (expr->kind == E_OPERATION) {
    printExpr(expr->attr.op.left);

    switch (expr->attr.op.operator) {
      case PLUS:
      printf("+");
      break;
      case MINUS:
      printf("-");
      break;
      case MULT:
      printf("*");
      break;
      case DIV:
      printf("/");
      break;
      case MOD:
      printf("%");
      break;
      case EQUAL:
      printf("==");
      break;
      case DIFF:
      printf("!=");
      break;
      case GREATER:
      printf(">");
      break;
      case LESS:
      printf("<");
      break;
      case GREATEREQ:
      printf(">=");
      break;
      case LESSEQ:
      printf("<=");
      break;
      default: yyerror("Unknown operator!");
    }
    printExpr(expr->attr.op.right);
  }
}
/*void printBool(BoolExpr* b){
int result = 0;
if (b == 0) {
yyerror("Null expression!!");
}
else if (b->kind == E_INTEGER) {
printf("%d",b->attr.value);
}
else if (b->kind == E_BOPERATION) {
printBool(b->attr.op.left);

switch (b->attr.op.operator) {
case EQUAL:
printf("==");
break;
case DIFF:
printf("!=");
break;
case GREATER:
printf(">");
break;
case LESS:
printf("<");
break;
case GREATEREQ:
printf(">=");
break;
case LESSEQ:
printf("<=");
break;
default: yyerror("Unknown operator!");
}
printBool(b->attr.op.right);
}
}*/
void printCmd(Cmd* command){
  if (command== 0) {
    yyerror("Null expression!!");
  }
  else if (command->kind == E_IF) {
    printf("IF");
    printCmd(command->attr.se.cond);
    printCmd(command->attr.se.cmd);
  }
  else if (command->kind == E_IF_ELSE) {
    printf("IF");
    printCmd(command->attr.entao.cond);
    printCmd(command->attr.entao.cmd);
      printf("ELSE");
      printCmd(command->attr.entao.cmd);

  }
  else if(command->kind== E_CICLO){
    printf("WHILE");
    printCmd(command->attr.ciclo.cond);
  }

  else if(command->kind == E_ATTR){
    printf("%c", command->attr.atributo.var);
    printCmd(command->attr.atributo.expr);
  }

  switch (command->attr.ciclo.cond) {
    case LESSEQ:
    printf("<=");
    break;
    default: yyerror("Unknown operator!");
  }
  printCmd(command->attr.ciclo.comando);
}
}


int main(int argc, char** argv) {
  --argc;++argv;
  if(argc!=0) {
    yyin=fopen(*argv,"r");
    if(!yyin){
      printf("'%s':could not open file\n", *argv);
      return 1;
    }
  }
  if(yyparse()==0)
  printExpr(root);
  //printBool(root);

  return 0;
}
