// CSE Valley
// cse_valley.c
//
// This program was written by Blair (z5351042)
// on 10/18/2021
//
// Version 1.0.0 (2021-10-04): Assignment Released.
//


#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_SIZE 50
#define MAX_NUM_SEED_TYPES 26
#define LAND_SIZE 8
#define NO_SEED ' '
#define TRUE 1
#define FALSE 0

struct land {
    int is_watered;
    char seed_name;
};

struct seeds {
    char name;
    int amount;
};

struct farmer {
    int curr_col;
    int curr_row;
    char curr_dir;
};


// HINT: You will be using this function in stage 2!
void print_land(struct land farm_land[LAND_SIZE][LAND_SIZE], struct farmer cse_farmer);
void func(struct seeds seed_collection[26], int length, int position, int insert_num);
void func2(struct seeds seed_collection[26], int length, int position, int insert_num);

// Provided functions use for game setup
// You do not need to use these functions yourself.
struct farmer initialise_farmer(struct farmer cse_farmer);
void initialise_seeds(struct seeds seed_collection[MAX_NUM_SEED_TYPES]);
void initialise_land(struct land farm_land[LAND_SIZE][LAND_SIZE]);
void print_top_row(struct land farm_land[LAND_SIZE][LAND_SIZE], int row);
void print_farmer_row(struct land farm_land[LAND_SIZE][LAND_SIZE], 
                      struct farmer cse_farmer);

