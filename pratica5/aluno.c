#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"

struct celula {
    char dado;
    struct celula* prox;
};

struct pilha {
    Celula* topo;
};

Pilha* PilhaInicia() {
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));

    if (p != NULL) {
        p->topo = NULL;
    }

    return p;
}

int PilhaEhVazia(Pilha* p) {
    return (p->topo == NULL);
}

void PilhaPush(Pilha* p, char c) {
    Celula* nova = (Celula*) malloc(sizeof(Celula));

    nova->dado = c;
    nova->prox = p->topo;
    p->topo = nova;
}

char PilhaPop(Pilha* p) {
    if (PilhaEhVazia(p))
        return '\0';

    Celula* temp = p->topo;
    char valor = temp->dado;

    p->topo = temp->prox;
    free(temp);

    return valor;
}

void PilhaLibera(Pilha* p) {
    while (!PilhaEhVazia(p)) {
        PilhaPop(p);
    }

    free(p);
}