<<<<<<< HEAD
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
	        	exit(0);
	        	break;
	        default:
	        	n--;
	        	break;
        }
    }
    
    printf("\n\tMAIN: termino el proceso %d\n", getpid());
    return 0;
}

=======
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
	        	exit(0);
	        	break;
	        default:
	        	n--;
	        	break;
        }
    }
    
    printf("\n\tMAIN: termino el proceso %d\n", getpid());
    return 0;
}

>>>>>>> 2a49c623a7a1b58ef254562563de5b0dd2a6682b
