// AST constructor functions

#include <stdlib.h> // for malloc
#include "ast.h" // AST header

Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}

Expr* ast_operation(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

Expr* ast_boolean(int v){
  Expr* node=(Expr*) malloc(sizeof(Expr));
  node->kind= E_BOOLEAN;
  node->attr.value = v;
  return node;
}
Expr* ast_booleanrel(Expr* left, int operator, Expr* right){
  Expr* node=(Expr*) malloc(sizeof(Expr));
  node->kind= E_BOOLEAN;
  node->attr.op.operator= operator;
  node->attr.op.left=left;
  node->attr.op.right=right;
  return node;
}

Cmd* ast_attrib(char var, Expr* expr){
  Cmd* node=(Cmd*) malloc (sizeof(Cmd));
  node->kind=E_ATTR;
  node->attr.atributo.var=var;
  node->attr.atributo.expr=expr;

  return node;

}
Cmd* ast_ciclos(Expr* cond, Cmd* comando){
  Cmd* node=(Cmd*) malloc (sizeof(Cmd));
  node->kind=E_CICLO;
  node->attr.ciclo.cond=cond;
  node->attr.ciclo.comando=comando;

  return node;
}
Cmd* ast_if(Expr* cond, Cmd* comando){
  Cmd* node=(Cmd*) malloc (sizeof(Cmd));
  node->kind=E_IF;
  node->attr.se.cond=cond;
  node->attr.se.comando=comando;

  return node;
}
Cmd* ast_ifthenelse(Expr* cond, Cmd* comando){
  Cmd* node=(Cmd*) malloc (sizeof(Cmd));
  node->kind=E_IF_ELSE;
  node->attr.entao.cond=cond;
  node->attr.entao.comando=comando;

  return node;
}

var* ast_ldecl_var(char* letra){
  var* node=(var*) malloc (sizeof(var));
  node->letra=strdup(letra);
  return node;
}

var* ast_ldecl_decl(char* letra, Expr* valor){
 var* node=(var *) malloc (sizeof(var));
 node->letra=strup(letra);
 node->valor=valor;
 return node;
}