int main(void) {

    struct farmer cse_farmer = {};
    cse_farmer = initialise_farmer(cse_farmer);

    struct land farm_land[LAND_SIZE][LAND_SIZE];
    initialise_land(farm_land);

    struct seeds seed_collection[MAX_NUM_SEED_TYPES];
    initialise_seeds(seed_collection);

    printf("Welcome to CSE Valley, farmer!\n");
    printf("Congratulations, you have received 60 seeds.\n");
    printf("How many different seeds do you wish to have? ");
    // Note: Please remove all TODO's in your submission (including this comment)
    int num_seed;
    scanf("%d", &num_seed);
    int i = 0;
    printf("Enter the names of the seeds to be given:\n");
    while (i < num_seed) {
        scanf(" %c", &seed_collection[i].name);
        seed_collection[i].amount = 60/num_seed;
        i++;
    }
    i = 0;

    printf("Game Started!\n");

    // with a loop that reads and executes commands until EOF.
    // See: https://cs1511.web.cse.unsw.edu.au/short/21T3_a1_explain/
    // for more information!
    
    char command;
    printf("Enter command: ");
    int dec = scanf(" %c", &command);
    int ini = 0;
    int check = 0;
    int day = 1;
    while (dec == 1) {

        if (command == 'a') {
            printf("  Seeds at your disposal:\n");
            while (ini < num_seed) {
                printf("  - %d seed(s) with the name '%c'\n", seed_collection[ini].amount,
                 seed_collection[ini].name);
                ini++;
            }
            ini = 0;
        }

        else if (command == 's') {
            char check_seed;
            scanf(" %c", &check_seed);
            i = 0;
            if ('a' <= check_seed && 'z' >= check_seed) {
                while (i < num_seed) {
                    if (check_seed == seed_collection[i].name) {
                        printf("  There are %d seeds with the name '%c'\n",
                         seed_collection[i].amount, seed_collection[i].name);
                        check = 1;
                        break;
                    }
                    i++;
                }
                if (check == 0) {
                    printf("  There is no seed with the name '%c'\n", check_seed);
                }
            }
            else {
                printf("  Seed name has to be a lowercase letter\n");
            }
            check = 0;
        }

        else if (command == 'l') {
            print_land(farm_land, cse_farmer);
        }

        else if (command == '<' || command == '>' || command == 'v' || command == '^') {
            if (command != cse_farmer.curr_dir) {
                cse_farmer.curr_dir = command;
            }

            else if (command == cse_farmer.curr_dir) {
                if (command == '<') {
                    if (cse_farmer.curr_col-1 > 0) {
                        cse_farmer.curr_col--;
                    }
                }
                else if (command == '>') {
                    if (cse_farmer.curr_col+1 < LAND_SIZE-1) {
                        cse_farmer.curr_col++;
                    }
                }
                else if (command == '^') {
                    if (cse_farmer.curr_row-1 > 0) {
                        cse_farmer.curr_row--;
                    }
                }
                else if (command == 'v') {
                    if (cse_farmer.curr_row+1 < LAND_SIZE-1) {
                        cse_farmer.curr_row++;
                    }
                }
            }
        }

        if (command == 'o') {
            char check_adja;
            scanf(" %c", &check_adja);
            if (check_adja == 'w') {
                if (cse_farmer.curr_dir == '>') {
                    if (cse_farmer.curr_col + 1 < LAND_SIZE - 1) {
                        farm_land[cse_farmer.curr_row][cse_farmer.curr_col + 1]
                        .is_watered = TRUE;
                    }
                }
                else if (cse_farmer.curr_dir == '<') {
                    if (cse_farmer.curr_col - 1 > 0) {
                        farm_land[cse_farmer.curr_row][cse_farmer.curr_col - 1]
                        .is_watered = TRUE;
                    }
                }
                else if (cse_farmer.curr_dir == 'v') {
                    if (cse_farmer.curr_row + 1 < LAND_SIZE - 1) {
                        farm_land[cse_farmer.curr_row + 1][cse_farmer.curr_col]
                        .is_watered = TRUE;
                    }
                }
                else if (cse_farmer.curr_dir == '^') {
                    if (cse_farmer.curr_row - 1 > 0) {
                        farm_land[cse_farmer.curr_row - 1][cse_farmer.curr_col]
                        .is_watered = TRUE;
                    }
                }
            }
            else if (check_adja == 'p') {
                char check_adja_seed;
                scanf(" %c", &check_adja_seed);
                if ('a' <= check_adja_seed && 'z' >= check_adja_seed) {
                    while (ini < num_seed) {
                        if (seed_collection[ini].amount <= 0) {
                            break;
                        }
                        if (check_adja_seed == seed_collection[ini].name) {
                            if (cse_farmer.curr_dir == '>') {
                                if (cse_farmer.curr_col+1 < LAND_SIZE-1) {
                                    farm_land[cse_farmer.curr_row]
                                    [cse_farmer.curr_col + 1]
                                    .seed_name = seed_collection[ini].name;
                                }
                            }
                            else if (cse_farmer.curr_dir == '<') {
                                if (cse_farmer.curr_col - 1 > 0) {
                                    farm_land[cse_farmer.curr_row]
                                    [cse_farmer.curr_col - 1]
                                    .seed_name = seed_collection[ini].name;
                                }
                            }
                            else if (cse_farmer.curr_dir == 'v') {
                                if (cse_farmer.curr_row + 1 < LAND_SIZE - 1) {
                                    farm_land[cse_farmer.curr_row + 1]
                                    [cse_farmer.curr_col]
                                    .seed_name = seed_collection[ini].name;
                                }
                            }
                            else if (cse_farmer.curr_dir == '^') {
                                if (cse_farmer.curr_row - 1 > 0) {
                                    farm_land[cse_farmer.curr_row - 1]
                                    [cse_farmer.curr_col]
                                    .seed_name = seed_collection[ini].name;
                                }
                            }
                            seed_collection[ini].amount--;
                            check = 1;
                            break;
                        }
                        ini++;
                    }
                    if (check == 0) {
                        printf("  There is no seed with the name '%c'\n", check_adja_seed);
                    }
                }
                else {
                    printf("  Seed name has to be a lowercase letter\n");
                }
                ini = 0;
                check = 0;
            }
        }

        else if (command == 'p') {
            int scatter_position = 0;
            char check_scatter_seed;
            scanf(" %c", &check_scatter_seed);
            if ('a' <= check_scatter_seed && 'z' >= check_scatter_seed) {
                while (ini < num_seed) {
                    if (check_scatter_seed == seed_collection[ini].name) {
                        if (cse_farmer.curr_dir == '<'
                         || cse_farmer.curr_dir == '^') {
                            printf("You cannot scatter seeds ^ or <\n");
                        }
                        else if (cse_farmer.curr_dir == 'v') {
                            scatter_position = cse_farmer.curr_row;
                            while (scatter_position < LAND_SIZE) {
                                farm_land[scatter_position]
                                [cse_farmer.curr_col]
                                .seed_name = seed_collection[ini].name;
                                scatter_position++;
                                seed_collection[ini].amount--;
                                if (seed_collection[ini].amount <= 0) {
                                    break;
                                }
                            }
                        }
                        else if (cse_farmer.curr_dir == '>') {
                            scatter_position = cse_farmer.curr_col;
                            while (scatter_position < LAND_SIZE) {
                                farm_land[cse_farmer.curr_row]
                                [scatter_position]
                                .seed_name = seed_collection[ini].name;
                                scatter_position++;
                                seed_collection[ini].amount--;
                                if (seed_collection[ini].amount <= 0) {
                                    break;
                                }
                            }
                        }
                        check = 1;
                        break;
                    }
                    ini++;
                    
                }
                if (check == 0) {
                    printf("  There is no seed with the name '%c'\n", check_scatter_seed);
                }
            }
            else {
                printf("  Seed name has to be a lowercase letter\n");
            }
            check = 0;
            ini = 0;
        }

        else if (command == 'w') {
            int rain_row = 0;
            int rain_col = 0;
            int check_rain_size;
            scanf(" %d", &check_rain_size);
            if (check_rain_size < 0) {
                printf("  The size argument needs to be a non-negative integer\n");
            }
            else {
                while (rain_row <= check_rain_size) {
                    while (rain_col <= check_rain_size) {
                        if (cse_farmer.curr_row + rain_row < LAND_SIZE
                         && cse_farmer.curr_col + rain_col < LAND_SIZE) {
                            farm_land[cse_farmer.curr_row + rain_row]
                            [cse_farmer.curr_col + rain_col]
                            .is_watered = TRUE;
                        }
                        if (cse_farmer.curr_row - rain_row >= 0
                         && cse_farmer.curr_col - rain_col >= 0) {
                            farm_land[cse_farmer.curr_row - rain_row]
                            [cse_farmer.curr_col - rain_col]
                            .is_watered = TRUE;
                        }
                        if (cse_farmer.curr_row + rain_row < LAND_SIZE
                         && cse_farmer.curr_col - rain_col >= 0) {
                            farm_land[cse_farmer.curr_row + rain_row]
                            [cse_farmer.curr_col - rain_col]
                            .is_watered = TRUE;
                        }
                        if (cse_farmer.curr_row - rain_row >= 0 &&
                         cse_farmer.curr_col + rain_col < LAND_SIZE) {
                            farm_land[cse_farmer.curr_row - rain_row]
                            [cse_farmer.curr_col + rain_col]
                            .is_watered = TRUE;
                        }
                        rain_col++;
                    }
                    rain_col = 0;
                    rain_row++;
                }
            }
        }

        else if (command == 'n') {
            day++;
            printf("  Advancing to the next day... Day %d, let's go!\n", day);
            int col = 0;
            while (col < LAND_SIZE) {
                int row = 0;
                while (row < LAND_SIZE) {
                    if (farm_land[row][col].seed_name >= 'A'
                     && farm_land[row][col].seed_name <= 'Z') {
                        farm_land[row][col].seed_name = NO_SEED;
                    }
                    else if (farm_land[row][col].seed_name >= 'a'
                     && farm_land[row][col].seed_name <= 'z') {
                        if (farm_land[row][col].is_watered == TRUE) {
                            farm_land[row][col].seed_name -= 'a' - 'A';
                        }
                        else {
                            farm_land[row][col].seed_name = NO_SEED;
                        }
                    }
                    farm_land[row][col].is_watered = FALSE;
                    row++;
                }
                col++;
            }
            cse_farmer = initialise_farmer(cse_farmer);
        }

        if (command == 'h') {
            int row = 0;
            int col = 0;

            if (cse_farmer.curr_dir == '>') {
                if (cse_farmer.curr_col + 1 < LAND_SIZE - 1) {
                    row = cse_farmer.curr_row;
                    col = cse_farmer.curr_col + 1;
                }
            }
            else if (cse_farmer.curr_dir == '<') {
                if (cse_farmer.curr_col - 1 > 0) {
                    row = cse_farmer.curr_row;
                    col = cse_farmer.curr_col - 1;
                }
            }
            else if (cse_farmer.curr_dir == 'v') {
                if (cse_farmer.curr_row + 1 < LAND_SIZE - 1) {
                    row = cse_farmer.curr_row + 1;
                    col = cse_farmer.curr_col;
                }
            }
            else if (cse_farmer.curr_dir == '^') {
                if (cse_farmer.curr_row - 1 > 0) {
                    row = cse_farmer.curr_row - 1;
                    col = cse_farmer.curr_col;
                }
            }

            if (farm_land[row][col].seed_name >= 'A'
             && farm_land[row][col].seed_name <= 'Z') {
                while (ini < num_seed) { 
                    if (farm_land[row][col].seed_name + 'a' - 'A' == seed_collection[ini].name) {
                        seed_collection[ini].amount += 5;
                        break;
                    }
                    ini++;
                }
                farm_land[row][col].seed_name = NO_SEED;
                printf("  Plant '%c' was harvested, resulting in 5 '%c' seed(s)\n",
                 seed_collection[ini].name - ('a' - 'A'),
                  seed_collection[ini].name );
            }
            ini = 0;
        }

        if (command == 't') {
            char give;
            int trade_amount;
            char receive;
            int ini2 = 0;
            int check2 = 0;
            scanf(" %c", &give);
            scanf(" %d", &trade_amount);
            scanf(" %c", &receive);
            if ('a' <= give && 'z' >= give && 'a' <= receive && 'z' >= receive) {
                while (ini < num_seed) {
                    if (give == seed_collection[ini].name) {
                        check = 1;
                        if (trade_amount < 0) {
                            printf("  You can't trade negative seeds\n");
                        }
                        else {
                            if (seed_collection[ini].amount >= trade_amount) {
                                seed_collection[ini].amount -= trade_amount;
                                while (ini2 < num_seed){
                                    if (receive == seed_collection[ini2].name) {
                                        seed_collection[ini2].amount += trade_amount;
                                        check2 = 0;
                                        break;
                                    }
                                    else {
                                        check2 = 1;
                                    }
                                        
                                    ini2++;
                                }
                            }
                            else{
                                printf("  You don't have enough seeds to be traded\n");
                            }
                        }
                        break;
                    }
                    ini++;
                }
                if (check == 0){
                    printf("  You don't have the seeds to be traded\n");
                }
            }
            else {
                    printf("  Seed name has to be a lowercase letter\n");
            }
            if (check2 == 1) {
                func(seed_collection, num_seed, 0, receive);
                func2(seed_collection, num_seed, 0, trade_amount);
                num_seed++;
            }

            ini = 0;
            check = 0;
            check2 = 0;
        }

        printf("Enter command: ");
        dec = scanf(" %c", &command);
    }
    // print_land(farm_land, cse_farmer);

    return 0;
}

