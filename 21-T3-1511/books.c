//
// Author: INSERT-NAME-HERE (INSERT-ZID-HERE)
// Date: INSERT-DATE-HERE
//
// Description:
// INSERT-DESCRIPTION-HERE
// Written by Blair (z5351042) on 11/11/2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "books.h"

struct book {
    struct book *next;
    char title[MAX_STR_LENGTH];
    char author[MAX_STR_LENGTH];
    int page;
};

struct book *insert_book(struct book *head, char *title, char *author, int num_pages) {
    struct book *newbook = malloc(sizeof(struct book));
    struct book *re;
    newbook->next = NULL;
    newbook->page = num_pages;
    strcpy(newbook->title, title);
    strcpy(newbook->author, author);
    if (head == NULL){
        re = newbook;
    }
    else{
        struct book *p = head;
        while (p->next != NULL){
            p = p->next;
        }
        p->next = newbook;
        re = head;
    }
    return re;
}

void print_books(struct book *head) {
    struct book *p = head;
    while (p != NULL){
        printf("%s by %s (%d pages)\n", p->title, p->author, p->page);
        p = p->next;
    }
}
