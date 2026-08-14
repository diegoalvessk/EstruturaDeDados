#include "aluno.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define LIMITE_TERMO 512

int main(void) {
    Indice *indice = indice_novo();
    char termo[LIMITE_TERMO];
    int tamanho_termo = 0;
    int caractere;

    /* Le caractere por caractere ate o EOF */
    while ((caractere = getchar()) != EOF) {
        if (isalpha((unsigned char)caractere)) {
            if (tamanho_termo < LIMITE_TERMO - 1)
                termo[tamanho_termo++] = (char)tolower((unsigned char)caractere);
        } else {
            if (tamanho_termo > 0) {
                termo[tamanho_termo] = '\0';
                indice_adicionar(indice, termo);
                tamanho_termo = 0;
            }
        }
    }

    /* Processa a ultima palavra se a entrada terminar sem um separador */
    if (tamanho_termo > 0) {
        termo[tamanho_termo] = '\0';
        indice_adicionar(indice, termo);
    }

    indice_mostrar(indice);
    indice_liberar(indice);
    return 0;
}
