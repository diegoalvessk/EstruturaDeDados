#include <stdio.h>
#include <string.h>

#include "aluno.h"

#define MAX_LINHA 10000
#define MAX_NOMES 1000
#define MIN_AMIGOS_COMUNS 3

static void remove_quebra_linha(char *linha)
{
    linha[strcspn(linha, "\r\n")] = '\0';
}

int main(void)
{
    char linha[MAX_LINHA];
    char amigos[MAX_NOMES][TAM_NOME];
    Sugestao sugestoes[MAX_NOMES];
    int qtd_amigos = 0;
    int qtd_sugestoes = 0;
    int imprimiu = 0;
    char *token;
    int i;

    if (fgets(linha, sizeof(linha), stdin) == NULL) {
        return 0;
    }

    remove_quebra_linha(linha);
    token = strtok(linha, " \t");

    while (token != NULL && qtd_amigos < MAX_NOMES) {
        snprintf(amigos[qtd_amigos], TAM_NOME, "%s", token);
        qtd_amigos++;
        token = strtok(NULL, " \t");
    }

    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        char vistos_na_linha[MAX_NOMES][TAM_NOME];
        int qtd_vistos = 0;

        remove_quebra_linha(linha);
        token = strtok(linha, " \t");

        if (token != NULL) {
            token = strtok(NULL, " \t");
        }

        while (token != NULL) {
            if (!esta_na_lista(amigos, qtd_amigos, token) &&
                !esta_na_lista(vistos_na_linha, qtd_vistos, token)) {
                adiciona_sugestao(sugestoes, &qtd_sugestoes, MAX_NOMES, token);
                if (qtd_vistos < MAX_NOMES) {
                    snprintf(vistos_na_linha[qtd_vistos], TAM_NOME, "%s", token);
                    qtd_vistos++;
                }
            }

            token = strtok(NULL, " \t");
        }
    }

    for (i = 0; i < qtd_sugestoes; i++) {
        if (sugestoes[i].aparicoes >= MIN_AMIGOS_COMUNS) {
            printf("%s\n", sugestoes[i].nome);
            imprimiu = 1;
        }
    }

    if (!imprimiu) {
        printf("Nenhuma sugestao disponivel\n");
    }

    return 0;
}
