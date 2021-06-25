#include "Arduino.h"
#include "lcd.h"

LiquidCrystal Lcd(PIN_LCD_RS, PIN_LCD_E, PIN_LCD_DATA[0], PIN_LCD_DATA[1], PIN_LCD_DATA[2], PIN_LCD_DATA[3]);

/*
 * begin communication with lcd.
 */
void LcdInit()
{
  Lcd.begin(16, 2);
  Lcd.write("LCD Work now!");
  Serial.println("LCD Work Now!");
  delay(500);
  Lcd.clear();
  delay(500);
}

/*
 * Print next position.
 */
 void LcdNextPosition(int nextPosition)
 {
    Lcd.clear();
    delay(500);
    Lcd.print("Welcome to CMSM");
    delay(1000);
    Lcd.setCursor(0,1);
    String msg = "Go to: ";
    msg.concat(nextPosition);
    Lcd.print(msg);
 }
