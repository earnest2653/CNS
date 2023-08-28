#include <stdio.h>
#include <string.h>

// Function to encrypt the given text using Caesar cipher
char* encryptCaesarCipher(char* text, int shift) {
    int length = strlen(text);
    for (int i = 0; i < length; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (text[i] - 'A' + shift) % 26 + 'A';
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (text[i] - 'a' + shift) % 26 + 'a';
        }
    }
    return text;
}

int main() {
    char text[100];
    int shift;

    printf("Enter the text to encrypt: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter the shift value: ");
    scanf("%d", &shift);

    // Remove the newline character from fgets
    text[strcspn(text, "\n")] = '\0';

    char* encryptedText = encryptCaesarCipher(text, shift);

    printf("Encrypted text: %s\n", encryptedText);

    return 0;
}
