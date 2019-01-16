

#ifndef CONFIG_H
#define CONFIG_H
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0007
#define DEVICE_VER         0x0001
#define MANUFACTURER    numazu Keyboards
#define PRODUCT         lovelive9
#define DESCRIPTION     lovelive sunshine Keyboards 9Key // Charleston, SC Meetup Handout

/* key matrix size */
#define RGBLIGHT_ANIMATIONS
#define BACKLIGHT_LEVELS 5
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 4
#define BREATHING_PERIOD 2
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

#define MATRIX_ROWS 9
#define MATRIX_COLS 1

#define NO_PIN 0xFF
#define MATRIX_ROW_PINS { B4, B6, B2, D7, B1, F7, F6, F5, F4 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL, or CUSTOM_MATRIX */
#define DIODE_DIRECTION CUSTOM_MATRIX

/* ws2812 RGB LED */
/* COL2ROW or ROW2COL */
//#define DIODE_DIRECTION COL2ROW

#define USE_SERIAL
#define RGB_DI_PIN D3
#define RGBLIGHT_TIMER
//#define RGBLED_NUM 12    // Number of LEDs. see ./keymaps/default/config.h
#define RGBLED_NUM 9    // Number of LEDs

#define ws2812_PORTREG  PORTD
#define ws2812_DDRREG   DDRD
#if defined(RGBLIGHT_ENABLE) && !defined(IOS_DEVICE_ENABLE)
// USB_MAX_POWER_CONSUMPTION value
//  120  RGBoff
//  330  RGB 6
//  300  RGB 32
 #define USB_MAX_POWER_CONSUMPTION 400
#else
 // fix iPhone and iPad power adapter issue
 // iOS device need lessthan 100
 #define USB_MAX_POWER_CONSUMPTION 100
#endif





#define TAPPING_TERM 200

#endif
