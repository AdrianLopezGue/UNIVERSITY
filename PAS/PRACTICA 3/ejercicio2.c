#include <stdio.h>
#include <stdlib.h> //exit, rand, srand
#include <unistd.h> //pipe, close, fork, usleep, read, write, getpid, getppid
#include <sys/wait.h> //wait
#include <errno.h> //Control de errores
#include <string.h> //strerror
#include <time.h> //Para la semilla del generador de aleatorios

int main()
{
	pid_t rf, flag;
	int status;

	int fildes1[2];
	int fildes2[2];
	int numeroAPedir;
	int resultado;

	const int BSIZE = 100;
	char buf[BSIZE];
	ssize_t nbytes;

	// Abrimos la primera tuberia
	status = pipe(fildes1);
	if (status == -1 )
	{
		perror("Error en pipe1");
		exit(EXIT_FAILURE);
	}

	// Abrimos la segunda tuberia
	status = pipe(fildes2);
	if (status == -1 )
	{
		perror("Error en pipe2");
		exit(EXIT_FAILURE);
	}


	switch (rf = fork())
	{
		case -1: // Ocurrió un error al hacer fork()
		perror("[PADRE]: No se ha podido crear el proceso hijo...");
		exit(EXIT_FAILURE);

		case 0:

		printf ("[HIJO]: mi PID es %d y mi PPID es %d \n", getpid(), getppid());

		// Se cierran los descriptores de ficheros que no utiliza el hijo
		if (close(fildes1[1]) == -1)
		{
			perror("Error en close");
			exit(EXIT_FAILURE);
		}

		if (close(fildes2[0]) == -1)
		{
			perror("Error en close");
			exit(EXIT_FAILURE);
		}


		// Se lee el resultado recibido por linea de ordenes por el usuario mediante READ en el
		// descriptor de fichero de la primera tuberia.
		resultado = read(fildes1[0], &numeroAPedir, sizeof(int));
		if (resultado != sizeof(int))
		{
			perror("Error en read");
			exit(EXIT_FAILURE);
		}
		else
		printf("[HIJO]: Leyendo el numero %d de la tuberia1.\n", numeroAPedir);


		// Una vez leido el elemento de la tuberia1, se cierra. Se comprueba si se ha cerrado correctamente.
		if (close(fildes1[0]) == -1)
		{
			perror("Error en close");
			exit(EXIT_FAILURE);
		}

		// Se comprueba si el numero leido en la tuberia es par o impar
		if(numeroAPedir%2 == 0){
			printf("[HIJO]: Enviando PAR por la tuberia2...\n");

			if ( write(fildes2[1], "PAR", 5) == -1)
			{
				perror("[HIJO]: Error en write");
				exit(EXIT_FAILURE);
			}
		}
		else{
			printf("[HIJO]: Enviando IMPAR por la tuberia2...\n");

			if ( write(fildes2[1], "IMPAR", 7) == -1)
			{
				perror("[HIJO]: Error en write");
				exit(EXIT_FAILURE);
			}
		}

		// Una vez leido el elemento de la tuberia2, se cierra. Se comprueba si se ha cerrado correctamente.
		if (close(fildes2[1]) == -1)
		{
			perror("Error en close");
			exit(EXIT_FAILURE);
		}


		exit(EXIT_SUCCESS);


		default:

		printf ("[PADRE]: Soy el Padre, mi PID es %d y el PID de mi hijo es %d \n", getpid(), rf);

		// Se cierran los descriptores de ficheros que no utiliza el padre
		if (close(fildes1[0]) == -1)
		{
			perror("Error en close fildes1");
			exit(EXIT_FAILURE);
		}

		if (close(fildes2[1]) == -1)
		{
			perror("Error en close fildes2");
			exit(EXIT_FAILURE);
		}

		printf("[PADRE]: Introduzca un numero entero: ");
		scanf("%d", &numeroAPedir);

		printf("[PADRE]: Enviando el numero %d por la tuberia1...\n", numeroAPedir);

		// Se escriben los datos en la tubería
		if ( write(fildes1[1], &numeroAPedir, sizeof(int)) == -1)
		{
			perror("Error en write");
			exit(EXIT_FAILURE);
		}

		// El hijo verá FEOF (por hacer close)
		if (close(fildes1[1]) == -1)
		{
			perror("Error en close");
			exit(EXIT_FAILURE);
		}

		// Se lee el resultado recibido por el proceso hijo mediante READ en el
		// descriptor de fichero de la segunda tuberia.
		nbytes = read(fildes2[0], buf, BSIZE);
		if(nbytes == -1)
		{
			perror("Error en read");
			exit(EXIT_FAILURE);
		}
		else if (nbytes == 0) //read() no ha leido nada -> Se ha llegado a EOF -> El padre ha cerrado la tuberia
		printf("[PADRE]: Detecto que mi hijo ha cerrado la tuberia...\n");
		else
		printf("[HIJO]: Leyendo %s de la tuberia2...\n", buf);


		// Una vez leido el elemento de la tuberia2, se cierra. Se comprueba si se ha cerrado correctamente.
		if (close(fildes2[0]) == -1)
		{
			perror("Error en close");
			exit(EXIT_FAILURE);
		}


		while ( (flag=wait(&status)) > 0 )
		{
			if (WIFEXITED(status))
			{
				printf("[PADRE]: Hijo con PID %ld finalizado, status = %d\n", (long int)flag, WEXITSTATUS(status));
			} else if (WIFSIGNALED(status)) {  //Para seniales como las de finalizar o matar
				printf("[PADRE]: Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)flag, WTERMSIG(status));
			} else if (WIFSTOPPED(status)) { //Para cuando se para un proceso. Al usar wait() en vez de waitpid() no nos sirve.
				printf("[PADRE]: Hijo con PID %ld parado al recibir la señal %d\n", (long int)flag,WSTOPSIG(status));
			} else if (WIFCONTINUED(status)){ //Para cuando se reanuda un proceso parado. Al usar wait() en vez de waitpid() no nos sirve.
				printf("[PADRE]: Hijo con PID %ld reanudado\n",(long int) flag);
			}
		}
		if (flag==(pid_t)-1 && errno==ECHILD)
		{
			printf("[PADRE]: valor de errno = %d, definido como %s, no hay más hijos que esperar!\n", errno, strerror(errno));
		}
		else
		{
			printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
			exit(EXIT_FAILURE);
		}

		exit(EXIT_SUCCESS);
	}//switch
}
