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
	
+ Compare o tempo de execução sem threads e com threads + semáforos. Use alguma biblioteca para pegar o tempo atual do sistema. Qual o mais rápido?

+ (*OBRIGATÓRIO*) Construa uma função que avalia se o resultado final está correto, ou seja:
	* faça remoção de múltiplos de 2 e 5 sequencialmente (ou seja, sem usar threads).
	* compare resultado com saída da versão com threads.


*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define TAM 10

int main(){
    int i;
    int *v;

    srand(time(NULL));

    for(i=1 ; i <= TAM ; i++){
        v[i] = rand()%100;
        printf("Numero %d: %d\n",i, v[i]);
    }

    // -------------------------------- COM THREADS ----------------------------------

    thrd_t T1, T2;

    // SEM SEMAFORO ----------------------------------


    // COM SEMAFORO ----------------------------------

    // -------------------------------- SEM THREADS ----------------------------------
}