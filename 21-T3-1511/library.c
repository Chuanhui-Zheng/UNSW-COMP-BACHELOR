
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "library.h"

///////////////////////////////////////////////////////////////////////////////
///////////            DO NOT EDIT THIS FUNCTION            ///////////////////
///////////////////////////////////////////////////////////////////////////////
struct library *create_library() {
    struct library *new = malloc(sizeof(struct library));

    new->genres = NULL;
    return new;
}

///////////////////////////////////////////////////////////////////////////////
///////////            DO NOT EDIT THIS FUNCTION            ///////////////////
///////////////////////////////////////////////////////////////////////////////
void add_genre(struct library *lib, char *genre) {
    struct genre *new = malloc(sizeof(struct genre));
    strcpy(new->name, genre);
    new->books = NULL;
    new->next = NULL;

    new->next = lib->genres;
    lib->genres = new;
}


///////////////////////////////////////////////////////////////////////////////
///////////         EDIT ALL FUNCTIONS BELOW HERE           ///////////////////
///////////////////////////////////////////////////////////////////////////////

int add_book_to_genre(
    struct library *lib,
    char *genre,
    char *title,
    char *author,
    int n_pages
) {
    // TODO: Complete this function according to the spec in `library.h`
    return NOT_FOUND;
}

void print_books_in_genre(struct library *lib, char *genre) {
    // TODO: Complete this function according to the spec in `library.h`
    printf("No books\n");
}
