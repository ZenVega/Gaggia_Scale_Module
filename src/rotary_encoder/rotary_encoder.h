#ifndef ROTARY
    #define ROTARY

#include "constants.h"
#include <Encoder.h>
#include <EEPROM.h>
void    init_rotary(float target_weight);
float   check_rotary(Stream &serialPort, float target_weight);

#endif