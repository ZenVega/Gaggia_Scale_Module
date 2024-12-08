#include <Arduino.h>
#include "HX711.h"

#define SCALE_1_CAL 2695
#define SCALE_2_CAL -2561.7

#define ROTARY_A 2
#define ROTARY_B 3
#define ROTARY_SWITCH_PIN 4
#define START_STOP 6
#define LOADCELL_SCK_PIN 9
#define LOADCELL_DOUT_PIN_1 10
#define LOADCELL_DOUT_PIN_2 11

float         target_timer = 10;
float         timer = 10;
int           currentStateCLK;
int           lastStateCLK;
String        currentDir = "";
unsigned long lastButtonPress = 0;
int          running = 0;
float         scale_1_reading;
float         scale_2_reading;
int btnState = 1;

HX711 scale_1;
HX711 scale_2;

void setup() {
  pinMode(ROTARY_SWITCH_PIN, INPUT_PULLUP);
	pinMode(ROTARY_A,INPUT);
  pinMode(ROTARY_B,INPUT);
	pinMode(START_STOP,INPUT);
  
  Serial.begin(57600);
  Serial.println("HX711 Demo");
  Serial.println("Initializing the scale");

  scale_1.begin(LOADCELL_DOUT_PIN_1, LOADCELL_SCK_PIN);
  scale_2.begin(LOADCELL_DOUT_PIN_2, LOADCELL_SCK_PIN);
  scale_1.set_scale(SCALE_1_CAL);
  scale_2.set_scale(SCALE_2_CAL);
  scale_1.tare();
  scale_2.tare();

  lastStateCLK = digitalRead(ROTARY_A);
//scale.read() - get raw reading
//scale.read_average(20)); - get average of 20 readings from the ADC
//scale.get_value(5)); - get the average of 5 readings from the ADC minus the tare weight, set with tare()
//scale.get_units(5), 1); - get the average of 5 readings from the ADC minus tare weight, divided by the SCALE parameter set with set_scale

  Serial.println("Readings:");
}

void loop() {
  btnState = digitalRead(ROTARY_SWITCH_PIN);
  currentStateCLK = digitalRead(ROTARY_A);
  scale_1_reading = scale_1.get_units();
  scale_2_reading = scale_2.get_units();

	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
		if (digitalRead(ROTARY_B) != currentStateCLK) {
			target_timer += .5;
		} else {
			target_timer -= .5;
		}
		Serial.print("SCALE TARGET: ");
		Serial.print(target_timer);
    Serial.print(" grams\n");
    lastStateCLK = currentStateCLK;
	}
  if (digitalRead(START_STOP) == LOW){
    Serial.print("~~~ START ~~~\n");
    running = 1;
  }
  while (running){
    scale_1_reading = scale_1.get_units();
    scale_2_reading = scale_2.get_units();
    if ( digitalRead(START_STOP) == LOW || scale_1_reading + scale_2_reading > target_timer){
      Serial.print("~~~ STOP ~~~\n");
      delay(1000);
      running = 0;
    }
    Serial.print("RUNNING:\t | ");
    Serial.print(scale_1_reading + scale_2_reading);
    Serial.print(" / ");
    Serial.print(target_timer);
    Serial.print(" grams\n");
    delay(300);
  }

	if (btnState == LOW) {
    scale_1.tare();
    scale_2.tare();
    Serial.print("~~~ TARE ~~~\n");
  }
}