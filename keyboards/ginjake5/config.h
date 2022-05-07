

#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0007
#define DEVICE_VER         0x0001
#define MANUFACTURER    numazu Keyboards
#define PRODUCT         ginjake
#define DESCRIPTION     ginjake Keyboards 5Key

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 5

#pragma once

#include "config_common.h"


#define DIRECT_PINS {{ B6, B2, E6, B4, B5 }}
#define UNUSED_PINS

/* ws2812 RGB LED */
#define RGB_DI_PIN D3

#define RGBLED_NUM 0    // Number of LEDs

#define RGBLIGHT_ANIMATIONS
#define BACKLIGHT_LEVELS 5
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 4
#define BREATHING_PERIOD 2
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17
#define USB_MAX_POWER_CONSUMPTION 400

#define TAPPING_TERM 200
