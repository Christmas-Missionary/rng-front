#!/usr/bin/env bash

   mkdir web;
   mkdir web/a;
   mkdir web/b;
   cd tests \
&& emcc -o ../web/a/index.html --emrun bench.c -DCE_ASSUME_ERROR -DCE_ASSUME_WARN -DCE_NO_FATAL -Wall -O3 -msimd128 --closure 1 -sIGNORE_CLOSURE_COMPILER_ERRORS=1 -sFILESYSTEM=0 --shell-file ../minshell.html \
&& emcc -o ../web/b/index.html --emrun basic.c ../src/external/custom-errors/custom_errors.c ../src/external/seed-gen/seed_gen.c -Wall -sASSERTIONS=2 -g -fsanitize=address,undefined --shell-file ../minshell.html \
&& emrun ../web/a/index.html --browser firefox \
&& emrun ../web/b/index.html --browser firefox \
