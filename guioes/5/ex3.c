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

        execlp("wc","wc",NULL);

        _exit(0);

    }else{
        close(fildes[0]);

        while( (readBytes = read(0,buffer,BUFFERSIZE)) > 0 )
            write(fildes[1],buffer,readBytes);

        close(fildes[1]);
        wait(&status);
    }
    return 0;
}