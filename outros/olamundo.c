#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *printOLA (void *parametro){
        printf("Olá Mundo\n");
    
}

void *printOUTRO(void *parametro){
        printf("Outra frase\n");
    
}

int main (){
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, printOLA, NULL);
    pthread_create(&thread2, NULL, printOUTRO, NULL);

    pthread_join(thread2, NULL);
    pthread_join(thread1, NULL);
    //pthread_join(thread2, NULL);

    return 0;
}