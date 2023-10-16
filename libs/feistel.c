#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "feistel.h"

uint64_t encipher(uint64_t plaintext, uint32_t *keySchedule);
uint64_t decipher(uint64_t ciphertext, uint32_t *keySchedule);
uint32_t roundFunction(uint32_t substring, uint32_t roundKey);
uint32_t *generate_roundkeys(uint64_t key);

int encrypt_decrypt(FILE *rawfile, uint64_t key, FILE *outfile, int mode)
{
    uint64_t rawtext, ciphertext;
    uint32_t *keySchedule;
    size_t returnStatus;

    // generate key schedule
    keySchedule = generate_roundkeys(key);
    if (keySchedule == NULL)
    {
        fprintf(stderr, "Malloc failed.\n");
        return EXIT_FAILURE;
    }

    // encipher all plaintext
    while (!feof(rawfile))
    {
        memset(&rawtext, 0, KEYSIZE);
        returnStatus = fread(&rawtext, 1, KEYSIZE, rawfile);
        if (returnStatus == 0)
        {
            break;
        }

        if (mode == 0)
        {
            ciphertext = encipher(rawtext, keySchedule);
        }
        else if (mode == 1)
        {
            ciphertext = decipher(rawtext, keySchedule);
        }

        fwrite(&ciphertext, 1, KEYSIZE, outfile);
    }

    free(keySchedule);
    return EXIT_SUCCESS;
}

uint64_t encipher(uint64_t plaintext, uint32_t *keySchedule)
{
    uint32_t leftString, rightString;

    leftString = (plaintext >> (32)) & 0xFFFFFFFF; // 32 bit shift
    rightString = plaintext & 0xFFFFFFFF;

    int i = 0;
    while (i < ROUNDS)
    {
        leftString = rightString;
        rightString = leftString ^ roundFunction(rightString, keySchedule[i]);
        i++;
    }

    return (uint64_t)rightString << 32 | leftString; // recombine string halves
}

uint64_t decipher(uint64_t ciphertext, uint32_t *keySchedule)
{
    uint32_t leftString, rightString;

    rightString = (ciphertext >> 32) & 0xFFFFFFFF; // 32 bit shift
    leftString = ciphertext & 0xFFFFFFFF;

    int i = 1;
    while (i <= ROUNDS)
    {
        rightString = leftString;
        leftString = rightString ^ roundFunction(leftString, keySchedule[ROUNDS - i]);
        i++;
    }

    return (uint64_t)leftString << 32 | rightString; // recombine string halves
}

uint32_t roundFunction(uint32_t substring, uint32_t roundKey)
{
    substring = (substring << 5) | (substring << 27); // rotation
    substring ^= roundKey;                            // xor
    return substring;
}

uint32_t *generate_roundkeys(uint64_t key)
{
    uint32_t *keySchedule;

    keySchedule = malloc(ROUNDS * sizeof(uint32_t));

    if (keySchedule == NULL)
    {
        return keySchedule;
    }

    keySchedule[0] = (key >> 32) & 0xFFFFFFFF;
    keySchedule[1] = key & 0xFFFFFFFF;
    keySchedule[3] = ((key >> 32) ^ key) & 0xFFFFFFFF;
    keySchedule[3] = ((key >> 32) | key) & 0xFFFFFFFF;

    return keySchedule;
}