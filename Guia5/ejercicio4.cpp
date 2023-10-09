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

	// TUBERIAS SIN NOMBRE: PIPE
	/* son unidireccionales: si quiero intercambiar información entre dos programas o procesos
	si o si tengo que usar dos tuberias, una de ida (escritura) y una de vuelta (salida).
	se usan en el mismo proceso cuando usamos el fork, generamos un proceso hijo y si quiero
	pasar informacion del padre al hijo o viceversa uso una tuberia sin nombre y tengo en
	comun una variable que es la variable de tubería 'pipe': son dos numeros enteros (indice 0 
	para leer y 1 para escribir, en un arreglo fd[2]. este arreglo se usa como un argumento en
	el comando pipe(fd) que crea la tubería y asigna identificadores).
	cuando quiera escribir del proceso padre al proceso hijo y establezcco una tuberia, 
	se asigna el valor que quiero escribir a la variable 0/1, pero cuando vaya a escribir, tengo
	que cerrar el lado de lectura de la tubería. lo mismo para leer,tengo que cerrar la parte
	de escritura.
	para usar la librería necesito un buffer de memoria. para eso uso dos primitivas del sistema,
	el write y el read que se usan para cualquier tipo de dispositivo. le indico el dispositivo
	de salida o entrada (fd[1] o fd[2] depende de qué quiero hacer), el buffer y el tamaño del
	buffer.
	si el padre tiene que enviar, cierro la lectura fd[0] y envío con write(fd[1],buffer,sizeof(buffer));
	y después cierro la esccritura fd[1].
	cuando el hijo va a leer, cierro la escritura fd[1], leo con read(fd[0],buffer, sizeof(buffer));
	y después cierro la lectura fd[0].*/

int main(int argc, char *argv[]) {
	pid_t pid;
	int fd[2];
	char buffer[128];
	pipe(fd);
	pid = fork();
	if(pid != 0){ // PADRE
		close(fd[0]); // cierro lectura
		strcpy(buffer,"Hola!");
		write(fd[1],buffer,(strlen(buffer)+1)); // envío mensaje.
		// strlen(buffer)+1 porque tiene el salto de finalización.
		cout << "Mensaje enviado por padre: " <<buffer<<endl<<endl;
		close(fd[1]); // cierro escritura
	} else { // HIJO
		close(fd[1]); // cierro escritura
		read(fd[0],buffer,sizeof(buffer));
		cout<<"Mensaje recibido por hijo: "<<buffer;
		close(fd[0]); // cierro lectura
	}
	waitpid(pid,NULL,0);
	return 0;
}



