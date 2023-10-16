#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libs/feistel.h"

int main(int argc, char **argv)  // program rawfile keyfile mode outfile
{
    FILE *rawfile, *outfile, *keyfile;
    size_t returnStatus;
    uint64_t key;

    // import the key
    keyfile = fopen(argv[2], "r");

    returnStatus = fread(&key, 1, KEYSIZE, keyfile);
    fclose(keyfile);
    if (returnStatus == 0) {
        fprintf(stderr, "unable to read key\n");
        return EXIT_FAILURE;
    }

    fprintf(stderr, "key is: %ld\n", key);

    rawfile = fopen(argv[1], "r");
    outfile = fopen(argv[4], "w");

    if (NULL == rawfile) {
        fprintf(stderr, "The input file could not be opened.\n");
        return EXIT_FAILURE;
    }

    if (NULL == outfile) {
        fprintf(stderr, "The output file could not be opened.\n");
        return EXIT_FAILURE;
    }

    // encryption
    if (strcmp(argv[3], "-e") == 0) {
        printf("encrypting\n");
        returnStatus = encrypt_decrypt(rawfile, key, outfile, ENCRYPT);

        if (returnStatus == EXIT_FAILURE) {
            fprintf(stderr, "encryption failed.\n");
            return EXIT_FAILURE;
        }
    } else if (strcmp(argv[3], "-d") == 0) {
        printf("decrypting\n");
        returnStatus = encrypt_decrypt(rawfile, key, outfile, DECRYPT);

        if (returnStatus == EXIT_FAILURE) {
            fprintf(stderr, "decryption failed.\n");
            return EXIT_FAILURE;
        }
    } else {
        printf("invalid argument: \"%s\"\n", argv[3]);
    }

    fclose(rawfile);
    fclose(outfile);

    return EXIT_SUCCESS;
}