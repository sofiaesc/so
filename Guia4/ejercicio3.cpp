#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;

struct registro{
	string cadena;
	int valor1;
	float valor2;
};

// DEVUELVE INT:
void *hilo1(void* x){
	while(1){
		int *m = (int *)x;
		*m = 25;
		sleep(1);
	}
	return x;
}

// DEVUELVE FLOAT:
void *hilo2(void* x){
	while(1){
		float *z = (float *)x;
		*z = 2*(*z);
		sleep(1);
	}
	return x;
}

// DEVUELVE STRUCT:
void *hilo3(void* x){
	while(1){
		registro *m = (registro *)x;
		m->cadena = "Chau";
		sleep(1);
	}
	return x;
}
	
int main(int argc, char *argv[]) {
	int cont = 0; // Contador global
	
	// ARGUMENTOS PARA HILOS:
	int *arg1 = new int;
	*arg1 = 12; // Valor entero para hilo 1.
	
	float *arg2 = new float; 
	*arg2 = 13.0; // Valor flotante para hilo 2.
	
	registro arg3; // Valor struct para hilo 3.
	arg3.cadena = "Hola.";
	arg3.valor1 = 1;
	arg3.valor2 = 2;
	
	// HILOS:
	pthread_t t[3];
	pthread_create(&t[1],NULL,hilo1,(void *)arg1);
	pthread_create(&t[2],NULL,hilo2,(void *)arg2);
	pthread_create(&t[3],NULL,hilo3,(void *)&arg3);
	for(int i=0;i<3;i++) pthread_join(t[i],NULL);
	
	cout<<"HILO 1: "<<*arg1<<"\n";
	cout<<"HILO 2: "<<*arg2<<"\n";
	cout<<"HILO 3: "<<arg3.cadena<<" "<<arg3.valor1<<" "<<arg3.valor2<<"\n";
	cout<<"CONTADOR: "<<cont<<"\n";
	
	return 0;
}



