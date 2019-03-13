#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <wait.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


typedef struct{

  int *v;
  int tam;

}parametros;


void *comprar(parametros *argumento){

  int *coches = argumento->v;

  int cantidad = rand()%7+1;
  int tipo = rand()%(argumento->tam);
  int i, errorsemaforo;

  errorsemaforo = pthread_mutex_lock(&mutex);

  if(errorsemaforo == 0){
    if(coches[tipo]-cantidad<0){
      printf("Cliente intento llevarse %d coches y solo habia %d del tipo %d. Se queda en 0\n", cantidad, coches[tipo], tipo);
      coches[tipo] = 0;
    }
    else{
      coches[tipo]-=cantidad;
      printf("Cliente compra %d. Total de coches del tipo %d: %d\n",cantidad, tipo, coches[tipo]);
    }

    errorsemaforo = pthread_mutex_unlock(&mutex);

    if(errorsemaforo == 0){
      pthread_exit(coches);
    }
    else{
      printf("Se ha producido un error al mandar la signal de post\n");
      pthread_exit(coches);
    }
  }


  else{
    printf("Se ha producido un error al mandar la signal de wait\n");
  }
}


void *suministrar(parametros *argumento){

  int *coches = argumento->v;

  int cantidad = rand()%3+1;
  int tipo = rand()%(argumento->tam);
  int i, errorsemaforo;

  errorsemaforo = pthread_mutex_lock(&mutex);

  if(errorsemaforo == 0){

    coches[tipo]+=cantidad;
    printf("Proveedor suministra %d. Total de coches del tipo %d: %d\n",cantidad, tipo, coches[tipo]);

    errorsemaforo = pthread_mutex_unlock(&mutex);

    if(errorsemaforo == 0){
      pthread_exit(coches);
    }
    else{
      printf("Se ha producido un error al mandar la signal de post\n");
      pthread_exit(coches);
    }
  }


  else{
    printf("Se ha producido un error al mandar la signal de wait\n");
  }

  pthread_exit(coches);
}

int main() {

  int NClientes, MProveedores;

  printf("Introduce el numero de clientes a crear: ");
  scanf("%d", &NClientes);

  printf("Introduce el numero de proveedores a crear: ");
  scanf("%d", &MProveedores);



  int errorhilo;


  // Creacion del vector coches y asignacion de coches a cada elemento del vector.
  int coches[MProveedores], i;

  for(i = 0; i<MProveedores; i++){
    coches[i] = 10;
  }


  pthread_t HilosClientes[NClientes];
  pthread_t HilosProveedores[MProveedores];
  parametros aux;
  int *arraydevuelto;
  srand(time(NULL));


  aux.v = coches;
  aux.tam = MProveedores;


  for(i = 0; i<NClientes+MProveedores; i++){
    if(i<NClientes){
      errorhilo = pthread_create(&HilosClientes[i], NULL, (void*)comprar, &aux);
      if(errorhilo != 0){
        printf("No se ha podido crear correctamente el hilo cliente numero %d\n",i);
      }
    }
    if(i<MProveedores){
      errorhilo = pthread_create(&HilosProveedores[i], NULL, (void*)suministrar, &aux);
      if(errorhilo != 0){
        printf("No se ha podido crear correctamente el hilo proveedor numero %d\n",i);
      }
    }
  }

  for(i = 0; i<NClientes+MProveedores; i++){
    if(i<NClientes){
      errorhilo = pthread_join(HilosClientes[i],(void**)&arraydevuelto);
      if(errorhilo != 0){
        printf("No se ha podido hacer el join correctamente del hilo cliente numero %d\n",i);
      }
    }
    if(i<MProveedores){
      errorhilo = pthread_join(HilosProveedores[i],(void**)&arraydevuelto);
      if(errorhilo != 0){
        printf("No se ha podido hacer el join correctamente del hilo proveedor numero %d\n",i);
      }
    }
  }

  printf("COCHES FINALES: { " );
  for(i = 0; i<MProveedores; i++){
    printf("%d,", arraydevuelto[i]);
  }
  printf("}\n");


  // Destruccion del semaforo utilizado y comprobacion de que se ha destruido correctamente.
  errorhilo = pthread_mutex_destroy(&mutex);

  if(errorhilo!=0){
    printf("Error al destruir el semaforo.\n");
  }
  return 0;
}
