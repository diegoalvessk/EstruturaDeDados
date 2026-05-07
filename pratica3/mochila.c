#include <stdio.h>
#include <stdlib.h>
#include "mochila.h"

void backtrack(Mochila *m, int i, int pesoAtual, int valorAtual) {

    // passou do peso → invalida
    if (pesoAtual > m->capacidade)
        return;

    // chegou no final → solução completa
    if (i == m->n) {

        m->solucoes++; // conta solução válida

        if (valorAtual > m->maiorValor)
            m->maiorValor = valorAtual;

        return;
    }

    // não pega o item
    backtrack(m, i + 1, pesoAtual, valorAtual);

    // pega o item
    backtrack(m, i + 1,
              pesoAtual + m->itens[i].peso,
              valorAtual + m->itens[i].valor);
}

Mochila* criarMochila(int n, int capacidade) {
    Mochila *m = (Mochila*) malloc(sizeof(Mochila));
    m->itens = (Item*) malloc(n * sizeof(Item));
    m->n = n;
    m->capacidade = capacidade;
    m->maiorValor = 0;
    m->solucoes = 0;
    return m;
}

void destruirMochila(Mochila *m) {
    free(m->itens);
    free(m);
}

void resolverMochila(Mochila *m) {
    backtrack(m, 0, 0, 0);
}