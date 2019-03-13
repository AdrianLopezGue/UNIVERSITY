#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <semaphore.h>
#include <pthread.h>

#define TAM 5

sem_t proveedorsemaforo, compradorsemaforo;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int buffer[TAM];
int INDICECOMPRADOR = 0;
int INDICEPROVEEDOR = 0;


void *proveer(){

  int i, errorsemaforo;
  int cantidad = rand()%10+1;

  while(1){
    errorsemaforo = sem_wait(&proveedorsemaforo);

    if(errorsemaforo == 0){

      errorsemaforo = pthread_mutex_lock(&mutex);

      if(errorsemaforo == 0){
        buffer[INDICEPROVEEDOR] +=cantidad;
        printf("P: Buffer[%d] + %d . TOTAL: %d\n", INDICEPROVEEDOR, cantidad, buffer[INDICEPROVEEDOR]);
        INDICEPROVEEDOR = (INDICEPROVEEDOR+1)%TAM;

        errorsemaforo = pthread_mutex_unlock(&mutex);

        if(errorsemaforo == 0){

          errorsemaforo = sem_post(&compradorsemaforo);

          if(errorsemaforo == 0){
            pthread_exit(NULL);
          }
          else{
            printf("ERROR: al mandar la signal post del comprador\n");
            pthread_exit(NULL);
          }

        }
        else{
          printf("ERROR: Se ha producido un error al cerrar el semaforo mutex que controla la seccion critica.\n");
          pthread_exit(NULL);
        }
      }
      else{
        printf("ERROR: No se ha podido acceder a la seccion critica de forma correcta.\n");
      }
    }
    else{
      printf("ERROR:  al mandar la signal wait en el semaforo del wait.\n");
    }
  }
}

void *comprar(){

  int errorsemaforo;

  while(1){
    errorsemaforo = sem_wait(&compradorsemaforo);

    if(errorsemaforo == 0){

      errorsemaforo = pthread_mutex_lock(&mutex);

      if(errorsemaforo == 0){
        buffer[INDICEPROVEEDOR] -=2;
        printf("C: Buffer[%d] -2 . TOTAL: %d\n", INDICECOMPRADOR, buffer[INDICECOMPRADOR]);
        INDICECOMPRADOR = (INDICECOMPRADOR+1)%TAM;

        errorsemaforo = pthread_mutex_unlock(&mutex);

        if(errorsemaforo == 0){

          errorsemaforo = sem_post(&proveedorsemaforo);

          if(errorsemaforo == 0){
            pthread_exit(NULL);
          }
          else{
            printf("ERROR: al mandar la signal post del comprador\n");
            pthread_exit(NULL);
          }

        }
        else{
          printf("ERROR: Se ha producido un error al cerrar el semaforo mutex que controla la seccion critica.\n");
          pthread_exit(NULL);
        }
      }
      else{
        printf("ERROR: No se ha podido acceder a la seccion critica de forma correcta.\n");
      }
    }
    else{
      printf("ERROR:  al mandar la signal wait en el semaforo del wait.\n");
    }
  }

}


int main(int argc, char const *argv[]) {

  if(argc != 3){
    printf("ERROR: Debes de ejecutar el programa de esta manera: ./main.exe numeroproveedor numerocomprador\n");
    exit(-1);
  }

  int Nproveedor = atoi(argv[1]);
  int Ncomprador = atoi(argv[2]);

  int errorhilo,i;

  errorhilo = sem_init(&proveedorsemaforo, 0, TAM);

  if(errorhilo != 0){
    printf("No se ha podido iniciar el semaforo proveedor\n");
    exit(-1);
  }

  errorhilo = sem_init(&compradorsemaforo, 0, 0);

  if(errorhilo != 0){
    printf("No se ha podido iniciar el semaforo comprador\n");
    exit(-1);
  }


  pthread_t proveedor[Nproveedor];
  pthread_t comprador[Ncomprador];
  srand(time(NULL));

  for(i = 0; i<Nproveedor+Ncomprador; i++){
    if(i<Nproveedor){
      errorhilo = pthread_create(&proveedor[i], NULL, (void*)proveer, NULL);
      usleep(10000);

      if(errorhilo!=0){
        printf("ERROR: No se ha podido crear correctamente el hilo proveedor: %d\n",i);
      }
    }
    if(i<Ncomprador){
      errorhilo = pthread_create(&comprador[i], NULL, (void*)comprar, NULL);
      usleep(10000);

      if(errorhilo!=0){
        printf("ERROR: No se ha podido crear correctamente el hilo comprador: %d\n",i);
      }
    }
  }

  for(i = 0; i<Nproveedor+Ncomprador; i++){
    if(i<Nproveedor){
      errorhilo = pthread_join(proveedor[i], NULL);

      if(errorhilo!=0){
        printf("ERROR: No se ha podido hacer el join correctamente el hilo proveedor: %d\n",i);
      }
    }
    if(i<Ncomprador){
      errorhilo = pthread_join(comprador[i], NULL);

      if(errorhilo!=0){
        printf("ERROR: No se ha podido hacer el join correctamente el hilo comprador: %d\n",i);
      }
    }
  }

  printf("BUFFER FINAL: { ");

  for(i = 0; i<TAM;i++){
    printf("%d, ", buffer[i]);
  }
  printf("}\n");



  errorhilo = sem_destroy(&proveedorsemaforo);

  if(errorhilo!=0){
    printf("Se ha producido un error al destruir el semaforo proveedor\n");
  }

  errorhilo = sem_destroy(&compradorsemaforo);

  if(errorhilo!=0){
    printf("Se ha producido un error al destruir el semaforo comprador\n");
  }

  errorhilo = pthread_mutex_destroy(&mutex);

  if(errorhilo!=0){
    printf("Se ha producido un error al destruir el semaforo mutex\n");
  }


  return 0;
}
