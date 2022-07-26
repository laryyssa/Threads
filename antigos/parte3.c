// MEU CODIGO

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define TAM 1000000

// Crie um vetor de tamanho 1000000
// Preencher de tam aleatórios de 1 a 100
// 2 threads: Remove numeros pares e remove multiplos de 5

// Teste o programa com e sem semáfaros. Qual dos dois pe mais tápido
// OBRIGATORIO: Constuir uma função para verificar se o final está correto 
    // Fazer remoção de /2 e /5 sem thread

void *pares (){

}

void *multiplosDeCinco(){

}

int main(){
    int v[TAM];
    time_t t;

    srand((unsigned) time(&t));


    for (int i=0; i<TAM; i++){
        v[i] = 1 + rand() % 101;
    }

    pthread_t T1;
    pthread_t T2;

    pthread_create(&T1, NULL, pares, (void *)&T1);
    pthread_create(&T2, NULL, multiplosDeCinco, (void *)&T2);

    pthread_exit(NULL);

    return 0;
}