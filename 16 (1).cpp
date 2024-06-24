#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Define the expected frequencies of English letters (in percent)
const double english_freq[ALPHABET_SIZE] = {
    8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0, 0.2, 0.8, 4.0, 2.4,
    6.7, 7.5, 1.9, 0.1, 6.0, 6.3, 9.1, 2.8, 1.0, 2.4, 0.2, 2.0, 0.1
};

// Function to calculate the frequency of letters in the text
void calculate_frequency(char *text, int *frequency) {
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        if (isalpha(text[i])) {
            frequency[tolower(text[i]) - 'a']++;
        }
    }
}

// Function to calculate the chi-squared statistic
double chi_squared(int *observed, const double *expected, int size) {
    double chi_sq = 0;
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += observed[i];
    }
    for (int i = 0; i < size; i++) {
        double expected_count = total * expected[i] / 100.0;
        chi_sq += ((observed[i] - expected_count) * (observed[i] - expected_count)) / expected_count;
    }
    return chi_sq;
}

// Function to decrypt the ciphertext using a given key
void decrypt(char *ciphertext, const char *key) {
    int len = strlen(ciphertext);
    printf("Key: %s, Plaintext: ", key);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            if (islower(ciphertext[i])) {
                printf("%c", key[ciphertext[i] - 'a']);
            } else {
                printf("%c", toupper(key[tolower(ciphertext[i]) - 'a']));
            }
        } else {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
}

// Function to perform the letter frequency attack
void frequency_attack(char *ciphertext) {
    int frequency[ALPHABET_SIZE] = {0};
    calculate_frequency(ciphertext, frequency);

    char best_key[ALPHABET_SIZE + 1] = {0};
    double best_chi_sq = 1e30;

    // Try all possible shifts
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        char key[ALPHABET_SIZE + 1] = {0};
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            key[i] = 'a' + (i + shift) % ALPHABET_SIZE;
        }

        // Decrypt using the current key
        int decrypted_freq[ALPHABET_SIZE] = {0};
        int len = strlen(ciphertext);
        for (int i = 0; i < len; i++) {
            if (isalpha(ciphertext[i])) {
                decrypted_freq[tolower(ciphertext[i]) - 'a']++;
            }
        }

        // Calculate the chi-squared statistic
        double chi_sq = chi_squared(decrypted_freq, english_freq, ALPHABET_SIZE);
        if (chi_sq < best_chi_sq) {
            best_chi_sq = chi_sq;
            strcpy(best_key, key);
        }
    }

    // Decrypt using the best key
    decrypt(ciphertext, best_key);
}

int main() {
    char ciphertext[] = "Jxu qjwxkx, wkh iwk cuiiqwvxq kb cuxrwb.";

    printf("Ciphertext: %s\n", ciphertext);
    frequency_attack(ciphertext);

    return 0;
}