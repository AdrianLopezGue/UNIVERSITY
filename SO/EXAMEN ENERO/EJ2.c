#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <wait.h>

typedef struct{
  int *vector1struct;
  int *vector2struct;
  int size;
}parametros;

void *producto(parametros *aux){

  int *resultado = (int*) malloc (sizeof(int));
  *resultado = 0;

  int i;

  for(i = 0; i<aux->size;i++){

    *resultado += aux->vector1struct[i]*aux->vector2struct[i];

  }

  pthread_exit(resultado);
}

int main() {

  int N, M;
  srand(time(NULL));

  printf("Introduce el tamano del vector: ");
  scanf("%d", &N);

  printf("Introduce el numero de hilos a crear: ");
  scanf("%d", &M);

  if(M>=N){
    printf("No se pueden crear mas hilos que elementos del vector.\n");
    exit(-1);
  }


  int vector1[N],vector2[N],i, errorhilo;
  pthread_t hilos[M];
  parametros aux[M];

  int resultadototal=0;
  int *arg = (int*) malloc (sizeof(int));


  printf("Vector 1 = {");
  for(i = 0; i<N; i++){
    vector1[i] = rand()%5+1;
    printf("%d,", vector1[i]);
  }
  printf("}\n");

  printf("Vector 2 = {");
  for(i = 0; i<N; i++){
    vector2[i] = rand()%5+1;
    printf("%d,", vector2[i]);
  }
  printf("}\n");

  int nelem = N/M;
  int resto = N%M;

  for(i = 0;i<M;i++){
    if(i==M-1){
      aux[i].vector1struct = &vector1[i*nelem];
      aux[i].vector2struct = &vector2[i*nelem];
      aux[i].size = nelem+resto;
    }
    else{
      aux[i].vector1struct = &vector1[i*nelem];
      aux[i].vector2struct = &vector2[i*nelem];
      aux[i].size = nelem;
    }

    errorhilo = pthread_create(&hilos[i], NULL, (void*)producto, &aux[i]);

    if(errorhilo!=0){
      printf("No se ha podido crear el hilo numero: %d\n", i);
    }
  }


  for(i = 0; i<M;i++){
    errorhilo = pthread_join(hilos[i], (void**)&arg);

    if(errorhilo!=0){
      printf("Se ha producido un error en el join del hilo numero: %d\n",i );
    }
    else{
      resultadototal += *arg;
    }

  }

  printf("El resultado total es: %d\n", resultadototal);

}
