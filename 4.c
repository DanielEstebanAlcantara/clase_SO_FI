#include <stdio.h>
#include <unistd.h>

int main()
{
    int pid;
    printf("\nPrueba de procesos:\n");
    // Lo primero lo hace el padre

    fork();
    // las dos impreciones no se sabe pq lo puede impimir el padre o el hijo
    // Se clona el padre y el hijo
    // una vez que se invoca el fork se crean dos contadores de procesos
    fork();
    fork();
    printf("\tSe a creado un proceso: \tPadre: %i\tyo: %i\n\n\n", getppid(), getpid());
    return 1;
}