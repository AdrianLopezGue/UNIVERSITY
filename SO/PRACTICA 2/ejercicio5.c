#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

typedef struct{
	int indice;
	int vectorfila[3];
	int vectorcolumna[3];
} the_params;

void *multiplicar(the_params *auxiliar){

	int *resultado = (int *) malloc(sizeof(int));
	int i;

	*resultado = 0;

	for(i = 0; i<3; i++){
		*resultado += (auxiliar->vectorfila[i]) * (auxiliar->vectorcolumna[i]);
	}

	pthread_exit(resultado);
}

int main()
{

	int matrix[3][3];
	int vector[3];
	int i,j;
	int *valor_devuelto;


	printf("\nMATRIX:\n");
	
	for(i = 0; i<3; i++){	
		for(j = 0; j<3;j++){
			matrix[i][j] = j+1;
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");



	printf("VECTOR COLUMNA { ");
	for(i = 0; i<3; i++){
		vector[i] = i+1;
		printf("%d, ", vector[i]);
	}
	printf("}\n\n");



	pthread_t thr[3];
	the_params parametros[3];

	for(i = 0; i<3; i++){

		parametros[i].indice = i;

		for(j=0; j<3; j++){
			parametros[i].vectorfila[j] = matrix[i][j];
		}

		for(j=0; j<3; j++){
			parametros[i].vectorcolumna[j] = vector[j];
		}
	

		pthread_create(&thr[i], NULL,  (void *) multiplicar, &parametros[i]);
	}

	printf("VECTOR RESULTANTE { ");
	for(i = 0; i<3;i++){
		pthread_join(thr[i], (void **)&valor_devuelto);
		
		printf("%d, ", *valor_devuelto);
	}
		printf("}\n");
		pthread_exit(NULL);
}