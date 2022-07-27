/* 
+ Faça um programa que some duas matrizes quadradas A e B de dimensões 1000x1000. 

+ Faça a soma sem usar threads e com 4 threads (uma thread para cada quadrante).

+ Compare o tempo de execução das duas versões. Meça o tempo com precisão de nanossegundos.

*/

#include <stdio.h>
//#include <pthreads.h>
#include <time.h>

#define TAM 5


int main(){
    int m1[TAM][TAM];
    int m2[TAM][TAM];

    long double tempo;
    time_t inicio, fim;

    inicio = time(NULL);

    for (int i=0; i<TAM; i++){
        for(int j=0; j<TAM; j++){
            m1[i][j] = 1;
            m2[i][j] = 1;
        }
    }
    
    for (int i=0; i<TAM; i++){
        for(int j=0; j<TAM; j++){
            printf("%d ", m1[i][j]);
        }
        printf("\n");
    }

    fim = time(NULL);

    tempo = difftime(fim, inicio);

    printf("Tempo: %le\n", tempo);
    
}