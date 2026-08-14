#include "aluno.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Item *item_novo(const char *termo) {
    Item *registro = (Item *)malloc(sizeof(Item));
    if (!registro) return NULL;
    registro->termo = strdup(termo);
    if (!registro->termo) { free(registro); return NULL; }
    registro->ocorrencias = 1;
    registro->menor       = NULL;
    registro->maior       = NULL;
    return registro;
}

static Item *encaixar_termo(Item *atual, const char *termo) {
    if (!atual) return item_novo(termo);

    int ordem = strcmp(termo, atual->termo);
    if      (ordem < 0) atual->menor = encaixar_termo(atual->menor, termo);
    else if (ordem > 0) atual->maior = encaixar_termo(atual->maior, termo);
    else                atual->ocorrencias++;

    return atual;
}

static void exibir_em_ordem(const Item *atual) {
    if (!atual) return;
    exibir_em_ordem(atual->menor);
    printf("%s: %d\n", atual->termo, atual->ocorrencias);
    exibir_em_ordem(atual->maior);
}

static void apagar_itens(Item *atual) {
    if (!atual) return;
    apagar_itens(atual->menor);
    apagar_itens(atual->maior);
    free(atual->termo);
    free(atual);
}

Indice *indice_novo(void) {
    Indice *indice = (Indice *)malloc(sizeof(Indice));
    if (indice) indice->inicio = NULL;
    return indice;
}

void indice_adicionar(Indice *indice, const char *termo) {
    if (!indice || !termo || termo[0] == '\0') return;
    indice->inicio = encaixar_termo(indice->inicio, termo);
}

void indice_mostrar(Indice *indice) {
    if (!indice) return;
    exibir_em_ordem(indice->inicio);
}

void indice_liberar(Indice *indice) {
    if (!indice) return;
    apagar_itens(indice->inicio);
    free(indice);
}
