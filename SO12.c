#include <stdio.h>
#include <stdlib.h> //se incluye para hacer uso de la clonación
#include <unistd.h>
#include <sys/wait.h> //para dormir

int main(void){
	pid_t pid;  //almacenar el id del proceso, puede tomar tres posibles valores: -1 = error, 0 = hijo, otro = padre
	int n;		//define cuántos hijos queremos
	printf("Numero de hijos: ");
	scanf("%d", &n);
	int contadorHijos = n; 
	printf("\nProceso principal: %d\n", getpid()); //getpid() regresa el id del proceso que invoca esa llamada (el del main en este caso)
    printf("-------------------\n");				//dependiendo de dónde se ejecute, regresa el id del padre o del hijo

    while (n>0) { //también podemos usar if else
        switch (pid=fork()){ //fork() es para clonar un proceso -1 = error, 0 = hijo, otro = padre
            case -1:
		            printf("Error al crear el proceso\n");
		            exit(0);
	            break;
	        case 0:
		        	printf("Soy el proceso hijo (pid=%d) y mi padre es (pid=%d)", getpid(), getppid());
		        	printf("\n\tHijo(pid=%d) Termino\n", getpid());
		        	exit(0);
	        	break;
	        default:
	        	
	        	n--; 
	        	break;
        }
    }
    
    wait(NULL); 
	//waitpid(-1, NULL, 0);
	printf("Termino un proceso hijo\n"); // 
	printf("\n\tTermino el proceso hijo(pid=%d)\n\n", pid); // pid guarda el id del hijo
	printf("\n\tTermino el proceso padre(pid=%d)\n\n", getpid());

    return 0;
}

