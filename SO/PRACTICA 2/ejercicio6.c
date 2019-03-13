#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

int contador = 0;

void sumar(){

	int i;

	for(i = 0; i<100; i++) contador++;
	
	pthread_exit(NULL);
}

int main()
{

int N;
int i;

printf("Introduce el numero de hilos que quieres crear: ");
scanf("%d", &N);

pthread_t thr[N];

for(i = 0; i<N; i++) pthread_create(&thr[i], NULL,  (void *) sumar, NULL);

for (i = 0; i < N; i++)	pthread_join(thr[i], NULL);

printf("Contador: %d\n", contador );

pthread_exit(NULL);

}