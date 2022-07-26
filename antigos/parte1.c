// MEU CODIGO

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

typedef struct THREAD{
    char nome[1000000];
    int num_thread;
    long ID;

} thread;

int num_threads(){
    int num;
    printf("Digite o numero de threads: ");
    scanf("%d", &num);
    return num;
}

void * criarThread(pthread_t *a, int valor){
    thread *novo = (no *) malloc (sizeof(no));
    novo -> nome = num;
    novo -> num_thread = valor;
    topo -> inicio = novo;
}

void * work(void * tid){
    long *myID = (long *) tid;
    printf ("Hello this is thread %ld\n", *myID);
}

int main(){

    int n = num_threads();
    pthread_t * array[n];

    for (int i=1; i<n+1; i++){
        pthread_create(array[i], NULL, work, (void *)array[i]);

    }

    pthread_exit(NULL);
    

    return 0;
}