#include "bit_rotate.h"

// return the value bits rotated left n_rotations
uint16_t bit_rotate(int n_rotations, uint16_t bits){
    int n = n_rotations % 16;
    if (n < 0)
        n = 16 + n;
    uint16_t front = bits << n;
    uint16_t end = bits >> (16 - n);
    return front + end;
}