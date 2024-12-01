// Small library to handle various operations on a deck of cards.
// Written by Blair (z5351042) on 11/11/2021

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "deck.h"

// Creates a new deck, this has already been done for you.
struct deck *create_deck() {
    struct deck *store = malloc(sizeof(struct deck));
    store->n_cards = 0;
    return store;
}

void add_card(struct deck *deck, char *card) {
    strcpy(deck->cards[deck->n_cards], card);
    deck->n_cards++;
}

void print_deck(struct deck *deck) {
    for (int i = 0; i < deck->n_cards; i++){
        for (int j = 0; deck->cards[i][j] != '\0'; j++){
            putchar(deck->cards[i][j]);
        }
        putchar('\n');
    }
    return;
}

int count_suit(struct deck *deck, char suit) {
    int ini = 0;
    for (int i = 0; i < deck->n_cards; i++)
    {
        for (int j = 0; deck->cards[i][j] != '\0'; j++)
        {
            if (deck->cards[i][j] == suit)
                ini++;
        }
    }
    return ini;
}
