#!/bin/sh
rm -rf zig_build && mkdir zig_build

CFLAGS="-pedantic-errors -Wall -Werror -Wextra -std=c11 -O3 -DNDEBUG"

RAYLIB_CFLAGS=$(pkg-config --cflags raylib)
RAYLIB_LIB_FLAGS=$(pkg-config --libs-only-L raylib)
RAYLIB_LINK_FLAGS=$(pkg-config --libs-only-l raylib)

echo -e "Compile cmd: \nzig cc ${CFLAGS} \
    ${RAYLIB_CFLAGS} \
    ${RAYLIB_LIB_FLAGS} \
    ${RAYLIB_LINK_FLAGS} \
    -o zig_build/my-game \
    src/*.c \
    && ./zig_build/my-game\n\n"

zig cc ${CFLAGS} \
    ${RAYLIB_CFLAGS} \
    ${RAYLIB_LIB_FLAGS} \
    ${RAYLIB_LINK_FLAGS} \
    -o zig_build/my-game \
    src/*.c \
    && ./zig_build/my-game
