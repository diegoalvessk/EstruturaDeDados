#ifndef ALUNO_H
#define ALUNO_H

/* Elemento da Arvore Binaria de Busca (ABB) */
typedef struct Item {
    char        *termo;
    int          ocorrencias;
    struct Item *menor;
    struct Item *maior;
} Item;

/* Arvore Binaria de Busca */
typedef struct {
    Item *inicio;
} Indice;

Indice *indice_novo(void);

void indice_adicionar(Indice *indice, const char *termo);

void indice_mostrar(Indice *indice);

void indice_liberar(Indice *indice);

#endif 
