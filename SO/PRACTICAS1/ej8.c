#include <sys/types.h> //Para estructura pid_t 
#include <sys/wait.h> 
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>

#define Clave (key_t) 234

int main() {

    pid_t pid;
    int childpid, status;
    int numerohijos;
    int i,j;
    int Id_Memoria;
    int *Memoria = NULL;
    
    printf("Introduce el numero de hijos que quieres crear: ");
    scanf("%d", &numerohijos);

    // Creamos un espacio de memoria con "shmget"

    Id_Memoria = shmget (Clave, sizeof(int)*100, 0777 | IPC_CREAT);
	if (Id_Memoria == -1){
		printf("No consigo Id para Memoria compartida\n");
		exit(0);
	}

	// Creamos una conexion con ese espacio de memoria a la variable que va a ser el contador con "shmat"

	Memoria = (int *)shmat (Id_Memoria, (char *)0, 0);
	if (Memoria == NULL){
		printf("No consigo Memoria compartida");
		exit(0);
	}

	Memoria[0]=0;
	Memoria[1]=0;

     for(i = 0; i<numerohijos;i++){

			pid = fork();

			if(pid == 0){

				while(Memoria[1]!=i){
					usleep(5);
				}			

				shmat (Id_Memoria, (char *)0, 0);

					for(j = 0; j<100; j++){
						Memoria[0] = Memoria[0] + 1;
					}

				Memoria[1] = Memoria[1] + 1;
				exit(EXIT_SUCCESS);			
			}				

			else{
				childpid=wait(&status);

				if(childpid!=0){
					if (WIFEXITED(status)) {
                	    printf("child %d exited, status=%d\n",childpid, WEXITSTATUS(status));
               	 } else if (WIFSIGNALED(status)) {
                    	printf("child %d killed (signal %d)\n", childpid, WTERMSIG(status));
                 } else if (WIFSTOPPED(status)) {
                    printf("child %d stopped (signal %d)\n", childpid, WSTOPSIG(status));
                }
			}	
		}
	}	

	printf("Contador: %d\n",Memoria[0]);

	shmdt ((char *)Memoria);
	shmctl (Id_Memoria, IPC_RMID, (struct shmid_ds *)NULL);

return 0;

}
