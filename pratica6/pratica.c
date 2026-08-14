#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[101];
    int vitorias;
    int pontos;
} Jogador;

void ordenar_ranking(Jogador jogadores[], int quantidade);

int main(void) {
    int quantidade;
    int i;
    Jogador *jogadores;

    if (scanf("%d", &quantidade) != 1) {
        return 0;
    }

    jogadores = (Jogador *) malloc((size_t) quantidade * sizeof(Jogador));
    if (jogadores == NULL) {
        return 1;
    }

    for (i = 0; i < quantidade; i++) {
        int derrotas;

        scanf("%100s %d %d", jogadores[i].nome, &jogadores[i].vitorias, &derrotas);
        jogadores[i].pontos = jogadores[i].vitorias - derrotas;
        if (jogadores[i].pontos < 0) {
            jogadores[i].pontos = 0;
        }
    }

    ordenar_ranking(jogadores, quantidade);

    for (i = 0; i < quantidade; i++) {
        printf("%s %d\n", jogadores[i].nome, jogadores[i].pontos);
    }

    free(jogadores);
    return 0;
}
