#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
using namespace std;

	// TUBERIAS CON NOMBRE: MKFIFO
	/* vinculo entre las aplicaciones a traves de un archivo. puedo generarla desde la consola
	o mediante programas con el comando mkfifo(nombre,permisos). Nombre funciona como una key,
	debe ser comun a ambos programas. Debo ejecutar ambos programas en diferentes terminales
	desde un mismo directorio de trabajo y primero ejecutar el que genera la tubería: EL MKFIFO
	SOLO LO CREO EN UN LADO, EN UN SOLO DE LOS PROCESOS.
	Si lo que devuelve el mkfifo me da 0, es porque no la pudo crear. Si la pudo crear, abro
	el archivo con fd = open(nombre,O_WRONLY): solo escritura. (puedo abrirlo de escritura, lectura,
	ambos). Si no lo pudo abrir, me da -1. Si abrió, escribo write(fd,argv[1],100); y cierro la tubería.
	Del lado de la lecctura, abro el archivo fd = open(nfifo,O_RDONLY): solo lectura. Si abrió leo
	read(fd,mensaje,100); y después cierro la tubería.
	PERMISOS: está en octal, va del 0 al 7. el 0 al principio de cada numero te dice que es
	ctal y no te deja poner un 8 o un 9 después de eso. Es como 0x54 con los hexadecimales.*/

int main(int argc, char *argv[]) {
	//...
	return 0;
}



