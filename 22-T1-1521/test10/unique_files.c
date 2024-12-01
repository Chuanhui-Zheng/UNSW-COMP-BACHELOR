//Blair z5351042

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv){
    struct stat buf_list[argc];
    int buf_list_size = 0;
    int i = 1;
    while(i < argc){
        struct stat buf;
        if (stat(argv[i], &buf) == -1){
            perror(argv[i]);
            exit(1);
        }
        int is_new = 1;
        for (int j = 0; j < buf_list_size; j++){
            if (buf.st_ino == buf_list[j].st_ino){
                is_new = 0;
                break;
            }
        }
        if(is_new){
            buf_list[buf_list_size] = buf;
            buf_list_size++;
            printf("%s\n", argv[i]);
        }
        i++;
    }
    return EXIT_SUCCESS;
}