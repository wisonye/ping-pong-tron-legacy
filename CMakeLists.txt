cmake_minimum_required(VERSION "3.22")

project("ping-pong-tron-legacy")

#
# Generate `compile_commands.json` for `Neovim` LSP needed
#
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

#
# Compiler flags
#
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_C_FLAGS "-pedantic-errors -std=gnu17")
set(CMAKE_CXX_FLAGS "-pedantic-errors -Wc99-extensions -Wvla-extension -Wc11-extensions -Wc11-extensions -std=c++11")

#
# Find installed libraries as compilation dependencies
# https://cmake.org/cmake/help/latest/command/find_package.html
#
find_package(raylib REQUIRED)

#
# Only one exectuable
#
add_executable("${PROJECT_NAME}"
    # "src/ball.c"
    # "src/racket.c"
    # "src/scoreboard.c"
    # "src/table.c"
    "src/game.c"
    "src/main.c")

#
# Link to `raylib`
#
target_link_libraries("${PROJECT_NAME}" raylib)

# target_compile_definitions("${PROJECT_NAME}" PRIVATE ENABLE_DEBUG_LOG)

#
# Debug log
#
message(">>> CMAKE_EXPORT_COMPILE_COMMANDS: ${CMAKE_EXPORT_COMPILE_COMMANDS}")
message(">>> CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message(">>> CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(">>> CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")
message(">>> CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
message(">>> CMAKE_C_FLAGS_DEBUG: ${CMAKE_C_FLAGS_DEBUG}")
message(">>> CMAKE_C_FLAGS_RELEASE: ${CMAKE_C_FLAGS_RELEASE}")
message(">>> CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(">>> CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(">>> CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message(">>> CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
message(">>> raylig_FOUND: ${raylib_FOUND}")
