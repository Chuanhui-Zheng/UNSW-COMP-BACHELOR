//Blair z5351042
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    for (int i = 1; i < argc; i++){
        struct stat statbuf;
        if (stat(argv[i], &statbuf) == -1){
            perror(argv[i]);
            exit(1);
        }
        if (S_ISDIR(statbuf.st_mode)){
            printf("d");
        }
        else{
            printf("-");
        }
        if (statbuf.st_mode & S_IRUSR) {
            printf("r");
        }
        else{
            printf("-");
        }

        if (statbuf.st_mode & S_IWUSR){
            printf("w");
        }
        else{
            printf("-");
        }

        if (statbuf.st_mode & S_IXUSR){
            printf("x");
        }
        else{
            printf("-");
        }
        if (statbuf.st_mode & S_IRGRP){
            printf("r");
        }
        else{
            printf("-");
        }
        if (statbuf.st_mode & S_IWGRP){
            printf("w");
        }
        else{
            printf("-");
        }
        if (statbuf.st_mode & S_IXGRP){
            printf("x");
        }
        else{
            printf("-");
        }
        if (statbuf.st_mode & S_IROTH){
            printf("r");
        }
        else{
            printf("-");
        }
        if (statbuf.st_mode & S_IWOTH){
            printf("w");
        }
        else{
            printf("-");
        }
        if (statbuf.st_mode & S_IXOTH){
            printf("x %s\n", argv[i]);
        }
        else{
            printf("- %s\n", argv[i]);
        }
    }
    return 0;
}