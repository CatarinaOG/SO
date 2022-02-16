#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//--------------------------------------Exercicio 1---------------------------------

/*int main (int argc, char** argv){

    int buffer_size;

    if(argc > 1) buffer_size = atoi(argv[1]);
    else buffer_size = 10;

    int fd_read = open("test", O_RDONLY | O_CREAT);

    if(fd_read < 0)
        perror("open error");

    int fd_write = open("test1", O_CREAT | O_WRONLY | O_TRUNC, 0600);

    ssize_t read_bytes = 0;
    ssize_t written_bytes = 0;

    char* buffer = malloc(sizeof(char) * buffer_size);

    while(read_bytes = read(fd_read,buffer,buffer_size) > 0)
        written_bytes = write(fd_write, buffer, read_bytes);


    free(buffer);

    return 0;
}*/




//--------------------------------------Exercicio 2---------------------------------




int main( int argc, char** argv){


    int buffer_size = 100;

    ssize_t read_bytes = 0;
    

    char* buffer = malloc(sizeof(char) * buffer_size);

    while(read_bytes = read(0,buffer,buffer_size) != 0)
        write(1, buffer, read_bytes);


    free(buffer);

    return 0;
}