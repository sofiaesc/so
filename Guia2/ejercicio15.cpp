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
	for (i = 0; i < 3; i++){
		if (fork() != 0)
			printf("Proceso %d hijo de %d\n", getpid(), getppid());
		wait(NULL);
	}
	return 0;
}



