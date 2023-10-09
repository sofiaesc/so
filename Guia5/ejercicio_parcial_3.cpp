#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;

int main(int argc, char *argv[]) {
	cout<<"Ingresar letra";
	int letra = cin.get();
	cout<<"Ingresar cantidad";
	int cant_letra = cin.get();
	cout<<"Ingresar número";
	int numero = cin.get();
	cout<<"Ingresar cantidad";
	int cant_numero = cin.get();
	
	pid = fork(); // genero el hijo
	if(pid == 0){
		
	} else {
		
	}
	return 0;
}



