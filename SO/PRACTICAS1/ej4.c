#include <sys/types.h> //Para estructura pid_t 
#include <sys/wait.h> 
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>

int main(int argc, char ** argv){

    pid_t pid; 
    int childpid, status;
    int i;


   if(argc<4){
   	printf("ERROR: El numero de argumentos es incorrecto.\n\nFORMA CORRECTA: ./nombreejectuble.exe gnome-calculator gedit nombrefichero.txt\n\n");
   	exit(-1);
   }

	for(i = 0; i<2;i++){

		pid = fork();

		if(pid == 0){
			if(i == 0){
				execlp(argv[1], argv[1], NULL);
				exit(EXIT_SUCCESS);
				break;
			}			
	
			if(i == 1){ 
				execvp(argv[2], &argv[2]);
				exit(EXIT_SUCCESS);
				break;
			}
		}

		else{

			childpid = wait(&status);    

       		if(childpid>0){
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
}