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
	int i;
	int padre = 1;
	for (i = 0; i < 3; i++){
		if (padre == 1){
			if (fork() == 0) { // Proceso hijo
				printf("Proceso hijo PID:%d con padre PPID:%d\n", getpid(), getppid());
				padre = 0; 
			} else {
				printf("Proceso padre PID:%d\n", getpid());
				padre = 1;
			}
		}
		sleep(1);
	}
	return 0;
}