void func(struct seeds seed_collection[26], int length, int position, int insert_num) {
    int j;
    for (j = length - 1; j >= position; j--) {
        seed_collection[j+1].name = seed_collection[j].name;
    }
    seed_collection[position].name = insert_num;
}
void func2(struct seeds seed_collection[26], int length, int position, int insert_num) {
    int j;
    for (j = length - 1; j >= position; j--) {
        seed_collection[j+1].amount = seed_collection[j].amount;
    }
    seed_collection[position].amount = insert_num;
}


///////////////////////////////
//     Provided Functions     //
////////////////////////////////

// Prints the structs land (including locating where the
// farmer is)
// You will need this function in Stage 2.
void print_land(struct land farm_land[LAND_SIZE][LAND_SIZE], struct farmer cse_farmer) {
    printf("|---|---|---|---|---|---|---|---|\n");
    int i = 0;
    while (i < LAND_SIZE) {
        print_top_row(farm_land, i);
        // only prints mid and bottom row when the farmer
        // is in that row
        if (i == cse_farmer.curr_row) {
            print_farmer_row(farm_land, cse_farmer);
        }
        printf("|---|---|---|---|---|---|---|---|\n");
        i++;
    }
}

// NOTE: You do not need to directly call any of the functions
// below this point. You are allowed to modify them, but you
// do not need to.

