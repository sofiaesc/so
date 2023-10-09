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

void *A(void *) {
	for(int i=1;i<=5;i++) { 
		cout<<i<<endl;
		sleep(rand()%2);
	}
	sem_post(&semaforo);
}
void *B(void *) {
	sem_wait(&semaforo);
	for(int i=6;i<=10;i++) { 
		cout<<i<<endl;
		sleep(rand()%2);
	}
}

int main(int argc, char *argv[]) {
	
	sem_init(&semaforo, 0, 0);
	
	pthread_t h1,h2;
	
	pthread_create(&h1,NULL,A,NULL);
	pthread_create(&h2,NULL,B,NULL);
	
	pthread_join(h1,NULL);
	pthread_join(h2,NULL);
	
	for(int i=11;i<=15;i++) { 
		cout<<i<<endl;
		sleep(rand()%2);
	}
	
	sem_destroy(&semaforo);
	
	return 0;
}
