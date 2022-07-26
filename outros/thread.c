// MEU CODIGO

#include <stdio.h>
#include <threads.h>


int num_threads(){
    int n;
    printf("Digite o numero de threads desejada: ");
    scanf("%d", &n);
    return n;
}

char nome(int num){
    char n_string = num+'0';
    return ("thread_%s", n_string);
}

void *identifica (char * n){
    //long t= (long)quant;
    printf("Eu sou a %s e meu ID: %lu\n", n, thrd_current());
    //thrd_exit(EXIT_SUCCESS);
}



void function(int num){
    if (num){
        thrd_t threads[num];
        int rc;
        for (long i=0; i<num; i++){
            int threadnumber = (intptr_t) param;
            rc = thrd_create(&threads[i], (thrd_start_t) identifica, &nome(i));
            // rc = thrd_create(thrd_t *threads, thrd_start_t identifica, void * nome);

            // int thrd_create(thrd_t *thr, thrd_start_t func, void *arg);
                // thr - ponteiro para o end de memoria da nova thread
                // func - ponteiro para a função que a thread vai executar
                // arg - argumento para a função
            // Em outras palavras: a thread vai executar -> identifica(nome)

            if (rc == thrd_error) {
                printf("ERORR; thrd_create() call failed\n");
                //exit(EXIT_FAILURE);
            }

        }
    } else {
        printf("Número invalido !");
    }
}

// -------------------------------------- main

int main(){
    function(num_threads());

    return 0; 
}