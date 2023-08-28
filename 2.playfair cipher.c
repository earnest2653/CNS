#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5 // Size of the Playfair matrix

void prepareKey(char *key, char *keyTable) {
    int len = strlen(key);
    int index = 0;
    // Fill the keyTable with the unique characters from the key
    for (int i = 0; i < len; i++) {
        if (key[i] == 'j') // Replace 'j' with 'i'
            continue;
        int exists = 0;
        for (int j = 0; j < index; j++) {
            if (key[i] == keyTable[j]) {
                exists = 1;
                break;
            }
        }
        if (!exists)
            keyTable[index++] = key[i];
    }
    // Fill the rest of the keyTable with remaining alphabets
    for (char c = 'a'; c <= 'z'; c++) {
        if (c == 'j') // Skip 'j'
            continue;
        int exists = 0;
        for (int j = 0; j < index; j++) {
            if (c == keyTable[j]) {
                exists = 1;
                break;
            }
        }
        if (!exists)
            keyTable[index++] = c;
    }
}

void generatePlayfairMatrix(char *keyTable, char matrix[SIZE][SIZE]) {
    int index = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = keyTable[index++];
        }
    }
}

void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'j') // Replace 'j' with 'i'
        ch = 'i';
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void playfairEncrypt(char matrix[SIZE][SIZE], char *text) {
    int len = strlen(text);
    // Adjust the length of the text by adding 'x' if necessary
    if (len % 2 != 0)
        strcat(text, "x");

    for (int i = 0; i < len; i += 2) {
        int row1, col1, row2, col2;
        findPosition(matrix, text[i], &row1, &col1);
        findPosition(matrix, text[i+1], &row2, &col2);

        if (row1 == row2) {
            col1 = (col1 + 1) % SIZE;
            col2 = (col2 + 1) % SIZE;
        } else if (col1 == col2) {
            row1 = (row1 + 1) % SIZE;
            row2 = (row2 + 1) % SIZE;
        } else {
            int temp = col1;
            col1 = col2;
            col2 = temp;
        }

        printf("%c%c", matrix[row1][col1], matrix[row2][col2]);
    }
}

int main() {
    char key[25];
    printf("Enter the key: ");
    scanf("%s", key);

    char keyTable[25];
    char matrix[SIZE][SIZE];

    prepareKey(key, keyTable);
    generatePlayfairMatrix(keyTable, matrix);

    char text[100];
    printf("Enter the plaintext: ");
    scanf("%s", text);

    for (int i = 0; text[i]; i++) {
        text[i] = tolower(text[i]); // Convert input to lowercase
    }

    printf("Playfair Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nEncrypted Text: ");
    playfairEncrypt(matrix, text);
    printf("\n");

    return 0;
}
