#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

typedef struct{
	int *vector;
	int length;
} params;



void *suma(params *aux){

	int i;
	int *valor=(int *)malloc(sizeof(int));

	for(i = 0; i< aux->length; i++){
		*valor += aux->vector[i];
	}
	pthread_exit(valor); 
}



int main(int argc, char const *argv[])
{

	if(argc != 2){
		printf("ERROR: Ejecuta el programa de esta manera: ./mainpractica3.exe numero\n");
		exit(-1);
	}

	if(atoi(argv[1]) > 10){
		printf("ERROR: El numero de hilos es mayor de 10\n");
		exit(-1);
	}


	int arraylength;	

	printf("Introduce el tamaño del vector: ");
	scanf("%d", &arraylength);


	int vector[arraylength],i;

	int sumatorio = 0;
	pthread_t thr[atoi(argv[1])];

	params aux[atoi(argv[1])];
	int *valor_devuelto;



	srand(time(NULL));

	printf("VECTOR: { ");

	for(i = 0; i<arraylength;i++){
		vector[i] = rand() & 9 + 1;
		printf("%d, ", vector[i]);
	}

	printf(" }\n");

	for(i = 0; i<atoi(argv[1]); i++){

		if(i == atoi(argv[1]) -1 && arraylength%atoi(argv[1]) != 0){

			aux[i].vector = &vector[i*arraylength/atoi(argv[1])+arraylength%atoi(argv[1])];
			aux[i].length = arraylength%atoi(argv[1]);	

		}

		else{

			aux[i].vector = &vector[i*arraylength/atoi(argv[1])];
			aux[i].length = arraylength/atoi(argv[1]);		

		}
		pthread_create (&thr[i], NULL, (void *) suma, &aux[i]);
		usleep(100000);

	}

	for (i=0; i<atoi(argv[1]); i++)
    {
        pthread_join(thr[i], (void **) &valor_devuelto);
        sumatorio += *valor_devuelto;
        printf("El hilo %d ha devuelto el valor %d, y la suma: %d\n",i, *valor_devuelto, sumatorio);
    }

    pthread_exit(NULL);
}