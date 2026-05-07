#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"

int main() {
    int n;
    scanf("%d", &n);

    Polinomio* p = criarPolinomio(n);

    for (int i = 0; i < n; i++) {
        double coeficiente;
        int expoente;
        scanf("%lf %d", &coeficiente, &expoente);

        if (inserirTermo(p, coeficiente, expoente) != 0) {
            destroiPolinomio(p);
            return 0;
        }
    }

    double inicio, fim;
    scanf("%lf %lf", &inicio, &fim);

    if (polinomioConstante(p)) {
        printf("Funcao constante em y = %.2f.\n", valorConstante(p));
        destroiPolinomio(p);
        return 0;
    }

    imprimirPolinomio(p);

    Polinomio* derivada = derivarPolinomio(p);
    imprimirDerivado(derivada);

    analisarPolinomio(derivada, inicio, fim);
    avaliarPolinomio(derivada);
    destroiPolinomio(p);

    return 0;
}

