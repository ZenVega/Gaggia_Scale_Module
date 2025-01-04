#include "rotary_encoder.h"
#include "constants.h"

Encoder rotaryEncoder(ROTARY_A, ROTARY_B);
float   newPosition;

void    init_rotary(float target_weight)
{
    pinMode(ROTARY_SWITCH_PIN, INPUT_PULLUP);
    pinMode(ROTARY_A,INPUT);
    pinMode(ROTARY_B,INPUT);

    if (EEPROM.read(EEPROM_INIT_FLAG_ADDR) != EEPROM_INIT_FLAG) {
        // EEPROM not initialized. Writing default target_weight
        EEPROM.put(TARGET_TIMER_ADDR, target_weight);
        EEPROM.write(EEPROM_INIT_FLAG_ADDR, EEPROM_INIT_FLAG);
    } else {
        // Load target_weight from EEPROM
        EEPROM.get(TARGET_TIMER_ADDR, target_weight);
        rotaryEncoder.write(target_weight * 8);
        newPosition = target_weight;
    }
}

float    check_rotary(Stream &serialPort, float target_weight)
{
  newPosition = floor(rotaryEncoder.read()/4); // Adjust scaling factor as needed
  newPosition /= 2;
  if (newPosition != target_weight) {
      target_weight = newPosition;
      EEPROM.put(TARGET_TIMER_ADDR, target_weight);
  }
  return target_weight;
}