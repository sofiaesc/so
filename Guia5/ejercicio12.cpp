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
int doble;
sem_t sem_vacio,sem_lleno;
pthread_mutex_t m;

int producir_dato() {
	static int dato = 0;
	dato++;
	return dato;
}

void *productor(void *p) {
	for (unsigned long i = 0; i < num_iter; i++) {
		sem_wait(&sem_vacio);
		int dato = producir_dato(); // Produce un dato
		pthread_mutex_lock(&m);
		vector[pos_productor % tam_vector] = dato;
		pthread_mutex_unlock(&m);
		cout << "Dato producido en la pos "<<pos_productor%tam_vector<<": " << dato<<endl;
		pos_productor++;
		sleep(rand()%2);
		sem_post(&sem_lleno);
	}
	return NULL;
}

void *consumidor(void *p) {
	for (unsigned long i = 0; i < num_iter; i++) {
		sem_wait(&sem_lleno);
		pthread_mutex_lock(&m);
		int dato = vector[pos_consumidor % tam_vector];
		pthread_mutex_unlock(&m);
		cout<<"Dato leido en la pos "<<pos_consumidor%tam_vector<<": "<<dato*2<<endl;
		pos_consumidor++;
		sleep(rand()%2);
		sem_post(&sem_vacio);
	}
	return NULL;
}

int main(int argc, char **argv) {
	sem_init(&sem_vacio, 0, 5);
	sem_init(&sem_lleno, 0, 0);
	pthread_mutex_init(&m,NULL);
	
	pthread_t h1, h2;
	pthread_create(&h1, NULL, productor, NULL);
	pthread_create(&h2, NULL, consumidor, NULL);
	pthread_join(h1, NULL);	pthread_join(h2, NULL);
	
	sem_destroy(&sem_vacio);
	sem_destroy(&sem_lleno);
	
	pthread_mutex_destroy(&m);
	return 0;
}