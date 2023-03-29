#include <stdio.h>
#include <string.h>

#define C_BUILD_IMPLEMENTATION

#include "cbuild.h"

int main(void) {
    CB_setup_build_folder();

    const char wasm_executable[256] = {0};
    snprintf((char *)wasm_executable, sizeof(wasm_executable), "%s/%s",
             CB_get_static_build_folder(), "game.html");

    char cmd_string[1024] = {0};

    join_args(cmd_string, sizeof(cmd_string), "emcc", "-o", wasm_executable,
              "src/ball.c", "src/game.c", "src/player.c", "src/scoreboard.c",
              "src/table.c", "src/utils.c", "src/main.c", "-Os", "-Wall",
              "./raylib-4.5.0_webassembly/lib/libraylib.a", "-I.",
              "-Iraylib-4.5.0_webassembly/include", "-L.",
              "-Lraylib-4.5.0_webassembly/lib", "-s", "USE_GLFW=3", "-s",
              "ASYNCIFY", "-DPLATFORM_WEB", NULL, NULL);
    CB_info("WASM", "cmd_string: %s", cmd_string);

    //
    // `--preload-file resources`:
    //
    // You can use parameter many times to include any resource file or folder,
    // `emcc` compiles all give files or files inside the given folder (sound
    // files, image files, etc) and generates a single `.data` file for the
    // WASM binary to load.
    //
    const char *cc_cmd[] = {
        "emcc", "-o", wasm_executable, "src/ball.c", "src/game.c",
        "src/player.c", "src/scoreboard.c", "src/table.c", "src/utils.c",
        "src/main.c", "-Os", "-Wall",
        "./raylib-4.5.0_webassembly/lib/libraylib.a", "-I.",
        "-Iraylib-4.5.0_webassembly/include", "-L.",
        "-Lraylib-4.5.0_webassembly/lib", "-s", "USE_GLFW=3", "-s", "ASYNCIFY",
        // "--shell-file",
        // wasm_shell_file,
        "--preload-file", "resources", "-DPLATFORM_WEB", NULL};

    CB_exec(cc_cmd[0], cc_cmd);
    CB_info("WASM", "Build successfully, generated executable: %s",
            wasm_executable);
}
