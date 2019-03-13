#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <time.h>
#include <errno.h>
#include <regex.h>
#include <getopt.h>
#include "common.h"

//Prototipo de funcionn
void funcionLog(char *);
// Apuntador al fichero de log.  No se usa en este ejemplo, pero le servira en ejercicio resumen
FILE *fLog = NULL;

int main(int argc, char **argv)
{

  static struct option long_options[] =
  {
    /* Opciones que no van a actuar sobre un flag */
    /* "opcion", recibe o no un argumento, 0,
    identificador de la opción */
    {"regex",	 required_argument,	   0, 'r'},
    {"help",	 no_argument,	   0, 'h'},
    /* Necesario para indicar el final de las opciones */
    {0, 0, 0, 0}
  };


  int c, option_index = 0;
  int rflag = 0;
  int hflag = 0;

  // Variable que almacena el argumento de la opcion regexarg
  char *regexarg = NULL;

  while ((c = getopt_long (argc, argv, "r:h", long_options, &option_index))!=-1){
    if (c == -1)
    break;
    switch (c){
      case 'r':
      rflag = 1;
      regexarg = optarg;
      break;

      case 'h':
      hflag = 1;
      break;

      case '?':
      abort();
    }
  }

  if(rflag == 1){
    // Cola del servidor
    mqd_t mq_server;
    mqd_t mq_client;

    char server_servidor[50];
    char server_cliente[50];

    sprintf(server_servidor, "%s-%s", SERVER_QUEUE, getenv("USER"));
    sprintf(server_cliente, "%s-%s", CLIENT_QUEUE, getenv("USER"));

    // Atributos de la cola
    struct mq_attr attr;
    // Buffer para intercambiar mensajes
    char buffer[MAX_SIZE + 1];
    // Char que almacena el mensaje log
    char mensajeLog[MAX_SIZE];
    // flag que indica cuando hay que parar. Se escribe palabra exit
    int must_stop = 0;
    // char que almacena el mensaje de emparejamiento
    char emparejar[MAX_SIZE];
    // Inicializar los atributos de la cola
    attr.mq_maxmsg = 10;        // Maximo número de mensajes
    attr.mq_msgsize = MAX_SIZE; // Maximo tamaño de un mensaje

    // Crear la cola de mensajes del servidor. La cola CLIENT_QUEUE le servira en ejercicio resumen
    mq_server = mq_open(server_servidor, O_CREAT | O_RDONLY, 0644, &attr);
    if(mq_server == (mqd_t)-1 )
    {
      sprintf(mensajeLog, "No se ha podido abrir la cola del servidor.");
      perror("Error al abrir la cola del servidor");
      funcionLog(mensajeLog);
      exit(-1);
    }

    mq_client = mq_open(server_cliente, O_CREAT | O_WRONLY, 0644, &attr);
    if(mq_client == (mqd_t)-1 )
    {
      sprintf(mensajeLog, "No se ha podido abrir la cola del cliente.");
      perror("Error al abrir la cola del cliente");
      funcionLog(mensajeLog);
      exit(-1);
    }

    regex_t regex;
    int reti;

    reti = regcomp(&regex, regexarg, 0);

    if(reti){
      sprintf(mensajeLog, "No se ha podido compilar la expresion regular.");
      perror("Error al compilar la expresion regular\n");
      funcionLog(mensajeLog);

      if(mq_send(mq_client, MSG_STOP, MAX_SIZE, 0) != 0){
        sprintf(mensajeLog, "No se ha podido enviar el mensaje de compilacion");
        perror("Error al mandar el mensaje de compilacion.\n");
        funcionLog(mensajeLog);
      }
      exit(1);
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
        sprintf(mensajeLog, "Error al recibir el mensaje");
        perror("Error al recibir el mensaje");
        funcionLog(mensajeLog);
        exit(-1);
      }
      // Cerrar la cadena
      buffer[bytes_read] = '\0';

      // Comprobar el fin del bucle
      if (strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0){
        must_stop = 1;
      }
      else{

        printf("< Recibido \"%s\"\n", buffer);

        reti = regexec(&regex, buffer, 0, NULL, 0);

        if(!reti){

          sprintf(emparejar, "Empareja");
          printf("> %s\n", emparejar);

          if(mq_send(mq_client, emparejar, MAX_SIZE, 0) != 0){
            sprintf(mensajeLog, "No se ha podido enviar el mensaje a la cola del cliente");
            perror("Error al mandar el mensaje a la cola del cliente.\n");
            funcionLog(mensajeLog);
          }
        }
        else if( reti == REG_NOMATCH){
          sprintf(emparejar, "No empareja");
          printf("> %s\n", emparejar);

          if(mq_send(mq_client, emparejar, MAX_SIZE, 0) != 0){
            sprintf(mensajeLog, "No se ha podido enviar el mensaje a la cola del cliente");
            perror("Error al mandar el mensaje a la cola del cliente.\n");
            funcionLog(mensajeLog);
          }
        }
        else{
          sprintf(mensajeLog, "No se ha podido ejecutar la expresion regular.");
          regerror(reti, &regex, mensajeLog, sizeof(mensajeLog));
          funcionLog(mensajeLog);
          exit(1);
        }
      }

    } while (!must_stop); 	// Iterar hasta que llegue el código de salida, es decir, la palabra exit

    regfree(&regex);

    // Cerrar la cola del servidor
    if(mq_close(mq_server) == (mqd_t)-1)
    {
      sprintf(mensajeLog, "No se ha podido cerrar la cola del servidor.");
      perror("Error al cerrar la cola del servidor");
      funcionLog(mensajeLog);
      exit(-1);
    }

    if(mq_close(mq_client) == (mqd_t)-1)
    {
      sprintf(mensajeLog, "No se ha podido cerrar la cola del cliente.");
      perror("Error al cerrar la cola del cliente");
      funcionLog(mensajeLog);
      exit(-1);
    }

    // Eliminar la cola del servidor

    if(mq_unlink(server_servidor) == (mqd_t)-1)
    {
      sprintf(mensajeLog, "No se ha desvincular la cola del servidor.");
      perror("Error al eliminar la cola del servidor");
      funcionLog(mensajeLog);
      exit(-1);
    }

    if(mq_unlink(server_cliente) == (mqd_t)-1)
    {
      sprintf(mensajeLog, "No se ha desvincular la cola del cliente.");
      perror("Error al eliminar la cola del cliente");
      funcionLog(mensajeLog);
      exit(-1);
    }
  }

  if(hflag == 1){
    printf("COMANDO DE AYUDA\n");
  }

  return 0;
}


// Función auxiliar, escritura de un log. No se usa en este ejemplo, pero le servira en ejercicio resumen
void funcionLog(char *mensaje)
{
  int resultado;
  char nombreFichero[100];
  char mensajeAEscribir[300];
  time_t t;

  // Abrir el fichero
  sprintf(nombreFichero,"log-servidor.txt");
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
  if (resultado < 0)
  perror("Error escribiendo en el fichero de log");

  fclose(fLog);
  fLog=NULL;
}
