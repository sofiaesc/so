#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;

void *func(void *a){
	cout<<"Sistemas Operativos"<<"\n";
	sleep(10);
	return a;
}

int main(int argc, char *argv[]) {
	// creando hilos en una matriz:
	pthread_t t[8];
	
	for(int i=0;i<8;i++) pthread_create(&t[i],NULL,func,NULL);
	for(int i=0;i<8;i++) pthread_join(t[i],NULL);
	
	// creando hilos de a uno:
	/*pthread_t t1, t2, t3, t4, t5, t6, t7, t8;
	
	pthread_create(&t1,NULL,func,NULL);
	pthread_create(&t2,NULL,func,NULL);
	pthread_create(&t3,NULL,func,NULL);
	pthread_create(&t4,NULL,func,NULL);
	pthread_create(&t5,NULL,func,NULL);
	pthread_create(&t6,NULL,func,NULL);
	pthread_create(&t7,NULL,func,NULL);
	pthread_create(&t8,NULL,func,NULL);
	
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	pthread_join(t4,NULL);
	pthread_join(t5,NULL);
	pthread_join(t6,NULL);
	pthread_join(t7,NULL);
	pthread_join(t8,NULL);*/
	return 0;
}



