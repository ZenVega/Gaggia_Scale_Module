#ifndef CONSTANTS
    #define CONSTANTS
#include <Arduino.h>
#include "HX711.h"

//ROTARY
#define ROTARY_A 7
#define ROTARY_B 5
#define ROTARY_SWITCH_PIN 4
#define EEPROM_INIT_FLAG_ADDR 4  // EEPROM address for initialization flag
#define EEPROM_INIT_FLAG 123
#define TARGET_TIMER_ADDR 0      // EEPROM address for target_timer

//START/STOP
#define START_STOP 6

//LOAD CELL
#define LOADCELL_SCK_PIN 9
#define LOADCELL_DOUT_PIN_1 10
#define LOADCELL_DOUT_PIN_2 11
#define SCALE_1_CAL 2695
#define SCALE_2_CAL -2561.7

//OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#endif