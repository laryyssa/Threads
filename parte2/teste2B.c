/* 
+ Faça um programa que some duas matrizes quadradas A e B de dimensões 1000x1000. 

+ Faça a soma sem usar threads e com 4 threads (uma thread para cada quadrante).

+ Compare o tempo de execução das duas versões. Meça o tempo com precisão de nanossegundos.

*/

#include <stdio.h>
//#include <threads.h>
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
    long double tempo, tempo_thread;
    clock_t inicio, fim;
    clock_t inicio_thread, fim_thread;

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

    inicio = clock();

    somaMatrizes();

    fim  = clock();

    // COM THREAD ------------------------------------

    pthread_t threads[4];
    int num;

    inicio_thread = clock();


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

    
    
    fim_thread = clock();

    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    tempo_thread = (double)(fim_thread - inicio_thread) / CLOCKS_PER_SEC;

    printf("------------------\n Tempo sem threads: %LF\n Tempo com threads: %LF.", tempo, tempo_thread);
    
}