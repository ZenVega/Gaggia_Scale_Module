#ifndef CONSTANTS
    #define CONSTANTS
#include <Arduino.h>
#include "HX711.h"

#define SCALE_1_CAL 2695
#define SCALE_2_CAL -2561.7

#define TARGET_TIMER_ADDR 0      // EEPROM address for target_timer
#define EEPROM_INIT_FLAG_ADDR 4  // EEPROM address for initialization flag
#define EEPROM_INIT_FLAG 123
#define ROTARY_A 3
#define ROTARY_B 2
#define ROTARY_SWITCH_PIN 4
#define START_STOP 6
#define LOADCELL_SCK_PIN 9
#define LOADCELL_DOUT_PIN_1 10
#define LOADCELL_DOUT_PIN_2 11

#endif