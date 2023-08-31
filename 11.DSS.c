#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openssl/dsa.h>

int main() {
    DSA *dsa = DSA_generate_parameters(1024, NULL, 0, NULL, NULL, NULL, NULL);
    if (dsa == NULL) {
        perror("Error generating parameters");
        return 1;
    }

    if (!DSA_generate_key(dsa)) {
        perror("Error generating keys");
        DSA_free(dsa);
        return 1;
    }

    // Simulate message to be signed
    uint8_t message[] = "Hello, DSA!";

    // Sign the message
    uint8_t signature[DSA_size(dsa)];
    unsigned int signatureLen;
    if (!DSA_sign(0, message, sizeof(message) - 1, signature, &signatureLen, dsa)) {
        perror("Error signing message");
        DSA_free(dsa);
        return 1;
    }

    // Verify the signature
    if (DSA_verify(0, message, sizeof(message) - 1, signature, signatureLen, dsa)) {
        printf("Signature verification successful.\n");
    } else {
        printf("Signature verification failed.\n");
    }

    DSA_free(dsa);
    return 0;
}
