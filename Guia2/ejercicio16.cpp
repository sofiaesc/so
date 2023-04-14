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
	printf("Inicio\n");
	for (i = 0; i < 4; i++)
		if (fork() == 0)
		// if (fork() != 0)
			break;
	sleep(30);
	return 0;
}



