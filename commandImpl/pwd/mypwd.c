#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

ino_t getFileINfo(char* filename){
    struct stat file_stat;
    if(0!=stat(filename, &file_stat)){
        fprintf(stderr,"can not get the file's information");
        exit(-1);
    }
    return file_stat.st_ino;
};

char* getFIleName(ino_t number){
    DIR *dir = NULL;
    struct  dirent *dptr = NULL;
    char* filename = NULL;
    if(NULL == (dir = opendir("."))){
        fprintf(stderr,"Can not open the dir\n");
        exit(-1);
    }else{
        while(NULL!= (dptr = readdir(dir))){
            if(dptr->d_ino == number){
                filename = strdup(dptr->d_name); //strdup duplicate the char[] and later you should free it. Because once function return, the memory of stack would be free.
                break;
            } 
        }
    }
    closedir(dir);
    return filename;
};


int main(int argc, char *argv[]){
    char* stk[10000];
    int depth = 0; 

    while (1){
        ino_t current = getFileINfo(".");
        ino_t parent = getFileINfo("..");
        

        if(current == parent) break; // if at the root of file system
        chdir("..");
        stk[depth++] = getFIleName(current);
    }

    for(int i = depth-1; i >=0 ;i--){
        fprintf(stdout,"/%s",stk[i]);
    }
    printf("\n");
    return 0;
    
}