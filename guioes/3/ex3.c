#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char** argv){
    
    int return_exec;
    int status;
    int pid;

    for(int i=1 ; i<argc+1 ; i++){
        if( (pid = fork())==0 ){
            execlp(argv[i],argv[i],NULL);
            _exit(i);
        }
    }

    for(int i=0 ; i<argc ; i++){
        pid_t terminated_pid = wait(&status);
        printf("terminated");
    }

}