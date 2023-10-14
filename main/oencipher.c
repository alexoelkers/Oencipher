#include <stdio.h>
#include "stdlib.h"

#define KEYSIZE 64

void main()
{
    FILE* rawfile;
    char ch;

    rawfile = fopen("test.txt", "r");

    if (NULL == rawfile){
        printf("The file coult not be opened.\n");
    }

    printf("the contents of this file are: \n");

    while ((ch = fgetc(rawfile)) != EOF){
        printf("%c", ch);
    }
    printf("\n");

    fclose(rawfile);
}

char* encipher(const char* plaintext, // 64 bit block
               const char** keySchedule,         
               const char* (*roundFunctionPtr)(char* substring, char* subkey))
{
    char* leftString, rightString;
    char* roundKey;

    leftString = plaintext;
    rightString = plaintext + KEYSIZE / 2;

    for (int i = 0; ((roundKey = *keySchedule++) != '\0'); i++) {
            RightString = leftString
    }


}