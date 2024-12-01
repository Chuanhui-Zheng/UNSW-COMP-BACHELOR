//
// Assignment 2 21T3 COMP1511: CS Pizzeria
// pizzeria.c
//
// This program was written by YOUR-NAME-HERE (z5555555)
// on INSERT-DATE-HERE
//
// TODO: INSERT-DESCRIPTION-HERE
//
// Version 1.0.0: Release

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: add any extra #includes your code needs here.

#include "pizzeria.h"

// TODO: add your own #defines here.

struct ingredient{
    // TODO: add your own fields in Stage 2.
    struct ingredient *next;
    double price;
    int amount;
    char name[MAX_STR_LENGTH];
};

struct order{
    // TODO: add your own fields in Stage 1.
    // Looking to store a price field? Try putting in "double price;" here!
    struct order *next;
    char user[MAX_STR_LENGTH];
    char pizz_name[MAX_STR_LENGTH];
    int time;
    double price;
    struct ingredient *ingredients;
};

struct pizzeria{
    // TODO: add your own fields if required.
    struct order *orders;
    struct order *sel;
};

// TODO: add any other structs you define here.

//////////////////////////////////////////////////////////////////////

// TODO: add prototypes for any helper functions you create here.

// Prints a single order
void print_order(
    int num,
    char *customer,
    char *pizza_name,
    double price,
    int time_allowed);

// Prints an ingredient given the name, amount and price in the required format.
// This will be needed for stage 2.
void print_ingredient(char *name, int amount, double price);

////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

struct pizzeria *create_pizzeria() {
    // Allocates memory to store a `struct pizzeria` and returns a pointer to
    // it. The variable `new` holds this pointer!
    struct pizzeria *new = malloc(sizeof(struct pizzeria));

    new->orders = NULL;
    new->sel = NULL;

    // TODO: this function has already been implemented for the current
    // struct pizzeria. When you decide to change struct pizzeria, change
    // this function as well.

    return new;
}

int add_order(
    struct pizzeria *pizzeria,
    char *customer,
    char *pizza_name,
    double price,
    int time_allowed)
{

    // TODO: fill in the rest of this function
    if (price < 0){
        return INVALID_PRICE;
    }
    else if (time_allowed <= 0){
        return INVALID_TIME;
    }
    else{
        struct order *n = malloc(sizeof(struct order));
        n->next = NULL;
        n->ingredients = NULL;
        n->price = price;
        n->time = time_allowed;
        strcpy(n->user, customer);
        strcpy(n->pizz_name, pizza_name);

        struct order *p = pizzeria->orders;
        if (p != NULL){
            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = n;
            return SUCCESS;
        }
        else{
            pizzeria->orders = n;
            return SUCCESS;
        }
    }
}

void print_all_orders(struct pizzeria *pizzeria) {

    // TODO: fill in the rest of this function
    struct order *p = pizzeria->orders;
    int i = 0;
    while (p != NULL) {
        i++;
        print_order(i, p->user, p->pizz_name, p->price, p->time);
        p = p->next;
    }
    // Do not change this part of the function
    print_selected_order(pizzeria);
    return;
}

int next_deadline(struct pizzeria *pizzeria)
{

    // TODO: fill in the rest of this function
    if (pizzeria->orders == NULL) {
        return INVALID_CALL;
    }
    else {
        struct order *p = pizzeria->orders;
        int time = p->time;
        while (p != NULL) {
            if (time > p->time) {
                time = p->time;
            }
            p = p->next;
        }
        return time;
    }
}

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

void select_next_order(struct pizzeria *pizzeria) {

    // TODO: fill in the rest of this function
    struct order *sel = pizzeria->sel;
    if (sel == NULL) {
        pizzeria->sel = pizzeria->orders;
    }
    else {
        pizzeria->sel = sel->next;
    }
}

void select_previous_order(struct pizzeria *pizzeria)
{

    // TODO: fill in the rest of this function
    struct order *sel = pizzeria->sel;
    struct order *ord = pizzeria->orders;
    if (ord == NULL)
        return;
    if (sel == NULL) {
        while (ord->next != NULL) {
            ord = ord->next;
        }
        pizzeria->sel = ord;
    }
    else {
        if (ord == sel) {
            pizzeria->sel = NULL;
            return;
        }
            
        while (ord->next != NULL) {
            if (ord->next == sel) {
                break;
            }
            ord = ord->next;
        }
        pizzeria->sel = ord;
    }
    return;
}

void print_selected_order(struct pizzeria *pizzeria) {

    // TODO: Change this once you have implemented the selected order
    // functionality.
    struct order *sel = pizzeria->sel;
    if (sel != NULL) {
        printf("\nThe selected order is %s's %s pizza ($%.2lf) due in %d minutes.\n", sel->user, sel->pizz_name, sel->price, sel->time);
        if (sel->ingredients!=NULL) {
            struct ingredient *p = sel->ingredients;
            while (p != NULL) {
                print_ingredient(p->name, p->amount, p->price);
                p = p->next;
            }
        }
    }
    else {
        printf("\nNo selected order.\n");
    }
}

