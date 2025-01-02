#include "constants.h"
#include "rotary_encoder/rotary_encoder.h"
#include "oled/oled.h"

unsigned long lastButtonPress = 0;
int           running = 0;
float         scale_1_reading;
float         scale_2_reading;
int           btnState = 1;
float         target_timer = 10;
float start_time;
float current_time;
float stop_time;

HX711 scale_1;
HX711 scale_2;


void setup() {
	pinMode(START_STOP,INPUT);
  init_oled();

  Serial.begin(57600);

  init_rotary(target_timer);
  start_screen();

  scale_1.begin(LOADCELL_DOUT_PIN_1, LOADCELL_SCK_PIN);
  scale_2.begin(LOADCELL_DOUT_PIN_2, LOADCELL_SCK_PIN);
  scale_1.set_scale(SCALE_1_CAL);
  scale_2.set_scale(SCALE_2_CAL);
  scale_1.tare();
  scale_2.tare();

  Serial.println("Readings:");
}

void loop() {
  btnState = digitalRead(ROTARY_SWITCH_PIN);
  scale_1_reading = scale_1.get_units();
  scale_2_reading = scale_2.get_units();
  target_timer = check_rotary(Serial, target_timer);

  if (digitalRead(START_STOP) == LOW){
    Serial.print("~~~ START ~~~\n");
    running = 1;
    delay(1000);
    start_time = millis() / 1000;
    Serial.print(start_time);
    Serial.print(" seconds\n");
    //display.fillScreen(cb);
    //display.display();
  }

  while (running){
    current_time = millis();
    scale_1_reading = scale_1.get_units();
    scale_2_reading = scale_2.get_units();
    Serial.print("RUNNING:\t | ");
    Serial.print(scale_1_reading + scale_2_reading);
    Serial.print(" / ");
    Serial.print(target_timer);
    Serial.print(" grams\n");
    Serial.print((current_time - start_time) / 1000);
    Serial.print(" seconds\n");
    if ( digitalRead(START_STOP) == LOW || scale_1_reading + scale_2_reading > target_timer){
      stop_time = current_time - start_time;
      Serial.print("STOPPED AT ");
      Serial.print(stop_time / 1000);
      Serial.print(" seconds\n");
      running = 0;
      //display.fillScreen(cw);
      //display.display();
      delay(1000);
    }
    delay(300);
  }

	if (btnState == LOW) {
    scale_1.tare();
    scale_2.tare();
    Serial.print("~~~ TARE ~~~\n");
  }
}