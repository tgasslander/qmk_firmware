# MCU name
MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = caterina

SPLIT_KEYBOARD = yes
SERIAL_DRIVER = bitbang

LAYOUTS = default

# Debugging
CONSOLE_ENABLE = yes
COMMAND_ENABLE = yes
DEBUG_ENABLE = yes
VERBOSE = yes

DEFAULT_FOLDER = toga/togasplit/v1
