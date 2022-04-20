#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#define NUM_CMDS 4
#define LINE 1024


void parseArgs(char* f_call , char ** final_args){
    int i;

    for( i = 0;f_call != NULL ; i++)
        final_args[i] = strdup(strsep(&f_call, " "));

    final_args[i] = NULL;
}


int main(){
    char* cmds[4];
    char* cmd_args[10];
    char buf[LINE];

    cmds[0] = strdup("grep -v ^# /etc/passwd");
    cmds[1] = strdup("cut -f7 -d:");
    cmds[2] = strdup("uniq");
    cmds[3] = strdup("wc -l");

    int p_fildes[4][2], nb_read;
    int cmd_total = NUM_CMDS;

    for (int cmd=0 ; cmd < cmd_total ; cmd++){

        if(cmd == 0){
            pipe(p_fildes[0]);
            switch (fork()) {
                case 0:
                    close(p_fildes[0][0]);
                    parseArgs(cmds[0],cmd_args);
                    dup2(p_fildes[0][1], 1);
                    close(p_fildes[0][1]);
                    execvp(cmd_args[0], cmd_args);
            }
        }

        else if(cmd == cmd_total - 1 ){
            close(p_fildes[cmd - 1][1]);//fechar os desc. de escrita associado ao pipe anterior
            switch (fork()) {
                case 0:
                    dup2(p_fildes[cmd - 1 ][0], 0);
                    close(p_fildes[cmd -1 ][0]);
                    parseArgs(cmds[cmd],cmd_args);
                    execvp(cmd_args[0],cmd_args);
            }

        }
        else{
            pipe(p_fildes[cmd]);
            close(p_fildes[cmd - 1][1]);//fechar o descritor de escrita do pipe anterior
            switch (fork()) {
                case 0://filho
                    dup2(p_fildes[cmd - 1][0],0); //redirecionar o desc. de leitura do pipe do comando anterior par o stdin
                    dup2(p_fildes[cmd][1],1); //redirecionar o desc. de escrita do novo pipe associado à execução deste comando para o stdout
                    close(p_fildes[cmd - 1][0]); //fechar o descritor de leitura
                    close(p_fildes[cmd][1]);//fechar o descritor de escrita
                    parseArgs(cmds[cmd],cmd_args);//fragmentar o comando nos seus argumentos
                    execvp(cmd_args[0],cmd_args);
            }
            close(p_fildes[cmd - 1 ][0]);
        }
    }
}

