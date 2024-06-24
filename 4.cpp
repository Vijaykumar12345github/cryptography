#include <stdio.h>
#include <string.h>
#include <ctype.h>
void encrypt(char plaintext[], char key[]) 
{
    int i, j;
    int key_len = strlen(key);
    int text_len = strlen(plaintext);
    char ciphertext[text_len];
    for (i = 0; i < text_len; i++) 
	{
        char current_char = plaintext[i];
        char current_key = key[i % key_len];
        int shift = tolower(current_key) - 'a'; 
        if (isalpha(current_char)) 
		{
            char base_char = islower(current_char) ? 'a' : 'A'; 
            ciphertext[i] = base_char + (current_char - base_char + shift) % 26;
        } 
		else 
		{
            ciphertext[i] = current_char; 
        }
    }
    
    printf("Encrypted Text: %s\n", ciphertext);
}
int main() 
{
    char plaintext[1000];
    char key[100];
    printf("Enter the plaintext to encrypt: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    printf("Enter the key (a word to use for encryption): ");
    scanf("%s", key);
    encrypt(plaintext, key);
    return 0;
}
