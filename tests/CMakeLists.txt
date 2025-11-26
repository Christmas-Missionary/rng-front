cmake_minimum_required(VERSION 3.25)

# cmake -S tests -B build
# cmake --build build
project(rng-front)

set(C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)

add_compile_definitions(CE_ASSUME_ERROR CE_ASSUME_WARN CE_NO_FATAL)

add_executable(a bench.c)
add_executable(b basic.c ../src/external/custom-errors/custom_errors.c ../src/external/seed-gen/seed_gen.c)

add_executable(c bench.c)
target_compile_definitions(c PRIVATE SHISHUA_TARGET=SHISHUA_TARGET_SCALAR)

if(MSVC)
  target_compile_options(a PRIVATE /Wall /O2)
  target_compile_options(b PRIVATE /Wall /Od /RTC1)
  target_compile_options(c PRIVATE /Wall /O2)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  target_compile_options(a PRIVATE -Wall -Wextra -Wpedantic -O3 -march=native)
  target_compile_options(b PRIVATE -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined)
  target_link_options(b PRIVATE -fsanitize=address,undefined)
  target_compile_options(c PRIVATE -Wall -Wextra -Wpedantic -O3 -march=native)
else()
  message(WARNING "Your compiler is not supported here!")
endif()

if(WIN32)
  set(CMAKE_C_FLAGS_DEBUG "")
  set(CMAKE_CXX_FLAGS_DEBUG "")
  target_link_libraries(b bcrypt.lib)
endif()
