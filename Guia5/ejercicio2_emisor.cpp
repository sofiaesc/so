#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <sys/shm.h>
#define SHMKEY 75
#include <cstring>
using namespace std;

struct dato{
	int sigue;
	int v[10];
};

int main(int argc, char *argv[]) {
	// Accedo o creo zona de memoria compartida: shmid = shmget(key,tamaño,permisos);
	// Hago attach (asignación) de la memoria: shmat
	// Hago dettach (desasignación) de la memoria: shmdt
	// Elimino la zona de memoria compartida: shmctl
	
	int shmid;
	dato *pdato;
	
	// Si le pusiera un 200 en vez de 777 por ejemplo, me daría un error porque no le
	// estoy dando permisos entonces la zona de memoria queda inutilizable. Es un error
	// de acceso a la memoria.
	shmid = shmget(75, sizeof(dato), 0777 | IPC_CREAT); // creo zona de memoria compartida
	pdato = (dato*)shmat(shmid,0,0); // hago attach a la zona de memoria
	
	// espero para poder ejecutar el receptor
	sleep(6);
	
	// envio el dato para que reciba el otro
	for(int i=0;i<10;i++) { 
		cin>>pdato->v[i];
	}
	pdato->sigue=1; 
	
	shmdt(pdato); // hago el dettach
	shmctl(shmid,IPC_RMID,0); // elimino la zona de memoria compartida
	return 0;
}



