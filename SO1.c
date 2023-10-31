<<<<<<< HEAD
#include <stdio.h>
#include <unistd.h>

int main(){
	int pid;
	printf("\nPrueba de procesos:\n");

	fork();
	fork();
	fork();
	
	printf("\tSe ha creado un proceso: padre=%d, yo=%d\n", getppid(), getpid());
    
	return 1;
}

=======
#include <stdio.h>
#include <unistd.h>

int main(){
	int pid;
	printf("\nPrueba de procesos:\n");

	fork();
	fork();
	fork();
	
	printf("\tSe ha creado un proceso: padre=%d, yo=%d\n", getppid(), getpid());
    
	return 1;
}

>>>>>>> 2a49c623a7a1b58ef254562563de5b0dd2a6682b
