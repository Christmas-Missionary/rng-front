#include "../src/external/custom-errors/custom_errors.h"
#include "../src/external/shishua/shishua.h"
#include "../src/external/stb/stb_image_write.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define SQUARE_LENGTH 64
#define BUFFER_SIZE (SQUARE_LENGTH * SQUARE_LENGTH * 3)

uint8_t byte_reduce(uint8_t x, uint8_t N) {
  CE_WARN(N > 1, "N needs to be at least 2 for a valid mod reduction!");
  return (uint8_t)(((uint32_t)x * N) >> 8U);
}

int main(void) {
  uint8_t buf[BUFFER_SIZE] = {0};
  prng_state state = {0};
  uint64_t shishua_seed[4] = {0x243f6a8885a308d3, 1, 0xa409382229f31d00, 1};
  prng_init(&state, shishua_seed);
  prng_gen(&state, buf, (size_t)BUFFER_SIZE);
  stbi_write_bmp("pic.bmp", SQUARE_LENGTH, SQUARE_LENGTH, 3, buf);
  for (int i = 0; i < 10; i++) {
    printf("%d ", +(byte_reduce(buf[i], 10)));
  }
  for (int j = 10; j < 15; j++) {
    printf("\n%d -> ", +buf[j]);
    for (int i = 2; i < 6; i++) {
      printf("(%d, %d) ", i, +(byte_reduce(buf[j], i)));
    }
  }
  printf("\n");
  return 0;
}
