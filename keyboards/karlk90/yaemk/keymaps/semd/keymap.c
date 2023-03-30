#include QMK_KEYBOARD_H
#include <stdio.h>
#include "keycodes.h"
#include "encoder_util.c"
#include "oled_util.c"
#include "case_mode_util.c"

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [_QWERTY] = LAYOUT( \
     KC_ESC         , KC_1          , KC_2          , KC_3          , KC_4          , KC_5          , KC_PSCREEN    ,                                 CAPS_CASE     , KC_6          , KC_7          , KC_8          , KC_9          , KC_0          , KC_BSPC       ,\
     KC_TAB         , KC_Q          , KC_W          , KC_E          , KC_R          , KC_T          , KC_END        ,                                 _______       , KC_Y          , KC_U          , KC_I          , KC_O          , KC_P          , SC_QUEST       ,\
     KC_LSFT        , KC_A          , KC_S          , KC_D          , KC_F          , KC_G          , KC_HOME       ,                                 CAMEL_CASE    , KC_H          , KC_J          , KC_K          , KC_L          , KC_UP         , SC_SCOL       ,\
     KC_LCTL        , KC_Z          , KC_X          , KC_C          , KC_V          , KC_B          , KC_RGUI       , KC_SPC         , KC_ENT       , KC_RGUI       , KC_N          , KC_M          , KC_DOT        , KC_LEFT       , KC_DOWN       , KC_RGHT      ,\
                                                      KC_C          , KC_LALT       , KC_RGUI       , MO(_LOWER)    , KC_SPC         , KC_ENT       , MO(_RAISE)    , KC_RALT       , KC_RSFT       , ENC_SHIFT \
  ),
   [_LOWER] = LAYOUT( \
    _______         , _______       , _______       , _______       , _______       , _______       , _______       ,                                 KC_CAPS       , _______       , _______       , _______       , _______       , _______       , KC_DEL       ,\
    KC_ESC          , KC_1          , KC_2          , KC_3          , KC_4          , KC_5          , _______       ,                                 _______       , _______       , _______       , _______       , _______       , _______       , SC_BACKSL       ,\
    _______         , _______       , SC_PERCE      , SC_AT         , SC_HASH       , SC_EXCLA      , _______       ,                                 ANY_CASE      , _______       , _______       , _______       , _______       , SC_ASTER      , SC_COLO         ,\
    _______         , KC_GRV        , KC_TILD       , SC_AMP        , SC_PIPE       , SC_DOLL       , _______       , _______       , _______       , _______       , KC_SCLN       , _______       , KC_COMM       , _______       , _______       , _______       ,\
                                                      _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______ \
  ),
   [_RAISE] = LAYOUT( \
    _______         , _______       , _______       , _______       , _______       , _______       , _______       ,                                 KC_CAPS       , _______       , _______       , _______       , _______       , _______       , KC_DEL       ,\
    KC_ESC          , KC_EQL        , SC_IQUEST     , SC_GEMIN      , SC_APROX      , SC_SYM1       , _______       ,                                 _______       , KC_LBRC       , KC_QUOT       , SC_OPAR       , SC_CPAR       , SC_EQUA       , SC_SLAS       ,\
    _______         , _______       , _______       , KC_NUBS       , SC_DIERE      , SC_CHAPE      , _______       ,                                 SNAKE_CASE    , SC_ODAT       , SC_CDAT       , SC_OKEY       , SC_CKEY       , KC_RBRC       , SC_COLO        ,\
    _______         , _______       , _______       , KC_NUHS       , _______       , _______       , _______       , _______       , _______       , _______       , KC_MINS       , SC_DQUO       , KC_COMM       , _______       , KC_SLSH       , SC_UNSC       ,\
                                                      _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______ \
  ),
   [_ADJUST] = LAYOUT( \
    KC_F12          , KC_F1         , KC_F2         , KC_F3         , KC_F4         , KC_F5         , RESET         ,                                 KC_WAKE       , KC_F6         , KC_F7         , KC_F8         , KC_F9         , KC_F10        , KC_F11       ,\
    _______         , RGB_TOG       , RGB_SAI       , RGB_HUI       , RGB_VAI       , RGB_MOD       , RGB_SPI       ,                                 _______       , _______       , _______       , _______       , _______       , _______       , _______       ,\
    _______         , RGB_FTOG       , RGB_SAD       , RGB_HUD       , RGB_VAD       , RGB_RMOD      , RGB_SPD       ,                                 _______       , _______       , _______       , _______       , _______       , _______       , _______       ,\
    _______         , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       ,\
                                                      _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______ \
  )
};

// clang-format on

void matrix_init_user(void) {
#ifdef ENCODER_ENABLE
    encoder_util_init();
#endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
#ifdef RGBLIGHT_ENABLE
    // rgb_set_layer_state(state);
#endif
    return state;
}

#if defined(IGNORE_MOD_TAP_INTERRUPT_PER_KEY)
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_SPC):
            return false;
        case RSFT_T(KC_SPC):
            return false;
        default:
            return true;
    }
}
#endif

#if defined(HOLD_ON_OTHER_KEY_PRESS_PER_KEY)
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_SPC):
            return true;
        case RSFT_T(KC_SPC):
            return true;
        default:
            return false;
    }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!process_record_user_case(keycode, record)) {
        return false;
    }

#ifdef ENCODER_ENABLE
    if (!process_record_user_encoder(keycode, record)) {
        return false;
    }
#endif

#ifdef RGB_MATRIX_ENABLE
    if (!process_record_user_oled(keycode, record)) {
        return false;
    }
#endif
    return true;
}

#if defined(ENCODER_ENABLE)
bool encoder_update_user(uint8_t encoderIndex, bool clockwise) {
    // layer_state_t current_state = get_highest_layer(layer_state);
    encoder_action(encoderIndex, clockwise);
    return false;
}
#endif

#if defined(OLED_ENABLE)

void render_display(void) {
    render_oled_slave();
}
#endif
