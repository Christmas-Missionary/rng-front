#!/usr/bin/env bash

   cd tests \
&& clang --std=c17 -Weverything -Wno-declaration-after-statement -Wno-unsafe-buffer-usage -O3 -DCE_ASSUME_ALL bench.c -o ../a \
&& clang --std=c17 -Weverything -Wno-declaration-after-statement -Wno-unsafe-buffer-usage -g -fsanitize=address,undefined basic.c ../external/custom-errors/custom_errors.c -o ../b \
&& cd .. \
&& ./a && ./b
