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
    int numerohijos;
    int i;
 
	FILE *f;

	if(argc != 2){
		printf("ERROR: Introduce el nombre del fichero a crear: ./mainejercicio5.exe nombrefichero.txt\n");
		exit(-1);
	}

	f= fopen(argv[1], "w");
	

	for(i = 0; i<2;i++){

		pid = fork();

		if(pid == 0){
			fprintf(f, "-----------------------------------------\n");
			sleep(1);
			exit(EXIT_SUCCESS);
		}

		else{
        
        fprintf(f, "+++++++++++++++++++++++++++++++\n");
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

	fclose(f);

}
