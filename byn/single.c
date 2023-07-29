#include "single.h"

int main(int argc, char *argv[]) {

    if (argc == 2) {
        int max_players;
        if (sscanf(argv[1], "%d", &max_players) != 1) {
            printf("Error: invalid argument '%s'\n", argv[1]);
            return 1;
        }

        // Declare an integer array of size 52 to store the deck of cards
        int deck[52];
        // Declare and initialize a variable to keep track of the array index
        int index = 0;

        // Loop through the numbers 2 to 13 four times
        int i;
        int j;
        for (i = 0; i < 4; i++) {
            for (j = 2; j <= 14; j++) {
                // Assign the current number to the current index of the deck array
                deck[index] = j;
                // Increment the index to move to the next element in the deck array
                index++;
            }
        }

        beggar(max_players, deck, 1);
    }
    else {
        printf("Usage: %s <max players> <number of trials>\n", argv[0]);
    }

    return 0;
}