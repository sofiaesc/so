#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;

int main(int argc, char *argv[]) {
	
	pid_t pid;
	int i;
	
	// Función fork() me retorna 0 a los procesos hijos y != 0 a los padres.
	pid = fork();
	
	if (pid == 0){ // Proceso hijo...
		for (i=0;i<10;i++){
			printf("Hijo: %d\n", i);
			sleep(1);
		}
		return 0;
	} else {
		if (pid > 0) { // Proceso padre...
			for(i=0;i<10;i++) { 
				printf("Padre: %d\n", i);
				sleep(1);
			}
			return 0;
		} else {
			printf("No se ha podido bifurcar");
		}
	}
	
	return 0;
}



