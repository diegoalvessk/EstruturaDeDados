#ifndef ALUNO_H
#define ALUNO_H

typedef struct celula Celula;
typedef struct pilha Pilha;

Pilha* PilhaInicia();
int PilhaEhVazia(Pilha* p);
void PilhaPush(Pilha* p, char c);
char PilhaPop(Pilha* p);
void PilhaLibera(Pilha* p);

#endif