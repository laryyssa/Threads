/* 
+ Faça um programa que some duas matrizes quadradas A e B de dimensões 1000x1000. 

+ Faça a soma sem usar threads e com 4 threads (uma thread para cada quadrante).

+ Compare o tempo de execução das duas versões. Meça o tempo com precisão de nanossegundos.

*/

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define TAM 8

int m1[TAM][TAM];
int m2[TAM][TAM];

int preencher(int i, int j){
    int t = TAM/2;
    if (i<t && j<t){
        return 1;
    } else if (i<t && j>=t) {
        return 2;
    } else if (i>=t && j<t) {
        return 3;
    }else if (i>=t && j>=t) {
        return 4;
    }
}

void p_main(){
    for (int i=0; i<TAM; i++){
        for(int j=0; j<TAM; j++){
            m1[i][j] = preencher(i,j);
            m2[i][j] = preencher(i,j);
        }
    }
}


void somaMatrizes(){
    for (int i=0; i<TAM; i++){
        for (int j=0; j<TAM; j++){
            printf("%d ",m1[i][j] + m2[i][j]);

            for (int k=0; k<10000000; k++){

            }
        }
        printf("\n");
    }
    printf("\n");
}

void * somarMatrizes_Thread(void *numero){
    int *num = (int*)numero;
    int t = TAM/2;
    switch (*num){
        case 1:
            for (int i=0; i<t; i++){
                for (int j = 0; j<t; j++){
                    printf("%d ",m1[i][j] + m2[i][j]);
                }
                printf("\n");
            }
        case 2:
            for (int i=0; i<t; i++){
                for (int j = t; j<TAM; j++){
                    printf("%d ",m1[i][j] + m2[i][j]);
                }
                printf("\n");
            }
        case 3:
            for (int i=t; i<TAM; i++){
                for (int j = 0; j<t; j++){
                    printf("%d ",m1[i][j] + m2[i][j]);
                }
                printf("\n");
            }
        case 4:
            for (int i=t; i<TAM; i++){
                for (int j = t; j<TAM; j++){
                    printf("%d ",m1[i][j] + m2[i][j]);
                }
                printf("\n");
            }
    }
}

int main(){
    
    struct timespec inicio, fim, t_inicio, t_fim;
    double tempo, t_tempo;

    p_main();
   
    printf("As duas matrizes inicialmente: \n");
    for (int i=0; i<TAM; i++){
        for(int j=0; j<TAM; j++){
            printf("%d ", m1[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // SEM THREAD ------------------------------------

    printf("Soma sem threads: \n");

    clock_gettime(CLOCK_MONOTONIC, &inicio);

    somaMatrizes();

    clock_gettime(CLOCK_MONOTONIC, &fim);

    // COM THREAD ------------------------------------

    pthread_t threads[4];
    int num;

    clock_gettime(CLOCK_MONOTONIC, &t_inicio);

    printf("Soma com threads: \n");
    for (int i=0; i<4; i++){
        num = i+1;
        if (pthread_create(&threads[i], NULL, somarMatrizes_Thread, (void*)&num) != 0){
            printf("erro");
        }
    }

    for (int i=0; i<4; i++){
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &t_fim);

    tempo = (double) (fim.tv_sec - inicio.tv_sec);
    tempo += (double) (fim.tv_nsec - inicio.tv_nsec) / 1000000000.0;

    t_tempo = (double) (t_fim.tv_sec - t_inicio.tv_sec);
    t_tempo += (double) (t_fim.tv_nsec - t_inicio.tv_nsec) / 1000000000.0;

    printf("-----------------\n");
    printf("Tempo sem thread: %f ns\nTempo com Thread: %f ns \n", tempo, t_tempo);

    printf("Tempo com thread %f  mais rápido\n", tempo/t_tempo *100);
}