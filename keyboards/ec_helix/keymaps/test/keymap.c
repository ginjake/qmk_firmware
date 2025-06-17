#include QMK_KEYBOARD_H

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    EISU,
    KANA,
    RGBRST
};

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Qwerty
    * ,-----------------------------------------.             ,-----------------------------------------.
    * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
    * |------+------+------+------+------+------|             |------+------+------+------+------+------|
    * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
    * |------+------+------+------+------+------|             |------+------+------+------+------+------|
    * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift|   Z  |   X  |   C  |   V  |   B  |   [  |   ]  |   N  |   M  |   ,  |   .  |   /  |Enter |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
    * |Adjust| Esc  | Alt  | GUI  | EISU |Lower |Space |Space |Raise | KANA | Left | Down |  Up  |Right |
    * `-------------------------------------------------------------------------------------------------'
    */
    [_QWERTY] = LAYOUT( \
        KC_A,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_B, \
        KC_A,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_B, \
        KC_A,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_B, \
        KC_A, KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_A,        KC_A,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_B , \
        RGBRST, KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,        KC_A,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_B \
    ),
    /* Lower
    * ,-----------------------------------------.             ,-----------------------------------------.
    * |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |
    * |------+------+------+------+------+------|             |------+------+------+------+------+------|
    * |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |
    * |------+------+------+------+------+------|             |------+------+------+------+------+------|
    * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   _  |   +  |   {  |   }  |  |   |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
    * | CAPS |  F7  |  F8  |  F9  |  F10 |  F11 |  (   |   )  |  F12 |      |      | Home | End  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
    * `-------------------------------------------------------------------------------------------------'
    */
    [_LOWER] = LAYOUT( \
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
        KC_CAPS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_LPRN, KC_RPRN, KC_F12,  _______, _______, KC_HOME, KC_END,  _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, MO(_ADJUST), _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
    ),

    /* Raise
    * ,-----------------------------------------.             ,-----------------------------------------.
    * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Bksp |
    * |------+------+------+------+------+------|             |------+------+------+------+------+------|
    * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
    * |------+------+------+------+------+------|             |------+------+------+------+------+------|
    * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   -  |   =  |   [  |   ]  |  \   |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
    * | CAPS |  F7  |  F8  |  F9  |  F10 |  F11 |      |      |  F12 |      |      |PageDn|PageUp|      |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
    * `-------------------------------------------------------------------------------------------------'
    */
    [_RAISE] = LAYOUT( \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
        KC_CAPS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______,  _______, KC_F12,  _______, _______, KC_PGDN, KC_PGUP, _______, \
        _______, _______, _______, _______, _______, MO(_ADJUST), _______, _______,    _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
    ),

    /* Adjust (Lower + Raise)
    * ,-----------------------------------------.             ,-----------------------------------------.
    * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
    * |------+------+------+------+------+------|             |------+------+------+------+------+------|
    * |      | Reset|RGBRST|      |      |      |             |      |      |      |      |      |  Del |
    * |------+------+------+------+------+------|             |------+------+------+------+------+------|
    * |      |      |      |Aud on|Audoff| Mac  |             | Win  |Qwerty|Colemk|Dvorak|      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      | MODE | HUE- | SAT- | VAL- |
    * `-------------------------------------------------------------------------------------------------'
    */
    [_ADJUST] =  LAYOUT( \
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
        RGB_MOD, QK_BOOT, RGBRST,  _______, _______, _______,                   _______, _______, _______, _______, _______, KC_DEL, \
        _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM,                   AG_SWAP, _______,  RGB_MODE_SNAKE, _______,  _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD \
    )
};


__attribute__ ((weak))
void get_matrix_key_val(uint8_t col, uint8_t row, uint8_t* val, uint8_t *threshold){
    *val=0;
    *threshold=0;
    (void)col;
    (void)row;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case EISU:
            if (record->event.pressed) {
                if(keymap_config.swap_lalt_lgui==false){
                    register_code(KC_LNG2);
                }else{
                    SEND_STRING(SS_LALT("`"));
                }
            } else {
                unregister_code(KC_LNG2);
            }
            return false;
        break;
        case KANA:
            if (record->event.pressed) {
                if(keymap_config.swap_lalt_lgui==false){
                    register_code(KC_LNG1);
                }else{
                    SEND_STRING(SS_LALT("`"));
                }
            } else {
                unregister_code(KC_LNG1);
            }
            return false;
        break;
        case RGBRST:
            #ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
            }
            #endif
        break;
    }
    return true;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
    static uint32_t last_timer=0;
    uint32_t timer_now = timer_read32();
    // 100msに一回
    if (TIMER_DIFF_32(timer_now, last_timer) > 100) {
        last_timer = timer_now;

        #ifdef CONSOLE_ENABLE
        uint8_t col,row,val,threshold;
        // for Debug
        col = 1;
        row = 2;
        get_matrix_key_val(col, row, &val, &threshold);
        uprintf("col=%d row=%d val=%d threshold=%d\n", col, row, val, threshold);
        #endif
    }
}
#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
    render_logo();
    return false;
}
#endif

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom();
  rgblight_mode_noeeprom(RGBLIGHT_MODE_RGB_TEST);
}
#endif
