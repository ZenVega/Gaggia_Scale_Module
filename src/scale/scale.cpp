#include "scale.h"

float   scale_1_reading;
float   scale_2_reading;

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

float get_median(float measurements[5])
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4 - i; j++)
    {
      if (measurements[j] > measurements[j + 1])
      {
        float temp = measurements[j];
        measurements[j] = measurements[j + 1];
        measurements[j + 1] = temp;
      }
    }
  }
  return measurements[2];
}

float   get_weight()
{
  float mes_arr[5];
  for (int i = 0; i < 5; i++)
  {
    scale_1_reading = scale_1.get_units();
    scale_2_reading = scale_2.get_units();
    mes_arr[i] = scale_1_reading + scale_2_reading;
  }
  float total = get_median(mes_arr);
  if( total > -0.5 && total < 0.5 )
    total = 0;
  return (total);
}

void    tare_scale()
{
    scale_1.tare();
    scale_2.tare();
}
