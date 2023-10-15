#ifndef OENCIPHER_H_
#define OENCIPHER_H_

#include "stdint.h"

#define KEYSIZE sizeof(uint64_t) // 64 bit Key
#define ROUNDS 4

uint64_t encipher(uint64_t plaintext, uint32_t *keySchedule);
uint32_t roundFunction(uint32_t substring, uint32_t roundKey);
uint32_t *generate_roundkeys(uint64_t key);

#endif