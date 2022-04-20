#include <stdio.h>
#include <unistd.h>

int main (int argc, char** argv){
    
    int return_exec;
    char* exec_args[] = {"/bin/ls","-ls",NULL};


    execl("/bin/ls","/bin/ls","-ls",NULL);

}