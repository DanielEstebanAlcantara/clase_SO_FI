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

