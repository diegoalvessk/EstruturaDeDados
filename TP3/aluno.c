#include "aluno.h"

#include <ctype.h>
#include <stdlib.h>

enum TipoNo {
    NO_VALOR,
    NO_OPERADOR
};

struct No {
    enum TipoNo tipo;
    int valor;
    char operador;
    No *esq;
    No *dir;
};

struct Expr {
    No *raiz;
    int valida;
};

/* guarda onde estou lendo a string da expr */
typedef struct Parser {
    const char *atual;
    int erro;
} Parser;

void pulaEspacos(Parser *p);
No *parseExpressao(Parser *p);
No *parseTermo(Parser *p);
No *parseFator(Parser *p);
No *criaValor(int valor);
No *criaOperador(char operador, No *esq, No *dir);
void destroiNo(No *no);
int avaliaNo(No *no, int *erro);

Expr *criarExpr(const char *expressao)
{
    Parser p;
    Expr *expr;

    if (expressao == NULL) {
        return NULL;
    }

    expr = (Expr *)malloc(sizeof(Expr));
    if (expr == NULL) {
        return NULL;
    }

    p.atual = expressao;
    p.erro = 0;

    /* aqui ja monta a arvore toda */
    expr->raiz = parseExpressao(&p);
    pulaEspacos(&p);
    expr->valida = !p.erro && expr->raiz != NULL && *p.atual == '\0';

    if (!expr->valida) {
        destroiNo(expr->raiz);
        expr->raiz = NULL;
    }

    return expr;
}

int avaliaExpr(Expr *e, int *erro)
{
    if (erro != NULL) {
        *erro = 0;
    }

    if (e == NULL || !e->valida || e->raiz == NULL) {
        if (erro != NULL) {
            *erro = 2;
        }
        return 0;
    }

    return avaliaNo(e->raiz, erro);
}

void destroiExpr(Expr *e)
{
    if (e == NULL) {
        return;
    }

    destroiNo(e->raiz);
    free(e);
}

void pulaEspacos(Parser *p)
{
    while (isspace((unsigned char)*p->atual)) {
        p->atual++;
    }
}

No *parseExpressao(Parser *p)
{
    No *esq;

    /* soma/sub fica por ultimo pq tem menor prioridade */
    esq = parseTermo(p);
    if (p->erro) {
        return esq;
    }

    while (1) {
        char op;
        No *dir;

        pulaEspacos(p);
        op = *p->atual;
        if (op != '+' && op != '-') {
            break;
        }

        p->atual++;
        dir = parseTermo(p);
        esq = criaOperador(op, esq, dir);

        if (esq == NULL || dir == NULL) {
            p->erro = 1;
            return esq;
        }
    }

    return esq;
}

No *parseTermo(Parser *p)
{
    No *esq;

    /* mult/div tem prioridade maior q soma/sub */
    esq = parseFator(p);
    if (p->erro) {
        return esq;
    }

    while (1) {
        char op;
        No *dir;

        pulaEspacos(p);
        op = *p->atual;
        if (op != '*' && op != '/') {
            break;
        }

        p->atual++;
        dir = parseFator(p);
        esq = criaOperador(op, esq, dir);

        if (esq == NULL || dir == NULL) {
            p->erro = 1;
            return esq;
        }
    }

    return esq;
}

No *parseFator(Parser *p)
{
    No *no;

    pulaEspacos(p);

    if (*p->atual == '-') {
        No *zero;
        No *dir;

        /* -x vira 0 - x, assim entra normal na arvore */
        p->atual++;
        zero = criaValor(0);
        dir = parseFator(p);
        no = criaOperador('-', zero, dir);

        if (no == NULL || dir == NULL) {
            p->erro = 1;
        }

        return no;
    }

    if (*p->atual == '(') {
        p->atual++;
        no = parseExpressao(p);

        pulaEspacos(p);
        if (*p->atual != ')') {
            p->erro = 1;
            return no;
        }

        p->atual++;
        return no;
    }

    if (isdigit((unsigned char)*p->atual)) {
        int valor = 0;

        while (isdigit((unsigned char)*p->atual)) {
            valor = valor * 10 + (*p->atual - '0');
            p->atual++;
        }

        return criaValor(valor);
    }

    p->erro = 1;
    return NULL;
}

No *criaValor(int valor)
{
    No *no = (No *)malloc(sizeof(No));

    if (no == NULL) {
        return NULL;
    }

    no->tipo = NO_VALOR;
    no->valor = valor;
    no->operador = '\0';
    no->esq = NULL;
    no->dir = NULL;

    return no;
}

No *criaOperador(char operador, No *esq, No *dir)
{
    No *no;

    if (esq == NULL || dir == NULL) {
        destroiNo(esq);
        destroiNo(dir);
        return NULL;
    }

    no = (No *)malloc(sizeof(No));
    if (no == NULL) {
        destroiNo(esq);
        destroiNo(dir);
        return NULL;
    }

    no->tipo = NO_OPERADOR;
    no->valor = 0;
    no->operador = operador;
    no->esq = esq;
    no->dir = dir;

    return no;
}

void destroiNo(No *no)
{
    if (no == NULL) {
        return;
    }

    destroiNo(no->esq);
    destroiNo(no->dir);
    free(no);
}

int avaliaNo(No *no, int *erro)
{
    int esq;
    int dir;

    if (no == NULL) {
        if (erro != NULL) {
            *erro = 2;
        }
        return 0;
    }

    if (erro != NULL && *erro != 0) {
        return 0;
    }

    if (no->tipo == NO_VALOR) {
        return no->valor;
    }

    esq = avaliaNo(no->esq, erro);
    dir = avaliaNo(no->dir, erro);

    /* se alguma subarvore deu erro, para por aqui */
    if (erro != NULL && *erro != 0) {
        return 0;
    }

    switch (no->operador) {
    case '+':
        return esq + dir;
    case '-':
        return esq - dir;
    case '*':
        return esq * dir;
    case '/':
        /* nao pode deixar dividir por zero */
        if (dir == 0) {
            if (erro != NULL) {
                *erro = 1;
            }
            return 0;
        }
        return esq / dir;
    default:
        if (erro != NULL) {
            *erro = 2;
        }
        return 0;
    }
}
