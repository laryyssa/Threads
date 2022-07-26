/* 
1 - Faça um programa que crie "N" threads ("N" é um dado de entrada lido do teclado) usando a biblioteca <threads.h> do C11. 
Cada thread, quando executar, deverá imprimir na tela "Eu sou a thread <nome> e meu ID é YY", onde YY é o ID 
que o sistema operacional dá para a thread. Explique as saídas do programa quando este é executado. 

Regra 1: NÃO USE VARIÁVEIS GLOBAIS!!!
Regra 2: quando criar uma thread com nome "thread_01", passe o nome completo como parâmetro no formato string.
Regra 3: pegue a ID da thread usando a função thrd_current() e %lu.

2 - Tanto thrd_current() quanto gettid() retornam o ID da thread. 
Altere o programa do exercício 1 para imprimir a ID da thread usando ambas funções. 
Elas retornam o mesmo valor? Se não, pesquise qual a diferença entre elas.

Dica: Para chamar gettid, use instrução syscall(SYS_gettid) e faça include da biblioteca <sys/syscall.h>

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <threads.h>
#include <sys/syscall.h>

void helloThread(void *argumento){
    char *nome = (char *)argumento;
    long id_thread = thrd_current();
    long id_syscall = syscall(SYS_gettid);

    printf("Eu sou a thread %s e meu ID pelo threads.h é %ld\n", nome, id_thread);
    printf("\n");
    printf("Eu sou a thread %s e meu ID pelo syscall.h é %ld\n", nome, id_syscall);
    printf("\n");
}

int main(){
    int n; 
    
    printf("Digite o numero N de threads: ");
    scanf("%d", &n);
    printf("\n");

    thrd_t *threads = malloc(sizeof(thrd_t) * n);
    char **nomes = malloc(sizeof(char**) * n);

    for (int i=0; i<n; i++){
        nomes[i] = malloc(sizeof(char*) * 16);
        sprintf(nomes[i], "thread_%d", i);
    }

    for (int i=0; i<n; i++){
        thrd_create(&threads[i], (thrd_start_t) helloThread, nomes[i]);

    }

    for (int i=0; i<n; i++){
        thrd_join(threads[i], NULL);
    }


    /* for (int i=0; i<n; i++){
        free(nomes[i]);
    }
    free(threads); */
}