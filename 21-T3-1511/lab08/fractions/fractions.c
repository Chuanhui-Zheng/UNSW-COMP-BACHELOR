// 
// Author: Blair (z5351042)
// Date: 11/7/2021
// Description:
// INSERT-DESCRIPTION-HERE

#include "fractions.h"

// These are function stubs!
// They are functions which compile but do not have the correct behaviour.

double convert(struct fraction frac) {
    double top = (double) frac.top;
    double bottom = (double) frac.bottom;
    return top / bottom;
}

struct fraction add(struct fraction first, struct fraction second) {
    // TODO: complete the function
    struct fraction result;
    int top = first.top * second.bottom + second.top * first.bottom;
    int bottom = first.bottom * second.bottom;
    int i = 1;
    int gcd = 0;
    while (i <= top && i <= bottom){
        if (top % i == 0 && bottom % i == 0){
            gcd = i;
        }
        i++;
    }
    top /= gcd;
    bottom /= gcd;
    result.top = top;
    result.bottom = bottom;

    return result;
}