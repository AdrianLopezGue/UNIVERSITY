#include <sys/types.h> //Para estructura pid_t
#include <sys/wait.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>

int main(){

	pid_t pid;


	pid = fork();

	if(pid == 0){
		printf("Este es el proceso hijo. ID HIJO: %d \n", getpid());
		exit(EXIT_SUCCESS);
	}

	else{
		printf("Este es el proceso padre");
		sleep(20);
	}

	system("ps -a");
	sleep(3);
	exit(EXIT_SUCCESS);
}
