//Blair z5351042

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int i = 1
    while(i < argc){
        struct stat file_stat;
        stat(argv[i], &file_stat);
        time_t current_time = time(NULL);
        if (file_stat.st_atime > current_time || file_stat.st_mtime > current_time){
            printf("%s has a timestamp that is in the future\n", argv[i]);
        }
        i++;
    }

    return EXIT_SUCCESS;
}