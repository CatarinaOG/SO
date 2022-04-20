#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#define BUFFERSIZE 100

int main(int argc, char** argv){

    int pid;
    int status;
    int fildes[2];
    int readBytes;
    char buffer[BUFFERSIZE];
    int p = pipe(fildes);
    char* string[] = {"hello\n","my\n","friends\n"};


    if( (pid = fork()) == 0 ){
        close(fildes[1]);
        dup2(fildes[0],0);
        close(fildes[0]);
        execlp("wc","wc","-l",NULL);

        _exit(0);

    }else{
        close(fildes[0]);
        dup2(fildes[1],1);
        close(fildes[1]);
        execlp("ls","ls","/etc",NULL);
        
        wait(&status);
    }
    return 0;
}