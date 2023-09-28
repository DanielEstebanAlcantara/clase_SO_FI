#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    printf("Proceso principal: %i\n", getpid());
    printf("\nPrueba de procesos:\n");

    fork();

    printf("\tSe a creado un proceso: \tPadre: %i\tyo: %i\n", getppid(), getpid());

    return 1;
}