/*
Copyright (c) 2025 Christmas_Missionary - BSD Zero Clause License
*/

#ifndef SG_SEED_GEN_QJD
#define SG_SEED_GEN_QJD

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum sg_error {
  SG_SUCCESS,
  SG_INVALID_PARAMETERS,
  SG_CANT_OPEN,
  SG_ERROR_DURING_GEN,
  SG_CANT_CLOSE,
} sg_error;

sg_error sg_generate_seed(void * dst, size_t size);

#ifdef __cplusplus
}
#endif

#endif
