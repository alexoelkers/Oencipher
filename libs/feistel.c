#include "feistel.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROUNDS 4
#define BLANK (int)' '

uint64_t encipher(uint64_t plaintext, const uint32_t *keySchedule);
uint64_t decipher(uint64_t ciphertext, const uint32_t *keySchedule);
uint32_t roundFunction(uint32_t substring, uint32_t roundKey);
uint32_t *generate_roundkeys(uint64_t key);

int encrypt_decrypt(FILE *rawfile, uint64_t key, FILE *outfile, int mode) {
    uint64_t rawtext, ciphertext;
    uint32_t *keySchedule;
    size_t returnStatus;
    uint64_t (*cipherFunction)(uint64_t, const uint32_t *);

    if (mode == ENCRYPT) {
        cipherFunction = &encipher;
    } else if (mode == DECRYPT) {
        cipherFunction = &decipher;
    } else {
        fprintf(stderr, "invalid mode.\n");
        return EXIT_FAILURE;
    }

    // generate key schedule
    keySchedule = generate_roundkeys(key);
    if (keySchedule == NULL) {
        fprintf(stderr, "Malloc failed.\n");
        return EXIT_FAILURE;
    }

    // encipher all plaintext
    while (!feof(rawfile)) {
        memset(&rawtext, BLANK, KEYSIZE);
        returnStatus = fread(&rawtext, 1, KEYSIZE, rawfile);
        if (returnStatus == 0) {
            break;
        }
        ciphertext = (*cipherFunction)(rawtext, keySchedule);
        fwrite(&ciphertext, 1, KEYSIZE, outfile);
    }

    free(keySchedule);
    return EXIT_SUCCESS;
}

uint64_t encipher(uint64_t plaintext, const uint32_t *keySchedule) {
    uint32_t leftString, rightString, nextLeftString, nextRightString;

    leftString = (plaintext >> (32)) & 0xFFFFFFFF;  // 32 bit shift
    rightString = plaintext & 0xFFFFFFFF;

    for (int i = 0; i < ROUNDS; i++) {
        nextLeftString = rightString;
        nextRightString = leftString ^ roundFunction(rightString, keySchedule[i]);
        leftString = nextLeftString;
        rightString = nextRightString;
    }

    return (uint64_t)rightString << 32 | leftString;  // recombine string halves
}

uint64_t decipher(uint64_t ciphertext, const uint32_t *keySchedule) {
    uint32_t leftString, rightString, nextLeftString, nextRightString;
    // reversed in decryption
    rightString = (ciphertext >> 32) & 0xFFFFFFFF;  // 32 bit shift
    leftString = ciphertext & 0xFFFFFFFF;

    for (int i = ROUNDS - 1; i >= 0; i--) {
        nextRightString = leftString;
        nextLeftString = rightString ^ roundFunction(leftString, keySchedule[i]);
        leftString = nextLeftString;
        rightString = nextRightString;
    }

    return (uint64_t)leftString << 32 | rightString;  // recombine string halves
}

uint32_t roundFunction(uint32_t substring, uint32_t roundKey) {
    substring = (substring << 5) | (substring >> 27);  // rotation
    substring ^= roundKey;                             // xor
    return substring;
}

uint32_t *generate_roundkeys(uint64_t key) {
    uint32_t *keySchedule;

    keySchedule = malloc(ROUNDS * sizeof(uint32_t));

    if (keySchedule == NULL) {
        return keySchedule;
    }

    keySchedule[0] = (key >> 32) & 0xFFFFFFFF;
    keySchedule[1] = key & 0xFFFFFFFF;
    keySchedule[2] = ((key >> 32) ^ key) & 0xFFFFFFFF;
    keySchedule[3] = ((key >> 32) | key) & 0xFFFFFFFF;

    return keySchedule;
}