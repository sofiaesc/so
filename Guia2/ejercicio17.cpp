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
	int num, pid;
	for (num = 1; num <= 3; num++){
		pid = fork();
		/*if ((num == 3) && (pid == 0)){
			printf("\n");
			execlp("ls", "ls", "-l", NULL);
		}*/
		wait(NULL);
	}
	return 0;
}



