/*
 * This program is to print the filename of files under one specific directory
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> //opendir
#include <sys/types.h>

DIR *dp ;
struct dirent *dptr ;

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr,"usage %s directory...\n", argv[0]);
        exit(-1);
    }
    if(NULL == (dp = opendir(argv[1]))){
        fprintf(stderr,"Can not open the dir");
        exit(-1);
    }else{
        printf("the content under the dir [%s] is: \n", argv[1]);
        while (NULL != (dptr = readdir(dp))){
            printf("inode-numer: %-10ld \t filename:%s\n",dptr->d_ino,dptr->d_name); //ld long int
        }
        
    }
    closedir(dp);
    return 0;
}