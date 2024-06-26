#include <stdio.h>
#include <math.h>

unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    unsigned long long e = 65537;  
    unsigned long long n = 999630013489;  
    
    unsigned long long ciphertexts[26];
    
    for (int m = 0; m < 26; m++) {
        ciphertexts[m] = mod_exp(m, e, n);
    }
    
    printf("Plaintext to Ciphertext mapping:\n");
    for (int m = 0; m < 26; m++) {
        printf("Plaintext: %d, Ciphertext: %llu\n", m, ciphertexts[m]);
    }
    
    unsigned long long intercepted_ciphertext = 123456789012;  
    
    for (int m = 0; m < 26; m++) {
        if (ciphertexts[m] == intercepted_ciphertext) {
            printf("Intercepted ciphertext %llu corresponds to plaintext %d\n", intercepted_ciphertext, m);
            break;
        }
    }
    
    return 0;
}
