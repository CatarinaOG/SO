#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char** argv){
    
    int return_exec;
    int status;
    int return_value;
    int pid;
    char* exec_args[20];
    char* string;
    int i=0;

    string = strtok(argv[1]," ");

    while(string != NULL){
        exec_args[i] = string;
        string = strtok(NULL," ");
        i++;
    }

    exec_args[i] = NULL;

    if( (pid = fork()) == 0){
        return_exec = execvp(exec_args[0],exec_args);
        _exit(return_exec);
    }
    else{
        
        if (pid != 1){
            pid_t terminated_pid = waitpid(pid, &status,0);

            if(WIFEXITED(status)) return_value = WEXITSTATUS(status);
            else return_value = -1;
        }
        else return_value = -1;

    }

}