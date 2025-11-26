/*
Copyright (c) 2025 Christmas_Missionary - BSD Zero Clause License
*/

#ifndef RNGFRONT_RESTRICT_IS_MY_FAV_KEYWORD_GFK2WB
#define RNGFRONT_RESTRICT_IS_MY_FAV_KEYWORD_GFK2WB

#if defined(__cplusplus) || (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)

  #if defined(__GNUC__) || defined(__clang__)
    #define restrict __restrict__
  #elif defined(_MSC_VER)
    #define restrict __restrict
  #else
    #define restrict
  #endif

#endif /* If C++ or before C99 */

#endif /* RNGFRONT_RESTRICT_IS_MY_FAV_KEYWORD_GFK2WB */
