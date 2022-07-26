// MEU CODIGO

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#define TAM 1000

// Some 2 matrizes A e B de dimensões 1000x1000
// Uma soma sem usar threads e com threads
// Compare o tempo em nano segundos

void preencherMatriz(int *m){
    for (int i=0; i<TAM; i++){
        for (int j=0; j<TAM; j++){
            *m[i][j] = 1;
        }
    }
}

void somaMatrizes(int *m, int  *n, int *o){
    for (int i=0; i<TAM; i++){
        for (int j=0; j<TAM; j++){
            *o[i][j] = *m[i][j] + *n[i][j];
        }
    }
}


int main(){
    clock_t t;
    int matrizA[TAM][TAM];
    int matrizB[TAM][TAM];
    int matrizC[TAM][TAM];

    preencherMatriz(matrizA);
    preencherMatriz(matrizB);

    t = clock(); // armazena tempo
    
    somaMatrizes(matrizA, matrizB, matrizC);

    t = clock() - t; // tempo final - inicial
    //printf("Tempo de execucao: %lf", ((double)t)/((CLOCKS_PER_SEC/1000000000)));
    printf("Tempo de execucao: %lf", ((double)t));

    return 0;
}