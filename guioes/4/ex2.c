#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char** argv){

    int res;
    char* line;
    char buffer;
    int i = 0;
    int status;

    int fdin = dup(0);
    int fdout = dup(1);

    int input_fd = open("/etc/passwd",O_RDONLY);
    int output_fd = open("saida.txt",O_CREAT|O_TRUNC|O_WRONLY,0666);
    int error_fd = open("erros.txt",O_CREAT|O_TRUNC|O_WRONLY,0666);

    res = dup2(input_fd,0);
    res = dup2(output_fd,1);
    res = dup2(error_fd,2);

    close(input_fd);
    close(output_fd);
    close(error_fd);

    int read_res;
    setbuf(stdout,NULL);

    if (fork() == 0){
        printf("Sou Filho");
        while( (read_res = read(0,&buffer,1)) > 0){

            line[i] = buffer;
            i++;

            if(buffer == '\n'){
                write(1,line,i);
                write(2,line,i);

                printf("After write line\n");
                fflush(stdout);
                i=0;
            }
        }
    }else{
        printf("Sou Pai");
        int terminated = wait(&status);

        dup2(fdin,0);
        dup2(fdout,1);


        printf("Terminei");
        fflush(stdout);
    }

    return 1;
}