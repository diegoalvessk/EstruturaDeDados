#include <stdio.h>
#include "mochila.h"

int main() {
    int T;
    scanf("%d", &T);

    int valores[T];
    int solucoes[T];

    for (int t = 0; t < T; t++) {

        int n, k;
        scanf("%d %d", &n, &k);

        Mochila *m = criarMochila(n, k);

        for (int i = 0; i < n; i++) {
            scanf("%d %d", &m->itens[i].peso, &m->itens[i].valor);
        }

        resolverMochila(m);

        valores[t] = m->maiorValor;
        solucoes[t] = m->solucoes;

        destruirMochila(m);
    }

    // 🔥 imprime tudo no final
    for (int t = 0; t < T; t++) {
        printf("Teste %d\n", t + 1);
        printf("%d %d\n\n", valores[t], solucoes[t]);
    }

    return 0;
}