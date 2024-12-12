#include "rotary_encoder.h"
#include "constants.h"

Encoder rotaryEncoder(ROTARY_A, ROTARY_B);
float         newPosition;

void    init_rotary(float target_timer){
    pinMode(ROTARY_SWITCH_PIN, INPUT_PULLUP);
    pinMode(ROTARY_A,INPUT);
    pinMode(ROTARY_B,INPUT);
    if (EEPROM.read(EEPROM_INIT_FLAG_ADDR) != EEPROM_INIT_FLAG) {
        // EEPROM not initialized. Writing default target_timer
        EEPROM.put(TARGET_TIMER_ADDR, target_timer);
        EEPROM.write(EEPROM_INIT_FLAG_ADDR, EEPROM_INIT_FLAG);
    } else {
        // Load target_timer from EEPROM
        EEPROM.get(TARGET_TIMER_ADDR, target_timer);
        rotaryEncoder.write(target_timer * 8);
        newPosition = target_timer;
    }
  
}

float    check_rotary(Stream &serialPort, float target_timer) {

  newPosition = floor(rotaryEncoder.read()/4); // Adjust scaling factor as needed
  newPosition /= 2;
  if (newPosition != target_timer) {
      target_timer = newPosition;
      serialPort.print("SCALE TARGET: ");
      serialPort.print(target_timer);
      serialPort.print(" grams\n");
      EEPROM.put(TARGET_TIMER_ADDR, target_timer);
  }
  return target_timer;
}