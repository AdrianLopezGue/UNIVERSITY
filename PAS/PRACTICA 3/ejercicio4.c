#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h> //Control de errores
#include <string.h> //Para la funcion strerror(), que permite describir el valor de errno como cadena.
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <time.h>
#include <errno.h>
#include "common.h"

int main(){

  mqd_t mq_server;
  struct mq_attr attr;
  char buffer[MAX_SIZE + 1];
  int must_stop = 0;

  attr.mq_maxmsg = 10;        // Maximo número de mensajes
  attr.mq_msgsize = MAX_SIZE; // Maximo tamaño de un mensaje

  pid_t rf, flag;
  int status;

  rf = fork();

  switch (rf)
  {
    case -1:
    printf ("Proceso Padre, no he podido crear el proceso hijo \n");
    exit(EXIT_FAILURE);
    case 0:
    printf ("Soy el Hijo, mi PID es %d y mi PPID es %d \n", getpid(), getppid());

    mq_server = mq_open(SERVER_QUEUE, O_WRONLY);
	if(mq_server == (mqd_t)-1 )
	{
      perror("Error al abrir la cola del servidor");
      exit(-1);
	}

  do
	{
		printf("> ");
		fflush(stdout);                  // Limpiar buffer de salida
		memset(buffer, 0, MAX_SIZE);     // Poner a 0 el buffer
		fgets(buffer, MAX_SIZE, stdin);  // Leer por teclado
		buffer[strlen(buffer)-1] = '\0'; // Descartar el salto de línea

		// Enviar y comprobar si el mensaje se manda
		if(mq_send(mq_server, buffer, MAX_SIZE, 0) != 0)
		{
			perror("Error al enviar el mensaje");
			exit(-1);
		}
	// Iterar hasta escribir el código de salida
	}while (strncmp(buffer, MSG_STOP, strlen(MSG_STOP)));

  if(mq_close(mq_server) == (mqd_t)-1)
	{
		perror("Error al cerrar la cola del servidor");
		exit(-1);
	}

    exit(EXIT_SUCCESS);


    default:
    printf ("Soy el Padre, mi PID es %d y el PID de mi hijo es %d \n", getpid(), rf);

    mq_server = mq_open(SERVER_QUEUE, O_CREAT | O_RDONLY, 0644, &attr);

    if(mq_server == (mqd_t)-1 )
    {
      perror("Error al abrir la cola del servidor");
      exit(-1);
    }

    do
    {
      // Número de bytes leidos
      ssize_t bytes_read;

      // Recibir el mensaje
      bytes_read = mq_receive(mq_server, buffer, MAX_SIZE, NULL);
      // Comprar que la recepción es correcta (bytes leidos no son negativos)
      if(bytes_read < 0)
      {
        perror("Error al recibir el mensaje");
        exit(-1);
      }
      // Cerrar la cadena
      buffer[bytes_read] = '\0';

      // Comprobar el fin del bucle
      if (strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
      must_stop = 1;
      else
      printf("Recibido el mensaje: %s\n", buffer);
    } while (!must_stop); 	// Iterar hasta que llegue el código de salida, es decir, la palabra exit

    if(mq_close(mq_server) == (mqd_t)-1)
	{
		perror("Error al cerrar la cola del servidor");
		exit(-1);
	}

	// Eliminar la cola del servidor
	if(mq_unlink(SERVER_QUEUE) == (mqd_t)-1)
	{
		perror("Error al eliminar la cola del servidor");
		exit(-1);
	}
  }

  while ( (flag=wait(&status)) > 0 )
  {
    if (WIFEXITED(status)) {
      printf("Proceso Padre, Hijo con PID %ld finalizado, status = %d\n", (long int)flag, WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status)) {  //Para seniales como las de finalizar o matar
      printf("Proceso Padre, Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)flag, WTERMSIG(status));
    }
    else if (WIFSTOPPED(status)) { //Para cuando se para un proceso. Al usar wait() en vez de waitpid() no nos sirve.
      printf("Proceso Padre, Hijo con PID %ld parado al recibir la señal %d\n", (long int)flag, WSTOPSIG(status));
    }
    else if (WIFCONTINUED(status)){ //Para cuando se reanuda un proceso parado. Al usar wait() en vez de waitpid() no nos sirve.
      printf("Proceso Padre, Hijo con PID %ld reanudado\n",(long int) flag);
    }
  }
  if (flag==(pid_t)-1 && errno==ECHILD)
  {
    printf("Proceso Padre, valor de errno = %d, definido como: %s\n", errno, strerror(errno));
  }
  else
  {
    printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
    exit(EXIT_FAILURE);
  }
}
