//Blair z5351042
// copy all of the values in source1 which are also found in source2 into destination
// return the number of elements copied into destination

int common_elements(int length, int source1[length], int source2[length], int destination[length]) {
    // PUT YOUR CODE HERE (you must change the next line!)
    int ini1 = 0;
    int num_copied = 0;
    while (ini1 < length){
        int ini2 = 0;
        int copy = 0;
        while(ini2 < length && !copy){
            if(source1[ini1] == source2[ini2]){
                copy = 1;
            }
            ini2++;
        }
        if (copy){
            destination[num_copied]=source1[ini1];
            num_copied++;
        }
        ini1++;
    }
    return num_copied;
}

// You may optionally add a main function to test your common_elements function.
// It will not be marked.
// Only your common_elements function will be marked.
