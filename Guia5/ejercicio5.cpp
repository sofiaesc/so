#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

#include <cstring>
using namespace std;

int main(int argc, char *argv[]) {
	// variables para tubería:
	int fd[2], fd2[2];
	char buffer[128];
	pipe(fd); pipe(fd2);
	
	// genero hijo:
	pid_t pid;
	pid = fork();
	
	// PRIMER ENVÍO:
	if(pid != 0){ // PADRE
		close(fd[0]); // cierro lectura para cuando envía el padre
		close(fd2[1]); // cierro escritura para cuando recibe el padre
		
		strcpy(buffer,"Hola!");
		write(fd[1],buffer,(strlen(buffer)+1)); // envío mensaje.
		// strlen(buffer)+1 porque tiene el salto de finalización.
		cout << "Mensaje enviado por padre: " <<buffer<<endl;
		
		read(fd2[0],buffer,sizeof(buffer)); // leo mensaje.
		cout<<"Mensaje recibido por padre: "<<buffer;
		
		close(fd2[0]); // cierro lectura para cuando ya leyó el padre
		close(fd[1]); // cierro escritura para cuando ya escribió el padre
	} else { // HIJO
		close(fd[1]); // cierro escritura para cuando lee el hijo
		close(fd2[0]); // ciero lectura para cuando escribe el hijo
		
		read(fd[0],buffer,sizeof(buffer)); // leo mensaje.
		cout<<"Mensaje recibido por hijo: "<<buffer<<endl<<endl;
		
		strcpy(buffer,"Chau!");
		write(fd2[1],buffer,(strlen(buffer)+1)); // envío mensaje.
		cout << "Mensaje enviado por hijo: " <<buffer<<endl;
		
		close(fd2[1]); // cierro escritura para cuando ya escribió el hijo
		close(fd[0]); // cierro lectura para cuando ya leyó el hijo.
	}
	
	// Espero a que termine el hijo, sino termina el padre y termina ejecución:
	waitpid(pid,NULL,0);
	return 0;
}



