#include <stdio.h>
#include <unistd.h>

int main()
{

    printf("\nPrueba de proceoss:\n");
    // Lo primero lo hace el padre
    printf("Pid del padre: %d\n", getpid());
    fork();
    printf("%d", getpid());
    // las dos impreciones no se sabe pq lo puede impimir el padre o el hijo
    // Se clona el padre y el hijo
    // una vez que se invoca el fork se crean dos contadores de procesos
    printf("\tSe a creado un proceso\n");

    return 1;
}