#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <sys/shm.h>
#include <cstring>
using namespace std;

struct dato{
	int sigue;
	int v[10];
};

// SIGSEGV(11): Si ejecuto primero receptor y después emisor, el receptor
// me tira este error porque todavía no se creó la zona de memoria compartida.
// Luego, hay un error de acceso a la memoria.

int main(int argc, char *argv[]) {
	int shmid;
	dato *pdato;
	
	shmid = shmget(75, sizeof(dato), 0777); // accedo a la memoria que creé antes
	pdato = (dato*)shmat (shmid, 0, 0); // hago attach de memoria en variable
	
	// mientras pdato->sigue == 0, espera.
	while(pdato->sigue == 0) sleep(1);
	
	// cuando mi bandera pdato->sigue == 1, puedo leer.
	cout<<"VECTOR:"<<endl;
	for(int i=0;i<10;i++) cout<<pdato->v[i]<<" ";
	
	shmdt((void *)pdato); // hago dettach
	// el emisor, que creó la zona de memoria, se encarga de borrarla 
	return 0;
}



