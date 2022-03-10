#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main (int argc, char** argv){

    int pid;
    int status;

    for(int i= 0; i<10 ; i++){

        if( (pid = fork()) == 0 ){
            printf("[son %d] my pid:%d\n",i,getpid());
            printf("[son %d] father pid:%d\n",i,getppid());

            _exit(i);
        }
    }

    for(int i=0 ; i<10 ; i++){

        int pidFilho = wait(&status);
        printf("[son %d] acabou\n",WEXITSTATUS(status));

    }
}