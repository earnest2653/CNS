#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate greatest common divisor (GCD)
uint64_t gcd(uint64_t a, uint64_t b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// Function to calculate modular inverse using extended Euclidean algorithm
int64_t modInverse(uint64_t a, uint64_t m) {
    int64_t m0 = m, t, q;
    int64_t x0 = 0, x1 = 1;

    if (m == 1) {
        return 0;
    }

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) {
        x1 += m0;
    }

    return x1;
}

// Generate RSA keys
void generateRSAKeys(uint64_t p, uint64_t q, uint64_t *publicKey, uint64_t *privateKey, uint64_t *modulus) {
    uint64_t n = p * q;
    uint64_t phi = (p - 1) * (q - 1);

    // Choose public exponent (commonly 65537)
    uint64_t e = 65537;

    // Calculate private exponent
    uint64_t d = modInverse(e, phi);

    *publicKey = e;
    *privateKey = d;
    *modulus = n;
}

// RSA encryption
uint64_t rsaEncrypt(uint64_t plaintext, uint64_t publicKey, uint64_t modulus) {
    return (uint64_t)(fmod(pow(plaintext, publicKey), modulus));
}

// RSA decryption
uint64_t rsaDecrypt(uint64_t ciphertext, uint64_t privateKey, uint64_t modulus) {
    return (uint64_t)(fmod(pow(ciphertext, privateKey), modulus));
}

int main() {
    uint64_t p = 61;
    uint64_t q = 53;
    uint64_t publicKey, privateKey, modulus;

    generateRSAKeys(p, q, &publicKey, &privateKey, &modulus);

    uint64_t plaintext = 123; // Message to be encrypted
    uint64_t encrypted = rsaEncrypt(plaintext, publicKey, modulus);
    uint64_t decrypted = rsaDecrypt(encrypted, privateKey, modulus);

    printf("Original: %llu\n", plaintext);
    printf("Encrypted: %llu\n", encrypted);
    printf("Decrypted: %llu\n", decrypted);

    return 0;
}
