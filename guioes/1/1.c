#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>





//---------------------------------Exercicio 1---------------------------------------

void mycp(){

    int readBytes;
    int bufferSize = 1024;
    char* buffer = malloc(sizeof(char) * bufferSize);

    int fd_from = open("hello.txt", O_RDONLY | O_CREAT);
    int fd_to = open("blank.txt", O_CREAT | O_TRUNC | O_WRONLY, 0600);

    if(fd_from <0 || fd_to < 0) printf("erro");

    while( (readBytes = read(fd_from,buffer,bufferSize)) > 0 )
        write(fd_to,buffer,readBytes);
    
    free(buffer);

}


//---------------------------------Exercicio 2---------------------------------------

void mycat(){

    int readBytes;
    int bufferSize = 1024;
    char* buffer = malloc(sizeof(char) * bufferSize);

    while( (readBytes = read(0,buffer,bufferSize)) > 0 )
        write(1,buffer,readBytes);

    free(buffer);

}

//---------------------------------Exercicio 3---------------------------------------

ssize_t readln(int fd, char *line, size_t size){
    size_t i = 0;
    while(i < size - 1){

        size_t nbr = (size_t) read(fd,&line[i],sizeof(char));
        if(nbr < 1) break;
        if(line[i++] == '\n') break;
    }

    line[i] = '\0';
    printf("%s",line);
    return (ssize_t) i;
}




//---------------------------------Exercicio 4---------------------------------------

void mynl(){

    int ind = 1;
    int readBytes;
    int bufferSize = 1024;
    char* buffer = malloc(sizeof(char) * bufferSize);

    while( (readBytes = readln(0,buffer,bufferSize)) > 0 )
        printf("%d: %s",ind++,buffer);
    
    free(buffer);
}


//---------------------------------Exercicio 5---------------------------------------

void readln2(int fd, char *line, size_t size){

    int readBytes;
    int posLine = 0;
    int continua = 1; 
    int posBuffer;
    int bufferSize = 1024;
    char* buffer = malloc(sizeof(char)*bufferSize);

    while( (readBytes = read(fd,buffer,bufferSize)) > 0){

        for(int i=0 ; i<readBytes && continua; i++){
            if(buffer[i] =='\n'){
                posBuffer = i;
                continua = 0;
            }
        }


        for(int i=0 ; i<posBuffer ; i++){
            line[posLine] = buffer[i];
            posLine++;
        }

        lseek(fd,posBuffer-bufferSize,SEEK_CUR);
    }
}


void mainReadln(){

    int bufferSize = 1024;
    char* buffer = malloc(sizeof(char) * bufferSize);

    int fd_from = open("hello.txt", O_RDONLY | O_CREAT, 0600);

    readln(fd_from,buffer,bufferSize);
    //readln2(fd_from,buffer,bufferSize);

}



//---------------------------------Main---------------------------------------

int main (int argc, char** argv){

    //mycp();
    //mycat();
    //mainReadln();
    //mynl();
    mainReadln();

}




