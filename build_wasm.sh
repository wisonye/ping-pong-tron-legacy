#!/bin/sh

C_COMPILER=$(which clang)
# C_COMPILER=$(which cc)
BUILD_FOLDER="wasm_build"
NO_CACHE=true
WASM_BUILD_FILE="cbuild_wasm"

#
# Compile `cbuild.c` and then use it to compile the project
#
${C_COMPILER} -o ${WASM_BUILD_FILE} -g "${WASM_BUILD_FILE}.c" \
    && \
    BUILD_FOLDER=${BUILD_FOLDER} \
    NO_CACHE=${NO_CACHE} \
    ./${WASM_BUILD_FILE}
