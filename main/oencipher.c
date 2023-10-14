#include <stdio.h>
#include "string.h"
#include "stdlib.h"

#define KEYSIZE 64

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
    char ciphertext[KEYSIZE];
    char *leftString, *rightString;
    char *roundKey;

    strcpy(ciphertext, plaintext);

    leftString = plaintext;
    rightString = plaintext + KEYSIZE / 2;

    for (int i = 0; ((roundKey = *keySchedule++) != '\0'); i++)
    {
        leftString = rightString;
        rightString = stringXOR(leftString, roundFunction(rightString, roundKey));
    }
    return;
}

char *roundFunction(char *substring, // 32 bit block
                    char *roundKey)
{
    return;
}

char *stringXOR(char *a, char *b)
{
    char *output;
    char *cp = a;
    int len = 0;

    for (int i = 0; *cp++ != EOF; len++)
    {
    } // determine the length of the string

    return;
}