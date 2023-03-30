#include QMK_KEYBOARD_H
#include <stdio.h>
#include "keycodes.h"
#include "oled_util.h"
#include "features/casemodes.h"

#define w_val(str, val)                         \
    snprintf(buffer, sizeof(buffer), str, val); \
    oled_write(buffer, false)

#define w_val_ln(str, val)                         \
    snprintf(buffer, sizeof(buffer), str, val); \
    oled_write_ln(buffer, false)


#define CAPS_WRD_CASE_STR   "  WORD"
#define SNAKE_CASE_STR      "snake_"
#define SCREAM_CASE_STR     "SNEAK_"
#define CAMEL_CASE_STR      "CamelC"
#define ANY_CASE_STR        "x-case"
#define NO_CASE_STR         "   OFF"

static char *x_case_mode = NO_CASE_STR;
void set_case_mode(uint16_t keycode) {
    switch (keycode) {
        case CAPS_CASE:
            if (strcmp(x_case_mode, SCREAM_CASE_STR) != 0) {
                x_case_mode = (strcmp(x_case_mode, SNAKE_CASE_STR) == 0) ? SCREAM_CASE_STR : CAPS_WRD_CASE_STR;
            }
            break;
        case SNAKE_CASE:
            if (strcmp(x_case_mode, SCREAM_CASE_STR) != 0) {
                x_case_mode = (strcmp(x_case_mode, CAPS_WRD_CASE_STR) == 0) ? SCREAM_CASE_STR : SNAKE_CASE_STR;
            }
            break;
        case CAMEL_CASE:
            x_case_mode = CAMEL_CASE_STR;
            break;
        case ANY_CASE:
            x_case_mode = ANY_CASE_STR;
            break;
    }
}
void unset_case_mode(void) {
    x_case_mode = NO_CASE_STR;
}

void render_qmk_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x80,
        0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xa0,
        0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xc0,0};

    oled_write_P(qmk_logo, false);
}

void render_status_bar(void) {
    uint8_t modifiers = get_mods();
    led_t   led_state = host_keyboard_led_state();
    oled_write_P(PSTR("\325\326"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("\327\330"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("\331\332"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("\333\334"), (modifiers & MOD_MASK_GUI));
    oled_write_P(PSTR("\275\276"), led_state.caps_lock);
}

void render_rgb_status(void) {
    switch (rgb_matrix_get_flags()) {
        case LED_FLAG_ALL: {
            oled_write_P(PSTR("RGB:    \52\52"), false);
        } break;
        case LED_FLAG_KEYLIGHT: {
            oled_write_P(PSTR("RGB:    \52o"), false);
        } break;
        case LED_FLAG_UNDERGLOW: {
            oled_write_P(PSTR("RGB:    o\52"), false);
        } break;
        default: {
            oled_write_ln("RGB:   OFF", false);
        } break;
    }
}

void render_layer(layer_state_t current_state) {
    oled_write_P(PSTR("\335\336:"), false);

    switch (current_state) {
        case _QWERTY:
            oled_write_P(PSTR("\272 QWERT"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("\233 LOWER"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("\234 RAISE"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("\274 ADJST"), false);
            break;
        default:
            oled_write_P(PSTR("UNDEF"), false);
    }
}

void render_oled_slave(void) {
    static layer_state_t last_state    = ~0;
    layer_state_t        current_state = get_highest_layer(layer_state);

    if (last_state != current_state) {
        oled_clear();
        last_state = current_state;
    }

    char buffer[25];

    render_qmk_logo();
    oled_write_ln_P(PSTR("----------"), false);

    render_layer(current_state);
    oled_write_ln("\n", false);

    switch (current_state) {
        case _ADJUST:
#if defined(RGB_MATRIX_ENABLE)
            w_val_ln("RGB n:  %02d", rgb_matrix_config.mode);
            w_val("Hue:   %03d", rgb_matrix_config.hsv.h);
            w_val("Sat:   %03d", rgb_matrix_config.hsv.s);
            w_val("Bri:   %03d", rgb_matrix_config.hsv.v);
            w_val("Spd:   %03d", rgb_matrix_config.speed);
#endif
            oled_write("\n\n", false);
#if defined(DEBUG_MATRIX_SCAN_RATE)
            w_val("Frq: %05ld", get_matrix_scan_rate());
#endif
            break;
        default:

            w_val_ln("CA: %s", x_case_mode);
#if defined(RGB_MATRIX_ENABLE)
            render_rgb_status();
#endif
            oled_write_ln("\n\n\n", false);
            render_status_bar();
            break;
    }
}

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case RGB_FTOG:
            if (record->event.pressed) {
                if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable();
                } else {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable();
                }
            }
            return false;
        default:
            return true;
    }
}

