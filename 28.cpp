#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>

uint64_t mod_exp(uint64_t a, uint64_t b, uint64_t q) {
    uint64_t result = 1;
    a = a % q;

    while (b > 0) {
        if (b & 1)
            result = (result * a) % q;
        
        b = b >> 1; 
        a = (a * a) % q; 
    }
    return result;
}

int main() {
    uint64_t q = 353; 
    uint64_t a = 3;   
    
    uint64_t x = 97;  

    uint64_t y = 233; 

    uint64_t A = mod_exp(a, x, q);

    uint64_t B = mod_exp(a, y, q);

    uint64_t secret_Alice = mod_exp(B, x, q); 
    uint64_t secret_Bob = mod_exp(A, y, q);  

    printf("Shared secret computed by Alice: %" PRIu64 "\n", secret_Alice);
    printf("Shared secret computed by Bob: %" PRIu64 "\n", secret_Bob);

    return 0;
}
