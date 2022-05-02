#include QMK_KEYBOARD_H


#define KC_KANJI KC_GRV


enum Layer
{
  _QWERTY = 0
};


enum custom_keycodes {
  QWERTY = SAFE_RANGE
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    KC_A, KC_B, KC_C, KC_D, KC_E
  )
};
