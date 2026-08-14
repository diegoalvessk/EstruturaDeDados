#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"


int main() {
    int num_processos;
    scanf("%d", &num_processos);

    Processo processos[num_processos];
    for (int i = 0; i < num_processos; ++i) {
        scanf("%d %d %ld", &processos[i].tempo_aloc, &processos[i].tempo_desaloc, &processos[i].tam);
    }

    long *alocacoes = first_fit(processos, num_processos);

    for (int i = 0; i < num_processos; ++i) {
        printf("Processo %d alocado na posi\303\247\303\243o %ld\n", i, alocacoes[i]);
    }

    free(alocacoes);

    return 0;
}
