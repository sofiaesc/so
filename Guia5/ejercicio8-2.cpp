#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
using namespace std;

// initialize sempahors of type sem_t:
sem_t sem_A, sem_B, sem_C, sem_A2;

/*	sem_post: increments (unlocks) the sempahore pointed to by sem.
	if value > 0 after increment, then another process or thread blocked
	in a sem_wait() call will be woken up and proceed. */
/* 	sem_wait: decrements (locks) the sempahore pointed to by sem. 
	if value > 0, decrement proceeds and the function returns immediately.
	if value = 0, call blocks until it becomes possible to decrement.*/

void *A(void *) {
	while (1) {
		sem_wait(&sem_A);
		cout << "A";
		sem_post(&sem_B); 
	}
}
void *B(void *) {
	while (1) {
		sem_wait(&sem_B);
		cout << "B";
		sem_post(&sem_A);
	}
}
void *C(void *) {
	while (1){
		sem_wait(&sem_C);
		cout << "C";
		sem_post(&sem_A);
	}
}
void *A2(void *) {
	while (1){
		sem_wait(&sem_A);
		cout << "A";
		sem_post(&sem_C);
	}
}

int main(int argc, char *argv[]) {
	// int sem_init (sem_t * sem, int pshared, unsigned int value);
	// initialize an unnamed semaphore at the address pointed to by sem.
	// pshared = 0: shared between threads of a process.
	// pshared != 0: shared between processes.
	// value: initial value for the sempahore.

	// BACA (4 SEMÁFOROS)
	sem_init(&sem_A, 0, 0);
	sem_init(&sem_B, 0, 1);
	sem_init(&sem_C, 0, 0);
	sem_init(&sem_A2, 0, 1);
	
	// declaring threads of type phread_t:
	pthread_t h1, h2, h3, h4;
	
	// thread creation:
	pthread_create(&h1, NULL, A, NULL);
	pthread_create(&h2, NULL, B, NULL);
	pthread_create(&h3, NULL, C, NULL);
	pthread_create(&h4, NULL, A2, NULL);
	
	// pthread_join: wait for thread termination.
	pthread_join(h2, NULL);
	pthread_join(h1, NULL);
	pthread_join(h3, NULL);
	pthread_join(h4, NULL);
	
	// int sem_destroy (sem_t *sem);
	// destroy an unnamed sempahore at the address pointed to by sem.
	sem_destroy(&sem_A);
	sem_destroy(&sem_B);
	sem_destroy(&sem_C);
	sem_destroy(&sem_A2);

	/*
	SEMÁFORO CONTADOR: Tengo un semáforo que inicialmente le asigno un 5, usando 
	sem_wait(s); me va a decir 4. Lo ejecuto otra vez y me da 3. Así sucesivamente
	y recién ahí accedo a la sección. TEngo que ejecutar cinco veces el while para
	que valga 0 y me deje pasar.
	*/
	
	return 0;
}


