#include "beggar.h"

/**
 * Displays a games information with a given number of players.
 * @param numPlayers: The number of players in the game.
 * @return: The game information.
 */
void displayGameOutput(Queue** players, Stack* cardPile, int numPlayers, int currentTurn, int nextPlayerIndex, int winnerIndex) {

    printf("Turn %d:\n", currentTurn);
    printf("Current Pile:");
    showStack(cardPile);
    printf("\n");

    int playerDeck;
    for (playerDeck = 0; playerDeck < numPlayers; playerDeck++) {
        if (playerDeck == nextPlayerIndex) {
            printf("* Player %d: ", playerDeck);
        } else {
            printf("  Player %d: ", playerDeck);
        }
        printQueue(players[playerDeck]);
        printf("\n");
    }


    if (10 >= getHeadOfStack(cardPile)) {

        printf("Player %d plays %d\n", nextPlayerIndex, getFrontOfQueue(players[nextPlayerIndex]));

        if (getQueueSize(players[nextPlayerIndex]) == 1) {
            printf("Player %d has no more cards!\n", nextPlayerIndex);
        }
    } else {
        int playedSpecialCard = 0;
        int penaltyCount = getHeadOfStack(cardPile) - 10;
        int c = getFrontOfQueue(players[nextPlayerIndex]);
        int i;
        for (i = 0; i < penaltyCount; i++) {
            printf("Player %d playing: %d\n", nextPlayerIndex, c);

            if (i == players[nextPlayerIndex]->size - 1) {
                printf("Player %d out of cards!\n", nextPlayerIndex);
                break;
            }

            if (!c <= 10) {
                printf("User has also played a special card!\n");
                playedSpecialCard = 1;
                break;
            }

        }

        if (playedSpecialCard == 0) {
            printf("Player %d wins the pile!\n", winnerIndex);
        }
    }

    printf("\n");
}

/**
 * Checks if the queue is empty.
 * @param target: The queue to check.
 * @return: 0 if the queue is empty, 1 otherwise.
*/
int checkQueueSize(Queue* target){
    if (getQueueSize(target)==0){
        return 0;
    }
    else{
        return 1;
    }
}

/**
 * Takes a turn for a player.
 * @param player: The player to take a turn.
 * @param pile: The pile of cards.
 * @return: The cards the player won.
*/
int* take_turn(Queue* player,Stack* pile){
    if (checkQueueSize(player) == 0){
        return NULL;
    } else {
        int topOfDeck = getFrontOfQueue(player);
        removeFromQueue(player);

        if (pile->size==0){
            pushStack(pile, topOfDeck);
            int* reward = malloc(sizeof(int));
            reward[0]=0;
            return reward;
        }

        if (getHeadOfStack(pile)<11){
            pushStack(pile, topOfDeck);
            int* reward = malloc(sizeof(int));
            reward[0]=0;
            return reward;
        }

        else{
            int penCount = getHeadOfStack(pile)-10;
            int i;
            for (i = 0; i < penCount; i++){
                pushStack(pile, topOfDeck);

                if(topOfDeck>10){
                    int* reward = malloc(sizeof(int));
                    reward[0]=0;
                    return reward;
                }
                if(getQueueSize(player)==0){
                    break;
                }
                if(i==penCount-1){
                    break;
                }
                topOfDeck = getFrontOfQueue(player);
                removeFromQueue(player);

            }
            int pileSize = getStackSize(pile);
            int* reward = malloc(sizeof(int)*pileSize+1);

            reward[pileSize]=0;
            for (i=pileSize-1;i>-1;i--){
                reward[i]=popStack(pile);
            }
            return reward;
        }
    }
}

/**
 * Checks if the game is finished.
 * @param players: The players in the game.
 * @param Nplayers: The number of players in the game.
 * @return: 1 if the game is finished, 0 otherwise.
*/
int finished(Queue** players, int Nplayers) {
    int i, j;
    for (i = 0; i < Nplayers; i++) {
        if (players[i]->capacity == players[i]->size) {
            for (j = 0; j < Nplayers; j++) {
                if (j != i && players[j]->size > 0) {
                    return 0;
                }
            }
            return 1;
        }
    }
    return 0;
}


/**
 * Plays a game of beggar my neighbour.
 * @param Nplayers: The number of players in the game.
 * @param deck: The deck of cards.
 * @param talkative: Whether the game should be talkative or not.
 * @return: The winner of the game.
*/
int beggar(int Nplayers, int *deck, int talkative){

    // shuffle the deck of cards
    srand(time(NULL));
    riffle(deck,52,sizeof(int),7);
    
    // create a queue for each player and deal the cards to the players
    Queue* players[Nplayers];
    int i;
    int j;

    for (i = 0; i < Nplayers; i++) {
        players[i] = createQueue(52);

        // deal cards to each player
        for (j = i; j < 52; j += Nplayers) {
            addToQueue(players[i], deck[51 - j]);
        }
    }

    // create a stack for the game's central pile
    Stack* pile = createStack(52);

    // set up initial game state
    int currentPlayer = 0;
    int roundNumber = 0;
    int gameOver = 0;
    
    // loop until the game is over
    while(!gameOver){
        roundNumber++;
        
        // loop through each player and take turns
        for(i = 0; i < Nplayers; i++){
            currentPlayer = (i + roundNumber - 1) % Nplayers;
            
            // skip players who are out of the game
            if(players[currentPlayer]->size == 0){
                continue;
            }
            
            // display game output if talkative flag is set
            if(talkative != 0){
                displayGameOutput(players, pile, Nplayers, roundNumber, currentPlayer, i);
            }
            
            // take turn and get rewards
            int* reward = take_turn(players[currentPlayer], pile);
            
            // add rewards to current player's queue
            int j = 0;
            while(reward[j] != 0){
                addToQueue(players[currentPlayer], reward[j]);
                j++;
            }
            
            // free the memory used by the reward array
            free(reward);
            
            // check if game is over
            if(finished(players, Nplayers) == 1){
                gameOver = 1;
                break;
            }
        }
    }

    // display message indicating the winner if talkative flag is set
    if(talkative!=0){
        printf("\nWe have a winner!\n");
    }

    // free the memory used by the pile and player queues
    wipeStack(pile);
    free(pile);

    for(i = 0; i < Nplayers; i++){
        wipeQueue(players[i]);
        free(players[i]);
    }

    // return the number of rounds played
    return roundNumber;
}