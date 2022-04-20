#include <stdio.h>
#include <unistd.h>

int main (int argc, char** argv){
    
    int return_exec;
    char* exec_args[] = {"/bin/ls","-l",NULL};
    int pid;

    if( (pid = fork())==0 ){

        execv("/bin/ls",exec_args);

    }
}