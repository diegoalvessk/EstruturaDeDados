#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d",&n);

    Upa *upas = malloc(sizeof(Upa)*n);

    for(int i=0;i<n;i++){
        int p;
        scanf("%d",&p);
        Upa *u = alocarUpa(p);
        upas[i] = *u;
        free(u);
        lePacientesUpa(&upas[i]);

        printf("Fila de prioridade da UPA %d:\n", i+1);
        imprimeUpa(&upas[i]);
        printf("\n");
    }

    Upa *total = alocarUpa(0);
    agrupaUpas(upas,n,total);

    printf("UPA com todos os pacientes:\n");
    imprimeUpa(total);

    for(int i=0;i<n;i++)
        free(upas[i].pacientes);

    free(upas);
    desalocarUpa(&total);

    return 0;
}
