#include <stdio.h>
#include "stdlib.h"
#include "stdint.h"
#include "string.h"

#define KEYSIZE 8

void main()
{
    FILE *rawfile, *outfile;
    int returnStatus;
    uint64_t plaintext;

    rawfile = fopen("test.txt", "r");
    outfile = fopen("out.txt", "w");

    if (NULL == rawfile)
    {
        printf("The file coult not be opened.\n");
    }

    printf("writing to out.txt: \n");

    while (!feof(rawfile))
    {
        memset(&plaintext, 0, sizeof(plaintext));
        returnStatus = fread(&plaintext, 1, sizeof(plaintext), rawfile);
        fwrite(&plaintext, 1, sizeof(plaintext), outfile);
    }
    printf("writing complete\n");

    fclose(rawfile);
}