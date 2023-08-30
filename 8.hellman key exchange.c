#include <stdio.h>
#include <stdint.h>
#include <math.h>

// Prime modulus and base (publicly agreed values)
const uint64_t p = 23; // Prime modulus
const uint64_t g = 5;  // Base

// Function to calculate modular exponentiation
uint64_t modExp(uint64_t base, uint64_t exponent, uint64_t modulus) {
    uint64_t result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent /= 2;
    }
    return result;
}

int main() {
    // Alice's private key
    uint64_t alicePrivate = 6; // Chosen privately by Alice

    // Bob's private key
    uint64_t bobPrivate = 15; // Chosen privately by Bob

    // Calculate public keys for Alice and Bob
    uint64_t alicePublic = modExp(g, alicePrivate, p);
    uint64_t bobPublic = modExp(g, bobPrivate, p);

    // Calculate shared secret keys for Alice and Bob
    uint64_t aliceSharedSecret = modExp(bobPublic, alicePrivate, p);
    uint64_t bobSharedSecret = modExp(alicePublic, bobPrivate, p);

    // Both Alice and Bob should now have the same shared secret
    printf("Alice's shared secret: %llu\n", aliceSharedSecret);
    printf("Bob's shared secret: %llu\n", bobSharedSecret);

    return 0;
}
