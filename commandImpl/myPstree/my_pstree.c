#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
#include <stdbool.h>

bool isnumber(char*);
void recur(char*);
int main(int argc, char* argv[]){
    recur("/proc");
};

void recur(char* filename){
    DIR *dir = opendir(filename);
    printf("%s",filename);
    if(dir == NULL) fprintf(stderr,"can not open %s",filename);
    struct  dirent* dptr = NULL;
    while(NULL!= (dptr = readdir(dir))){
        if(isnumber(dptr->d_name)){
            printf("%s\n","|");
            printf("%s","-");
            printf("%s\n",dptr->d_name);
            char name[100] = "./"; 
            strcat(name,strcat(dptr->d_name,"/task"));
            recur(name);
        }
    }
    closedir(dir);
}

bool isnumber(char* filename){
    if(filename[0] == '0'||filename[0] == '1'||filename[0] == '2'||filename[0] == '3'
    ||filename[0] == '4'||filename[0] == '5'||filename[0] == '6'||filename[0] == '7'||filename[0] == '8'||filename[0] == '9')
    return true;
    else return false;
}