#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <time.h>
#include <errno.h>
#include "common.h"

//Prototipo de funcion
void funcionLog(char *);
// Apuntador al fichero de log. No se usa en este ejemplo, pero le servira en ejercicio resumen
FILE *fLog = NULL;

int main(int argc, char **argv)
{
  // Colas servidor y cliente
  mqd_t mq_server;
  mqd_t mq_client;

  char server_servidor[50];
  char server_cliente[50];

  sprintf(server_servidor, "%s-%s", SERVER_QUEUE, getenv("USER"));
  sprintf(server_cliente, "%s-%s", CLIENT_QUEUE, getenv("USER"));
  // Buffer para intercambiar mensajes
  char buffer[MAX_SIZE];
  char buffer2[MAX_SIZE];
  // Char que almacena el mensaje log
  char mensajeLog[MAX_SIZE];
  // Abrir la cola del servidor. La cola CLIENT_QUEUE le servira en ejercicio resumen
  mq_server = mq_open(server_servidor, O_WRONLY);
  if(mq_server == (mqd_t)-1 )
  {
    sprintf(mensajeLog, "No se ha podido abrir la cola del servidor.");
    perror("Error al abrir la cola del servidor");
    funcionLog(mensajeLog);
    exit(-1);
  }

  mq_client = mq_open(server_cliente, O_RDONLY);
  if(mq_client == (mqd_t)-1 )
  {
    sprintf(mensajeLog, "No se ha podido abrir la cola del cliente.");
    perror("Error al abrir la cola del cliente");
    funcionLog(mensajeLog);
    exit(-1);
  }

  printf("Mandando mensajes al servidor (escribir \"%s\" para parar):\n", MSG_STOP);
  do
  {
    printf("> ");
    fflush(stdout);                  // Limpiar buffer de salida
    memset(buffer, 0, MAX_SIZE);     // Poner a 0 el buffer
    fgets(buffer, MAX_SIZE, stdin);  // Leer por teclado
    buffer[strlen(buffer)-1] = '\0'; // Descartar el salto de línea

    if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP)) == 0){
      printf("< Recibido mensaje de finalización por parte del cliente\n");

      if(mq_send(mq_server, buffer, MAX_SIZE, 0) != 0)
      {
        sprintf(mensajeLog, "No se ha podido enviar el mensaje.");
        perror("Error al enviar el mensaje");
        funcionLog(mensajeLog);
        exit(-1);
      }

      exit(0);
    }

    // Enviar y comprobar si el mensaje se manda
    if(mq_send(mq_server, buffer, MAX_SIZE, 0) != 0)
    {
      sprintf(mensajeLog, "No se ha podido enviar el mensaje.");
      perror("Error al enviar el mensaje");
      funcionLog(mensajeLog);
      exit(-1);
    }

    if(mq_receive(mq_client, buffer2, MAX_SIZE, NULL) < 0){
      sprintf(mensajeLog, "No se ha podido recibir el mensaje.");
      perror("Error al recibir el mensaje");
      funcionLog(mensajeLog);
      exit(-1);
    }



    if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP)) == 0){
      printf("< Recibido mensaje de finalización por parte del servidor\n");
      exit(0);
    }

    printf("< %s\n", buffer2);

    // Iterar hasta escribir el código de salida
  }while (strncmp(buffer, MSG_STOP, strlen(MSG_STOP)));

  // Cerrar la cola del servidor
  if(mq_close(mq_server) == (mqd_t)-1)
  {
    sprintf(mensajeLog, "No se ha podido cerrar la cola del cliente.");
    perror("Error al cerrar la cola del servidor");
    funcionLog(mensajeLog);
    exit(-1);
  }

  if(mq_close(mq_client) == (mqd_t)-1)
  {
    sprintf(mensajeLog, "No se ha podido cerrar la cola del cliente.");
    perror("Error al cerrar la cola del servidor");
    funcionLog(mensajeLog);
    exit(-1);
  }
  return 0;
}


// Función auxiliar, escritura de un log
void funcionLog(char *mensaje)
{
  int resultado;
  char nombreFichero[100];
  char mensajeAEscribir[300];
  time_t t;

  // Abrir el fichero
  sprintf(nombreFichero,"log-cliente.txt");
  if(fLog==NULL)
  {
    fLog = fopen(nombreFichero,"at");
    if(fLog==NULL)
    {
      perror("Error abriendo el fichero de log");
      exit(1);
    }
  }

  // Obtener la hora actual
  t = time(NULL);
  struct tm * p = localtime(&t);
  strftime(mensajeAEscribir, 1000, "[%Y-%m-%d, %H:%M:%S]", p);

  // Vamos a incluir la hora y el mensaje que nos pasan
  sprintf(mensajeAEscribir, "%s ==> %s\n", mensajeAEscribir, mensaje);

  // Escribir finalmente en el fichero
  resultado = fputs(mensajeAEscribir,fLog);
  if ( resultado < 0)
  perror("Error escribiendo en el fichero de log");

  fclose(fLog);
  fLog=NULL;
}
