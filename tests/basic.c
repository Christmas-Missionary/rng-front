#include "../external/custom-errors/custom_errors.h"
#include "../external/shishua/shishua.h"
#include "external/stb/stb_image_write.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define SQUARE_LENGTH 64
#define BUFFER_SIZE (SQUARE_LENGTH * SQUARE_LENGTH * 3)

uint8_t byte_reduce(uint8_t x, uint8_t N) {
  CE_WARN(N > 1, "N needs to be at least 2 for a valid mod reduction!");
  return (uint8_t)(((uint32_t)x * N) >> 8U);
}

uint32_t reduce(uint32_t x, uint32_t N) {
  CE_WARN(N > 1, "N needs to be at least 2 for a valid mod reduction!");
  return ((uint64_t)x * (uint64_t)N) >> 32;
}

static inline uint32_t merge_four_bytes(const uint8_t * buf) {
  static_assert(sizeof(uint8_t) == 1, "God is not here!");
  static_assert(sizeof(uint32_t) == 4, "32-bit value is not 4 bytes!");
  return ((uint32_t)buf[3] << 24) | ((uint32_t)buf[2] << 16) | ((uint32_t)buf[1] << 8) | (uint32_t)buf[0];
}

int main(void) {
  uint8_t buf[BUFFER_SIZE] = {0};
  prng_state state = {0};
  uint64_t shishua_seed[4] = {0x243f6a8885a308d3, 1, 0xa409382229f31d00, 1};
  prng_init(&state, shishua_seed);
  prng_gen(&state, buf, (size_t)BUFFER_SIZE);
  stbi_write_bmp("pic.bmp", SQUARE_LENGTH, SQUARE_LENGTH, 3, buf);
  printf("Each byte with the range being 10:\n");
  for (int i = 0; i < 10; i++) {
    printf("%d ", +(byte_reduce(buf[i], 10)));
  }
  printf("\n\nEach byte with ranges 2, 3, 4, and 5:");
  for (int j = 10; j < 15; j++) {
    printf("\n%d -> ", +buf[j]);
    for (int i = 2; i < 6; i++) {
      printf("(%d, %d) ", i, +(byte_reduce(buf[j], i)));
    }
  }
  printf("\n\n4 bytes at a time, assuming little-endianness, with the range being 100'000:\n");
  for (int i = 15; i < 31; i += 4) {
    printf("%d ", reduce(merge_four_bytes(buf + i), 100000));
  }
  printf("\n");
  return 0;
}