int add_ingredient(
    struct pizzeria *pizzeria,
    char *ingredient_name,
    int amount,
    double price)
{

    // TODO: fill in the rest of this function
    if (pizzeria->sel == NULL) {
        return INVALID_ORDER;
    }
    else if (amount <= 0) {
        return INVALID_AMOUNT;
    }
    else if (price < 0) {
        return INVALID_PRICE;
    }
    struct ingredient *new = malloc(sizeof(struct ingredient));
    new->amount = amount;
    new->price = price;
    new->next = NULL;
    strcpy(new->name,ingredient_name);

    if (pizzeria->sel->ingredients == NULL) {
        pizzeria->sel->ingredients = new;
        return SUCCESS;
    }
    else{
        struct ingredient *p = pizzeria->sel->ingredients;
        struct ingredient *q = pizzeria->sel->ingredients;
        while(q!=NULL)
        {
            if (strcmp(q->name,ingredient_name)==0)
            {
                q->amount += amount;
                free(new);
                return SUCCESS;
            }
            q=q->next;
        }
        int num1 = strcmp(p->name,ingredient_name);
        p->next= NULL;
        if (num1 == 0){
            p->amount += amount;
            free(new);
            return SUCCESS;
        }
        else if (num1 == 1) {
            if (p == pizzeria->sel->ingredients)
            {
                new->next = p;
                pizzeria->sel->ingredients = new;
                return SUCCESS;
            }
        }
        int symble = 0;
        while (p->next != NULL){
            int num2 = strcmp(ingredient_name,p->next->name);
            printf("%d",num2);
            if (num2 == 0){
                p->next->amount += amount;
                free(new);
                symble = 1;
                break;
            }
            else if (num2 == -1) {
                struct ingredient *next = p->next;
                p->next = new;
                new->next = next;
                symble = 1;
                break;
            }
            p = p->next;
        }
        // printf("%d",symble);
        if (symble == 0) {
            p->next = new;
        }
        return SUCCESS;
    }
}

double calculate_total_profit(struct pizzeria *pizzeria) {

    // TODO: fill in the rest of this function

    if (pizzeria->sel == NULL) {
        return INVALID_ORDER;
    }
    else {
        struct ingredient *p = pizzeria->sel->ingredients;
        double coust = 0;
        while (p != NULL) {
            coust += p->amount * p->price;
            p = p->next;
        }
        double price = pizzeria->sel->price - coust;
        return price;
    }
}

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////

int cancel_order(struct pizzeria *pizzeria) {

    // TODO: fill in the rest of this function
    if (pizzeria->sel == NULL){
        return INVALID_ORDER;
    }
    else{
        struct order *sel = pizzeria->sel;
        struct order *p = pizzeria->orders;
        pizzeria->sel= sel->next;
        if (p == sel) {
            pizzeria->orders=pizzeria->orders->next;
        }
        else {
            while (p != NULL){
                if (p->next == sel){
                    break;
                }
                p = p->next;
            }
            p->next = sel->next;
        }

        struct ingredient *q = sel->ingredients;
        while (q!=NULL) {
            struct ingredient *remove = q;
            q=q->next;
            free(remove);
        }
        free(sel);
        return SUCCESS;
    }

}

void free_pizzeria(struct pizzeria *pizzeria) {

    // TODO: fill in the rest of this function
    struct order *p = pizzeria->orders;
    while (p != NULL) {
        struct ingredient *ig = p->ingredients;
        while (ig != NULL) {
            struct ingredient *ign = ig->next;
            free(ig);
            ig = ign;
        }
        struct order *next = p->next;
        free(p);
        p = next;
    }
    return;
}

int refill_stock(
    struct pizzeria *pizzeria,
    char *ingredient_name,
    int amount,
    double price)
{

    // TODO: fill in the rest of this function
    if (amount <= 0) {
        return INVALID_AMOUNT;
    }
        
    if (price < 0) {
        return INVALID_PRICE;
    }
        
    return SUCCESS;
}

void print_stock(struct pizzeria *pizzeria) {

    // TODO: fill in the rest of this function
    printf("\n");
    return;
}

int can_complete_order(struct pizzeria *pizzeria) {

    // TODO: fill in the rest of this function
    if (pizzeria->sel == NULL) {
        return INVALID_ORDER;
    }
        
    return SUCCESS;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

int complete_order(struct pizzeria *pizzeria) {
    if (pizzeria->sel == NULL) {
        return INVALID_ORDER;
    }
    return SUCCESS;
}

int save_ingredients(struct pizzeria *pizzeria, char *file_name) {

    if (pizzeria->sel == NULL) {
        return INVALID_ORDER;
    }
    return SUCCESS;
}

int load_ingredients(struct pizzeria *pizzeria, char *file_name) {
    if (pizzeria->sel == NULL) {
        return INVALID_ORDER;
    }
    return SUCCESS;
}

////////////////////////////////////////////////////////////////////////
//               HELPER FUNCTIONS - Add your own here                 //
////////////////////////////////////////////////////////////////////////

// Prints a single order
//
// `print_order` will be given the parameters:
// - `num` -- the integer that represents which order it is sequentially.
// - `customer` -- the name of the customer for that order.
// - `pizza_name` -- the pizza the customer ordered.
// - `price` -- the price the customer is paying for the pizza.
// - `time_allowed` -- the time the customer will wait for the order.
//
// `print_order` assumes all parameters are valid.
//
// `print_order` returns nothing.
//
// This will be needed for Stage 1.
void print_order(
    int num,
    char *customer,
    char *pizza_name,
    double price,
    int time_allowed)
{

    printf("%02d: %s ordered a %s pizza ($%.2lf) due in %d minutes.\n",
           num, customer, pizza_name, price, time_allowed);

    return;
}

// Prints a single ingredient
//
// `print_ingredient` will be given the parameters:
// - `name` -- the string which contains the ingredient's name.
// - `amount` -- how many of the ingredient we either need or have.
// - `price` -- the price the ingredient costs.
//
// `print_ingredient` assumes all parameters are valid.
//
// `print_ingredient` returns nothing.
//
// This will be needed for Stage 2.
void print_ingredient(char *name, int amount, double price)
{
    printf("    %s: %d @ $%.2lf\n", name, amount, price);
}
