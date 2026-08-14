#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void heapConstroi(Paciente*, int);
void heapRefaz(Paciente*, int, int);
bool heapInsere(Paciente*, int, Paciente, int);
bool heapRemove(Paciente*, int, Paciente*);
bool compara(const Paciente*, const Paciente*);

Upa* alocarUpa(int n){
    Upa *u = malloc(sizeof(Upa));
    u->pacientes = NULL;
    u->n = 0;
    u->capacidade = n;
    return u;
}

void desalocarUpa(Upa **upa){
    if(*upa){
        free((*upa)->pacientes);
        free(*upa);
        *upa = NULL;
    }
}

Paciente* alocarPacientes(int n){
    return malloc(sizeof(Paciente)*n);
}

void desalocarPacientes(Paciente **p){
    free(*p);
    *p = NULL;
}

void lePacientesUpa(Upa *upa){
    upa->pacientes = alocarPacientes(upa->capacidade);
    upa->n = upa->capacidade;

    for(int i=0;i<upa->n;i++)
        scanf("%s %d %d", upa->pacientes[i].nome,
              &upa->pacientes[i].idade,
              &upa->pacientes[i].estado);

    heapConstroi(upa->pacientes, upa->n);
}

void imprimeUpa(Upa *upa){
    for(int i=0;i<upa->n;i++)
        printf("%s %d %d\n", upa->pacientes[i].nome,
               upa->pacientes[i].idade,
               upa->pacientes[i].estado);
}

void agrupaUpas(Upa *upas, int n, Upa *dest){
    int total = 0;
    for(int i=0;i<n;i++) total += upas[i].n;

    dest->pacientes = alocarPacientes(total);
    dest->capacidade = total;
    dest->n = 0;

    Paciente p;

    for(int i=0;i<n;i++){
        while(upas[i].n > 0){
            heapRemove(upas[i].pacientes, upas[i].n-1, &p);
            upas[i].n--;
            heapInsere(dest->pacientes, dest->n-1, p, dest->capacidade);
            dest->n++;
        }
    }
}

void heapConstroi(Paciente *v, int n){
    for(int esq=(n/2)-1; esq>=0; esq--)
        heapRefaz(v, esq, n-1);
}

void heapRefaz(Paciente *v, int esq, int dir){
    int i = esq;
    Paciente x = v[i];
    int j = i*2 + 1;

    while(j <= dir){
        if(j < dir && compara(&v[j+1], &v[j]))
            j++;

        if(compara(&x, &v[j]))
            break;

        v[i] = v[j];
        i = j;
        j = 2*i + 1;
    }
    v[i] = x;
}

bool heapInsere(Paciente *v, int dir, Paciente p, int k){
    if(dir + 1 >= k) return false;

    int i = dir + 1;
    while(i > 0){
        int pai = (i-1)/2;
        if(compara(&v[pai], &p))
            break;
        v[i] = v[pai];
        i = pai;
    }
    v[i] = p;
    return true;
}

bool heapRemove(Paciente *v, int dir, Paciente *p){
    if(dir < 0) return false;

    *p = v[0];
    v[0] = v[dir];
    heapRefaz(v,0,dir-1);
    return true;
}

bool compara(const Paciente *a, const Paciente *b){
    if(a->estado != b->estado)
        return a->estado > b->estado;
    if(a->idade != b->idade)
        return a->idade > b->idade;
    return strcmp(a->nome,b->nome) < 0;
}
