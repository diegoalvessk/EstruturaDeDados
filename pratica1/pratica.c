#include <stdio.h>
#include <stdlib.h>
#include "pratica.h"

float **alocaMatriz(int n) {
    float **matriz = (float **) malloc(n * sizeof(float *));
    if (matriz == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        matriz[i] = (float *) malloc(n * sizeof(float));
        if (matriz[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matriz[j]);
            }
            free(matriz);
            return NULL;
        }
    }

    return matriz;
}

void liberaMatriz(float **matriz, int n) {
    if (matriz == NULL) {
        return;
    }

    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void leMatriz(float **matriz, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%f", &matriz[i][j]);
        }
    }
}

static int pertenceArea(int i, int j, int n, char area) {
    if (area == 'U') {
        return (i < j) && (i < n - 1 - j);
    }
    if (area == 'B') {
        return (i > j) && (i > n - 1 - j);
    }
    if (area == 'L') {
        return (j < i) && (j < n - 1 - i);
    }
    if (area == 'R') {
        return (j > i) && (j > n - 1 - i);
    }

    return 0;
}

double calculaArea(float **matriz, int n, char operacao, char area) {
    double soma = 0.0;
    int quantidade = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (pertenceArea(i, j, n, area)) {
                soma += matriz[i][j];
                quantidade++;
            }
        }
    }

    if (operacao == 'M' && quantidade > 0) {
        return soma / quantidade;
    }

    return soma;
}