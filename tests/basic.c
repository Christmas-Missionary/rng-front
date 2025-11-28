// Copyright (c) 2025 Christmas_Missionary - BSD Zero Clause License

#include "../src/external/custom-errors/custom_errors.h"
#include "../src/external/seed-gen/seed_gen.h"
#include "../src/external/shishua/shishua.h"
#include "external/stb/stb_image_write.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define SQUARE_LENGTH 64
#ifdef __EMSCRIPTEN__
  #define BUFFER_SIZE 128
#else
  #define BUFFER_SIZE (SQUARE_LENGTH * SQUARE_LENGTH * 3)
#endif

static inline uint8_t byte_reduce(uint8_t val, uint8_t range) {
  CE_WARN(range > 1, "The range needs to be at least 2 for a valid mod reduction!");
  return (uint8_t)(((uint32_t)val * range) >> 8U);
}

static inline uint32_t reduce(uint32_t val, uint32_t range) {
  CE_WARN(range > 1, "The range needs to be at least 2 for a valid mod reduction!");
  return ((uint64_t)val * (uint64_t)range) >> 32U;
}

static inline uint32_t merge_four_bytes(const uint8_t * buf) {
  static_assert(sizeof(uint8_t) == 1, "God is not here!");
  static_assert(sizeof(uint32_t) == 4, "32-bit value is not 4 bytes!");
  return ((uint32_t)buf[3] << 24U) | ((uint32_t)buf[2] << 16U) | ((uint32_t)buf[1] << 8U) | (uint32_t)buf[0];
}

int main(void) {
  {
    const uint64_t ns_time = sg_get_time();
    if (ns_time) {
      printf("The amount of nanoseconds since the UNIX epoch is: %lld\n\n", (long long)ns_time);
    } else {
      printf("Can't get time!\n");
      return 2;
    }
  }

  uint8_t buf[BUFFER_SIZE] = {0};
  prng_state state = {0};
  uint64_t shishua_seed[4] = {0};
  if (sg_generate_seed(shishua_seed, sizeof(uint64_t) * 4) != SG_SUCCESS) {
    printf("Seed can't be generated!\n");
    return 1;
  }
  prng_init(&state, shishua_seed);
  prng_gen(&state, buf, 128);
  printf("Each byte with the range being 10:\n");
  for (uint8_t i = 0; i < 10; i++) {
    printf("%d ", +(byte_reduce(buf[i], 10)));
  }
  printf("\n\nEach byte with ranges 2, 3, 4, and 5:");
  for (uint8_t j = 10; j < 15; j++) {
    printf("\n%d -> ", +buf[j]);
    for (uint8_t i = 2; i < 6; i++) {
      printf("(%d, %d) ", i, +(byte_reduce(buf[j], i)));
    }
  }
  printf("\n\n4 bytes at a time, assuming little-endianness, with the range being 100'000:\n");
  for (uint8_t i = 15; i < 31; i += 4) {
    printf("%u ", reduce(merge_four_bytes(buf + i), 100000));
  }
  const uint64_t consistency_seed[4] = {0x243f6a8885a308d3, 1, 0xa409382229f31d00, 1};
  prng_init(&state, consistency_seed);
  prng_gen(&state, buf, (size_t)BUFFER_SIZE);
  printf("\n\nGiven the seed {0x243f6a8885a308d3, 1, 0xa409382229f31d00, 1}:\n");
  printf("Basic Consistency Test: Should be: {36, 109, 218, 224, 32, 169, 78, 35}\n");
  printf("{%d, %d, %d, %d, %d, %d, %d, %d}", +buf[0], +buf[1], +buf[2], +buf[3], +buf[4], +buf[5], +buf[6], +buf[7]);

#ifndef __EMSCRIPTEN__
  printf("\nBONUS: `consistency.bmp` should be the same as "
         "sample.bmp\n");
  stbi_write_bmp("consistency.bmp", SQUARE_LENGTH, SQUARE_LENGTH, 3, buf);
#endif
  return 0;
}
