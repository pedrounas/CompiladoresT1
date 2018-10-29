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
      printf("%%");
      break;
      case EQUAL:
      printf("==");
      break;
      case DIFF:
      printf("!=");
      break;
      case LESS:
      printf("<");
      break;
      case GREATER:
      printf(">");
      break;
      case LESSOREQ:
      printf("<=");
      break;
      case GREATEROREQ:
      printf(">=");
      break;
      break;
      default: yyerror("Unknown operator!");
    }
    printExpr(expr->attr.op.right);
  }

  /*else if (expr->kind == E_ROPERATION) {
    printExpr(expr->attr.op.left);
    switch (expr->attr.op.operator) {

      default: yyerror("Unknown operator!");
    }
    printExpr(expr->attr.op.right);
  }*/
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
      if(yyparse()==0) {
      printExpr(root);
      printf("\n");
    }
      return 0;
    }
