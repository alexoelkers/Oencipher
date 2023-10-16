#ifndef FEISTEL_H_
#define FEISTEL_H_

#include <stdint.h>
#include <stdio.h>

#define KEYSIZE sizeof(uint64_t)  // 64 bit Key
#define ENCRYPT 0
#define DECRYPT 1

int encrypt_decrypt(FILE *rawfile, uint64_t key, FILE *outfile, int mode);

#endif