#include <stdio.h>
#include "string.h"
#include "stdlib.h"
#include "stdint.h"
#include "oencipher.h"

uint64_t encipher(uint64_t plaintext, uint32_t *keySchedule);
uint32_t roundFunction(uint32_t substring, uint32_t roundKey);
uint32_t *generate_roundkeys(uint64_t key);

int main(int argc, char **argv) // program rawfile keyfile mode outfile
{
    FILE *rawfile, *outfile, *keyfile;
    size_t returnStatus;
    uint64_t key;

    // import the key
    keyfile = fopen(argv[2], "r");
    // memset(&key, 0, KEYSIZE);
    returnStatus = fread(&key, 1, KEYSIZE, keyfile);
    fclose(keyfile);
    if (returnStatus == 0)
    {
        printf("unable to read key\n");
        return EXIT_FAILURE;
    }
    printf("key is: %ld\n", key);

    rawfile = fopen(argv[1], "r");
    outfile = fopen(argv[4], "w");

    if (NULL == rawfile)
    {
        printf("The input file could not be opened.\n");
        return EXIT_FAILURE;
    }

    if (NULL == outfile)
    {
        printf("The output file could not be opened.\n");
        return EXIT_FAILURE;
    }

    // encryption
    if (strcmp(argv[3], "-e") == 0)
    {
        returnStatus = encrypt_file(rawfile, key, outfile);
        if (returnStatus == 0)
        {
            printf("encryption failed.\n");
            return EXIT_FAILURE;
        }
    }

    fclose(rawfile);
    fclose(outfile);

    return EXIT_SUCCESS;
}

int encrypt_file(FILE *rawfile, uint64_t key, FILE *outfile)
{
    uint64_t key, plaintext, ciphertext;
    uint32_t *keySchedule;
    size_t returnStatus;

    // generate key schedule
    keySchedule = generate_roundkeys(key);

    // encipher all plaintext
    while (!feof(rawfile))
    {
        memset(&plaintext, 0, KEYSIZE);
        returnStatus = fread(&plaintext, 1, KEYSIZE, rawfile);
        if (returnStatus == 0)
        {
            break;
        }

        ciphertext = encipher(plaintext, keySchedule);

        fwrite(&ciphertext, 1, KEYSIZE, outfile);
    }

    free(keySchedule);
    return EXIT_SUCCESS;
}

uint64_t encipher(uint64_t plaintext, uint32_t *keySchedule)
{
    uint64_t ciphertext;
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

    keySchedule[0] = (key >> 32) & 0xFFFFFFFF;
    keySchedule[1] = key & 0xFFFFFFFF;
    keySchedule[3] = ((key >> 32) ^ key) & 0xFFFFFFFF;
    keySchedule[3] = ((key >> 32) | key) & 0xFFFFFFFF;

    return keySchedule;
}