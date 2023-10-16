#ifndef OENCIPHER_H_
#define OENCIPHER_H_

#include "stdint.h"

#define KEYSIZE sizeof(uint64_t) // 64 bit Key
#define ROUNDS 4

int encrypt_file(FILE *rawfile, uint64_t key, FILE *outfile);

#endif