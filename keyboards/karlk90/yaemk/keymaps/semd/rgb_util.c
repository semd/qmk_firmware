#include "quantum.h"
#include "keycodes.h"
#include "features/casemodes.h"

#define RGB_VERMELL 0x77, 0x05, 0x01
#define RGB_ROSA 0xAA, 0x11, 0x11
#define RGB_BLAU 0x00, 0x70, 0x70
#define RGB_VERD  0x40, 0xAA, 0x00

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (caps_word_enabled()) {
        rgb_matrix_set_color_all(RGB_ROSA);
    } else if (get_xcase_state() == 1) {
        rgb_matrix_set_color_all(RGB_PURPLE);
    } else if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color_all(RGB_WHITE);
    } else {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY:
                // default default color
                break;
            case _LOWER:
                rgb_matrix_set_color_all(RGB_BLAU);
                break;
            case _RAISE:
                rgb_matrix_set_color_all(RGB_VERD);
                break;
            case _ADJUST:
                rgb_matrix_set_color_all(RGB_VERMELL);
                break;
        }
    }
}