// Initialises struct farmer to its default state upon starting
// in which the farmer will be on the top left of the farm
// facing to the right (as noted by '>')
struct farmer initialise_farmer(struct farmer cse_farmer) {
    cse_farmer.curr_col = 0;
    cse_farmer.curr_row = 0;
    cse_farmer.curr_dir = '>';
    return cse_farmer;
}

// Initialises a 2d array of struct land to its default state 
// upon starting, which is that all land is unwatered and
// contains no seed
void initialise_land(struct land farm_land[LAND_SIZE][LAND_SIZE]) {
    int i = 0;
    while (i < LAND_SIZE) {
        int j = 0;
        while (j < LAND_SIZE) {
            farm_land[i][j].is_watered = FALSE;
            farm_land[i][j].seed_name = NO_SEED;
            j++;
        }
        i++;
    }
}

// Initialises struct farmer to its default state upon starting,
// which that all names are initialised as NO_SEED and its
// amount is 0
void initialise_seeds(struct seeds seed_collection[MAX_NUM_SEED_TYPES]) {
    int i = 0;
    while (i < MAX_NUM_SEED_TYPES) {
        seed_collection[i].amount = 0;
        seed_collection[i].name = NO_SEED;
        i++;
    }
}

////////////////////////////////
//      Helper Functions      //
////////////////////////////////

