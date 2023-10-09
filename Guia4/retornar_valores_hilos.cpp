#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;

struct registro{
	string cadena;
	int n1,n2,n3;
	float promedio;
};

void *calculapromedio(void *x){
	registro *m = (registro *)x;
	m->promedio = (m->n1 + m->n2 + m->n3)/3.0;
	
	return (void *)m; //no es necesario que retorne m porque estoy trabajando con un puntero en el argumento.
}
	
void *valorfloatporreferencia(void *x){
	// por referencia me devuelve 2*argumento
	float *z = (float *)x;
	*z = 2*(*z);
	// por return me devuelve otra cosa
	float *otro = new float;
	*otro = 99.88;
	
	return (void *)otro;
}
	
void *texto(void *x){
	string *w = (string *)x;
	*w = *w + " FICH UNL";
	
	return (void *)w;
}

int main(int argc, char *argv[]) {
	registro a, *b;
	pthread_t ww, tid1, tid2, tid3, tid4, tid5;
	b = new registro;
	
	a.cadena = "Juan Perez";
	a.n1 = 9;
	a.n2 = 3;
	a.n3 = 10;
	
	b->cadena = "Luis Lopez";
	b->n1 = 3;
	b->n2 = 8;
	b->n3 = 6;
	
	float *res = new float;
	*res = 34;
	
	string s = "Sistemas operativos";
	
	float r = 65;
	
	pthread_create(&ww, NULL, valorfloatporreferencia, (void *)&r);
	pthread_join(ww, NULL);
	cout << "El valor devuelto en r es: " << r << endl;
	
	pthread_create(&tid1, NULL, calculapromedio, (void *)&a); 
	pthread_create(&tid2, NULL, calculapromedio, (void *)b); // como b ya es un puntero, no le saco la dirección de memoria, sólo lo desreferencio 
	pthread_create(&tid3, NULL, valorfloatporreferencia, (void *)res);
	pthread_create(&tid4, NULL, texto, (void *)&s);
	pthread_create(&tid5, NULL, calculapromedio, (void *)&a);
	
	void *pp;
	float *t;
	string *q;
	registro *z;
	
	pthread_join(tid1, NULL);
	pthread_join(tid2, &pp); // &pp donde pp = (void *) --> &(void *): lo apuntado por el puntero del tipo void va a ser un registro 
	pthread_join(tid3, (void **)&t); // t tiene el valor de return de la función del hilo tid3
	pthread_join(tid4, (void **)&q);
	pthread_join(tid5, (void **)&z); // (void **)&z me devuelve un puntero
	
	cout << "Promedio: " << ((registro *)pp)->promedio << "\n";
	cout << "Valor por referencia: " << a.cadena << " " << a.n1 << " " << a.n2 << " " << a.n3 << " " << a.promedio << "\n";
	cout << "Valor por referencia: " << b->cadena << " " << b->n1 << " " << b->n2 << " " << b->n3 << " " << b->promedio << "\n";
	cout << "Valor por referencia: " << *res << "\n";
	cout << "Valor de float por return: " << *t << "\n";
	cout << "Valor de string por return: " << *q << "\n";
	cout << "Valor de struct por return: " << z->cadena << " " << z->n1 << " " << z->n2 << " " << z->n3 << " " << z->promedio << " " << "\n";
	
	return 0;
}



