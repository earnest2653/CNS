#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 10

// Function to perform matrix multiplication
void matrixMultiply(int key[MAX_SIZE][MAX_SIZE], int block[MAX_SIZE], int result[MAX_SIZE], int keySize) {
    for (int i = 0; i < keySize; i++) {
        result[i] = 0;
        for (int j = 0; j < keySize; j++) {
            result[i] += key[i][j] * block[j];
        }
        result[i] %= 26; // Modulo 26 to keep it within the range of alphabets
    }
}

// Function to calculate the determinant of a 2x2 matrix
int calculateDeterminant(int key[2][2]) {
    return (key[0][0] * key[1][1]) - (key[0][1] * key[1][0]);
}

// Function to find the modular multiplicative inverse
int findModularInverse(int det) {
    int inverse = -1;
    for (int i = 0; i < 26; i++) {
        if ((det * i) % 26 == 1) {
            inverse = i;
            break;
        }
    }
    return inverse;
}

int main() {
    int keySize;
    printf("Enter the size of the key matrix (2 or 3): ");
    scanf("%d", &keySize);

    if (keySize != 2 && keySize != 3) {
        printf("Invalid key size. Please enter 2 or 3.\n");
        return 1;
    }

    int key[MAX_SIZE][MAX_SIZE];
    printf("Enter the key matrix:\n");
    for (int i = 0; i < keySize; i++) {
        for (int j = 0; j < keySize; j++) {
            scanf("%d", &key[i][j]);
        }
    }

    // Calculate the determinant of the key matrix
    int determinant = calculateDeterminant(key);

    // Find the modular multiplicative inverse of the determinant
    int detInverse = findModularInverse(determinant);
    
    if (detInverse == -1) {
        printf("The modular multiplicative inverse does not exist.\n");
        return 1;
    }

    char plaintext[MAX_SIZE];
    printf("Enter the plaintext (uppercase letters only): ");
    scanf("%s", plaintext);

    int block[MAX_SIZE];
    int result[MAX_SIZE];

    int blockSize = keySize;
    int paddedSize = (int)ceil((float)strlen(plaintext) / blockSize) * blockSize;

    printf("Ciphertext: ");

    for (int i = 0; i < paddedSize; i += blockSize) {
        for (int j = 0; j < blockSize; j++) {
            if (i + j < strlen(plaintext))
                block[j] = plaintext[i + j] - 'A';
            else
                block[j] = 0; // Padding with 0 for incomplete blocks
        }

        matrixMultiply(key, block, result, keySize);

        for (int j = 0; j < blockSize; j++) {
            printf("%c", result[j] + 'A');
        }
    }

    printf("\n");

    return 0;
}
