#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>



void sumar(int numero){

  int aux;
  aux = getpid()%10;

  int childpid, status;

  while((childpid = wait(&status))>0){
    if(WIFEXITED(status)){
      aux+=WEXITSTATUS(status);

    }else if(WIFSIGNALED(status)){
      printf("PID: %d signaled, status = %d\n", childpid, status);
    }else if(WIFSTOPPED(status)){
      printf("PID: %d stopped, status = %d\n", childpid, status);
    }
    printf("ITERACION: %d. PID: %d. PID PADRE: %d. Valor recibido: %d\n",numero, getpid(), getppid(), WEXITSTATUS(status));
    exit(aux);
  }


}

int main(int argc, char **argv){

  if(argc!=2){
    printf("Debes de escribir el comando de esta manera: ./main.exe 5\n");
    exit(-1);
  }

  int childpid, status;


  int numerohijos = atoi(argv[1]);
  int i;

  pid_t pid;


  for(i = 0; i<numerohijos;i++){

    pid = fork();


    if(pid == 0){
      // No hace nada
    }
    else{

      sumar(i);


    }

  }

}
