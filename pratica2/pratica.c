#include <stdio.h>
#include "regiao.h"

int main() {
    int N;
    scanf("%d", &N);

    if (N == 0) {
        printf("nenhum\n");
        return 0;
    }

    int x, y, u, v;
    scanf("%d %d %d %d", &x, &y, &u, &v);

    Regiao atual = criarRegiao(x, y, u, v);

    for (int i = 1; i < N; i++) {
        scanf("%d %d %d %d", &x, &y, &u, &v);
        Regiao nova = criarRegiao(x, y, u, v);
        atual = intersecao(atual, nova);
    }

    if (vazia(atual)) {
        printf("nenhum\n");
    } else {
        printf("%d %d %d %d\n",
            atual.sup_esq.x,
            atual.sup_esq.y,
            atual.inf_dir.x,
            atual.inf_dir.y);
    }

    return 0;
}