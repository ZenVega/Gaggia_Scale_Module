#include "constants.h"
#include "rotary_encoder/rotary_encoder.h"

unsigned long lastButtonPress = 0;
int           running = 0;
float         scale_1_reading;
float         scale_2_reading;
int           btnState = 1;
float         target_timer = 10;

HX711 scale_1;
HX711 scale_2;

void setup() {
	pinMode(START_STOP,INPUT);

  Serial.begin(57600);

  init_rotary(target_timer);

  scale_1.begin(LOADCELL_DOUT_PIN_1, LOADCELL_SCK_PIN);
  scale_2.begin(LOADCELL_DOUT_PIN_2, LOADCELL_SCK_PIN);
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
  btnState = digitalRead(ROTARY_SWITCH_PIN);
  scale_1_reading = scale_1.get_units();
  scale_2_reading = scale_2.get_units();
  target_timer = check_rotary(Serial, target_timer);

  if (digitalRead(START_STOP) == LOW){
    Serial.print("~~~ START ~~~\n");
    running = 1;
    delay(1000);
  }

  while (running){
    scale_1_reading = scale_1.get_units();
    scale_2_reading = scale_2.get_units();
    Serial.print("RUNNING:\t | ");
    Serial.print(scale_1_reading + scale_2_reading);
    Serial.print(" / ");
    Serial.print(target_timer);
    Serial.print(" grams\n");
    if ( digitalRead(START_STOP) == LOW || scale_1_reading + scale_2_reading > target_timer){
      Serial.print("~~~ STOP ~~~\n");
      running = 0;
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