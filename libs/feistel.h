#ifndef FEISTEL_H_
#define FEISTEL_H_

#include "stdint.h"
#include <stdio.h>

#define KEYSIZE sizeof(uint64_t) // 64 bit Key
#define ROUNDS 4

int encrypt_decrypt(FILE *rawfile, uint64_t key, FILE *outfile, int mode);

#endif