#include "constants.h"
#include "rotary_encoder/rotary_encoder.h"
#include "oled/oled.h"
#include "scale/scale.h"

unsigned long lastButtonPress = 0;
int           running = 0;
int           btnState = 1;
float         target_timer = 10;
float         start_time;
float         current_time;
float         stop_time;
float         weight;


void setup() {
  Serial.begin(57600);
	pinMode(START_STOP,INPUT);

  init_oled();
  init_rotary(target_timer);
  start_screen();
  init_scale();

  Serial.println("Readings:");
}

void loop() {
  btnState = digitalRead(ROTARY_SWITCH_PIN);
  target_timer = check_rotary(Serial, target_timer);
  weight = get_weight();

  if (digitalRead(START_STOP) == LOW){
    Serial.print("~~~ START ~~~\n");
    running = 1;
    delay(1000);
    start_time = millis() / 1000;
    Serial.print(start_time);
    Serial.print(" seconds\n");
  }

  while (running){
    current_time = millis();
    weight = get_weight();
    Serial.print("RUNNING:\t | ");
    Serial.print(weight);
    Serial.print(" / ");
    Serial.print(target_timer);
    Serial.print(" grams\n");
    Serial.print((current_time - start_time) / 1000);
    Serial.print(" seconds\n");
    if ( digitalRead(START_STOP) == LOW || weight > target_timer){
      stop_time = current_time - start_time;
      Serial.print("STOPPED AT ");
      Serial.print(stop_time / 1000);
      Serial.print(" seconds\n");
      running = 0;
      delay(1000);
    }
    delay(300);
  }

	if (btnState == LOW)
    tare_scale();
}