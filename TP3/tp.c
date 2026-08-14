#include "aluno.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAM_LINHA 1000

void removeQuebraLinha(char *linha)
{
    linha[strcspn(linha, "\r\n")] = '\0';
}

void descartaRestoLinha(void)
{
    int c;

    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int main(void)
{
    int n;

    while (scanf("%d", &n) == 1) {
        int i;
        int *resultados;
        int *erros;

        descartaRestoLinha();

        resultados = (int *)malloc(n * sizeof(int));
        erros = (int *)malloc(n * sizeof(int));

        if (resultados == NULL || erros == NULL) {
            free(resultados);
            free(erros);
            return 0;
        }

        for (i = 0; i < n; i++) {
            char linha[TAM_LINHA];
            Expr *expr;

            if (fgets(linha, sizeof(linha), stdin) == NULL) {
                free(resultados);
                free(erros);
                return 0;
            }

            removeQuebraLinha(linha);

            /* tp.c so chama o TAD e guarda oq deu */
            expr = criarExpr(linha);
            resultados[i] = avaliaExpr(expr, &erros[i]);
            destroiExpr(expr);
        }

        for (i = 0; i < n; i++) {
            if (erros[i] == 1) {
                printf("Erro: divisao por zero.\n");
            } else if (erros[i] != 0) {
                printf("Erro: expressao invalida.\n");
            } else {
                printf("%d\n", resultados[i]);
            }
        }

        free(resultados);
        free(erros);
    }

    return 0;
}
