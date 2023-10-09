#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>
using namespace std;

int main(int argc, char *argv[]) {
	char mensaje[100];
	char nfifo[100] = "fifo";
	int fd;
	
	fd = open(nfifo,O_RDONLY);
	if (fd != -1) {
		read(fd,mensaje,strlen(mensaje));
		cout<<"Consumidor recibio: "<<mensaje;
		close(fd);
	} else {
		perror("Error al abrir tubería. ");
	}
	
	unlink(nfifo);
	return 0;
}



