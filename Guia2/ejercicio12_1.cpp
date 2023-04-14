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
	unsigned int i, j, a, v[50000];
	for(i = 0; i < 50000; i++)
		v[i] = i * i;
	
	printf("\nInicio\n");
	for(i = 0; i < 50000 - 1; i++)
		for(j = i + 1; j < 50000; j++)
		if (v[i] < v[j]){
			a = v[i];
			v[i] = v[j];
			v[j] = a;
		}
	printf("\nOrdenamiento terminado!\n\n"); // de burbuja
	execlp("/bin/ls","ls",NULL);
	return 0;
}



