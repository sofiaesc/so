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
	// variables para tuber�a:
	int fd[2], fd2[2];
	char buffer[128];
	pipe(fd); pipe(fd2);
	
	// genero hijo:
	pid_t pid;
	pid = fork();
	
	// PRIMER ENV�O:
	if(pid != 0){ // PADRE
		close(fd[0]); // cierro lectura para cuando env�a el padre
		close(fd2[1]); // cierro escritura para cuando recibe el padre
		
		strcpy(buffer,"Hola!");
		write(fd[1],buffer,(strlen(buffer)+1)); // env�o mensaje.
		// strlen(buffer)+1 porque tiene el salto de finalizaci�n.
		cout << "Mensaje enviado por padre: " <<buffer<<endl;
		
		read(fd2[0],buffer,sizeof(buffer)); // leo mensaje.
		cout<<"Mensaje recibido por padre: "<<buffer;
		
		close(fd2[0]); // cierro lectura para cuando ya ley� el padre
		close(fd[1]); // cierro escritura para cuando ya escribi� el padre
	} else { // HIJO
		close(fd[1]); // cierro escritura para cuando lee el hijo
		close(fd2[0]); // ciero lectura para cuando escribe el hijo
		
		read(fd[0],buffer,sizeof(buffer)); // leo mensaje.
		cout<<"Mensaje recibido por hijo: "<<buffer<<endl<<endl;
		
		strcpy(buffer,"Chau!");
		write(fd2[1],buffer,(strlen(buffer)+1)); // env�o mensaje.
		cout << "Mensaje enviado por hijo: " <<buffer<<endl;
		
		close(fd2[1]); // cierro escritura para cuando ya escribi� el hijo
		close(fd[0]); // cierro lectura para cuando ya ley� el hijo.
	}
	
	// Espero a que termine el hijo, sino termina el padre y termina ejecuci�n:
	waitpid(pid,NULL,0);
	return 0;
}



