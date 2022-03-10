#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char** argv){
    pid_t pid;
    int status;

    if( (pid = fork())==0){
        printf("son: my pid:%d\n",getpid());
        _exit(0);
    }
    else{
        int pid_son = wait(&status);
        printf("father: son's pid:%d\n",pid);
        printf("father: son's pid:%d\n",pid_son);
        printf("father: my pid:%d\n",getpid());

    }
}   