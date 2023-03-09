#!/bin/sh

#
# Remove everything exists
#
./remove_all_cmake_build_folders.sh

#
# Run cmake to generate all files
#
cmake -S ./ -B ./temp_build

#
# Copy `compile_commands.json` to `build/compile_commands.json` for neovim LSP
#
mkdir build
cp -rvf ./temp_build/compile_commands.json ./build
