#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
using namespace std;
sem_t semaforo;

void *A(void *) {
	sem_wait(&semaforo); // debe esperar a sem�foro que se desbloquea cuando terminan las Z
	for(int i=0;i<10;i++) { 
		cout<<"A";
	}
	// no hago otro post porque ya termin�.
	return NULL;
}
void *Z(void *) { // no tiene wait de sem�foro, arranca de una nom�s.
	for(int i=0;i<10;i++) { 
		cout<<"Z";
	}
	sem_post(&semaforo); // una vez que termin�, desbloquea el sem�foro para que empiecen las A
	
	return NULL;
}

int main(int argc, char *argv[]) {

	sem_init(&semaforo, 0, 0);
	
	pthread_t h1, h2;
	
	pthread_create(&h1, NULL, A, NULL);
	pthread_create(&h2, NULL, Z, NULL);
	
	pthread_join(h2, NULL);
	pthread_join(h1, NULL);
	
	sem_destroy(&semaforo);

	return 0;
}


