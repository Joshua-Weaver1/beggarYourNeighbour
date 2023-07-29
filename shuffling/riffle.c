#include "riffle.h"

/**
 * Performs a single riffle shuffle on the array L.
 * @param L: The array to shuffle.
 * @param len: The length of the array.
 * @param size: The size of each element in the array.
 * @param work: A workspace array of the same size as L.
 * @return: The shuffled array.
*/
void riffle_once(void *L, int len, int size, void *work) {
    char *A = (char*)L;
    char *B = (char*)work;
    int i, j, k;
    
    // Divide the array L into two halves
    int half = len / 2;
    
    // Randomly shuffle the elements of L by copying them into workspace B
    srand(time(NULL));  // Seed the random number generator
    for (i = 0, j = 0, k = half; i < len; i++) {
        // Randomly choose whether to take the next element from A or B
        if (k == len || (j < half && rand() % 2 == 0)) {
            memcpy(B + i * size, A + j * size, size);
            j++;
        } else {
            memcpy(B + i * size, A + k * size, size);
            k++;
        }
    }
    
    // Copy the shuffled elements from B back into L
    memcpy(A, B, len * size);
}

/**
 *  Performs N riffle shuffles on the array L.
 * @param L: The array to shuffle.
 * @param len: The length of the array.
 * @param size: The size of each element in the array.
 * @param N: The number of shuffles to perform.
 * @return: The shuffled array.
*/
void riffle(void *L, int len, int size, int N) {
    void *work = malloc(len * size);
    if (work == NULL)
    {
        printf("Error: malloc failed");
        exit(1);
    }
    
    int i;
    
    // Perform N riffle shuffles
    for (i = 0; i < N; i++) {
        riffle_once(L, len, size, work);
    }
    
    free(work);
}

/**
 * Compares two integers.
 * @param a: The first integer.
 * @param b: The second integer.
 * @return: 1 if a > b, -1 if a < b, 0 if a == b.
*/
int cmp_int(void *a, void *b) {
    int x = *(int*)a;
    int y = *(int*)b;
    if (x > y) {
        return 1;
    } else if (x < y) {
        return -1;
    } else {
        return 0;
    }
}

/**
 * Compares two strings.
 * @param a: The first string.
 * @param b: The second string.
 * @return: 1 if a > b, -1 if a < b, 0 if a == b.
*/
int cmp_str(void *a, void *b) {
    char *x = *(char**)a;
    char *y = *(char**)b;
    return strcmp(x, y);
}

/**
 * Checks whether the array L is a valid shuffle of the original array.
 * @param L: The array to check.
 * @param len: The length of the array.
 * @param size: The size of each element in the array.
 * @param cmp: A pointer to a function that compares two elements of the array.
 * @return: 1 if L is a valid shuffle of the original array, 0 otherwise.
*/
int check_shuffle(void *L, int len, int size, int (*cmp)(void*, void*)) {
    void *orig = malloc(len * size);
    if (orig == NULL)
    {
        printf("Error: malloc failed");
        exit(1);
    }

    // Copy the original array    
    memcpy(orig, L, len * size);
    // Shuffle the array once
    riffle(L, len, size, 1);
    // Assume the shuffle is correct
    int res = 1;
    int i, j;
    for (i = 0; i < len; i++) {
        // Flag for whether the current element was found in the shuffled array
        int found = 0;
        for (j = 0; j < len; j++) {
            // Compare the i-th element of the original array with the j-th element of the shuffled array
            if (cmp(orig + i*size, L + j*size) == 0) {
                // Set the flag to true if the elements are equal
                found = 1;
                break;
            }
        }
        // If the current element was not found in the shuffled array, the shuffle is incorrect
        if (!found) {
            res = 0;
            break;
        }
    }
    riffle(L, len, size, 1);
    free(orig);
    return res;
}

/**
 * Calculates the quality of the shuffle.
 * @param numbers: The array to check.
 * @param len: The length of the array.
 * @return: The quality of the shuffle.
*/
float quality(int *numbers, int len) {
    int i, count = 0;
    for (i = 0; i < len - 1; i++) {
        if (numbers[i] < numbers[i+1]) {
            count++;
        }
    }
    return (float)count / (len - 1);
}

/**
 * Calculates the average quality of the shuffle.
 * @param N: The length of the array.
 * @param shuffles: The number of shuffles to perform.
 * @param trials: The number of trials to perform.
 * @return: The average quality of the shuffle.
*/
float average_quality(int N, int shuffles, int trials) {
    int *numbers = malloc(N * sizeof(int));
    if (numbers == NULL)
    {
        printf("Error: malloc failed");
        exit(1);
    }
    float sum = 0;
    int i, j;
    for (i = 0; i < trials; i++) {
        // Initialize the array with the integers 0 to N-1
        for (j = 0; j < N; j++) {
            numbers[j] = j;
        }
        // Shuffle the array shuffles times
        riffle(numbers, N, sizeof(int), shuffles);
        // Calculate the quality of the shuffle and add it to the sum
        sum += quality(numbers, N);
    }
    free(numbers);
    return sum / trials;
}
