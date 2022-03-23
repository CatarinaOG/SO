#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main (int argc, char** argv){

    clock_t start, end;
    double cpu_time_used;
    int status;

    int lines = 10;
    int columns = 1000;

    int matrix [lines][columns];
    int pids[lines];

    for( int i= 0 ; i<lines ; i++){
        for(int j = 0 ; j<columns ; j++){
            matrix[i][j] = rand() % 10;
        }
    }

    start = clock();
    
    for( int i= 0 ; i<lines ; i++){
        int pid = fork();

        if(pid == 0){
            for(int j = 0 ; j<columns ; j++){
                if (matrix[i][j] == atoi(argv[1])){
                    _exit(i);
                }
            }
            _exit(-1);
        }
        else{
            pids[i] = pid;
        }
    }

    for(int i=0 ; i<lines ; i++){
        pid_t pidFilho = waitpid(pids[i],&status,0);
        printf("PidFilho encontrou na linha %d\n",WEXITSTATUS(status));
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time taken: %f\n",cpu_time_used);
    
    return 0;
}
