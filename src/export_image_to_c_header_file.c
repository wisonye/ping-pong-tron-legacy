#include <raylib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
    //
    // No arguments were passed, print the usage prompt
    //
    if (argc < 3) {
        printf(
            "\n[ Usage ] - export_image_to_c_header IMAGE_FILENAME "
            "C_HEADER_FILENAME\n\n");
        return -1;
    }

    //
    // Check image file exists or not
    //
    const char *image_filename = argv[1];
    const char *c_header_filename = argv[2];

    printf("\n>>> image_filename: %s", image_filename);
    printf("\n>>> c_header_filename: %s", c_header_filename);

    if (access(image_filename, F_OK) != 0) {
        printf("\n\n>>> File not found: %s\n", image_filename);
    }

    //
    // Read image file and save it
    //
    Image img = LoadImage(image_filename);
    ExportImageAsCode(img, c_header_filename);
    UnloadImage(img);

    printf("\n\n>>> Exported image into c header file successfully: %s\n",
           c_header_filename);
}
