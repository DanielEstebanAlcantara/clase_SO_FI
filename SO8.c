#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int pid;
	int n;
	printf("Numero de hijos: ");
	scanf("%d", &n);
	printf("\nProceso principal: %d\n", getpid());
    printf("-------------------\n");
    
    while (n>0) {
        switch (pid=fork()){
            case -1:
	            printf("Error al crear el proceso\n");
	            exit(0);
	            break;
	        case 0:
	        	printf("Soy el proceso hijo (pid=%d) y mi padre es (pid=%d), i = %d, i = %d", getpid(), getppid(), i, i++);
	        	n--;
	        	break;
	        default:
	        	exit(0);
	        	break;
        }
    }
    
    printf("\n\tMAIN: termino el proceso %d\n", getpid());
    return 0;
}

