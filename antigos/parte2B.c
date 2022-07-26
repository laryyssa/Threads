#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

// Dividir as matrizes em 4 partes 
// Somar cada parte separadamente - threads


void preencherMatriz(int *m[TAM][TAM]){
    for (int i=0; i<TAM; i++){
        for (int j=0; j<TAM; j++){
            *m[i][j] = 1;
        }
    }
}

void somaMatrizes(int *m[TAM][TAM], int  *n[TAM][TAM], int *o[TAM][TAM]){
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

    preencherMatriz(&matrizA);
    preencherMatriz(&matrizB);

    t = clock(); // armazena tempo
    
    somaMatrizes(&matrizA, &matrizB, &matrizC);

    t = clock() - t; // tempo final - inicial
    
    //printf("Tempo de execucao: %lf", ((double)t)/((CLOCKS_PER_SEC/1000000000)));
    printf("Tempo de execucao: %lf", ((double)t));

    return 0;
}