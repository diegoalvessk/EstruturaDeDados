#ifndef ALUNO_H
#define ALUNO_H

typedef struct No No;
typedef struct Expr Expr;

/* Cria uma arvore a partir da expressao. */
Expr *criarExpr(const char *expressao);

/* Avalia a expressao. Em caso de divisao por zero, erro recebe 1. */
int avaliaExpr(Expr *e, int *erro);

/* Libera a memoria usada pela expressao. */
void destroiExpr(Expr *e);

#endif
