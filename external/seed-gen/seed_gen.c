/*
Copyright (c) 2025 Christmas_Missionary - BSD Zero Clause License
*/

#include "seed_gen.h"

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
  if (dst == NULL || size == 0) {
    return SG_INVALID_PARAMETERS;
  }
  // Make this one line?
  NTSTATUS status = BCryptGenRandom(BCRYPT_RNG_ALG_HANDLE, dst, size, 0);
  if (!BCRYPT_SUCCESS(status)) {
    return SG_ERROR_DURING_GEN;
  }
  return SG_SUCCESS;
}

#elif defined(unix) || defined(__unix) || defined(__unix__) || (defined(__APPLE__) && defined(__MACH__)) || \
  defined(BSD) || defined(__ANDROID__)
// Emscripten defines __unix__, __unix, and unix
  #include <stdio.h>

sg_error sg_generate_seed(void * dst, size_t size) {
  if (dst == NULL || size == 0) {
    return SG_INVALID_PARAMETERS;
  }
  FILE * file = fopen("/dev/urandom", "rb");
  if (file == NULL) {
    return SG_CANT_OPEN;
  }
  unsigned long chrs_read = fread(dst, 1, size, file);
  if (chrs_read != size) {
    (void)fclose(file);
    return SG_ERROR_DURING_GEN;
  }
  if (fclose(file)) {
    return SG_CANT_CLOSE;
  }
  return SG_SUCCESS;
}

#else
  #error "Operating System is not Windows nor Unix-based!"
#endif
