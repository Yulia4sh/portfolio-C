/* 
    Program: triangle_prime_polygon.c
    Description:
    1. Determine the type of a triangle based on the lengths of its sides.
       - If the triangle is a right-angled, obtuse, isosceles, or scalene.
       - Also check if the sides cannot form a triangle.
    2. Perform operations on natural numbers:
       - Input a natural number n.
       - Check if n is prime.
       - Compute the sum and product of all prime numbers less than n.
    3. Calculate the area of a convex polygon:
       - Input the number of sides and the coordinates of the vertices.
       - Ensure the polygon is convex.
       - Calculate the area of the polygon using triangulation.
*/

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Function prototypes for Task 1
void type_of_triangle(float x, float y, float z);

// Function prototypes for Task 2
int input_number();
bool is_prime(int x);
int sum_primes(int x);
int product_primes(int x);

// Function prototypes for Task 3
double input_x();
double input_y();
double distance(double x1, double y1, double x2, double y2);
double triangle_area(double a, double b, double c);
int is_convex(double x[], int n);
double calculate_polygon_area();

// Function to determine the type of a triangle based on side lengths
void type_of_triangle(float x, float y, float z) {
    if (x + y > z && y + z > x && z + x > y) {
        float cos_a = ((y * y) + (z * z) - (x * x)) / (2 * y * z);
        float cos_b = ((x * x) + (z * z) - (y * y)) / (2 * x * z);
        float cos_c = ((x * x) + (y * y) - (z * z)) / (2 * x * y);
        float deg_a = acos(cos_a) * 180 / M_PI;
        float deg_b = acos(cos_b) * 180 / M_PI;
        float deg_c = acos(cos_c) * 180 / M_PI;
        if (fabs(deg_a - 90) < 1e-6 || fabs(deg_b - 90) < 1e-6 || fabs(deg_c - 90) < 1e-6) {
            printf("Type of triangle: right-angled\n");
        } else if (cos_a < 0 || cos_b < 0 || cos_c < 0) {
            printf("Type of triangle: obtuse\n");
        } else if (x == y || x == z || y == z) {
            printf("Type of triangle: isosceles\n");
        } else {
            printf("Type of triangle: scalene\n");
        }
    } else {
        printf("These sides cannot form a triangle\n");
    }
}

// Function to input a natural number
int input_number() {
    int n;
    printf("Enter a number: \n");
    scanf("%d", &n);
    while (n < 1) {
        printf("The entered number is incorrect, enter again: \n");
        scanf("%d", &n);
    }
    return n;
}

// Function to check if a number is prime
bool is_prime(int x) {
    if (x < 2) return false;
    if (x == 2 || x == 3) return true;
    if (x % 2 == 0) return false;
    for (int i = 3; i <= (int) sqrt(x); i += 2) {
        if (x % i == 0) return false;
    }
    return true;
}

// Function to calculate the sum of all prime numbers less than n
int sum_primes(int x) {
    int sum = 0;
    for (int i = 2; i < x; i++) {
        if (is_prime(i)) {
            sum += i;
        }
    }
    return sum;
}

// Function to calculate the product of all prime numbers less than n
int product_primes(int x) {
    int product = 1;
    bool has_prime = false;
    for (int i = 2; i < x; i++) {
        if (is_prime(i)) {
            product *= i;
            has_prime = true;
        }
    }
    return has_prime ? product : 0;
}

// Function to input x coordinate
double input_x() {
    double x;
    printf("Enter x: ");
    scanf("%lf", &x);
    return x;
}

// Function to input y coordinate
double input_y() {
    double y;
    printf("Enter y: ");
    scanf("%lf", &y);
    return y;
}

// Function to calculate the distance between two points
double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Function to calculate the area of a triangle given its sides
double triangle_area(double a, double b, double c) {
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

// Function to check if a polygon is convex
int is_convex(double x[], int n) {
    double v1x, v1y, v2x, v2y, z, sign;
    for (int i = 0; i < n * 2; i += 2) {
        v1x = x[(i + 2) % (n * 2)] - x[i];
        v1y = x[(i + 3) % (n * 2)] - x[i + 1];
        v2x = x[(i + 4) % (n * 2)] - x[(i + 2) % (n * 2)];
        v2y = x[(i + 5) % (n * 2)] - x[(i + 3) % (n * 2)];
        z = v1x * v2y - v1y * v2x;
        if (i == 0) {
            sign = z > 0 ? 1 : -1;
        } else if (z != 0 && sign * z < 0) {
            printf("The polygon is not convex. Please enter the coordinates of another point.\n");
            return 0;
        }
    }
    return 1;
}

// Function to calculate the area of a convex polygon
double calculate_polygon_area() {
    int n;
    printf("Enter the number of sides of the polygon:\n");
    scanf("%d", &n);
    double coor[n * 2], sides[n];
    for (int i = 0; i < n * 2; i += 2) {
        coor[i] = input_x();
        coor[i + 1] = input_y();
    }
    while (is_convex(coor, n) == 0) {
        for (int i = 0; i < n * 2; i += 2) {
            coor[i] = input_x();
            coor[i + 1] = input_y();
        }
    }
    for (int i = 0; i < n * 2; i += 2) {
        if (i + 3 <= (n * 2) - 1) {
            sides[i / 2] = distance(coor[i], coor[i + 1], coor[(i + 2) % (n * 2)], coor[(i + 3) % (n * 2)]);
        } else {
            sides[i / 2] = distance(coor[i], coor[i + 1], coor[0], coor[1]);
        }
    }
    double x_center = 0, y_center = 0;
    for (int i = 0; i < n * 2; i += 2) {
        x_center += coor[i];
        y_center += coor[i + 1];
    }
    x_center /= n;
    y_center /= n;
    double r[n];
    for (int i = 0; i < n * 2; i += 2) {
        r[i / 2] = distance(coor[i], coor[i + 1], x_center, y_center);
    }
    double area = 0;
    for (int i = 0; i < n; i++) {
        area += triangle_area(sides[i], r[i], r[(i + 1) % n]);
    }
    return area;
}

// Main function to run all tasks
int main() {
    // Task 1: Triangle Type
    float a, b, c;
    printf("Task 1: Determine the type of a triangle\n");
    printf("Please enter the sides of the triangle:\n");
    scanf("%f", &a);
    scanf("%f", &b);
    scanf("%f", &c);
    type_of_triangle(a, b, c);

    // Task 2: Prime Number Operations
    int n = input_number();
    printf("Task 2: Operations on Prime Numbers\n");
    printf("The sum of all prime numbers less than %d: \n", n);
    printf("%d\n", sum_primes(n));
    printf("The product of these numbers: \n");
    printf("%d\n", product_primes(n));

    // Task 3: Polygon Area Calculation
    printf("Task 3: Calculate the area of a convex polygon\n");
    printf("The area of the polygon is %.2lf\n", calculate_polygon_area());

    return 0;
}
