#include <stdio.h>
#include <stdlib.h>
#include "pratica.h"

int main(void) {
    char operacao, area;
    int n;
    float **matriz;
    double resultado;

    printf("Digite a operacao, area e ordem da matriz: ");
    scanf(" %c %c %d", &operacao, &area, &n);

    if (n < 3) {
        printf("Erro!Ordem minima:3");
        return 0;
    }

    matriz = alocaMatriz(n);
    if (matriz == NULL) {
        return 1;
    }

    leMatriz(matriz, n);

    resultado = calculaArea(matriz, n, operacao, area);

    printf("%.1lf\n", resultado);

    liberaMatriz(matriz, n);

    return 0;
}