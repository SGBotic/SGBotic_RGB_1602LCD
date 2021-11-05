/*
   hellow world example for SGBotic I2C RGB LCD library

   Copyright SGBotic (http://www.sgbotic.com)
   Copyright GNU Lesser General Public License

   version  V1.0
   date  Sept 2021
*/
#include <Wire.h>
#include "SGBotic_RGB_1602LCD.h"

uint16_t count = 0;
SGBotic_RGB_LCD lcd;

void setup() {
  lcd.begin();
  lcd.setRGB(2, 119, 189);
  lcd.setCursor(2, 0);
  lcd.print("hello world");
  lcd.setCursor(2, 1);
  lcd.print("1602 RGB LCD");
}

void loop() {
  /*available functions: */

  // lcd.displayOff();
  // lcd.displayOn();

  // lcd.backlightOff();
  // lcd.backlightOn();

  // lcd.blinkBacklight();
  // lcd.blinkBacklightOff();

  // lcd.autoscrollOff();
  // lcd.autoscrollOn();

  /* clear display */
  // lcd.clear();

  /* move cursor to row 0, coloum 0 */
  // lcd.home();

  // lcd.cursorOff();
  // lcd.cursorOn();
}
