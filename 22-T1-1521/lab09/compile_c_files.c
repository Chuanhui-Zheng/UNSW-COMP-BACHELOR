// compile .c files specified as command line arguments
//
// if my_program.c and other_program.c is speicified as an argument then the follow two command will be executed:
// /usr/local/bin/dcc my_program.c -o my_program
// /usr/local/bin/dcc other_program.c -o other_program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spawn.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DCC_PATH "/usr/local/bin/dcc"

extern char **environ;

int main(int argc, char **argv){
    int i = 1;
    while (i < argc){
        pid_t pid;
        int status;
        char file[1000] = {0};
        strncpy(file, argv[i],strlen(argv[i])-2);
        printf("running the command: \"%s %s -o %s\"\n", DCC_PATH, argv[i], file);
        char *args[] = {DCC_PATH, argv[i], "-o", file, NULL};
        status = posix_spawn(&pid, args[0], NULL, NULL, args, environ);
        if (status != 0)
        {
            perror("posix_spawn");
            exit(1);
        }
        waitpid(pid, &status, 0);
        i++;
    }
    return EXIT_SUCCESS;
}
