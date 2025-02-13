#include "oled.h"
#include "constants.h"
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/Org_01.h>
#include <Fonts/Picopixel.h>

int cw = SSD1306_WHITE;
int cb = SSD1306_BLACK;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void    init_oled()
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

void    welcome_screen()
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
}

void    rest_screen(float weight, float target_weight)
{
    display.setCursor(70, 10);
    display.setTextSize(2);
    display.print(target_weight, 1);
    display.println("g");
    display.setTextSize(4);
    if (weight < 0)
    {
        display.setCursor(-5, 50);
        display.print("-");
        weight = -weight;
    }
    display.setCursor(15, 50);
    display.print(weight, 1);
    display.setTextSize(2);
    display.println("g");
    display.display();
    display.clearDisplay();
}

void    start_screen()
{
    display.clearDisplay();
    display.setTextSize(3);
    display.setCursor(0, 40);
    display.println("~START~");
    display.display();
    delay(700);
}

void    running_screen(float run_time, float weight, float target_weight){
    display.clearDisplay();
    //TIME
    int r_time = (int)run_time;
    display.setTextSize(3);
    display.setCursor(30, 14);
    display.setTextSize(2);
    display.print(r_time);
    display.println(" Sec");

    //WEIGHT
    display.setCursor(10, 36);
    display.print(weight, 1);
    display.print("/");
    display.print(target_weight, 1);
    display.println("g");

    //LOADING BAR
    int height = 14;
    int width = 108;
    int percentage = weight / target_weight * (width - 4);
    if(percentage > 104)
        percentage = 104; 
    display.drawRect(10, 50, width, height, SSD1306_WHITE);
    display.fillRect(12, 52, percentage, height - 4, SSD1306_WHITE);
    display.display(); 
}

void    stop_screen(float stop_time)
{
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(10, 12);
    display.println("Brew time");
    display.setTextSize(4);
    display.setCursor(10, 40);
    display.println(stop_time, 1);
    display.setTextSize(2);
    display.setCursor(40, 60);
    display.println("seconds");
    display.display();
    delay(4500);
}

void    tare_screen()
{
    display.clearDisplay();
    display.setTextSize(3);
    for(int i = 0; i < 2; i++){
        display.setCursor(10, 40);
        display.println("~TARE~");
        display.display();
        delay(300);
        display.clearDisplay();
        display.display();
        delay(300);
    }
}