#!/usr/bin/env bash

   cd tests \
&& clang --std=c17 -Weverything -Wno-declaration-after-statement -Wno-unsafe-buffer-usage -O3 -DNDEBUG bench.c -o ../a \
&& cd .. \
&& ./a
