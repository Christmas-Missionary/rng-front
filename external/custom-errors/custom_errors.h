// Copyright (c) 2025 Christmas_Missionary - BSD Zero Clause License

#ifndef CE_CUSTOM_ERRORS
#define CE_CUSTOM_ERRORS

#ifdef __cplusplus
  #define CE_NO_RET [[noreturn]]
#endif

#if defined(__STDC_VERSION__) && !defined(CE_NO_RET)
  #if __STDC_VERSION__ >= 202311L
    #define CE_NO_RET [[noreturn]]
  #elif __STDC_VERSION__ >= 201112L
    #define CE_NO_RET _Noreturn
  #endif
#endif // defined(__STDC_VERSION__) && !defined(CE_NO_RET)

// `CE_NO_RET` helps static analyzers determine if code is reachable.
// If it isn't, there are less false positives.
#ifndef CE_NO_RET
  #define CE_NO_RET
#endif

#if defined(NDEBUG) && !defined(CE_ASSUME_ALL)
  #define CE_WARN(expr, msg)
  #define CE_ERROR(expr, msg)
  #define CE_FATAL(expr, msg)
#else // if no NDEBUG

  #if defined(CE_NO_WARN)
    #define CE_WARN(expr, msg)
  #elif defined(CE_ASSUME_WARN) || defined(CE_ASSUME_ALL)

    #if (defined(_MSVC_LANG) && _MSVC_LANG >= 202302L) || (defined(__cplusplus) && __cplusplus >= 202302L)
      #define CE_WARN(expr, msg) [[assume(expr)]]
    #elif defined(_MSC_VER) // #if Not C++23
      #define CE_WARN(expr, msg) __assume(expr)
    #elif defined(__clang__) || defined(__EMSCRIPTEN__) // Not MSVC, but Clang or Emscripten
      #define CE_WARN(expr, msg) __builtin_assume(expr)
    #elif defined(__GNUC__) // Not Clang, but GCC
      #define CE_WARN(expr, msg) __attribute__((assume(expr)))
    #else // None of the above
      #define CE_WARN(expr, msg)
    #endif // #ifdef CE_ASSUME

  #endif // CE_ASSUME_WARN or CE_ASSUME_ALL

  #if defined(CE_NO_ERROR)
    #define CE_ERROR(expr, msg)
  #elif defined(CE_ASSUME_ERROR) || defined(CE_ASSUME_ALL)

    #if (defined(_MSVC_LANG) && _MSVC_LANG >= 202302L) || (defined(__cplusplus) && __cplusplus >= 202302L)
      #define CE_ERROR(expr, msg) [[assume(expr)]]
    #elif defined(_MSC_VER) // #if Not C++23
      #define CE_ERROR(expr, msg) __assume(expr)
    #elif defined(__clang__) || defined(__EMSCRIPTEN__) // Not MSVC, but Clang or Emscripten
      #define CE_ERROR(expr, msg) __builtin_assume(expr)
    #elif defined(__GNUC__) // Not Clang, but GCC
      #define CE_ERROR(expr, msg) __attribute__((assume(expr)))
    #else // None of the above
      #define CE_ERROR(expr, msg)
    #endif // #ifdef CE_ASSUME

  #endif // CE_ASSUME_ERROR or CE_ASSUME_ALL

  #if defined(CE_NO_FATAL)
    #define CE_FATAL(expr, msg)
  #elif defined(CE_ASSUME_FATAL) || defined(CE_ASSUME_ALL)

    #if (defined(_MSVC_LANG) && _MSVC_LANG >= 202302L) || (defined(__cplusplus) && __cplusplus >= 202302L)
      #define CE_FATAL(expr, msg) [[assume(expr)]]
    #elif defined(_MSC_VER) // #if Not C++23
      #define CE_FATAL(expr, msg) __assume(expr)
    #elif defined(__clang__) || defined(__EMSCRIPTEN__) // Not MSVC, but Clang or Emscripten
      #define CE_FATAL(expr, msg) __builtin_assume(expr)
    #elif defined(__GNUC__) // Not Clang, but GCC
      #define CE_FATAL(expr, msg) __attribute__((assume(expr)))
    #else // None of the above
      #define CE_FATAL(expr, msg)
    #endif // #ifdef CE_ASSUME

  #endif // CE_ASSUME_FATAL or CE_ASSUME_ALL

#endif // if no NDEBUG

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(CE_ERROR) || !defined(CE_FATAL)
CE_NO_RET
void ce_err_handler(unsigned char type, const char * msg, const char * file, const char * fnc, int line,
                    const char * expr);
  #if !defined(CE_ERROR)
    #define CE_ERROR(expr, msg) ((expr) ? (void)0 : ce_err_handler(0, msg, __FILE__, __func__, __LINE__, #expr))
  #endif
  #if !defined(CE_FATAL)
    #define CE_FATAL(expr, msg) ((expr) ? (void)0 : ce_err_handler(1, msg, __FILE__, __func__, __LINE__, #expr))
  #endif
#endif

#if !defined(CE_WARN)
void ce_warn_handler(const char * msg, const char * file, const char * fnc, int line, const char * expr);
  #define CE_WARN(expr, msg) ((expr) ? (void)0 : ce_warn_handler(msg, __FILE__, __func__, __LINE__, #expr))
#endif

#ifdef _WIN32
unsigned long set_windows_colors(void);
#endif

#ifdef __cplusplus
}
#endif

// convenience macro for noreturn, if needed
#ifndef CE_INCLUDE_NORET
  #undef CE_NO_RET
#endif

// convenience macro for static_assert, if in C
#ifndef __cplusplus
  #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
    #define static_assert _Static_assert
  #else
    #define static_assert(expr, msg)
    #define _Static_assert(expr, msg)
  #endif
#endif // ifndef __cplusplus

#endif // CE_CUSTOM_ERRORS
