#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#define numerohilos 5

pthread_mutex_t semaforo = PTHREAD_MUTEX_INITIALIZER;	// Semaforo para regular la entrada a la zona critica
sem_t semaforolleno;
sem_t semaforovacio;

int camisetas[5] = {50,50,50,50.50};

void* proveer(int *indice){

	int tipo = rand()%5;
	int cantidad = rand()%10;

	sem_wait(&semaforolleno);
	pthread_mutex_lock(&semaforo);

	camisetas[tipo]+=cantidad;

	pthread_mutex_unlock(&semaforo);
	sem_post(&semaforovacio);

	pthread_exit (NULL);

}

void* comprar(int *indice){

	int tipo = rand()%5;
	int cantidad = rand()%10;

	sem_wait(&semaforovacio);
	pthread_mutex_lock(&semaforo);

	camisetas[tipo]-=cantidad;

	pthread_mutex_unlock(&semaforo);
	sem_post(&semaforolleno);
}

int main(){

	pthread_t thdusuarios[numerohilos];

	sem_init(&semaforo, 0,1);
	sem_init(&semaforolleno, 0, 100);
	sem_init(&semaforovacio, 0, 0);

	srand(time(NULL));

		for(i=0; i<numerohilos ; i++){

			pthread_create(&thdusuarios[i], NULL, comprar, &i);
			usleep(500);
			pthread_create(&thdusuarios[i], NULL,  proveer, &i);
			usleep(500);
		}

	for(i=0;i<numerohilos;i++){
		pthread_join(thdusuarios[i], NULL);
	}


	return 0;
}
