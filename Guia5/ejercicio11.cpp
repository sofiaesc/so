#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;
sem_t semaforoA,semaforoB;
int cont = 0;

void *A(void *) {
	for(int n=0;n<2;n++) { 
		sem_wait(&semaforoA);
		cout<<"Hilo h1:"<<endl;
		for(int i=0;i<10;i++) {
			cont += 1;
			cout<<cont<<endl;
			sleep(rand()%2);
		}
		sem_post(&semaforoB);
	}
	return NULL;
}
	
void *B(void *) {
	for(int n=0;n<2;n++) { 
		sem_wait(&semaforoB);
		cout<<"Hilo h2:"<<endl;
		for(int i=0;i<10;i++) { 
			cont += 1;
			cout<<cont<<endl;
			sleep(rand()%2);
		}
		sem_post(&semaforoA);
	}
	return NULL;
}

int main(int argc, char *argv[]) {
	
	sem_init(&semaforoA, 0, 1);
	sem_init(&semaforoB, 0, 0);
	
	pthread_t h1,h2;
	
	pthread_create(&h1,NULL,A,NULL);
	pthread_create(&h2,NULL,B,NULL);
	
	pthread_join(h1,NULL);
	pthread_join(h2,NULL);
	
	cout<<"Hilo padre:"<<endl;
	for(int i=0;i<10;i++) { 
		cont += 1;
		cout<<cont<<endl;
		sleep(rand()%2);
	}
	
	sem_destroy(&semaforoA);
	sem_destroy(&semaforoB);
	
	return 0;
}
