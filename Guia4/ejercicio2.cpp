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
	
	for(int i=0;i<3;i++) { 
		fork();
	}
	printf("Sistemas Operativos\n");
	return 0;
}



