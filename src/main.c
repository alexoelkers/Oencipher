#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "../libs/feistel.h"

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
        returnStatus = encrypt_decrypt(rawfile, key, outfile, 0);
        if (returnStatus == 1)
        {
            printf("encryption failed.\n");
            return EXIT_FAILURE;
        }
    }
    else if (strcmp(argv[3], "-d") == 0)
    {
        returnStatus = encrypt_decrypt(rawfile, key, outfile, 1);
        if (returnStatus == 1)
        {
            printf("decryption failed.\n");
            return EXIT_FAILURE;
        }
    }

    fclose(rawfile);
    fclose(outfile);

    return EXIT_SUCCESS;
}