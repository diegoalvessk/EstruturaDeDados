#include <stdio.h>
#include <string.h>
#include "aluno.h"

int main() {
    char expressao[10000];

    scanf("%s", expressao);

    Pilha* p = PilhaInicia();

    int faltaAbertura = 0;
    int faltaFechamento = 0;

    for (int i = 0; expressao[i] != '\0'; i++) {

        if (expressao[i] == '(') {
            PilhaPush(p, '(');
        }

        else if (expressao[i] == ')') {

            if (PilhaEhVazia(p)) {
                faltaAbertura = 1;
            }
            else {
                PilhaPop(p);
            }
        }
    }

    if (!PilhaEhVazia(p)) {
        faltaFechamento = 1;
    }

    if (!faltaAbertura && !faltaFechamento) {
        printf("correto\n");
    }
    else {
        if (faltaAbertura) {
            printf("falta abertura de parentese\n");
        }

        if (faltaFechamento) {
            printf("falta fechamento de parentese\n");
        }
    }

    PilhaLibera(p);

    return 0;
}