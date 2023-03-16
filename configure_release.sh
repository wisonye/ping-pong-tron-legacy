#!/bin/sh

#
# Remove everything exists
#
./remove_all_cmake_build_folders.sh

#
# Run cmake to generate all files
#
LLVM_CLANG=$(which clang)
cmake -S ./ -B ./temp_build \
    -DCMAKE_C_COMPILER="${LLVM_CLANG}" \
    -DCMAKE_BUILD_TYPE=Release

#
# Copy `compile_commands.json` to `build/compile_commands.json` for neovim LSP
#
mkdir build
cp -rvf ./temp_build/compile_commands.json ./build

#
# Copy resources to `temp_build`
#
cp -rvf ./resources ./temp_build
