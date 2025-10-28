#include "../external/shishua/shishua.h"
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define ITERS 2000000000UL

static void print_time(const clock_t difference, const char * rng_used, int bytes_generated_per_iter) {
  long double millis = (((long double)difference) / CLOCKS_PER_SEC) * 1000.0L;
  printf("%s\n%Lf milliseconds\n%lu total clock cycles\n%f clock cycles per gen\n%f bytes per cycle\n\n",
         rng_used,
         millis,
         difference,
         ((double)difference / ITERS),
         (1 / ((double)difference / ITERS)) * bytes_generated_per_iter);
}

int main(void) {
  uint8_t shishua_buf[128] = {0};
  prng_state state;
  uint64_t shishua_seed[4] = {0x243f6a8885a308d3, 1, 0xa409382229f31d00, 1};
  prng_init(&state, shishua_seed);

  clock_t start = clock();
  for (uint64_t i = 0; i < ITERS; i++) {
    prng_gen(&state, shishua_buf, sizeof(shishua_buf));
  }
  clock_t shi_diff = clock() - start;
  printf("%hhu\n", shishua_buf[127]);

  printf("Given %lu iterations...\n\n", ITERS);
  print_time(shi_diff, "Shishua (128)", 128);

  return 0;
}
