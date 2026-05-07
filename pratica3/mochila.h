#ifndef MOCHILA_H
#define MOCHILA_H

typedef struct {
    int peso;
    int valor;
} Item;

typedef struct {
    Item *itens;
    int n;
    int capacidade;
    int maiorValor;
    int solucoes;
} Mochila;

// funções
Mochila* criarMochila(int n, int capacidade);
void destruirMochila(Mochila *m);
void resolverMochila(Mochila *m);

#endif