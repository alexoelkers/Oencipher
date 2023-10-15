#ifndef OENCIPHER_H_
#define OENCIPHER_H_

#define KEYSIZE 8 // 8 byte (64 bit) Key

char *encipher(const char *plaintext, const char **keySchedule);
char *roundFunction(char *substring, char *roundKey);
char *stringXOR(const char *a, const char *b, int length);

#endif