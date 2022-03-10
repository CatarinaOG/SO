#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


typedef struct pessoa{
    char name[200];
    int age;
} Pessoa;


int new_Person(int fd, char* name, char* age){

    int offset = lseek(fd,0,SEEK_END);
    int registo = offset/sizeof(struct pessoa);

    Pessoa p;

    p.age = atoi(age);
    strcpy(p.name,name);

    lseek(fd,registo * sizeof(struct pessoa),SEEK_SET);

    write(fd,&p,sizeof(struct pessoa));

    return registo ;
}

int person_change_age(int fd, char* name, char* age){

    Pessoa p;
    while((read(fd,&p,sizeof(struct pessoa)))>0){
        if(strcmp(name,p.name) == 0){
            p.age = atoi(age);
            lseek(fd,-sizeof(struct pessoa),SEEK_CUR);
            write(fd,&p,sizeof(struct pessoa));


            //confirming
            Pessoa ppp;

            lseek(fd,-sizeof(struct pessoa),SEEK_CUR);
            read(fd,&ppp,sizeof(struct pessoa));
            printf("%s: %d",ppp.name,ppp.age);


        }
    }

}

int person_change_age_position(int fd, char*registo, char*age){

    Pessoa p;
    lseek(fd,atoi(registo) * sizeof(struct pessoa),SEEK_SET);
    read(fd,&p,sizeof(struct pessoa));

    p.age = atoi(age);

    lseek(fd,-sizeof(struct pessoa),SEEK_SET);
    write(fd,&p,sizeof(struct pessoa));

    //Confirming
    Pessoa ppp;
    lseek(fd,-sizeof(struct pessoa),SEEK_CUR);
    read(fd,&ppp,sizeof(struct pessoa));
    printf("%s: %d",ppp.name,ppp.age);


}

void pessoas(char* option, char* name, char* age, char* filename){

    int fd = open(filename, O_RDWR| O_CREAT,0600);
    int registo;

    if(strcmp("-i",option) == 0 ){
        registo = new_Person(fd,name,age);
        printf("%d",registo);
    }
    else if(strcmp("-u",option) == 0 ){
        person_change_age(fd,name,age);

    }else if(strcmp("-h",option) == 0){
        person_change_age_position(fd,name,age);
    }

}

//---------------------------------Main---------------------------------------

int main (int argc, char** argv){
    pessoas(argv[1],argv[2],argv[3], "filePeople.txt");
}