#pragma once

#include "quantum.h"

void set_case_mode(uint16_t keycode);
void unset_case_mode(void);
bool process_record_user_oled(uint16_t keycode, keyrecord_t *record);
void render_oled_slave(void);
