#include <stdlib.h>
#include "aluno.h"


#define ALLOCATION_EVENT 0
#define DEALLOCATION_EVENT 1


//Define a ordem dos eventos na simulacao: primeiro pelo tempo, e quando empata, libera memoria antes de tentar uma nova alocacao
//já estudada
static int comparar(const void *a, const void *b) {
    const Evento *evento_a = (const Evento *)a;
    const Evento *evento_b = (const Evento *)b;

    //para ver qual tem que ficar primeiro
    if (evento_a->tempo != evento_b->tempo) {
        return evento_a->tempo - evento_b->tempo;
    }

    //para ver se o tipo é diferente e o instante for o mesmo ele entra meio que no mesmo instante que o outro sai
    if (evento_a->tipo != evento_b->tipo) {
        return evento_b->tipo - evento_a->tipo;
    }

    //ordena pelo indice se tempo e tipo forem iguais
    return evento_a->processo - evento_b->processo;
}


//Mantem os intervalos livres ordenados pelo endereco inicial
//perguntar p estudar mais afundo apos termino
static int compara_intervalos(const void *a, const void *b) {
    //transforma ponteiro em tipo intervalo
    const Intervalo *intervalo_a = (const Intervalo *)a;
    const Intervalo *intervalo_b = (const Intervalo *)b;


    if (intervalo_a->inicio < intervalo_b->inicio) {
        return -1;
    }
    if (intervalo_a->inicio > intervalo_b->inicio) {
        return 1;
    }
    return 0;
}


//arruma todos os eventos antes da simulacao comecar
//apenas qsort
static void ordenar(Evento *eventos, int num_eventos) {
    qsort(eventos, num_eventos, sizeof(Evento), comparar);
}


//junta pedacos livres que ficaram lado a lado
static void juntar(Intervalo *memoria_livre, int *num_intervalos) {
    int destino = 0;

    //se tiver penas um bloco livre n tem nada p juntar
    if (*num_intervalos <= 1) {
        return;
    }

    //organiza por endereço ordem crescente
    qsort(memoria_livre, *num_intervalos, sizeof(Intervalo), compara_intervalos);

    for (int origem = 1; origem < *num_intervalos; ++origem) {

        //aqui calcula onde termina o bloco atual do for
        long fim_atual = memoria_livre[destino].inicio + memoria_livre[destino].tam;

        //ve se o fim do atual esta contido colado no proximo ou dentro dele
        if (fim_atual >= memoria_livre[origem].inicio) {
            //calcula onde termina o bloco do proximo para poder juntar
            long fim_origem = memoria_livre[origem].inicio + memoria_livre[origem].tam;
            //fim do proximo eh maior que fim do atual
            if (fim_origem > fim_atual) {
                //muda o tamanho da memoria livre do atual pois juntamos com o proximo
                memoria_livre[destino].tam = fim_origem - memoria_livre[destino].inicio;
            }
        } else {
            ++destino;
            //proximo bloco continua separado
            memoria_livre[destino] = memoria_livre[origem];
        }
    }
    //pra saber quantos blocos livres tem
    *num_intervalos = destino + 1;
}


//Procura o primeiro espaco livre onde o processo cabe
static long alocar(Processo processo, Intervalo *memoria_livre, int *num_intervalos) {
    //percorre todo os blocos livres
    for (int i = 0; i < *num_intervalos; ++i) {
        //procura uma memoria livre maior que o tamanho do processo
        if (memoria_livre[i].tam >= processo.tam) {
            //guarda onde começa
            long inicio_alocado = memoria_livre[i].inicio;

            //ocupa o tamanho do processo e retira o tamanho do processo do espaço livre para saber  o que tem livre de verdade
            memoria_livre[i].inicio += processo.tam;
            memoria_livre[i].tam -= processo.tam;
            
            //verifica se ocupou todo o espaço do bloco livre
            if (memoria_livre[i].tam == 0) {
                //for para remover o bloco da lista e arrumar o vetor de blocos livres
                for (int j = i; j < *num_intervalos - 1; ++j) {
                    memoria_livre[j] = memoria_livre[j + 1];
                }
                //como um bloco foi removido atualiza a quantidade de intervalos livres
                --(*num_intervalos);
            }

            //retorna onde o bloco foi alocado, o começo dele
            return inicio_alocado;
        }
    }

    //se nenhum bloco servir retorna isso
    return -1;
}


//devolve para a lista de memoria livre o espaco que o processo ocupava
static void mexer_processo(Processo processo, long inicio, Intervalo *memoria_livre, int *num_intervalos) {
    //cria um novo bloco livre onde começa onde o processo estava
    memoria_livre[*num_intervalos].inicio = inicio;
    //tamanho igual do processo
    memoria_livre[*num_intervalos].tam = processo.tam;
    ++(*num_intervalos);
    //chama essa função para caso existam vazios juntam eles
    juntar(memoria_livre, num_intervalos);
}


//simula todas as entradas e saidas de processos usando o first-fit
long * first_fit(Processo *processos, int num_processos) {
    //vetor que guardara onde cada processo foi colocado
    long * alocacoes = (long *)malloc(num_processos*sizeof(long));
    //cada processo tem 2 eventos (entrada e saida)
    Evento eventos[num_processos*2];
    //lista de espaços vazios
    Intervalo *memoria_livre = (Intervalo *)malloc((num_processos + 1)*sizeof(Intervalo));
    int num_intervalos = 1;
    long max_tam = 0;

    //percorre todos os processos
    for (int i = 0; i < num_processos; ++i) {
        //tempo de chegada
        eventos[2*i].tempo = processos[i].tempo_aloc;
        //tipo do evento
        eventos[2*i].tipo = ALLOCATION_EVENT;
        //qual processo esse evento representa
        eventos[2*i].processo = i;

        //tempo de saida
        eventos[2*i + 1].tempo = processos[i].tempo_desaloc;
        //tipo do evento
        eventos[2*i + 1].tipo = DEALLOCATION_EVENT;
        //qual processo esse evento representa
        eventos[2*i + 1].processo = i;

        //soma o tamanho de todos
        max_tam += processos[i].tam;
    }

    //inicializa a memoria
    memoria_livre[0].inicio = 0;
    memoria_livre[0].tam = max_tam;

    //ordena todos os eventos
    ordenar(eventos, num_processos*2);

    for (int i = 0; i < num_processos*2; ++i) {
        //saber qual processo pertence o evento 
        int indice_processo = eventos[i].processo;

        //verifica se é de entrada ou saida
        if (eventos[i].tipo == ALLOCATION_EVENT) {
            //guarda a posição que foi alocado
            alocacoes[indice_processo] = alocar(processos[indice_processo], memoria_livre, &num_intervalos);
        } else {
            //devolve o espaço vazio
            mexer_processo(processos[indice_processo], alocacoes[indice_processo], memoria_livre, &num_intervalos);
        }
    }

    free(memoria_livre);

    return alocacoes;
}
