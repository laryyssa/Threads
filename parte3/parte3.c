/* 

Implementar o seguinte programa:

+ Criar um vetor de inteiros de tamanho 100.000.

+ Preencher o vetor com números aleatórios entre 1 e 100.
   * Mude o seed quando achar que terminou e rode algumas vezes para ver se não tem erros.

+ Criar 2 threads:
	* T1 remove números pares do vetor.
	* T2 remove números múltiplos de 5 do vetor.
	
+ Remova do fim para o começo do vetor e mantenha a ordem original dos elementos.

+ Teste o programa com e sem semáforos (ambos com threads), observe o resultado e explique o que está acontecendo.
	
+ Compare o tempo de execução sem threads e com threads + semáforos. Use alguma biblioteca para pegar o tempo atual do sistema. 
  Qual o mais rápido?

+ (*OBRIGATÓRIO*) Construa uma função que avalia se o resultado final está correto, ou seja:
	* faça remoção de múltiplos de 2 e 5 sequencialmente (ou seja, sem usar threads).
	* compare resultado com saída da versão com threads.


*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define TAM 10

int m[TAM];
int n[TAM];
int o[TAM];

void * removePares(void * v){
    int **vetor = (int**)v;
    int *vetor_aux = (int*)vetor;
    for (int i=0; i<TAM; i++){
        if (vetor_aux[i] % 2 == 0){
            vetor_aux[i] = 0;
        }
    }
}

void * removeMultiplosCinco(void *v){
    int **vetor = (int**)v;
    int *vetor_aux = (int*)vetor;
    for (int i=0; i<TAM; i++){
        if (vetor_aux[i] % 5 == 0){
            vetor_aux[i] = 0;
        }
    }
}

void imprimir(int *vetor){
    for(int i; i<TAM; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main(){
    int i, valor;
    struct timespec inicio, fim, s_inicio, s_fim;

    srand(time(NULL));

    for(i=1 ; i <= TAM ; i++){
        valor = rand()%100;
        m[i] = valor;
        n[i] = valor;
        o[i] = valor;
        printf("Numero %d: %d\n",i, valor);
    }

    // -------------------------------- COM THREADS ----------------------------------

    pthread_t T1, T2;

    // SEM SEMAFORO ----------------------------------

    clock_gettime(CLOCK_MONOTONIC, &inicio);

    if (pthread_create(&T1, NULL, removePares, (void*)m) != 0){
        printf("erro");
    }
    if (pthread_create(&T2, NULL, removeMultiplosCinco, (void*)m) != 0){
        printf("erro");
    }
    pthread_join(T1, NULL);
    pthread_join(T2, NULL);

    clock_gettime(CLOCK_MONOTONIC, &fim);

    // COM SEMAFORO ----------------------------------

    clock_gettime(CLOCK_MONOTONIC, &s_inicio);

    

    clock_gettime(CLOCK_MONOTONIC, &s_fim);

    // -------------------------------- SEM THREADS ----------------------------------
    
    for (int i=0; i<TAM; i++){
        if (o[i] % 2 ==0){
            o[i] = 0;
        } else if (o[i] % 5 == 0){
            o[i] = 0;
        }
    }

    printf("Com thread, sem semáforo: \n");
    imprimir(m);
    printf("Com thread, com semáforo: \n");
    imprimir(n);
    printf("Sem thread, sem semáforo: \n");
    imprimir(o);
}