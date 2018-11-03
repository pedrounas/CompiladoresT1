
// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions
struct _Expr {
  enum {
    E_INTEGER,
    E_OPERATION
  } kind;
  union {
    int value; // for integer values
    struct {
      int operator; // PLUS, MINUS, etc
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
};

struct var {
  char* nome;
}

struct _BoolExpr{
  enum {
    E_BOPERATION,
    E_BOOLEAN
  } kind;
  union {
    int value; // for integer values
    struct {
      int operator; // PLUS, MINUS, etc
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
};

struct _Cmd{
  enum {
    E_IF; //expr e uma lista de comando
    E_IF_ELSE;
    E_CICLO;
    E_ATTR;//1 var
    E_SCAN;
    E_PRINT;
  } kind;
  union {
    struct {
      char var;
      struct _Expr* expr;
    } atributo; // para atribuições
    struct {
      struct _Expr* cond;
      struct _Cmd* comando;
    } ciclo; //para o while
    struct {
      struct _Expr* cond;
      struct _Cmd* comando; //por lista de comandos
    } se; //if
    struct {
      struct _Expr* cond;
      struct _Cmd* comando;
    } entao; //if than else
    struct {
      char* letra;
      lvar* vars;
    } scan;
    struct{
      char* letra;
      lvar* vars;
    } print;
  } attr;
};

struct
{
  struct _Cmd* comando;
  struct lcmd* next;
} lcmd ;

struct {
  char* letra;
} var;

struct {
  char* letra;
  struct _Expr* valor;
} ldecl;

struct {
  char* letra;
  struct var* next;
} lvar;


typedef struct _Expr Expr; // Convenience typedef
typedef struct _BoolExpr BoolExpr;
typedef struct _Cmd Cmd;

// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
//BoolExpr* ast_boolean(int v);
//BoolExpr* ast_booleanrel(Expr* left, int operator, Expr* right);
Cmd* ast_attrib (char var, Expr* expr);
lcmd* lista_comandos(Cmd* comando, lcmd* next);
Expr ast_var(char* v);
Cmd* ast_ciclos (Expr* cond, Cmd* comando);
Cmd* ast_if(Expr* cond, Cmd* comando);
Cmd* ast_ifthenelse(Expr* cond, Cmd* comando);
var* ast_ldecl_var(char* letra);
var* ast_ldecl_decl(char* letra, Expr* valor);
lvar* ast_lvar(char* letra, lvar* next);
var* ast_var(char* letra);
cmd* ast_scan();
cmd* ast_scan();

#endif
