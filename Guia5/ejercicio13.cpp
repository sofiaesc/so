#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;

const int num_iter = 100; // Número de iteraciones
const int tam_vector = 5; // Tamaño del vector
int vector[tam_vector]; // Vector para producir o consumir
int pos_productor = 0;
int pos_consumidor = 0;
sem_t semaforoA,semaforoB;

void *productor(void *p) {
	for (unsigned long i = 0; i < num_iter; i++) {
		sem_wait(&semaforoA);
		int dato = rand()%100;
		vector[pos_productor % tam_vector] = dato;
		pos_productor++;
		cout << "Dato producido: " << dato<<endl;
		sem_post(&semaforoB);
	}
	return NULL;
}

void *consumidor(void *p) {
	for (unsigned long i = 0; i < num_iter; i++) {
		sem_wait(&semaforoB);
		int dato = vector[pos_consumidor % tam_vector];
		pos_consumidor++;
		cout << "Dato consumido: "<<dato<<endl;
		sem_post(&semaforoA);
	}
	return NULL;
}

int main(int argc, char **argv) {
	srand(time(0));
	
	sem_init(&semaforoA, 0, 5);
	sem_init(&semaforoB, 0, 0);
	
	pthread_t h1, h2;
	pthread_create(&h1, NULL, productor, NULL);
	pthread_create(&h2, NULL, consumidor, NULL);
	pthread_join(h1, NULL);	pthread_join(h2, NULL);
	
	sem_destroy(&semaforoA);
	sem_destroy(&semaforoB);
	return 0;
}