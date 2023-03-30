
#pragma once

#ifdef OLED_ENABLE
    #undef OLED_TIMEOUT
    #undef OLED_UPDATE_INTERVAL
    #undef OLED_FONT_H
    #define OLED_TIMEOUT 15000
    #define OLED_UPDATE_INTERVAL 0
    #define OLED_FONT_H "keyboards/karlk90/yaemk/keymaps/semd/glcdfont.c"
#endif
