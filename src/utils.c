#include "utils.h"

#include <stdio.h>
#include <string.h>

#define COLOR_STRUCT_BYTES 4

///
///
///
void Utils_get_color_string(Color color, char *out_buffer, usize buffer_size) {
    // RGBA each 2 bytes for HEX + '\0'
    usize memory_bytes_len = COLOR_STRUCT_BYTES * 2 + 1;
    u8 memory_bytes[memory_bytes_len];
    memset(memory_bytes, '\0', memory_bytes_len);

    u8 memory_byte = 0x00;
    for (usize index = 0; index < COLOR_STRUCT_BYTES; index++) {
        // 1. Convert (Color *) to `(unsigned char *)`, so each `+1` means
        //    moving just 1 byte!!!
        // 2. Get back the pointer offset by `(u8 *) + index`
        // 3. Dereference that pointer offset value (in HEX format)
        memory_byte = *(((u8 *)&color) + index);

        snprintf((char *)memory_bytes + (index * 2), 3, "%02X", memory_byte);
        // printf("\n>>> memory_bytes : %s", memory_bytes);
    }
    // printf(
    //     "\n>>> memory_bytes_len: %llu, memory_bytes[memory_bytes_len - 1] : "
    //     "%02X\n",
    //     memory_bytes_len, memory_bytes[memory_bytes_len - 1]);
    memory_bytes[memory_bytes_len - 1] = '\0';

    snprintf(out_buffer, buffer_size, "%s", memory_bytes);
}

///
///
///
void Utils_get_player_string(Player *player, char *out_buffer,
                             usize buffer_size) {
    char player_type_str[10];
    snprintf(player_type_str, sizeof(player_type_str), "%s",
             player->type == PT_LEFT ? "LEFT" : "RIGHT");

    char default_racket_color_str[9];
    Utils_get_color_string(player->default_racket.color,
                           default_racket_color_str,
                           sizeof(default_racket_color_str));
    printf("\n>>> default_racket_color_str len: %lu",
           strlen(default_racket_color_str));

    snprintf(out_buffer, buffer_size,
             "\tplayer: {\n\t\ttype: %s\n\t\tname: %s\n\t\tscore: "
             "%llu\n\t\tdefault_racket: {\n\t\t\tcolor: 0x%s\n\t\t\tvelocity: "
             "%.2f\n\t\t}\n\t}",
             player_type_str, player->name, player->score,
             default_racket_color_str, RACKET_UI_VELOCITY);
}
