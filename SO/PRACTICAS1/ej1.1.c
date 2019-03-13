#include <sys/types.h> //Para estructura pid_t
#include <sys/wait.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>

int main(){

    pid_t pid;
    int childpid, status;
    int numerohijos;
    int i;

    printf("Introduce el numero de hijos que quieres crear: ");
    scanf("%d", &numerohijos);

    for(i = 0; i<numerohijos;i++){

        pid = fork();

        if(pid == 0){
            printf("ID HIJO: %d ID PADRE: %d\n", getpid(), getppid());
            exit(EXIT_SUCCESS);
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
