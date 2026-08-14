#ifndef ALUNO_H
#define ALUNO_H

#define TAM_NOME 128

typedef struct {
    char nome[TAM_NOME];
    int aparicoes;
} Sugestao;

int esta_na_lista(char lista[][TAM_NOME], int quantidade, const char *nome);
int procura_sugestao(Sugestao sugestoes[], int quantidade, const char *nome);
void adiciona_sugestao(Sugestao sugestoes[], int *quantidade, int limite, const char *nome);

#endif
