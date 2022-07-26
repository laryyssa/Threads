#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef MAX
#define MAX 100
#endif

int main(int argc, char *argv[]) {
    const char* str1 = "hello there";
    int n1 = 1234;

    char *num;
    char buffer[MAX];

    if (asprintf(&num, "%d", n1) == -1) {
        perror("asprintf");
    } else {
        strcat(strcpy(buffer, str1), num);
        printf("%s\n", buffer);
        free(num);
    }

    exit(EXIT_SUCCESS);
}