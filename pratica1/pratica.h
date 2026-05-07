#ifndef PRATICA_H
#define PRATICA_H

float **alocaMatriz(int n);
void liberaMatriz(float **matriz, int n);
void leMatriz(float **matriz, int n);
double calculaArea(float **matriz, int n, char operacao, char area);

#endif