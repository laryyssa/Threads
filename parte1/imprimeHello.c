#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#ifndef NUM_THREADS
#define NUM_THREADS 4
#endif
#define MAX 100

void *printHello(void *threadid) {
    long tid;
    tid = (long)threadid;
    printf("Hello There! thread %ld, pthread ID - %lu\n", tid, pthread_self());
    pthread_exit(NULL);
}


int main(int argc, char const *argv[]) {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    const char* nome = "thread_";char buffer[MAX];char *num;

    for (t = 0; t < NUM_THREADS; t++) {
        /* rc = pthread_create(&threads[t], NULL, printHello, (void *)t); */
        //char numero = t + '0';
        
        /* rc = pthread_create(&threads[t], NULL, printHello, ());
        if (rc) {
            printf("ERORR; return code from pthread_create() is %d\n", rc);
            exit(EXIT_FAILURE);
        } */

        if (asprintf(&num, "%d", t) == -1) {
            perror("asprintf");
        } else {
            strcat(strcpy(buffer, nome), num);
            printf("%s\n", buffer);
            free(num);
        }

        exit(EXIT_SUCCESS);
    }
    pthread_exit(NULL);
}