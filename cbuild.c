#include <stdio.h>

#define EXTRA_COMPILE_FLAGS "-I/opt/homebrew/Cellar/raylib/4.5.0/include"
// #define EXTRA_LINK_FLAGS "-L/opt/homebrew/Cellar/raylib/4.5.0/lib",
// "-lraylib"

// Static link version
#define EXTRA_LINK_FLAGS                                                 \
    "-L/opt/homebrew/Cellar/raylib/4.5.0/lib", "-lraylib", "-framework", \
        "Cocoa", "-framework", "OpenGL", "-framework", "IOKit"

#define C_BUILD_IMPLEMENTATION

#include "cbuild.h"

int main(void) {
    CB_setup_build_folder();
    CB_setup_compiler();

    CB_compile_and_build_executable("src/ball.c", "src/game.c", "src/player.c",
                                    "src/scoreboard.c", "src/table.c",
                                    "src/utils.c", "src/main.c", NULL);
}
