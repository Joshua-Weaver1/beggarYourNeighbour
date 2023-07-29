#include "pig.h"

/**
* Translates an input word to Pig Latin.
* If the word starts with a vowel or 'y' as a consonant, add "way" to the end of the word.
* If the word starts with a consonant or 'y' as a vowel, move all the consonants before the first vowel or 'y' to the end of the word and add "ay".
* @param word: The word to be translated.
* @return: The translated word.
*/
char* pig(char* word) {
    // Get the length of the word and allocate memory for the Pig Latin version
    int len = strlen(word);
    char* result = (char*)malloc(sizeof(char) * (len + 3));

    // Check if memory allocation was successful
    if (result == NULL)
    {
        printf("Error allocating memory\n");
        exit(1);
    }

    // Initialize a counter variable
    int i = 0;

    // Check if the word starts with a vowel or 'y' as a consonant
    if (tolower(word[0]) == 'a' || tolower(word[0]) == 'e' || tolower(word[0]) == 'i'
        || tolower(word[0]) == 'o' || tolower(word[0]) == 'u' || (tolower(word[0]) == 'y' && len > 1 && tolower(word[1]) != 'a' && tolower(word[1]) != 'e' && tolower(word[1]) != 'i' && tolower(word[1]) != 'o' && tolower(word[1]) != 'u')) {
    
    // If the word starts with a vowel or 'y' as a consonant, just add "way"
    strcpy(result, word);
    strcat(result, "way");
    } else {
    // Find the position of the first vowel or 'y' as a vowel
    while (i < len && tolower(word[i]) != 'a' && tolower(word[i]) != 'e' &&
            tolower(word[i]) != 'i' && tolower(word[i]) != 'o' && tolower(word[i]) != 'u' && !(tolower(word[i]) == 'y' && i > 0 && tolower(word[i-1]) != 'a' && tolower(word[i-1]) != 'e' && tolower(word[i-1]) != 'i' && tolower(word[i-1]) != 'o' && tolower(word[i-1]) != 'u')) {
        i++;
    }

    // Move the consonants to the end of the word and add "ay"
    strcpy(result, word + i);
    strncat(result, word, i);
    strcat(result, "ay");
}

// Return the Pig Latin version of the word
return result;

}
