#include <stdio.h>
#include <string.h>

void encrypt(char plaintext[], char key[], char ciphertext[]);
void decrypt(char ciphertext[], char key[], char decryptedtext[]);
void createDecryptionKey(char key[], char decryptionKey[]);

int main() {
    char plaintext[100], ciphertext[100], decryptedtext[100];
    char key[26] = "DANGER"; 
    char decryptionKey[26];

    createDecryptionKey(key, decryptionKey);

    printf("Enter plaintext: ");
    gets(plaintext);

    encrypt(plaintext, key, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    decrypt(ciphertext, decryptionKey, decryptedtext);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

void encrypt(char plaintext[], char key[], char ciphertext[]) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = key[plaintext[i] - 'A'];
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = key[plaintext[i] - 'a'] + ('a' - 'A');
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
}

void decrypt(char ciphertext[], char key[], char decryptedtext[]) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            decryptedtext[i] = key[ciphertext[i] - 'A'];
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            decryptedtext[i] = key[ciphertext[i] - 'a'] + ('a' - 'A');
        } else {
            decryptedtext[i] = ciphertext[i];
        }
    }
    decryptedtext[i] = '\0';
}

void createDecryptionKey(char key[], char decryptionKey[]) {
    int i;
    for (i = 0; i < 26; i++) {
        decryptionKey[key[i] - 'A'] = 'A' + i;
    }
}