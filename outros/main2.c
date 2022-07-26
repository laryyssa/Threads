#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void * work(void * tid){
    long *myID = (long *) tid;
    printf ("Hello this is thread %ld\n", *myID);
}

/* int main(){

    pthread_t tid;
    pthread_create(&tid, NULL, work, (void *)&tid);
    // Endereço de tid
    // Atributos de uma thread e como vc quer q ela se comport (ex: not joinable)
    // A funçãoq ue a thread vai executar
    // Argumento que passará para a função

    pthread_exit(NULL);
    // A função main é forçada a aguardar a thread terminar seu trabalho
    // Se não incluir main vai terminar antes da thread 

    return 0;
}  */

pthread_t * enderecoThread(){
    pthread_t variavel;
    return &variavel;
}

int main(){
    int n = 5;
    pthread_t array[n];

    for (int i=0; i<n; i++){
        array[i] = enderecoThread()
    }
}