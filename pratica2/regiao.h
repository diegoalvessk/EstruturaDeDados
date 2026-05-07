#ifndef REGIAO_H
#define REGIAO_H

typedef struct {
    int x, y;
} Ponto;

typedef struct {
    Ponto sup_esq;
    Ponto inf_dir;
} Regiao;

Regiao criarRegiao(int x, int y, int u, int v);
Regiao intersecao(Regiao r1, Regiao r2);
int vazia(Regiao r);

#endif