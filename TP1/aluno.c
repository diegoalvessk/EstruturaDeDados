#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "aluno.h"

typedef struct {
    double coeficiente;
    int expoente;
} Termo;

struct polinomio {
    Termo* termos;
    int quantidade;
    //Guarda os resultados da derivada em cada ponto
    double* valor;
    //Guarda os valores de x dos resultados acima
    double* x;
    int qtd_valores;
};

Polinomio* criarPolinomio(int n) {
    Polinomio* p = malloc(sizeof(Polinomio));

    if (p == NULL) return NULL;

    p->termos = malloc(n * sizeof(Termo));
    p->quantidade = 0;
    if (p->termos == NULL) {
        free(p);
        return NULL;
    }

    p->valor = NULL;
    p->x = NULL;
    p->qtd_valores = 0;

    return p;
}

int inserirTermo(Polinomio* p, double coeficiente, int expoente) {
     if (p == NULL) {
        fprintf(stderr, "Erro ao criar o polinômio.\n");
        return 1;
    }

    // Pelo enunciado, expoente negativo nao entra no polinomio.
    if (expoente < 0) {
        printf("Erro: expoente negativo.\n");
        return 1;
    }

    p->termos[p->quantidade].coeficiente = coeficiente;
    p->termos[p->quantidade].expoente = expoente;
    p->quantidade++;
    return 0; // Sucesso
}

int polinomioConstante(Polinomio* p) {
    if (p == NULL) return 0;

    // Se todos os expoentes forem zero, nao existe x variando na funcao.
    for (int i = 0; i < p->quantidade; i++) {
        if (p->termos[i].expoente != 0) {
            return 0;
        }
    }

    return 1;
}

double valorConstante(Polinomio* p) {
    double soma = 0;

    if (p == NULL) return soma;

    //Quando tem funcao constante, o valor final eh a soma dos termos constantes
    for (int i = 0; i < p->quantidade; i++) {
        soma += p->termos[i].coeficiente;
    }

    return soma;
}

Polinomio* derivarPolinomio(Polinomio* p) {
    for (int i = 0; i < p->quantidade; i++) {

        // Constante some na derivada, porque a inclinacao dela e zero.
        if (p->termos[i].expoente == 0) {
            p->termos[i].coeficiente = 0;
        } 
        else {
            // Regra basica da derivada: a*x^n vira a*n*x^(n-1).
            p->termos[i].coeficiente = p->termos[i].coeficiente * p->termos[i].expoente;
            p->termos[i].expoente = p->termos[i].expoente - 1;
        }
    }

    return p;
}

void analisarPolinomio(Polinomio* derivada, double inicio, double fim) {
    //k funciona como o contador da recursao, substituindo o for
    static int k = 0;
    //Guardo o inicio original para calcular cada x sem substituir por cima
    static double primeiro = 0;

    //vetores que vao guardar x e f'(x)
    if (k == 0) {
        int c = (int)((fim - inicio) / 0.1) + 1;

        //caso o fim nao caia exatamente de 0.1 em 0.1, adiciono o ultimo ponto
        if (inicio + (c - 1) * 0.1 < fim - 0.000001) {
            c++;
        }

        derivada->valor = calloc(c, sizeof(double));
        derivada->x = calloc(c, sizeof(double));
        derivada->qtd_valores = c;
        primeiro = inicio;
    }

    //Caso base: quando ja calculei todos os pontos ela para
    if (k >= derivada->qtd_valores) {
        k = 0;
        return;
    }

    double x = primeiro + k * 0.1;
    double resultado = 0;

    if (x > fim) {
        x = fim;
    }

    //olha a derivada no ponto x somando todos os termos dela
    for (int j = 0; j < derivada->quantidade; j++) {
        resultado += derivada->termos[j].coeficiente * pow(x, derivada->termos[j].expoente);
    }

    //Salvo o par x e f'(x)
    derivada->x[k] = x;
    derivada->valor[k] = resultado;
    k++;

    //Chamada recursiva: calcula o proximo ponto do intervalo
    analisarPolinomio(derivada, inicio, fim);
}

static int sinal(double valor) {
    //evita que um numero muito perto de zero atrapalhe a analise
    if (valor > 0.000001) return 1;
    if (valor < -0.000001) return -1;
    return 0;
}

