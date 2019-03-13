#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

void *suma(int *indice){

int *valor=(int *)malloc(sizeof(int));

int x,y;

x = rand() & 9 + 1;
y = rand() & 9 + 1;

*valor = x+y;

printf("HEBRA %d: El primer numero es %d y el segundo es %d: SUMA --> %d\n", *indice, x , y, x+y);

pthread_exit(valor);

}

int main()
{
	int N = 5,i;
	srand(time(NULL));
	pthread_t thr[N];
	int *valor_devuelto;
	int sumatorio = 0;


	for(i = 0; i<N; i++){
		pthread_create (&thr[i], NULL, (void *) suma, &i);
		usleep(100000);
	}

	for(i = 0; i < N; i++) {
        pthread_join(thr[i], (void **) &valor_devuelto);
        sumatorio += *valor_devuelto;
        printf("El hilo %d ha devuelto el valor %d, y la suma: %d\n",i, *valor_devuelto, sumatorio);
    }
pthread_exit(NULL);
}
