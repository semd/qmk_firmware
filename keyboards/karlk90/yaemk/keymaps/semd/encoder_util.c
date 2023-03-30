#pragma once

#include QMK_KEYBOARD_H
#include "keycodes.h"

enum Encoder {
    _ENCODER_LEFT  = 0,
    _ENCODER_RIGHT = 1,
};

typedef enum {
    ENC_MODE_VOLUME = 0,
    ENC_MODE_PAGING,
    ENC_MODE_UNDO,
} encoder_mode_t;

encoder_mode_t encoder_mode_left;
encoder_mode_t encoder_mode_right;


void encoder_util_init(void) {
    encoder_mode_left  = ENC_MODE_UNDO;
    encoder_mode_right  = ENC_MODE_VOLUME;
}

void encoder_shift_right(void) {
    if (encoder_mode_right == ENC_MODE_PAGING) {
        encoder_mode_right = ENC_MODE_VOLUME;
    } else {
        encoder_mode_right = ENC_MODE_PAGING;
    }
}

void encoder_action_volume(uint8_t clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
}

void encoder_action_paging(uint8_t clockwise) {
    if (clockwise) {
        tap_code(KC_PGUP);
    } else {
        tap_code(KC_PGDN);
    }
}

void encoder_action_undo(uint8_t clockwise) {
    if (clockwise) {
        tap_code16(LGUI(LSFT(KC_Z)));
    } else {
        tap_code16(LGUI(KC_Z));
    }
}

void encoder_action(uint8_t encoderIndex, bool clockwise) {
    encoder_mode_t encoder_mode = (encoderIndex == _ENCODER_LEFT) ? encoder_mode_left : encoder_mode_right;
    switch (encoder_mode) {
        case ENC_MODE_VOLUME:
            encoder_action_volume(clockwise);
            break;
        case ENC_MODE_PAGING:
            encoder_action_paging(clockwise);
            break;
        case ENC_MODE_UNDO:
            encoder_action_undo(clockwise);
            break;
        default:
            encoder_action_volume(clockwise);
    }
}


bool process_record_user_encoder(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case ENC_SHIFT:
            if (record->event.pressed) {
                encoder_shift_right();
            }
            return false;
        default:
            return true;
    }
}
