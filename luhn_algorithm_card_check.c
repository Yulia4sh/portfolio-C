#include <stdio.h>
#include <string.h>

// 1. Implement a function that checks if a bank card number is valid using the Luhn algorithm.
// 2. Implement a function that restores one missing digit in a bank card number if the other digits and the position of the missing digit are known.

void checkCardNumber() {
    // This function checks if the entered card number is valid using the Luhn algorithm
    char n[20];
    printf("Enter your card number: ");
    scanf("%s", n);
    int len = strlen(n);
    int sum = 0;
    int s = 0;
    for (int i = len - 1; i >= 0; i--) {
        int d = n[i] - '0';
        // If the position is even from the right (second, fourth, etc.), double the digit
        if (s) {
            d = d * 2;
            if (d > 9) {
                d = d - 9; // If doubling the digit results in a number greater than 9, subtract 9
            }
        }
        sum += d;
        s = !s; // Alternate between doubling and not doubling digits
    }
    if (sum % 10 == 0) {
        printf("Valid card number\n");
    } else {
        printf("Invalid card number\n");
    }
}

void missingDigit() {
    // This function tries to find the missing digit in a card number using the Luhn algorithm
    char str[20];
    int pos;
    printf("Enter a string of 15 digits: ");
    scanf("%s", str);
    printf("Enter the position to add the number from 0 to 14: ");
    scanf("%d", &pos);

    // Iterate through all possible digits (0-9) to find the one that makes the card number valid
    for (int i = 0; i <= 9; i++) {
        char new_str[20]; // Create a new string with the potential correct digit
        int j = 0;
        // Copy the characters up to the missing digit's position
        for (j = 0; j < pos; j++) {
            new_str[j] = str[j];
        }
        new_str[j] = i + '0'; // Insert the potential digit at the missing position
        // Copy the remaining characters from the original string, shifting them to the right
        for (; j < strlen(str); j++) {
            new_str[j + 1] = str[j];
        }
        new_str[j + 1] = '\0'; // Ensure the string is properly terminated

        // Validate the new string using the Luhn algorithm
        int len = strlen(new_str);
        int sum = 0;
        int s = 0;
        for (int k = len - 1; k >= 0; k--) {
            int d = new_str[k] - '0';
            // If the position is even from the right (second, fourth, etc.), double the digit
            if (s) {
                d = d * 2;
                if (d > 9) {
                    d = d - 9; // If doubling the digit results in a number greater than 9, subtract 9
                }
            }
            sum += d;
            s = !s; // Alternate between doubling and not doubling digits
        }
        if (sum % 10 == 0) {
            printf("Oops... You forgot to enter a number %d\n", i);
            break; // Stop once the correct digit is found
        }
    }
}

int main() {
    checkCardNumber();   // Check if the entered card number is valid
    missingDigit();      // Restore a missing digit in a card number
    return 0;
}
