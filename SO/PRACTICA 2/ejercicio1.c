#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *leerchar (char *arg){

	int i;

	for(i=0; i<strlen(arg); i++){
		printf("%c\n", arg[i]);
		//sleep(1);
	}
} 

int main(){

char char1[30] = "Hola";
char char2[30] = "Mundo";

pthread_t tid1[2];

pthread_create(&tid1[0], NULL, (void *)leerchar, &char1);
pthread_create(&tid1[1], NULL, (void *)leerchar, &char2);

printf("\n");

pthread_join(tid1[0], NULL); 
pthread_join(tid1[1], NULL);

printf("\n");

    exit(EXIT_SUCCESS); 
}