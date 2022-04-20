#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(int argc, char** argv){

    char* input = "";
    char* output = "";
    char* comando;
    int i=1;

    for(i=1 ; i<argc-1 ; i++){
        printf("%s",argv[i]);
    }

    for(i=1 ; i<argc-1 ; i++){

        if(argv[i] == "-i"){
            input = argv[i+1];
            i++;
            printf("input:%s",input);
        }

        else if(argv[i] == "-o") {
            output = argv[i+1];
            i++;
            printf("output:%s",output);
        }

        else{
            comando = argv[i];
            printf("comando:%s",comando);
            i++;
            break;
        }
    }

    int res;

    /*

    int fdin = dup(0);
    int fdout = dup(1);

    int input_fd = open(input,O_RDONLY);
    int output_fd = open(output,O_CREAT|O_TRUNC|O_WRONLY,0666);

    res = dup2(input_fd,0);
    res = dup2(output_fd,1);

    


    close(input_fd);
    close(output_fd);

    execlp(argv[1],argv[1],NULL);
    */

    return 1;
}




/*
<input
>output
>> append
*/