// prints the top row of a particular struct land
void print_top_row(struct land farm_land[LAND_SIZE][LAND_SIZE], int row) {
    int j = 0;
    while (j < LAND_SIZE) {
        printf("|");
        printf("%c", farm_land[row][j].seed_name);
        printf(" ");
        if (farm_land[row][j].is_watered == TRUE) {
            printf("W");
        } else {
            printf(" ");
        }
        j++;
    }
    printf("|");
    printf("\n");
}

// prints the 2 additional row when a farmer is in
// a particular row
void print_farmer_row(struct land farm_land[LAND_SIZE][LAND_SIZE], 
                      struct farmer cse_farmer)  {
    int j = 0;
    while (j < LAND_SIZE) {
        printf("|");
        if (j == cse_farmer.curr_col) {
            if (cse_farmer.curr_dir == '<') {
                printf("<");
            } else {
                printf(" ");
            }
            if (cse_farmer.curr_dir == '^') {
                printf("^");
            } else {
                printf("f");
            }
            if (cse_farmer.curr_dir == '>') {
                printf(">");
            } else {
                printf(" ");
            }
        } else {
            printf("   ");
        }
        j++;
    }
    printf("|");
    printf("\n");
    j = 0;
    while (j < LAND_SIZE) {
        printf("|");
        if (j == cse_farmer.curr_col) {
            printf(" ");
            if (cse_farmer.curr_dir == 'v') {
                printf("v");
            } else if (cse_farmer.curr_dir == '^') {
                printf("f");
            } else {
                printf(" ");
            }
            printf(" ");
        } else {
            printf("   ");
        }
        j++;
    }
    printf("|");
    printf("\n");
}
