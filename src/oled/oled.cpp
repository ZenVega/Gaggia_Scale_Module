#include "oled.h"
#include "constants.h"
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/Org_01.h>
#include <Fonts/Picopixel.h>

int cw = SSD1306_WHITE;
int cb = SSD1306_BLACK;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void init_oled()
{
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }
    display.setTextColor(cw, cb);
    display.setFont(&Org_01);
    display.clearDisplay();
    display.display();
}

void    show_rest_screen(float weight, float target_weight)
{
    display.setCursor(70, 10);
    display.setTextSize(2);
    display.print(target_weight, 1);
    display.println("g");
    display.setTextSize(4);
    if (weight > -0.1 && weight < 0.1)
        weight = 0;
    if (weight < 0)
    {
        display.setCursor(-5, 50);
        display.print("-");
        weight = -weight;
    }
    display.setCursor(15, 50);
    //weight *= 10;
    //int weight_int = (int)weight;
    //weight = (float)weight_int;
    //weight /= 10;
    display.print(weight, 1);
    display.setTextSize(2);
    display.println("g");
    display.display();
    display.clearDisplay();
}
void start_screen()
{
    display.clearDisplay();
    display.display();

// LOGO fade in    
    for(int16_t i=display.width(); i > 0; i-=4) {
        for (int y = 0; y < 4; y++)
            display.drawCircle(display.width()/2, display.height()/2, i + y, cw);
        display.display();
        delay(1);
    }

    for(int16_t i=0; i < display.width()/3.5; i+=4) {
        for (int y = 0; y < 4; y++)
            display.drawCircle(display.width()/2, display.height()/2, i + y, cb);
        display.display();
        delay(1);
    }

    display.drawBitmap(display.width()/2 - 24, display.height()/2 - 24, coffee_mug, 48, 48, 1);
    display.display();
    delay(1200);
    for(int16_t i=display.width()/3.5; i < display.width(); i+=4) {
        for (int y = 0; y < 4; y++)
            display.drawCircle(display.width()/2, display.height()/2, i + y, cb);
        display.display();
        delay(1);
    }

    display.display();

 // Welcome Text   
    if (0)
    {
        char msg_1[] =  "Coffee";
        char msg_2[] =  "Time";
        int delay_time = 50;
        display.setTextSize(1); 
        display.clearDisplay();
        display.display();
        int y = 0;
        for (int i = 0; i < 6; i++){
            char ch = msg_1[i];
            int xx = i * 12 + 20;
            display.drawChar(xx, y, ch, cw, cb, 2);
            y = y + 5;
        }
        display.display();
        delay(delay_time);
        y = 36;
        for (int i = 0; i < 4; i++){
            char ch = msg_2[i];
            int xx = i * 12 + 46;
            display.drawChar(xx, y, ch, cw, cb, 2);
            y = y + 5;
        }
        display.display();
        delay(delay_time);
        display.drawBitmap(92, 2, heart_icon16x16, 16, 16, 1);
        delay(delay_time);
        display.display();
        display.drawBitmap(14, 36, heart_icon16x16, 16, 16, 1);
        delay(delay_time);
        display.display();
        delay(1000);
    }
}

void    arrows()
{
    display.drawBitmap(0, 0, arrow_down_icon16x16, 16,16,cw);
    display.drawBitmap(0, 0, arrow_up_icon16x16, 16,16,cw);
}