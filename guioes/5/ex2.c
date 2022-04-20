#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv){

    int pid;
    int status;
    int fildes[2];
    int readbytes;
    char buffer[2];
    int p = pipe(fildes);
    char* string[] = {"hello\n","my\n","friends\n"};


    if( (pid = fork()) == 0 ){
        close(fildes[1]);
        while( (readbytes = read(fildes[0],&buffer,10)) > 0 ){ 
            write(1,&buffer,readbytes);
        }
        close(fildes[0]);
        _exit(0);

    }else{
        close(fildes[0]);

        for (int i=0 ; i<3 ; i++)
            write(fildes[1],string[i],strlen(string[i]));

        close(fildes[1]);
        wait(&status);
    }
    return 0;
}