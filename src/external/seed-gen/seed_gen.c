/*
Copyright (c) 2025 Christmas_Missionary - BSD Zero Clause License
*/

#include "seed_gen.h"
#include "../custom-errors/custom_errors.h"

#ifdef _WIN32

  #include <Windows.h>
  #include <bcrypt.h>
/*
# bcrypt.lib must be linked explicitly. I prefer CMake.
if(WIN32)
  target_link_libraries(<PROJECT_NAME> bcrypt.lib)
endif()
*/

// For Windows 10 and above
sg_error sg_generate_seed(void * dst, size_t size) {
  CE_ERROR(dst != NULL, "Destination ptr is NULL!");
  CE_ERROR(size != 0, "Destination size is 0!");
  if (dst == NULL || size == 0) {
    return SG_INVALID_PARAMETERS;
  }
  NTSTATUS status = BCryptGenRandom(BCRYPT_RNG_ALG_HANDLE, dst, size, 0);
  if (!BCRYPT_SUCCESS(status)) {
    CE_FATAL(0, "Not all bytes were generated upon request!");
    return SG_ERROR_DURING_GEN;
  }
  return SG_SUCCESS;
}

#elif defined(unix) || defined(__unix) || defined(__unix__) || (defined(__APPLE__) && defined(__MACH__)) || \
  defined(BSD) || defined(__ANDROID__)
// Emscripten defines __unix__, __unix, and unix
  #include <stdio.h>

sg_error sg_generate_seed(void * dst, size_t size) {
  CE_ERROR(dst != NULL, "Destination ptr is NULL!");
  CE_ERROR(size != 0, "Destination size is 0!");
  if (dst == NULL || size == 0) {
    return SG_INVALID_PARAMETERS;
  }
  FILE * file = fopen("/dev/urandom", "rb");
  if (file == NULL) {
    CE_FATAL(0, "/dev/urandom, your computer's built-in RNG, couldn't be opened for seeding!");
    return SG_CANT_OPEN;
  }
  unsigned long chrs_read = fread(dst, 1, size, file);
  if (chrs_read != size) {
    (void)fclose(file);
    CE_FATAL(0, "Not all bytes for a seed were generated upon request!");
    return SG_ERROR_DURING_GEN;
  }
  if (fclose(file)) {
    CE_FATAL(0, "/dev/urandom, your computer's built-in RNG, couldn't be closed!");
    return SG_CANT_CLOSE;
  }
  return SG_SUCCESS;
}

#else
sg_error sg_generate_seed(void * dst, size_t size) {
  return SG_CANT_OPEN;
}
#endif

#include <time.h>

uint64_t sg_get_time(void) {
  struct timespec tsp;
  if (timespec_get(&tsp, TIME_UTC) == 0) {
    CE_FATAL(0, "Can't get the timespec on this computer!");
    return 0;
  }
  return (uint64_t)tsp.tv_sec * 1000000000 + tsp.tv_nsec;
}
