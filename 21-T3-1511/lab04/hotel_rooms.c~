// 
// Written 10/10/2021
// By Blair z5351042
//
// INSERT-DESCRIPTION-HERE
//

#include <stdio.h>

#define MAX_ROOMS 50

struct hotel_room {
    // TODO: fill this in with the details of each hotel room
    int number;
    int cap;
    float pri;
};

// Prints the room in the correct format when given the room_number, capacity
// and price of it.
void print_room(int room_number, int capacity, double price);

int main(void) {

    int how_many_room;
    int people;
    
    printf("How many rooms? ");
    // TODO: scan in how many rooms in the hotel
    scanf("%d", &how_many_room);
    
    struct hotel_room lord[how_many_room];
    
    printf("Enter hotel rooms:\n");
    // TODO: scan in the details of each hotel room
    int i=0;
    while (i<how_many_room){
        scanf("%d %d %f", &lord[i].number, &lord[i].cap, &lord[i].pri);
        i++;
    }
    
    printf("How many people? ");
    // TODO: scan in how many people are in the user's group
    scanf("%d", &people);

    printf("Rooms that fit your group:\n");
    // TODO: print all the rooms that fit the user's group
    i = 0;
    while (i < how_many_room){
        if (people <= lord[i].cap){
            print_room(lord[i].number,lord[i].cap,lord[i].pri);
        }
    i++;
    }
    return 0;
}

// Prints the room in the correct format when given the room_number, capacity
// and price of it.
//
// Takes in:
// - `room_number` -- The hotel room's room number.
// - `capacity` -- How many people the hotel room can fit.
// - `price` -- How much the hotel room costs.
//
// Returns: nothing.
void print_room(int room_number, int capacity, double price) {

    printf("Room %d (%d people) @ $%.2lf\n", room_number, capacity, price);

    return;
}
