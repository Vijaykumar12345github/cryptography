#include <stdio.h>
#include <stdint.h>
#include <string.h>

void generate_subkey(uint8_t *subkey, int block_size, uint8_t Rb) {
    int i;
    uint8_t msb = subkey[0] & 0x80;
    
    for (i = 0; i < block_size / 8; i++) {
        subkey[i] <<= 1;
        if (i < block_size / 8 - 1 && (subkey[i + 1] & 0x80)) {
            subkey[i] |= 1;
        }
    }
    
    if (msb) {
        subkey[block_size / 8 - 1] ^= Rb;
    }
}

void print_subkey(const uint8_t *subkey, int block_size) {
    for (int i = 0; i < block_size / 8; i++) {
        printf("%02x", subkey[i]);
    }
    printf("\n");
}

int main() {
    int block_size_64 = 64;
    int block_size_128 = 128;
    uint8_t Rb_64 = 0x1B;
    uint8_t Rb_128 = 0x87;

    uint8_t L_64[8] = {0x00};  
    uint8_t L_128[16] = {0x00};  

    generate_subkey(L_64, block_size_64, Rb_64);
    printf("Subkey K1 (64-bit): ");
    print_subkey(L_64, block_size_64);

    uint8_t K1_64[8];
    memcpy(K1_64, L_64, 8);
    generate_subkey(K1_64, block_size_64, Rb_64);
    printf("Subkey K2 (64-bit): ");
    print_subkey(K1_64, block_size_64);

    generate_subkey(L_128, block_size_128, Rb_128);
    printf("Subkey K1 (128-bit): ");
    print_subkey(L_128, block_size_128);

    uint8_t K1_128[16];
    memcpy(K1_128, L_128, 16);
    generate_subkey(K1_128, block_size_128, Rb_128);
    printf("Subkey K2 (128-bit): ");
    print_subkey(K1_128, block_size_128);

    return 0;
}
