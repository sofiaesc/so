#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
using namespace std;

sem_t sem_A, sem_B, sem_C;

void *A(void *) {
	while (1){
		sem_wait(&sem_A);
		cout << "A";
		sleep(rand()%2);
		sem_post(&sem_C);
		sem_wait(&sem_A);
		cout<<"A";
		cout.flush();
		sem_post(&sem_C);
		cout.flush();
	}
}
void *B(void *) {
	while (1){
		sem_wait(&sem_B);
		cout << "B";
		sleep(rand()%2);
		sem_post(&sem_A);
		sem_wait(&sem_B);
		cout<<"B";
		cout.flush();
		sem_post(&sem_A);
		cout.flush();
		cout<<endl;
	}
}
void *C(void *) {
	while (1){
		sem_wait(&sem_C);
		cout << "C";
		sleep(rand()%2);
		sem_post(&sem_B);
		sem_wait(&sem_C);
		cout << "C";
		cout.flush();
		sem_post(&sem_B);
		cout.flush();
	}
}

int main(int argc, char *argv[]) {
	sem_init(&sem_A, 0, 2);
	sem_init(&sem_B, 0, 0);
	sem_init(&sem_C, 0, 0);
	
	pthread_t h1, h2, h3;
	
	pthread_create(&h1, NULL, A, NULL);
	pthread_create(&h2, NULL, B, NULL);
	pthread_create(&h3, NULL, C, NULL);
	
	pthread_join(h2, NULL);
	pthread_join(h1, NULL);
	pthread_join(h3, NULL);
	
	sem_destroy(&sem_A);
	sem_destroy(&sem_B);
	sem_destroy(&sem_C);
	
	return 0;
}


