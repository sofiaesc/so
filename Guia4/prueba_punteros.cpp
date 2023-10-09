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
	int a = 5;
	int *p = &a;
	
	cout<<"p: "<<p<<endl;
	cout<<"*p: "<<*p<<endl;
	cout<<"&p: "<<&p<<endl;
	cout<<"a: "<<a<<endl;
	cout<<"&a: "<<&a<<endl;
	
//...
	return 0;
}



