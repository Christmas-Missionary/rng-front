#include "../src/external/shishua/shishua.h"
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define ITERS 2000000000ULL

static void print_time(const clock_t difference, const char * rng_used, int bytes_generated_per_iter) {
  long double seconds = (((long double)difference) / CLOCKS_PER_SEC);
  long double micros = (double)(seconds * 1000000.0);
  printf("%s\n%Lf seconds\n%Lf microseconds per gen\n%Lf bytes per microsecond\n\n",
         rng_used,
         seconds,
         (micros / ITERS),
         (1 / (micros / ITERS)) * bytes_generated_per_iter);
}

#if SHISHUA_TARGET == SHISHUA_TARGET_AVX2
  #define TARGET_STR "AVX2 "
#elif SHISHUA_TARGET == SHISHUA_TARGET_SSE2
  #if defined(__SSSE3__) || defined(__AVX__)
    #define TARGET_STR "SSSE3 "
  #else
    #define TARGET_STR "SSE2 "
  #endif
#elif SHISHUA_TARGET == SHISHUA_TARGET_NEON
  #define TARGET_STR "NEON "
#else
  #define TARGET_STR "Portable "
#endif

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

  printf("Given %llu iterations...\n\n", ITERS);
  print_time(shi_diff, TARGET_STR "Shishua (128)", 128);

  return 0;
}
