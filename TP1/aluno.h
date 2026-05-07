#ifndef ALUNO_H
#define ALUNO_H

typedef struct polinomio Polinomio;

Polinomio* criarPolinomio(int n);
void destroiPolinomio(Polinomio* p);

int inserirTermo(Polinomio* p, double coeficiente, int expoente);

void avaliarPolinomio(Polinomio* derivada);

int polinomioConstante(Polinomio* p);

double valorConstante(Polinomio* p);

Polinomio* derivarPolinomio(Polinomio* p);

void analisarPolinomio(Polinomio* derivada, double inicio, double fim);

void imprimirPolinomio(Polinomio* p);

void imprimirDerivado(Polinomio* derivada);


#endif
