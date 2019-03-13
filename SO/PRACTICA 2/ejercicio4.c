#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *leerfichero(char *nombrefichero){

	FILE *f;
	
	if((f=fopen((char*) nombrefichero, "r"))==NULL){    
		printf("\nError al abrir el fichero ");
		exit(-1);
	}	

	char auxiliar[255];

	int *valor=(int *)malloc(sizeof(int));
	*valor = 0;

	while(fgets(auxiliar, 255, f) != NULL){
		(*valor)++;
	}

	fclose(f);
	pthread_exit(valor);

}

int main(int argc, char *argv[])
{
	if(argc<2){
		printf("ERROR: Ejecute el programa incluyendo el nombre de un fichero: ./mainpractica4.exe fichero1 fichero2\n");
		exit(-1);
	}



	int i;
	int sumatorio = 0;
	int *valor_devuelto;
	

	pthread_t thr[argc-1];

	for(i = 0; i<argc-1; i++){

		char filename[50] = "";

		strcat(filename, argv[i+1]);
		strcat(filename, ".txt");		

		pthread_create(&thr[i], NULL,  (void *) leerfichero, filename);
		usleep(10000);
		
	}

	for(i = 0; i<argc-1; i++){
		pthread_join(thr[i], (void **)&valor_devuelto);
		sumatorio += *valor_devuelto;
		printf("El hilo %d ha devuelto el valor %d y la suma por ahora es: %d\n", i, *valor_devuelto, sumatorio);

	}

	pthread_exit(NULL);
}