#!/bin/sh
rm -rf zig_build && mkdir zig_build

CFLAGS=$(pkg-config --cflags raylib)
LIB_FLAGS=$(pkg-config --libs-only-L raylib)
LINK_FLAGS=$(pkg-config --libs-only-l raylib)
# echo "CFLAGS: ${CFLAGS}, LIB_FLAGS: ${LIB_FLAGS}, LINK_FLAGS: ${LINK_FLAGS}"

echo -e "Compile cmd: \nzig cc -I${CFLAGS} \
    -L${LIB_FLAGS} \
    ${LINK_FLAGS} \
    -o zig_build/my-game \
    src/*.c \
    && ./zig_build/my-game\n\n"

zig cc -I${CFLAGS} \
    -L${LIB_FLAGS} \
    ${LINK_FLAGS} \
    -o zig_build/my-game \
    src/*.c \
    && ./zig_build/my-game
