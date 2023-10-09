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
int resultado = 0;

void *A(void *x) {
	int* args = (int*) x;
	int ini = args[0];
	int fin = args[1];
	int prod = 1;
	for(int i=ini;i<=fin;i++) { 
		prod *= i;
	}
	resultado += prod;
	sem_post(&semaforo);
}
void *B(void *x) {
	sem_wait(&semaforo);
	int* args = (int*) x;
	int ini = args[0];
	int fin = args[1];
	int sum = 0;
	for(int i=ini;i<=fin;i++) { 
		sum += i;
	}
	resultado += sum;
}

int main(int argc, char *argv[]) {
	
	// Obtengo números:
	int num1,num2;
	cout<<"Ingrese primer numero: ";
	cin>>num1;
	cout<<"Ingrese segundo numero: ";
	cin>>num2;
	
	// Determino el corte de mitades:
	int mitad = (num1 + num2)/2;
	
	// Argumentos para las funciones de los hilos:
	int arg1[] = { num1, mitad };
	int arg2[] = { mitad+1, num2 };
	
	// Defino semáforos:
	sem_init(&semaforo, 0, 0);
	
	pthread_t h1,h2;
	
	pthread_create(&h1,NULL,A,(void *)arg1);
	pthread_create(&h2,NULL,B,(void *)arg2);
	
	pthread_join(h1,NULL);
	pthread_join(h2,NULL);
	
	cout<<endl<<"Resultado: "<<resultado;
	
	sem_destroy(&semaforo);
	
	return 0;
}



