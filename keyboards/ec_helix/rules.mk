# QMK Standard Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
#   See TOP/docs/config_options.md for more information.
#
SRC += matrix.c

BOOTMAGIC_ENABLE = no   # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no    # Mouse keys
EXTRAKEY_ENABLE = no    # Audio control and System control
CONSOLE_ENABLE = no     # Console for debug
COMMAND_ENABLE = no     # Commands for debug and configuration
OLED_ENABLE = yes
OLED_DRIVER = ssd1306
LOCAL_GLCDFONT = no         # use each keymaps "helixfont.h" insted of "common/glcdfont.c"
IOS_DEVICE_ENABLE = no  # connect to IOS device (iPad,iPhone)
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no   # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no        # USB Nkey Rollover
BACKLIGHT_ENABLE = no   # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes   # Enable WS2812 RGB underlight.
LED_ANIMATIONS = yes
MIDI_ENABLE = no        # MIDI support
BLUETOOTH_ENABLE = no   # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no       # Audio output on port C6
FAUXCLICKY_ENABLE = no  # Use buzzer to emulate clicky switches
HD44780_ENABLE = no     # Enable support for HD44780 based LCDs

