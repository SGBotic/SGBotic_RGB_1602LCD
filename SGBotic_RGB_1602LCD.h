/*
 * Arduino library for SGBotic RGB LCD
 * @copyright	SGBotic (http://www.sgbotic.com), 2021
 * @copyright	GNU Lesser General Public License
 *
 * @author KC
 * @version  V1.0
 * @date  March 2021
 */

#ifndef SGBOTIC_RGB_1602LCD_H
#define SGBOTIC_RGB_1602LCD_H

#include <inttypes.h>
#include "Print.h"

//#define LCD_ADDRESS (0x7c >> 1)
#define LCD_ADDRESS 0x3E
#define RGB_ADDRESS (0xc0 >> 1)

#define RGB_REG_MODE1 0x00
#define RGB_REG_MODE2 0x01
/**
 * LED output state
 */
#define REG_LEDOUT 0x08
#define REG_RED 0x04   // pwm2
#define REG_GREEN 0x03 // pwm1
#define REG_BLUE 0x02  // pwm0

#define LCD_2LINE 0x28
#define LCD_1LINE 0x20
#define LCD_5x11DOTS 0x24
#define LCD_5x8DOTS 0x20

#define LCD_DISPLAYON 0b00001100
#define LCD_DISPLAYOFF 00b00001000

#define LCD_CURSORON 0b00001010
#define LCD_CURSOROFF 0b00001000

#define LCD_BLINKON 0b00001001
#define LCD_BLINKOFF 0b00001000
#define LCD_HOME 0x02

#define LCD_DISPLAYCONTROL 0x08
#define LCD_MODECONTROL 0x04
#define LCD_CLEARDISPLAY 0x01
#define LCD_CURSORINCREMENTON 0b00000110
#define LCD_CURSORINCREMENTOFF 0b00000100
#define LCD_CURSORSHIFTON 0b00000101
#define LCD_CURSORSHIFTOFF 0b00000100
#define LCD_ENTRYSHIFTINCREMENT 0b00000001
#define LCD_ENTRYSHIFTDECREMENT 0b00000000

class SGBotic_RGB_LCD : public Print
{
public:
    SGBotic_RGB_LCD(uint8_t lcd_cols, uint8_t lcd_rows);
    SGBotic_RGB_LCD::SGBotic_RGB_LCD();

    void begin();

    void clear();
    void home();
    void displayOff();
    void displayOn();
    void blinkOff();
    void blinkOn();
    void cursorOff();
    void cursorOn();
    void setCursor(uint8_t col, uint8_t row);
    void setRGB(uint8_t r, uint8_t g, uint8_t b);
    void autoscrollOff();
    void autoscrollOn();
    void blinkBacklight();
    void blinkBacklightOff();
    void backlightOn();
    void backlightOff();
   // void rgbOn();
   // void rgbOff();
    virtual size_t write(uint8_t);
    void printstr(const char[]);
    using Print::write;

private:
    uint8_t _cols;
    uint8_t _rows;
    uint8_t _storedRegLedout;
    uint8_t _displaySetting;
    uint8_t _modeSetting;

    void lcdCommand(uint8_t data);
    void lcdData(uint8_t data);
    void i2cWrite(uint8_t *data, uint8_t len);
    void rgbWriteReg(uint8_t registerAddress, uint8_t data);
    uint8_t rgbReadReg(uint8_t registerAddress);
};

#endif