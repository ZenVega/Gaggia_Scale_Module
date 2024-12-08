#include <Arduino.h>
#include "HX711.h"

#define SCALE_1_CAL 2695
#define SCALE_2_CAL -2561.7

#define ROTARY_SWITCH_PIN 4
#define LOADCELL_SCK_PIN 9
#define LOADCELL_DOUT_PIN_1 10
#define LOADCELL_DOUT_PIN_2 11

HX711 scale_1;
HX711 scale_2;
void setup() {
  pinMode(ROTARY_SWITCH_PIN, INPUT_PULLUP);

  Serial.begin(57600);
  Serial.println("HX711 Demo");
  Serial.println("Initializing the scale");

  scale_1.begin(LOADCELL_DOUT_PIN_1, LOADCELL_SCK_PIN);
  scale_2.begin(LOADCELL_DOUT_PIN_2, LOADCELL_SCK_PIN);

  Serial.println(scale_1.read());      // print a raw reading from the ADC
  Serial.println(scale_2.read());      // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale_1.read_average(20));   // print the average of 20 readings from the ADC
  Serial.println(scale_2.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale_1.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)
  Serial.println(scale_2.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  scale_1.set_scale(SCALE_1_CAL);
  scale_2.set_scale(SCALE_2_CAL);
  
  scale_1.tare();
  scale_2.tare();

//scale.read() - get raw reading
//scale.read_average(20)); - get average of 20 readings from the ADC
//scale.get_value(5)); - get the average of 5 readings from the ADC minus the tare weight, set with tare()
//scale.get_units(5), 1); - get the average of 5 readings from the ADC minus tare weight, divided by the SCALE parameter set with set_scale

  Serial.println("Readings:");
}

void loop() {
  int btnState = digitalRead(ROTARY_SWITCH_PIN);

	if (btnState == LOW) {
    scale_1.tare();
    scale_2.tare();
    Serial.print("~~~ TARE ~~~");
  }

  float scale_1_reading = scale_1.get_units();
  float scale_2_reading = scale_2.get_units();
  Serial.print("scale_1:\t");
  Serial.print(scale_1_reading);
  Serial.print("\t| scale_2:\t");
  Serial.print(scale_2_reading);
  Serial.print("\t| total:\t");
  Serial.print(scale_1_reading + scale_2_reading);
  Serial.print("\n");
  delay(2000);
}