#include <stdio.h>
#include <string.h>

#include "aluno.h"

int esta_na_lista(char lista[][TAM_NOME], int quantidade, const char *nome)
{
    int i;

    for (i = 0; i < quantidade; i++) {
        if (strcmp(lista[i], nome) == 0) {
            return 1;
        }
    }

    return 0;
}

int procura_sugestao(Sugestao sugestoes[], int quantidade, const char *nome)
{
    int i;

    for (i = 0; i < quantidade; i++) {
        if (strcmp(sugestoes[i].nome, nome) == 0) {
            return i;
        }
    }

    return -1;
}

void adiciona_sugestao(Sugestao sugestoes[], int *quantidade, int limite, const char *nome)
{
    int posicao = procura_sugestao(sugestoes, *quantidade, nome);

    if (posicao >= 0) {
        sugestoes[posicao].aparicoes++;
        return;
    }

    if (*quantidade >= limite) {
        return;
    }

    snprintf(sugestoes[*quantidade].nome, TAM_NOME, "%s", nome);
    sugestoes[*quantidade].aparicoes = 1;
    (*quantidade)++;
}
