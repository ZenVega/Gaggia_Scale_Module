#include "constants.h"
#include "rotary_encoder/rotary_encoder.h"
#include "oled/oled.h"
#include "scale/scale.h"

int   running = 0;
int   btnState = 1;
float target_weight = 0;
float start_time;
float current_time;
float stop_time;
float weight;


void  setup() {
  //Serial.begin(57600);
	pinMode(START_STOP,INPUT);

  init_oled();
  init_rotary(target_weight);
  welcome_screen();
  init_scale();
}

void  loop() {
  btnState = digitalRead(ROTARY_SWITCH_PIN);
  target_weight = check_rotary(Serial, target_weight);
  weight = get_weight();
  rest_screen(weight, target_weight);

  if (digitalRead(START_STOP) == LOW){
    start_screen();
    running = 1;
    start_time = millis();
  }

  while (running){
    current_time = millis();
    weight = get_weight();
    float running_time = (current_time - start_time) / 1000;
    running_screen(running_time, weight, target_weight);
    if ( digitalRead(START_STOP) == LOW || weight > target_weight){
      stop_time = current_time - start_time;
      running = 0;
      stop_screen(stop_time / 1000);
    }
  }

	if (btnState == LOW)
  {
    tare_scale();
    tare_screen();
  }
}