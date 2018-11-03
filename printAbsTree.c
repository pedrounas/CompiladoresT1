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
int conta=0;
void printCmd(Cmd* command){
  conta++;
  if (command== 0) {
    yyerror("Null expression!!");
  }
  else if (command->kind == E_IF) {
    printf("IF ");
    printExpr(command->attr.se.cond);
    //printCmd(command->attr.se.cmd);
    printf("\n");
    printf("{");
    //fazer lista de comandos
  }
  else if (command->kind == E_IF_ELSE) {
    printf("IF");
    printCmd(command->attr.entao.cond);
    printCmd(command->attr.entao.cmd);
    printf("\n");
    printf("ELSE");
    printCmd(command->attr.entao.cmd);
    //fazer lista de comandos

  }
  else if(command->kind== E_CICLO){
    printf("WHILE ");
    printExpr(command->attr.ciclo.cond);
    printf("\n");
    printf("{");

    //fazer lista de comandos
  }

  else if(command->kind == E_ATTR){
    printf("%s =", command->attr.atributo.var);
    printExpr(command->attr.atributo.expr);
    printf("\n");
  }

  else if(command->kind == E_SCAN){
    printf("scanf ", command->attr.scan.var);
  }
  else if(command->kind ==E_PRINT){
    printf("printf ", command->attr.print.letra);
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
  if(yyparse()==0){
    //printExpr(root);
    while (root!=NULL){
      printCmd(root->comando, 0);
      printf("\n");
      root= root->next;
    }
  }


  return 0;
}
