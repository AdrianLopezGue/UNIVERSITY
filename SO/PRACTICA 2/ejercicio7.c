#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>

pthread_mutex_t semaforo = PTHREAD_MUTEX_INITIALIZER;

void* proveer(void* argumento){

	int *camisetas = (int *) argumento;

	int tipo = rand()%5;
	int cantidad = rand()%(100)+1;

	pthread_mutex_lock(&semaforo);

	camisetas[tipo] = camisetas[tipo] + cantidad;
	printf("Añadidas %d a las camisetas de tipo %d. Total de ese tipo: %d\n", cantidad, tipo, camisetas[tipo]);

	pthread_mutex_unlock(&semaforo);

	pthread_exit ((void*)(camisetas));

}

void* comprar(void* argumento){

	int *camisetas = (int *) argumento;

	int tipo = rand()%5;
	int cantidad = rand()%(30)+1;

	pthread_mutex_lock(&semaforo);

	if(camisetas[tipo]>cantidad){
		camisetas[tipo] -= cantidad;
		printf("Cliente toma %d camisetas del tipo %d. Total de ese tipo %d\n", cantidad, tipo, camisetas[tipo]);
	}
	else{
		printf("No hay suficientes camisetas para el usuario. Queria %d habia %d\n", cantidad, camisetas[tipo]);
	}

	pthread_mutex_unlock(&semaforo);
	pthread_exit ((void*)(camisetas));
}

int main(){

	int N, M = 5, i;

	printf("Introduce el numero de clientes: ");
	scanf("%d", &N);

	int *camisetas = (int*) malloc ((M)*sizeof(int));
	int *arraydevuelto;

	for(i = 0; i<M; i++){
		camisetas[i] = 50;
	}

		pthread_t thdclientes[N];
    pthread_t thdproveedores[M];

    srand(time(NULL));

    if(M>N){

    	for(i=0; i<M ; i++){

    	if(i<N){
    		pthread_create(&thdclientes[i], NULL, comprar, (void *) camisetas);
    	}
    	pthread_create(&thdproveedores[i], NULL,  proveer, (void *) camisetas);

   		 }
    }

    else{
 		for(i=0; i<N ; i++){

    	if(i<M){
    		pthread_create(&thdproveedores[i], NULL,  proveer, (void *) camisetas);
    	}
    		pthread_create(&thdclientes[i], NULL, comprar, (void *) camisetas);

    }
}

   for(i=0;i<M;i++){
	pthread_join(thdproveedores[i], (void **)&arraydevuelto);

}
       for(i=0;i<N;i++){
	pthread_join(thdclientes[i], (void **)&arraydevuelto);

}

   for(i=0;i<M;i++){
	printf("Hay %d camisetas del tipo %d en stock\n", arraydevuelto[i],i);

}
   return 0;

}
