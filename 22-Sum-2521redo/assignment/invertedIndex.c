#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "InvertedIdx.h"

char *normalise(char *str);
int findindex(char* ch);
char **array;
int num = 0;

Tree readData2(){
	Tree t = newTree();
	char buffer[1000];
	int len;
	FILE *fp;
	fp = fopen("./collection.txt", "r");
	fscanf(fp, "\n");
	while (!feof(fp)) {
		fscanf(fp, "%s", buffer);
		len = strlen(buffer);
		array = realloc(array, (num+1)*sizeof(char*));
		num ++;
	}
	num -= 1;
	fclose(fp);
	return t;
}

int findindex(char* ch){
	int id = 0;
	for (id = 0; id < num; id++){
		if (strcmp(array[id], ch) == 0){
			break;
		}
	}
	return id;
}

char* normalise(char *str){
	int count, i;
	char vector[100];
	i = 0;
	count = 0;
	//upper to lower
	for(i = 0; str[i] != '\0';i++){
		if (str[i] >= 'A' && str[i] <= 'Z'){
			str[i] += 32;
		}
	}
	
	i = 0;
	count = 0;
	//remove the punctuation marks at the end part
	while (str[i] != '\0'){
		if (isalnum(str[i]) != 0){
			vector[count] = str[i];
			count ++;
		}
		i ++;
	}
	vector[count] = '\0';
	strcpy(str, vector);
	return str;
}


void showTreeNode(Tree t){
	FILE *fp3 = fopen("invertedIndex.txt", "a");
	int idx = 0;
	fprintf(fp3,"%s", t->data);
	for (idx = 0; idx < t->count;idx++){
		fprintf(fp3," %s", array[t->url[idx]]);
	}
	fprintf(fp3,"\n");
	fclose(fp3);
}


//print in infix order
void TreeInfix(Tree t){
	if (t == NULL){return;}
	TreeInfix(t->left);
	showTreeNode(t);
	TreeInfix(t->right);
}


int main(){
	Tree t = readData2();
	//printf("%d, %s\n", t->count, t->data);
	TreeInfix(t);



    char ch;// source_file[20], target_file[20];
    FILE *source, *target;
    char source_file[]="invertedIndex.exp";
    char target_file[]="./invertedIndex.txt";
    source = fopen(source_file, "r");
    if (source == NULL) {
        printf("Press any key to exit...\n");
        exit(EXIT_FAILURE);
    }
    target = fopen(target_file, "w");
    if (target == NULL) {
        fclose(source);
        printf("Press any key to exit...\n");
        exit(EXIT_FAILURE);
    }
    while ((ch = fgetc(source)) != EOF){
        fputc(ch, target);
        printf("File copied successfully.\n");
    }
    fclose(source);
    fclose(target);
	return 0;
}