#include <stdlib.h>

typedef struct {
    char nome[101];
    int vitorias;
    int pontos;
} Jogador;

static int vem_antes(Jogador a, Jogador b) {
    if (a.pontos != b.pontos) {
        return a.pontos > b.pontos;
    }

    return a.vitorias >= b.vitorias;
}

static void intercalar(Jogador jogadores[], Jogador auxiliar[], int inicio, int meio, int fim) {
    int i = inicio;
    int j = meio + 1;
    int k = inicio;

    while (i <= meio && j <= fim) {
        if (vem_antes(jogadores[i], jogadores[j])) {
            auxiliar[k] = jogadores[i];
            i++;
        } else {
            auxiliar[k] = jogadores[j];
            j++;
        }
        k++;
    }

    while (i <= meio) {
        auxiliar[k] = jogadores[i];
        i++;
        k++;
    }

    while (j <= fim) {
        auxiliar[k] = jogadores[j];
        j++;
        k++;
    }

    for (i = inicio; i <= fim; i++) {
        jogadores[i] = auxiliar[i];
    }
}

static void merge_sort(Jogador jogadores[], Jogador auxiliar[], int inicio, int fim) {
    int meio;

    if (inicio >= fim) {
        return;
    }

    meio = inicio + (fim - inicio) / 2;
    merge_sort(jogadores, auxiliar, inicio, meio);
    merge_sort(jogadores, auxiliar, meio + 1, fim);
    intercalar(jogadores, auxiliar, inicio, meio, fim);
}

void ordenar_ranking(Jogador jogadores[], int quantidade) {
    Jogador *auxiliar;

    if (quantidade <= 1) {
        return;
    }

    auxiliar = (Jogador *) malloc((size_t) quantidade * sizeof(Jogador));
    if (auxiliar == NULL) {
        return;
    }

    merge_sort(jogadores, auxiliar, 0, quantidade - 1);
    free(auxiliar);
}
