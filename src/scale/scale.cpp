#include "scale.h"
#include "constants.h"

float         scale_1_reading;
float         scale_2_reading;

HX711   scale_1;
HX711   scale_2;

void    init_scale()
{
  scale_1.begin(LOADCELL_DOUT_PIN_1, LOADCELL_SCK_PIN);
  scale_2.begin(LOADCELL_DOUT_PIN_2, LOADCELL_SCK_PIN);
  scale_1.set_scale(SCALE_1_CAL);
  scale_2.set_scale(SCALE_2_CAL);
  scale_1.tare();
  scale_2.tare();
}

float   get_weight()
{
  scale_1_reading = scale_1.get_units();
  scale_2_reading = scale_2.get_units();
  return (scale_1_reading + scale_2_reading);
}

void    tare_scale()
{
    scale_1.tare();
    scale_2.tare();
    Serial.print("~~~ TARE ~~~\n");
}