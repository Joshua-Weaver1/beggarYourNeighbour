#include "piglatin.h"

/**
* Translates an input word or sentence to Pig Latin.
* @return: The translated input.
*/
int main() {
    // Declare a char array of size 1024 to store the input line
    char line[1024];
    // A loop that continues until the user enters an empty line
    while (1) {
    // Prompt the user to enter a line of English text
    printf("Enter a line of English: ");

    // Read the line of text from the user, up to a maximum of 1024 characters
    fgets(line, 1024, stdin);

    // If the length of the line is less than or equal to 1 (i.e. only the newline character), exit the loop
    if (strlen(line) <= 1) {
        break;
    }

    // Tokenize the line into individual words using space or newline as delimiters
    char* word = strtok(line, " \n");

    // Loop through all the words in the line
    while (word != NULL) {
        // Convert the word to pig latin using the pig() function and print it
        printf("%s ", pig(word));
        // Get the next word from the line
        word = strtok(NULL, " \n");
    }

    // Print a newline character to separate each line of input/output
    printf("\n");
    }

    // Return 0 to indicate successful program execution
    return 0;
}