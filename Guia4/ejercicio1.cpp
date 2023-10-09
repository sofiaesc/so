#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;

// void* es un puntero sin tipo, no es nada como el void
void *thread1(void *){
	for(int i=0;i<10;i++) cout<<i<<" ";
	pthread_exit(NULL);
	// si pongo un valor de retorno en vez de null, me da un puntero.
	// esos valores los recopilo con el join después.
}
	
void *thread2(void *){
	for(char i='A';i<='Z';i++) cout<<i<<" ";
	pthread_exit(NULL);
}
		
int main(int argc, char *argv[]) {
	pthread_t tid1, tid2;
	
	pthread_create(&tid1,NULL,*thread1,NULL);
	pthread_create(&tid2,NULL,*thread2,NULL);
	
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	return 0;
}
