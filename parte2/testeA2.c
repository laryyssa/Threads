/* 
+ Faça um programa que some duas matrizes quadradas A e B de dimensões 1000x1000. 

+ Faça a soma sem usar threads e com 4 threads (uma thread para cada quadrante).

+ Compare o tempo de execução das duas versões. Meça o tempo com precisão de nanossegundos.

*/

#include <stdio.h>
#include <threads.h>
#include <time.h>
#include <unistd.h>

#define TAM 8



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

void somaMatrizes(void* a[TAM][TAM], void* b[TAM][TAM]){
    for (int i=0; i<TAM; i++){
        for (int j=0; j<TAM; j++){
            printf("%d ",a[i][j] + b[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    int m1[TAM][TAM];
    int m2[TAM][TAM];

    long double tempo, tempo_thread;
    clock_t inicio, fim;
    clock_t inicio_thread, fim_thread;

   
    for (int i=0; i<TAM; i++){
        for(int j=0; j<TAM; j++){
            m1[i][j] = preencher(i,j);
            m2[i][j] = preencher(i,j);
        }
    }
    
    printf("As duas matrizes inicialmente: \n");
    for (int i=0; i<TAM; i++){
        for(int j=0; j<TAM; j++){
            printf("%d ", m1[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // SEM THREAD ------------------------------------

    inicio = clock();

    somaMatrizes(m1, m2);

    fim  = clock();

    // COM THREAD ------------------------------------

    thrd_t t1, t2, t3, t4;
    thrd_t *threads[] = {&t1, &t2, &t3, &t4};

    inicio_thread = clock();

    for(int i=0; i<4; i++){
        thrd_create(threads[i], (thrd_start_t) somaMatrizes, (void*)m1, (void*)m2);
    }
    
    fim_thread = clock();

    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    tempo_thread = (double)(fim_thread - inicio_thread) / CLOCKS_PER_SEC;

    printf("------------------\n Tempo sem threads: %LF\n Tempo com threads: %LF.", tempo, tempo_thread);
    
}