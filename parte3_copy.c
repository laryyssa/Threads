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

// REMOVER SEM SEMAFORO (THREAD) ----------------------------- 

void * removePares(void * v){
    for (int i=TAM; i>=0; i--){
        if (n[i] % 2 == 0){
            n[i] = 0;
        }
    }
}

void * removeMultiplosCinco(void *v){
    for (int i=TAM; i>=0; i--){
        if (n[i] % 5 == 0){
            n[i] = 0;
        }
    }
}

// REMOVER COM SEMAFORO (THREAD) ----------------------------- 

void * removeComSemaforo(void *v){
    int **vetor = (int**)v;
    int *vetor_aux = (int*)vetor;

    //pthread_mutex_lock(&mutex);
    sem_wait(&smutex);

    for (int i=TAM; i>=0; i--){
        if (vetor_aux[i] % 5 == 0){
            vetor_aux[i] = 0;
        }
    }

    //pthread_mutex_unlock(&mutex);
    sem_post(&smutex);
}

// REMOVER SEM THREADS ------------------------------

void removerSemThread (){
    printf("Imprimir sem Threads \n");
    for (int i=TAM; i>=0; i--){
        if (o[i] % 2 == 0){
            o[i] = 0;
        } else if (n[i] % 5 == 0){
            o[i] = 0;
        }
        printf("%d ", o[i]);
    }
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
    double tempo, s_tempo;

    sem_init(&smutex, 0, 1);

    srand(time(NULL));

    for(i=0 ; i < TAM ; i++){
        valor = rand()%100;
        m[i] = valor;
        n[i] = valor;
        o[i] = valor;
       // printf("Numero %d: %d\n",i, valor);
    }

    
    // -------------------------------- COM THREADS ----------------------------------

    pthread_t T1, T2;

    // SEM SEMAFORO ----------------------------------

    clock_gettime(CLOCK_MONOTONIC, &inicio);

    if (pthread_create(&T1, NULL, removePares, NULL) != 0){
        printf("erro");
    }
    if (pthread_create(&T2, NULL, removeMultiplosCinco, NULL) != 0){
        printf("erro");
    }
    pthread_join(T1, NULL);
    pthread_join(T2, NULL);

    clock_gettime(CLOCK_MONOTONIC, &fim);

    // COM SEMAFORO ----------------------------------

    pthread_t *threads []= {&T1, &T2};

    clock_gettime(CLOCK_MONOTONIC, &s_inicio);

    for(int i=0; i<2; i++){
        if (pthread_create(threads[i], NULL, removeComSemaforo, (void*)n) != 0){
        printf("erro");
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &s_fim);



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

    tempo = (double) (fim.tv_sec - inicio.tv_sec);
    tempo += (double) (fim.tv_nsec - inicio.tv_nsec) / 1000000000.0;

    s_tempo = (double) (s_fim.tv_sec - s_inicio.tv_sec);
    s_tempo += (double) (s_fim.tv_nsec - s_inicio.tv_nsec) / 1000000000.0;

    printf("Tempo sem semáforo: %f\n Tempo com semáforo: %f", tempo, s_tempo);

    removerSemThread();
    
}