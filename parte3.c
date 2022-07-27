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
#include <semaphore.h>

#define TAM 10

int m[TAM];
int n[TAM];
int o[TAM];

//pthread_mutex_t mutex;
sem_t smutex;

// REMOVER SEM SEMAFORO ----------------------------- 

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

// REMOVER COM SEMAFORO ----------------------------- 

void * removeComSemaforo(void *v){
    int **vetor = (int**)v;
    int *vetor_aux = (int*)vetor;

    //pthread_mutex_lock(&mutex);
    sem_wait(&smutex);

    for (int i=0; i<TAM; i++){
        if (vetor_aux[i] % 5 == 0){
            vetor_aux[i] = 0;
        }
    }

    //pthread_mutex_unlock(&mutex);
    sem_post(&smutex);
}

// IMPRIMIR VETOR ----------------------------------

void imprimir(int *vetor){
    printf("oi");
    for(int i; i<TAM; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

// MAIN --------------------------------------------- 

int main(){
    int i, valor;
    struct timespec inicio, fim, s_inicio, s_fim;

    sem_init(&smutex, 0, 1);

    srand(time(NULL));

    for(i=0 ; i < TAM ; i++){
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

    pthread_ threads[] = {&T1, &T2};

    clock_gettime(CLOCK_MONOTONIC, &s_inicio);

    for(int i=0; i<2; i++){
        if (pthread_create(&treads[i], NULL, removeComSemaforo, (void*)n) != 0){
        printf("erro");
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &s_fim);

    // -------------------------------- SEM THREADS ----------------------------------
    
    for (int i=0; i<TAM; i++){
        printf("%d ", o[i]);
        if (o[i] % 2 == 0){
            o[i] = 0;
        } else if (o[i] % 5 == 0){
            o[i] = 0;
        }
    }





    // ----------------------------------------------------------------

    printf("\nCom thread, sem semáforo: \n");
    for(int i; i<TAM; i++){
        printf("%d ", m[i]);
    }
    printf("\n");

    printf("\nCom thread, com semáforo: \n");
    for(int i; i<TAM; i++){
        printf("%d ", n[i]);
    }
    printf("\n");

    printf("\nSem thread, sem semáforo: \n");
    for(int i; i<TAM; i++){
        printf("%d ", o[i]);
    }
    printf("\n");
}