#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int pid;//para almacenar quienes el padre y el hijo
    int n;//numero de hijos
        	printf("Numero de hijos: ");
            scanf("%d", &n);
            int cocontador_de_hijos = n;
            printf("\nProceso principal: %d\n", getpid());//regresa el id dedel proceso que lo mandó llamar 
            printf("-------------------\n");
            //                 
                while (n>0) {
                    switch (pid=fork()){//clonar el proceso, regresa 3 procesos, -1 es un error, 0 es codigo del hijo si es diferente de 0 es el padre Uganda
                        case -1:
                            printf("Error al crear el proceso\n");
                            exit(0);
                            break;
                        case 0:
                            printf("Soy el proceso hijo (pid=%d) y mi padre es (pid=%d)", getpid(), getppid());
                            exit(0);
                            break;
                        default:
                            wait (NULL);
                            printf("termino mi proceso hijo (pid = %i)", pid);//pid almacena la variable del hijo
                            n--;
                            break;
                            }
                    }
                                                                                                                                                                                                        
                    printf("\n\tMAIN: termino el proceso %d\n", getpid());
            return 0;
                                                                                                                                                                                                                                