void avaliarPolinomio(Polinomio* derivada){
    printf("Intervalos de crescimento: ");
    int inicio = -1;

    //Crescimento: derivada eh positiva
    for (int i = 0; i < derivada->qtd_valores; i++) {
        int atual = sinal(derivada->valor[i]);

        if (atual >= 0 && inicio == -1) {
            int tem_crescimento = 0;

            if (atual > 0) tem_crescimento = 1;
            if (i > 0 && sinal(derivada->valor[i - 1]) > 0) tem_crescimento = 1;
            if (i + 1 < derivada->qtd_valores && sinal(derivada->valor[i + 1]) > 0) tem_crescimento = 1;

            if (tem_crescimento) inicio = i;
        }
        else if ((atual < 0 || i == derivada->qtd_valores - 1) && inicio != -1) {
            int fim = i;

            if (atual < 0) fim = i - 1;

            //fecha o intervalo
            printf("[%.2f, %.2f] ", derivada->x[inicio], derivada->x[fim]);
            inicio = -1;
        }
    }
    printf("\n");

    printf("Intervalos de decrescimento: ");
    inicio = -1;

    //Decrescimento eh a mesma ideia, mas negativa
    for (int i = 0; i < derivada->qtd_valores; i++) {
        int atual = sinal(derivada->valor[i]);

        if (atual <= 0 && inicio == -1) {
            int tem_decrescimento = 0;

            if (atual < 0) tem_decrescimento = 1;
            if (i > 0 && sinal(derivada->valor[i - 1]) < 0) tem_decrescimento = 1;
            if (i + 1 < derivada->qtd_valores && sinal(derivada->valor[i + 1]) < 0) tem_decrescimento = 1;

            if (tem_decrescimento) inicio = i;
        }
        else if ((atual > 0 || i == derivada->qtd_valores - 1) && inicio != -1) {
            int fim = i;

            if (atual > 0) fim = i - 1;

            printf("[%.2f, %.2f] ", derivada->x[inicio], derivada->x[fim]);
            inicio = -1;
        }
    }
    printf("\n");

    printf("Pontos de transicao: ");

    //Transicao: muda ou passa por zero
    for (int i = 1; i < derivada->qtd_valores; i++) {
        int anterior = sinal(derivada->valor[i - 1]);
        int atual = sinal(derivada->valor[i]);

        if ((anterior < 0 && atual > 0) ||
            (anterior > 0 && atual < 0)) {
            printf("[%.2f, %.2f] ", derivada->x[i - 1], derivada->x[i]);
        }
        else if (atual == 0 &&
            ((i > 0 && anterior != 0) ||
            (i + 1 < derivada->qtd_valores && sinal(derivada->valor[i + 1]) != 0))) {
            printf("[%.2f, %.2f] ", derivada->x[i], derivada->x[i]);
        }
    }
    printf("\n");
}


void imprimirPolinomio(Polinomio* p) {
    if (p == NULL || p->quantidade == 0) {
        printf("Polinômio vazio.\n");
        return;
    }

    printf("Polinomio: ");

    for (int i = 0; i < p->quantidade; i++) {

        if(p->termos[i].expoente == 0){
            printf("%.2f", p->termos[i].coeficiente);
        }else if (p->termos[i].expoente == 1)
        {
              printf("%.2fx", p->termos[i].coeficiente);
        }else{
            printf("%.2fx^%d", p->termos[i].coeficiente, p->termos[i].expoente);
        }

        if(i + 1 < p->quantidade && p->termos[i + 1].coeficiente > 0){
            printf("+");
        }
    }

    printf("\n");
}

void imprimirDerivado(Polinomio* derivada) {
    if (derivada == NULL || derivada->quantidade == 0) {
        printf("Polinomio vazio.\n");
        return;
    }

    printf("Derivada: ");

    int primeiro = 1;

    for (int i = 0; i < derivada->quantidade; i++) {

        if (derivada->termos[i].coeficiente == 0) {
            continue;
        }

        if (!primeiro && derivada->termos[i].coeficiente > 0) {
            printf("+");
        }

        if (derivada->termos[i].expoente > 1) {
            printf("%.2fx^%d", derivada->termos[i].coeficiente, derivada->termos[i].expoente);
        }
        else if (derivada->termos[i].expoente == 1) {
            printf("%.2fx", derivada->termos[i].coeficiente);
        }
        else {
            printf("%.2f", derivada->termos[i].coeficiente);
        }

        primeiro = 0;
    }

    printf("\n");
}

void destroiPolinomio(Polinomio* p) {
    if (p == NULL) {
        return;
    }
    free(p->termos);
    free(p->valor);
    free(p->x);
    free(p);
}
