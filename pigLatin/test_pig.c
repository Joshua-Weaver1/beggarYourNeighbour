#include "test_pig.h"

/**
 * Tests the pig() function using an array of words and expected values.
 * Will print the converted word if the test passes.
 * @return: 0 if all tests pass.
*/
int main() {
    // Define an array of test cases and expected results
    char* test_cases[] = {"happy", "duck", "glove", "evil", "eight", "yowler", "crystal"};
    char* expected[] = {"appyhay", "uckday", "oveglay", "evilway", "eightway", "owleryay", "ystalcray"};

    // Calculate the number of test cases
    int num_tests = sizeof(test_cases) / sizeof(char*);

    // Iterate through each test case and check the result
    int i;
    for (i = 0; i < num_tests; i++) {
        char* result = pig(test_cases[i]);
        // Compare the result to the expected value and print the appropriate message
        if (strcmp(result, expected[i]) == 0) {
            printf("%s => %s\n", test_cases[i], result);
        } else {
            printf("Test failed: %s => %s (expected %s)\n", test_cases[i], result, expected[i]);
        }
    }

    return 0;
}