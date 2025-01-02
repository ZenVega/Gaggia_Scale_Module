#include "oled.h"
#include "constants.h"

int cw = SSD1306_WHITE;
int cb = SSD1306_BLACK;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void init_oled()
{
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    display.setTextColor(cw, cb);
}

void start_screen()
{
    display.setTextSize(2); 
    display.fillScreen(cw);
    display.clearDisplay();
    display.drawBitmap(32, 0, coffee_mug, 60, 60, 1);
    //display.println("");
    //display.println(" Coffee");
    //display.println("    Time");

    //display.drawBitmap(95, 10, heart_icon16x16, 16, 16, 1);
    //display.drawBitmap(20, 40, heart_icon16x16, 16, 16, 1);
    display.display();
    delay(2000);
}

void    arrows()
{
    display.drawBitmap(0, 0, arrow_down_icon16x16, 16,16,cw);
    display.drawBitmap(0, 0, arrow_up_icon16x16, 16,16,cw);
}