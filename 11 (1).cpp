#include <stdio.h>
#include <math.h>

int main() {
    // Initialize the variable to store the sum of log2(i)
    double log2_factorial = 0.0;

    // Calculate log2(25!)
    for (int i = 1; i <= 25; i++) {
        log2_factorial += log2(i);
    }

    // Print the result
    printf("log2(25!) = %.2lf\n", log2_factorial);
    printf("Approximate power of 2: 2^%.2lf\n", log2_factorial);

    return 0;
}