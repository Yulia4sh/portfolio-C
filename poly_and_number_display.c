/* 
    Program: poly_and_number_display.c
    Description:
    1. Implement polynomial division where each polynomial is represented as a one-dimensional array of coefficients. 
       The program should output two arrays: one for the quotient and one for the remainder.
    2. Display a given number using stars to visually represent each digit.
*/

#include <stdio.h>
#include <stdlib.h>

// Function to perform polynomial division
void poly_divide(int poly1[], int n1, int poly2[], int n2, int quotient[], int *nq, int remainder[], int *nr) {
    int i, j;
    int temp[n1];
    *nq = n1 - n2 + 1; // Calculate the length of the quotient array
    *nr = n2 - 1; // Calculate the length of the remainder array

    // Initialize temporary array with the coefficients of poly1
    for (i = 0; i < n1; i++) {
        temp[i] = poly1[i];
    }

    // Perform polynomial division
    for (i = 0; i < *nq; i++) {
        quotient[i] = temp[i] / poly2[0];
        for (j = 0; j < n2; j++) {
            temp[i + j] -= quotient[i] * poly2[j];
        }
    }

    // Copy the remainder
    for (i = 0; i < *nr; i++) {
        remainder[i] = temp[i + n2];
    }
}

// Function to print a polynomial in human-readable format
void print_polynomial(int poly[], int n) {
    int i;
    int degree = n - 1;

    printf("Polynomial: ");
    for (i = 0; i < n; i++) {
        if (poly[i] != 0) {
            if (i < n - 1) {
                if (poly[i] > 0) {
                    printf(" + ");
                } else {
                    printf(" - ");
                }
            }

            if (i == n - 1 || poly[i] != 1 && poly[i] != -1) {
                printf("%d", poly[i]);
            } else if (poly[i] == -1) {
                printf("-");
            }

            if (degree - i > 0) {
                printf("x");
                if (degree - i > 1) {
                    printf("^%d", degree - i);
                }
            }
        }
    }
    printf("\n");
}

// Function to display a number with stars
void display_number_with_stars(int number) {
    char *digits[10][7] = {
        {"  ***  ", " *   * ", "*     *", "*     *", "*     *", " *   * ", "  ***  "}, // 0
        {" *  ", "**   ", " *  ", " *  ", " *  ", " *  ", "*** "},         // 1
        {" *** ", "*   *", "   * ", "  *  ", " *   ", "*    ", "*****"},  // 2
        {" *** ", "*   *", "    *", "   * ", "    *", "*   *", " *** "},  // 3
        {"   *  ", "  **  ", " * *  ", "*  *  ", "*****", "   *  ", "   *  "}, // 4
        {"*****", "*    ", "*    ", " *** ", "    *", "*   *", " *** "},  // 5
        {" *** ", "*    ", "*    ", "**** ", "*   *", "*   *", " *** "},  // 6
        {"*****", "    *", "   * ", "  *  ", " *   ", "*    ", "*    "},  // 7
        {" *** ", "*   *", "*   *", " *** ", "*   *", "*   *", " *** "},  // 8
        {" ****", "*   *", "*   *", " ****", "    *", "    *", " *** "}   // 9
    };

    int digits_array[10];
    int count = 0;

    // Convert the number into its digits
    while (number > 0) {
        digits_array[count++] = number % 10;
        number /= 10;
    }

    // Reverse the digits array
    int reversed[10];
    for (int i = 0; i < count; i++) {
        reversed[i] = digits_array[count - i - 1];
    }

    // Print the number using stars
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < count; j++) {
            int digit = reversed[j];
            printf("%s\t", digits[digit][i]);
        }
        printf("\n");
    }
}

int main() {
    // Task 1: Polynomial Division
    printf("Task 1: Polynomial Division\n");
    int poly1[] = {2, 1, 3, -2, 2}; // Polynomial 2x^4 + x^3 + 3x^2 - 2x + 2
    int n1 = 5; // Length of poly1
    int poly2[] = {1, 2, 2};       // Polynomial x^2 + 2x + 2
    int n2 = 3; // Length of poly2
    int quotient[n1 - n2 + 1];
    int remainder[n2 - 1];
    int nq, nr;

    poly_divide(poly1, n1, poly2, n2, quotient, &nq, remainder, &nr);

    printf("Quotient: ");
    print_polynomial(quotient, nq);

    printf("Remainder: ");
    print_polynomial(remainder, nr);

    // Task 2: Display Number with Stars
    printf("Task 2: Display Number with Stars\n");
    int number;
    printf("Enter a number to see it displayed with stars:\n");
    scanf("%d", &number);

    display_number_with_stars(number);

    return 0;
}
