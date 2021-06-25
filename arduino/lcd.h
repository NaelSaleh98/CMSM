#include <LiquidCrystal.h>

/*
 * Pins.
 */
const int PIN_LCD_RS = 12; // 0 -> command , 1 -> data
const int PIN_LCD_E = 11; // To enable LCD
const int PIN_LCD_DATA[4] = {10, 9, 8, 7};

/*
 * Objects.
 */
extern LiquidCrystal Lcd;

/*
 * begin communication with lcd.
 */
void LcdInit();

/*
 * Print next position.
 */
 void LcdNextPosition(int nextPosition);
