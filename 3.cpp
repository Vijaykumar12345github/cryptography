#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
void generateKeyMatrix(char *key, char keyMatrix[SIZE][SIZE]) 
{
    int i, j, k;
    int flag[26] = {0};
    for(i = 0; i < strlen(key); ++i) 
	{
        if(key[i] != ' ') 
		{
            if(!flag[toupper(key[i]) - 'A']) 
			{
                flag[toupper(key[i]) - 'A'] = 1;
                keyMatrix[i / SIZE][i % SIZE] = toupper(key[i]);
            }
        }
    }
    k = strlen(key);
    for(i = 0; i < 26; ++i) {
        if(flag[i] == 0) {
            keyMatrix[k / SIZE][k % SIZE] = 'A' + i;
            flag[i] = 1;
            ++k;
        }
    }
}
void findPosition(char ch, char keyMatrix[SIZE][SIZE], int *row, int *col) 
{
    int i, j;
    for(i = 0; i < SIZE; ++i) 
	{
        for(j = 0; j < SIZE; ++j) 
		{
            if(keyMatrix[i][j] == ch) 
			{
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encrypt(char *plaintext, char keyMatrix[SIZE][SIZE]) 
{
    int i, j;
    int row1, col1, row2, col2;
    char cipher[100];
    for(i = 0; i < strlen(plaintext); i += 2) 
	{
        findPosition(toupper(plaintext[i]), keyMatrix, &row1, &col1);
        findPosition(toupper(plaintext[i + 1]), keyMatrix, &row2, &col2);
        if(row1 == row2) 
		{
            cipher[i] = keyMatrix[row1][(col1 + 1) % SIZE];
            cipher[i + 1] = keyMatrix[row2][(col2 + 1) % SIZE];
        }
        else if(col1 == col2) 
		{
            cipher[i] = keyMatrix[(row1 + 1) % SIZE][col1];
            cipher[i + 1] = keyMatrix[(row2 + 1) % SIZE][col2];
        }
        else 
		{
            cipher[i] = keyMatrix[row1][col2];
            cipher[i + 1] = keyMatrix[row2][col1];
        }
    }
    cipher[i] = '\0';
    printf("Encrypted message: %s\n", cipher);
}
int main() 
{
    char key[100];
    char plaintext[100];
    char keyMatrix[SIZE][SIZE];
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    generateKeyMatrix(key, keyMatrix);
    printf("Enter the plaintext (even number of characters, excluding spaces): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    encrypt(plaintext, keyMatrix);
    return 0;
}