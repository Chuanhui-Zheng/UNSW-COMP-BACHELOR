#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spawn.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    char target[1024];
    if (argc != 2){
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(1);
    }
    while (scanf("%s",target)!= EOF){
        char *args[] = {argv[1], target, NULL, NULL, NULL};
        pid_t pid;
        int status = posix_spawn(&pid, argv[1], NULL, NULL, args, NULL);
        waitpid(pid, &status, 0);
    }
    return 0;
}