#include "quality.h"

/**
 * Calculates the average quality of a shuffle.
 * @return: The quality of the shuffle.
 */
int main() {
    // Loop through each shuffle count from 1 to 15
    int i;
    for (i = 1; i <= 15; i++) {
        // Print the average quality of a riffle shuffle of 50 integers with i shuffles, rounded to 3 decimal places
        printf("Average quality of a riffle shuffle of 50 integers with %d shuffles: %.3f\n", i, average_quality(50, i, 30));
    }
    return 0;
}