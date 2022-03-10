#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>





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
    int i = 0;

    while(i < size && read(fd,&line[i],sizeof(char)) > 0){
        i++;
        if(((char*)line)[i-1] == '\n') return i;
    }

    printf("%s",line);
    return i;
}




//---------------------------------Exercicio 4---------------------------------------

void mynl(){
 
    int line_counter = 0;
    char buffer[1024];
    int bytes_read = 0;
    int newline = 1;

    while( (bytes_read = read(0,buffer,1024)) > 0){
        char line_number[10] = "";

        if(newline && buffer[0] != '\n'){
            snprintf(line_number,10,"%d:",line_counter);
            write(1,line_number,sizeof(line_number));
            line_counter++;
        }

        write(1,buffer,bytes_read);
    }

    if(buffer[bytes_read] != '\n') newline = 0;
    else newline = 1;

}




//---------------------------------Exercicio 5--------------------------------------- Para confirmar

#define MAX_SIZE 1024
char read_buffer[MAX_SIZE];
int buffer_end = 0;
int buffer_pos = 0;

int readc(int fd, char* c){

    if(buffer_pos == buffer_end){
        buffer_end = read(fd,read_buffer,MAX_SIZE);
        buffer_pos = 0;
    }

    *c = read_buffer[buffer_pos++];
    return 1;
}

int readln2(int fd, char *line, size_t size){

    int i = 0;
    char* c;

    while(i < size && readc(fd,line+i) > 0){
        i++;
        if(((char*)line)[i-1] == '\n') return i;
    }

    printf("%s",line);
    return i;
}

void mainReadln(){

    int bufferSize = 10;
    char* buffer = malloc(sizeof(char) * bufferSize);

    int fd_from = open("hello.txt", O_RDONLY | O_CREAT, 0600);

    //readln(fd_from,buffer,bufferSize);
    readln2(fd_from,buffer,bufferSize);
}



//---------------------------------Exercicio 6---------------------------------------





