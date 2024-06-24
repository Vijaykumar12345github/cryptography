#include <stdio.h>
#include <string.h>
#include <ctype.h>
int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;

    return x1;
}
void affineEncrypt(const char *plaintext, int a, int b, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            int p = tolower(plaintext[i]) - 'a';
            int c = (a * p + b) % 26;
            ciphertext[i] = c + 'a';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}
void affineDecrypt(const char *ciphertext, int a, int b, char *plaintext) {
    int a_inv = modInverse(a, 26);
    if (a_inv == 0) {
        printf("Decryption is not possible. 'a' has no modular inverse.\n");
        return;
    }

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            int c = tolower(ciphertext[i]) - 'a';
            int p = (a_inv * (c - b + 26)) % 26;
            plaintext[i] = p + 'a';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}
int isCoprimeWith26(int a) 
{
    int temp, m = 26;
    while (m != 0) {
        temp = m;
        m = a % m;
        a = temp;
    }
    return (a == 1);
}
int main() 
{
    char plaintext[256];
    char ciphertext[256];
    char decryptedtext[256];
    int a, b;
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    printf("Enter the value of a: ");
    scanf("%d", &a);
    printf("Enter the value of b: ");
    scanf("%d", &b);
    if (!isCoprimeWith26(a)) 
	{
        printf("The value of 'a' must be coprime with 26. Invalid 'a' value.\n");
        return 1;
    }
    affineEncrypt(plaintext, a, b, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);
    affineDecrypt(ciphertext, a, b, decryptedtext);
    printf("Decrypted text: %s\n", decryptedtext);
    return 0;
}