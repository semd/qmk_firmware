#pragma once

#include QMK_KEYBOARD_H
#include "features/casemodes.h"
#include "keycodes.h"
#include "oled_util.h"

bool process_record_user_case(uint16_t keycode, keyrecord_t *record) {

    if (!process_case_modes(keycode, record)) {
        return false;
    }

    // Regular user keycode case statement
    switch (keycode) {
        case CAPS_CASE:
            if (record->event.pressed) {
                enable_caps_word();
                set_case_mode(CAPS_CASE);
            }
            return false;
        case SNAKE_CASE:
            if (record->event.pressed) {
                enable_xcase_with(SC_UNSC);
                set_case_mode(SNAKE_CASE);
            }
            return false;
        case CAMEL_CASE:
            if (record->event.pressed) {
                enable_xcase_with(OSM(MOD_LSFT));
                set_case_mode(CAMEL_CASE);
            }
            return false;
        case ANY_CASE:
            if (record->event.pressed) {
                enable_xcase();
                set_case_mode(ANY_CASE);
            }
            return false;
        default:
            return true;
    }
}

// Returns true if the case modes should terminate, false if they continue
// Note that the keycodes given to this function will be stripped down to
// basic keycodes if they are dual function keys. Meaning a modtap on 'a'
// will pass KC_A rather than LSFT_T(KC_A).
// Case delimiters will also not be passed into this function.
bool terminate_case_modes(uint16_t keycode, const keyrecord_t *record) {
    switch (keycode) {
        // Keycodes to ignore (don't disable caps word)
        case KC_A ... KC_Z:
        case KC_1 ... KC_0:
        case KC_MINS:
        case KC_UNDS:
        case KC_BSPC:
        case CAPS_CASE:
        case CAMEL_CASE:
        case ANY_CASE:
        case SNAKE_CASE:
            // If mod chording disable the mods
            if (record->event.pressed && (get_mods() != 0)) {
                unset_case_mode();
                return true;
            }
            break;
        default:
            if (record->event.pressed) {
                unset_case_mode();
                return true;
            }
            break;
    }
    return false;
}
