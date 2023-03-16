# Ping pong game TronLegacy version

## How to configure

```bash
# For debug build
./configure.sh

# For release build
./configure_release.sh
```

</br>


## How to run

```bash
# Custom player name and use stand ball radius (`30.0f`)
PLAYER_1_NAME=Dad PLAYER_2_NAME=Mom ./run.sh

# Use bigger ball for beginner level
BALL_RADIUS=60.0 PLAYER_1_NAME='Ball game killer' PLAYER_2_NAME='Blow your mind' ./run.sh
```

</br>

If you don't provide the above env vars, it uses the default settings:

```bash
PLAYER_1_NAME=Player 1
PLAYER_2_NAME=Player 2
```

</br>

## How to run test code

If you got a new idea and you want to test it, try it in `./src/main_test.c`
and then run the following script to test it:

```bash
./run_test.sh
```

</br>


## Export image data into C header file

If you want to build a single executable that includes all image data without
loading them from a file, this is what you want:)

```bash
./run_export_image_to_c_header_file.sh IMAGE_FILENAME C_HEADER_FILENAME
```

After that, load the included C header file (raw image pixels) to generate the
image instance:

```c
#include "YOUR_EXPORTED_HERADER_FILE.h"

//
// Load pixels data into an image structure and create texture
//
Image temp_image = {
    .data = XXXX_DATA,
    .width = XXXX_WIDTH,
    .height = XXXX_HEIGHT,
    .format = XXXX_FORMAT,
    .mipmaps = 1
};

Texture2D temp_texture = LoadTextureFromImage(temp_image);
UnloadImage(temp_image);
```

You can find the `XXXX` in `YOUR_EXPORTED_HERADER_FILE.h`.

</br>


