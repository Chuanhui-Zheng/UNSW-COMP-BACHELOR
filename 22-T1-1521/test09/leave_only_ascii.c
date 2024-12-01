//Blair z5351042

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *read_file(char *filename, long *lSize);

int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    long lSize = 0;
    unsigned char *buffer;
    buffer = read_file(argv[1],&lSize);


    FILE *fo;
    fo = fopen(argv[1], "w");

    for (int i = 0; i < lSize; i++){
        
        if (buffer[i] > 255 || buffer[i] < 128)
            fwrite(&buffer[i], 1, 1, fo);
    }

    fclose(fo);
    free(buffer);

    return EXIT_SUCCESS;
}

// Read file to buffer
unsigned char *read_file(char *filename, long *lSize){
    FILE *fo;
    
    fo = fopen(filename, "r");
    if (fo == NULL){
        printf("Error opening file %s\n", filename);
        exit(1);
    }
    fseek(fo, 0, SEEK_END);
    *lSize = ftell(fo);
    rewind(fo);

    unsigned char *buffer = (unsigned char *)malloc(*lSize + 1);
    *lSize = fread(buffer, sizeof(char), *lSize, fo);
    buffer[*lSize] = '\0';
    fclose(fo);
    return buffer;
}