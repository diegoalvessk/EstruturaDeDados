#ifndef HEAP_H
#define HEAP_H

typedef struct {
    char nome[100];
    int idade;
    int estado;
} Paciente;

typedef struct {
    Paciente *pacientes;
    int n;
    int capacidade;
} Upa;

Upa* alocarUpa(int);
void desalocarUpa(Upa**);
Paciente* alocarPacientes(int);
void desalocarPacientes(Paciente**);
void lePacientesUpa(Upa*);
void imprimeUpa(Upa*);
void agrupaUpas(Upa*, int, Upa*);

#endif
