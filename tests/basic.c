#include "../src/external/shishua/shishua.h"
#include "../src/external/stb/stb_image_write.h"
#include <stdint.h>
#include <stdio.h>

#define SQUARE_LENGTH 64
#define BUFFER_SIZE (SQUARE_LENGTH * SQUARE_LENGTH * 3)

int main(void) {
  uint8_t buf[BUFFER_SIZE] = {0};
  prng_state state = {0};
  uint64_t shishua_seed[4] = {0x243f6a8885a308d3, 1, 0xa409382229f31d00, 1};
  prng_init(&state, shishua_seed);
  prng_gen(&state, buf, (size_t)BUFFER_SIZE);
  stbi_write_bmp("pic.bmp", SQUARE_LENGTH, SQUARE_LENGTH, 3, buf);
  return 0;
}
