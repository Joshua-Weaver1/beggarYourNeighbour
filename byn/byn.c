#include "byn.h"

INFO gameInfo(int Nplayers, int games) {
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

    // Initializing struct
    INFO gameInfo = {100000, 0, 0}; // shortest initialized to largest possible int value

    int count = 0;
    srand(time(NULL));
    int longest = 0;
    int shortest = 10000;

    while (j < games) {
        riffle(deck, 52, sizeof(int), 7);
        int turns = beggar(Nplayers, deck, 0);
        count += turns;

        if (turns > longest) {
            longest = turns;
        }

        if (turns < shortest) {
            shortest = turns;
        }
        
        j++;
    }

    gameInfo.longest = longest;
    gameInfo.shortest = shortest;
    gameInfo.average = count / games;
    return gameInfo;
}

int main(int argc, char *argv[]) {
    int playerCount, attempts;

    if (argc != 3 || sscanf(argv[1], "%d", &playerCount) != 1 || sscanf(argv[2], "%d", &attempts) != 1) {
        printf("Usage: %s <max players> <number of trials>\n", argv[0]);
        return 1;
    }

    int i;
    for (i = 2; i <= playerCount; i++) {
        INFO info = gameInfo(i, attempts);

        // write output to terminal
        printf("Game with %d players:\n", i);
        printf("Shortest: %d turns\n", info.shortest);
        printf("Longest: %d turns\n", info.longest);
        printf("Average: %d turns\n\n", info.average);
    }

    return 0;
}
