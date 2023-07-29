#include "demo_shuffle.h"

/**
 * Shuffles an array of greek letter names and array of integers using riffle.
 * Also checks that the shuffle is correct.
 * @return: The shuffled arrays.
 */
int main() {
    int i;
    int nums[20];
    char *greek[] = {"alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta", "theta", "iota", "kappa", "lambda", "mu"};

    // Initialize the array of integers 1 to 20
    for (i = 0; i < 20; i++) {
        nums[i] = i + 1;
    }

    // Shuffle the array of integers 10 times
    srand(time(NULL));  // Seed the random number generator
    riffle(nums, 20, sizeof(int), 10);
    printf("Shuffled array of integers:\n");
    for (i = 0; i < 20; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
    if (check_shuffle(nums, 20, sizeof(int), cmp_int)) {
        printf("Shuffled array of integers is correct\n");
    } else {
        printf("Shuffled array of integers is incorrect\n");
    }

    // Shuffle the array of Greek letter names 5 times
    srand(time(NULL));  // Seed the random number generator
    riffle(greek, 12, sizeof(char*), 5);
    printf("Shuffled array of Greek letter names:\n");
    for (i = 0; i < 12; i++) {
        printf("%s ", greek[i]);
    }
    printf("\n");
    if (check_shuffle(greek, 12, sizeof(char*), cmp_str)) {
        printf("Shuffled array of Greek letter names is correct\n");
    } else {
        printf("Shuffled array of Greek letter names is incorrect\n");
    }

    return 0;
}