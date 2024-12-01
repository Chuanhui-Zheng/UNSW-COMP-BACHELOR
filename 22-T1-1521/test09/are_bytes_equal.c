//Blair z5351042

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc != 5){
        printf("Usage: %s <filename1> <position1> <filename2> <position2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fo;
    fo = fopen(argv[1], "r");
    if (fo == NULL){
        printf("Error opening file %s\n", argv[1]);
        exit(1);
    }

    fseek(fo, 0, SEEK_END);
    int size1 = ftell(fo);
    fseek(fo, atoi(argv[2]), SEEK_SET);

    unsigned char byte1;
    fread(&byte1, 1, 1, fo);
    fclose(fo);

    FILE *fp2;
    fp2 = fopen(argv[3], "r");
    if (fp2 == NULL){
        printf("Error opening file %s\n", argv[3]);
        exit(1);
    }

    fseek(fp2, 0, SEEK_END);
    int size2 = ftell(fp2);
    fseek(fp2, atoi(argv[4]), SEEK_SET);

    unsigned char byte2;
    fread(&byte2, 1, 1, fp2);
    fclose(fp2);

    if (atoi(argv[2]) > size1 || atoi(argv[4]) > size2){
        printf("byte %d in %s and byte %d in %s are not the same\n", atoi(argv[2]), argv[1], atoi(argv[4]), argv[3]);
        return EXIT_SUCCESS;
    }
    if (byte1 == byte2)
        printf("byte %d in %s and byte %d in %s are the same\n", atoi(argv[2]), argv[1], atoi(argv[4]), argv[3]);
    else
        printf("byte %d in %s and byte %d in %s are not the same\n", atoi(argv[2]), argv[1], atoi(argv[4]), argv[3]);
    return EXIT_SUCCESS;
}