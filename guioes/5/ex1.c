#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv){

    int pid;
    int status;
    int fildes[2];
    char buffer[200];
    int p = pipe(fildes);
    char string[] = "hello\n";


    if( (pid = fork()) == 0 ){
        close(fildes[1]);
        read(fildes[0],&buffer,sizeof(buffer));
        printf("i read: %s",buffer);
        close(fildes[0]);
        _exit(0);

    }else{
        close(fildes[0]);
        write(fildes[1],&string,strlen(string));
        close(fildes[1]);

        wait(&status);
    }
    return 0;
}