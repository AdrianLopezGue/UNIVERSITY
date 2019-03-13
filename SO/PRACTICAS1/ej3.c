#include <sys/types.h> //Para estructura pid_t 
#include <sys/wait.h> 
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>

// Funcion que va a sumar el ultimo digito del identificador de cada proceso.
void sumar(char *nombre){

	int aux;
	int childpid, status;
	aux = getpid()%10;

	while((childpid=wait(&status))>0){
		
		if(WIFEXITED(status)>0){
			aux+=WEXITSTATUS(status);
		}

		else if (WIFSIGNALED(status)) {
            printf("child %d killed (signal %d)\n", childpid, WTERMSIG(status));                
       }

        else if (WIFSTOPPED(status)) {
            printf("child %d stopped (signal %d)\n", childpid, WSTOPSIG(status));
       }
	}

	printf("Soy %s (pid=%d) y mi suma es:%d\n", nombre, getpid(), aux);
	exit(aux);
}


// Main del programa.

int main(void) {
	
	pid_t pid;

	// Creacion del primer hijo
	pid = fork(); 
	
	if(pid==0){	
		sumar("el primer hijo");	
	}

	// Creacion del segundo hijo
	pid = fork();


	if(pid==0){

		// Creacion del primer nieto
		pid=fork();

		if(pid==0){	

			sumar("el primer nieto");
		}

		// Creacion del segundo nieto
		pid=fork();

		if (pid==0){			
			
			// Creacion del unico bisnieto
			pid=fork();

			if (pid==0){
				sumar("el bisnieto");
			}

			sumar("el segundo nieto");
		}

		sumar("el tercer nieto");
	}
	
sumar("el padre");
}



