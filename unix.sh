#!/usr/bin/env bash

warnings="--std=c17 -Wall -Wextra -Wpedantic"

   cd tests \
&& cc $warnings -O3 -march=native -DCE_ASSUME_ERROR -DCE_ASSUME_WARN -DCE_NO_FATAL bench.c -o ../a \
&& cc $warnings -g -fsanitize=address,undefined basic.c ../src/external/custom-errors/custom_errors.c ../src/external/seed-gen/seed_gen.c -o ../b \
&& cc $warnings -O3 -march=native -DCE_ASSUME_ERROR -DCE_ASSUME_WARN -DCE_NO_FATAL -DSHISHUA_TARGET=SHISHUA_TARGET_SCALAR bench.c -o ../c \
&& cd .. \
&& ./a && ./b && ./c
