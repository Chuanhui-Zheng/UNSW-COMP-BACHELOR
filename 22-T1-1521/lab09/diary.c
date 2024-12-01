//Blair z5351042
# include<stdio.h>
# include<stdlib.h>
# include<string.h>

int main(int argc, char **argv)
{
    char *path = getenv("HOME");
    if (path == NULL){
        path = ".";
    }
    char *file = "/.diary";
    char *complete = (char *)malloc(strlen(path) + strlen(file) + 2);
    strcpy(complete, path);
    strcat(complete, file);
    FILE *fp = fopen(complete, "a");
    for (int i = 1; i < argc; i++){
        fprintf(fp, "%s ", argv[i]);
    }
    fprintf(fp, "%c", '\n');
    free(complete);
    return 0;
}