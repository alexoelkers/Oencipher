#include <stdio.h>
#include "string.h"
#include "stdlib.h"

#define KEYSIZE 8 // 8 byte (64 bit) Key

void main()
{
    FILE *rawfile;
    char ch;

    rawfile = fopen("test.txt", "r");

    if (NULL == rawfile)
    {
        printf("The file coult not be opened.\n");
    }

    printf("the contents of this file are: \n");

    while ((ch = fgetc(rawfile)) != EOF)
    {
        printf("%c", ch);
    }
    printf("\n");

    fclose(rawfile);
}

char *encipher(const char *plaintext,   // 64 bit block
               const char **keySchedule // 4 keys
               )                        // encipher plaintext using keySchedule
{
    char *ciphertext;
    char *leftString, *rightString;
    char *roundKey;

    ciphertext = malloc(KEYSIZE * sizeof(char));
    strncpy(ciphertext, plaintext, KEYSIZE);

    leftString = ciphertext;
    rightString = ciphertext + KEYSIZE / 2;

    for (int i = 0; ((roundKey = *keySchedule++) != '\0'); i++)
    {
        leftString = rightString;
        rightString = stringXOR(leftString, roundFunction(rightString, roundKey), KEYSIZE / 2);
    }
    return;
}

char *roundFunction(char *substring, // 32 bit block
                    char *roundKey)
{
    return;
}

char *stringXOR(const char *a, const char *b, int length)
{
    char *output;
    int i = 0;

    output = malloc(length * sizeof(char));

    while (i < length)
    {
        *output++ = *a++ ^ *b++;
        i++;
    }

    return output - length;
}