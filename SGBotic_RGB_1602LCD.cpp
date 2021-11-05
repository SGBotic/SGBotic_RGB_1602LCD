/*
 * Arduino library for SGBotic RGB LCD
 * @copyright	SGBotic (http://www.sgbotic.com), 2021
 * @copyright	GNU Lesser General Public License
 *
 * @author KC
 * @version  V1.0
 * @date  March 2021
 */

#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <Wire.h>
#include "SGBotic_RGB_1602LCD.h"

SGBotic_RGB_LCD::SGBotic_RGB_LCD(uint8_t lcd_cols, uint8_t lcd_rows)
{
    _cols = lcd_cols;
    _rows = lcd_rows;
}

SGBotic_RGB_LCD::SGBotic_RGB_LCD()
{
    _cols = 16;
    _rows = 2;
}

void SGBotic_RGB_LCD::begin()
{
    delay(100);
    Wire.begin();

    delay(50);

    // clear/ reset RGB registers
    rgbWriteReg(RGB_REG_MODE1, 0x0);
    rgbWriteReg(RGB_REG_MODE2, 0x0);

    //init LCD
    lcdCommand(LCD_2LINE | LCD_5x8DOTS); // Function set
    delay(5);
    _displaySetting = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    lcdCommand(_displaySetting); // Display ON/OFF
    delay(5);
    lcdCommand(LCD_CLEARDISPLAY); // Clear display
    delay(10);
    lcdCommand(LCD_CURSORINCREMENTON | LCD_CURSORSHIFTOFF); // set display mode, 0x06
    delay(5);
    setCursor(0, 0);

    rgbWriteReg(RGB_REG_MODE1, 0x0);
    rgbWriteReg(REG_LEDOUT, 0xFF);
    rgbWriteReg(RGB_REG_MODE2, 0x20);

    setRGB(255, 255, 255); //set color white
}

void SGBotic_RGB_LCD::clear()
{
    lcdCommand(LCD_CLEARDISPLAY); // Clear display
    delay(2);
}

void SGBotic_RGB_LCD::home()
{
    lcdCommand(LCD_HOME);
}

void SGBotic_RGB_LCD::displayOff()
{
    _displaySetting |= LCD_DISPLAYON;
    lcdCommand(LCD_DISPLAYCONTROL | _displaySetting);
}

void SGBotic_RGB_LCD::displayOn()
{
    _displaySetting &= ~LCD_DISPLAYON;
    lcdCommand(LCD_DISPLAYCONTROL | _displaySetting);
}

void SGBotic_RGB_LCD::blinkOff()
{
    _displaySetting &= ~LCD_BLINKON;
    lcdCommand(LCD_DISPLAYCONTROL | _displaySetting);
}
void SGBotic_RGB_LCD::blinkOn()
{
    _displaySetting |= LCD_BLINKON;
    lcdCommand(LCD_DISPLAYCONTROL | _displaySetting);
}

void SGBotic_RGB_LCD::cursorOff()
{
    _displaySetting &= ~LCD_CURSORON;
    lcdCommand(LCD_DISPLAYCONTROL | _displaySetting);
}

void SGBotic_RGB_LCD::cursorOn()
{
    _displaySetting |= LCD_CURSORON;
    lcdCommand(LCD_DISPLAYCONTROL | _displaySetting);
}

void SGBotic_RGB_LCD::setCursor(uint8_t col, uint8_t row)
{
    col = (row == 0 ? col | 0x80 : col | 0xc0);
    uint8_t data[2] = {0x80, col};
    //i2cWrite(data, 2);
    lcdCommand(0x80);
    lcdCommand(col);
}

void SGBotic_RGB_LCD::autoscrollOff(void)
{
    _modeSetting &= ~LCD_ENTRYSHIFTINCREMENT;
    lcdCommand(LCD_MODECONTROL | _modeSetting);
}

void SGBotic_RGB_LCD::autoscrollOn(void)
{
    _modeSetting |= LCD_ENTRYSHIFTINCREMENT;
    lcdCommand(LCD_MODECONTROL | _modeSetting);
}

void SGBotic_RGB_LCD::blinkBacklight()
{

    rgbWriteReg(0x07, 0x17); // blink every second
    rgbWriteReg(0x06, 0x7F); // half on, half off
}

void SGBotic_RGB_LCD::blinkBacklightOff(void)
{
    rgbWriteReg(0x07, 0x00); // GRPFREQ
    rgbWriteReg(0x06, 0xFF); // GRPPWM
}
void SGBotic_RGB_LCD::backlightOn(void)
{
    rgbWriteReg(REG_LEDOUT, 0xFF);
}

void SGBotic_RGB_LCD::backlightOff(void)
{
    rgbWriteReg(REG_LEDOUT, 0x00);
}

inline size_t SGBotic_RGB_LCD::write(uint8_t value)
{

    //uint8_t data[2] = {0x40, value};
    //i2cWrite(data, 2);
    lcdData(value);
    //delay(5);
    return 1; // assume sucess
}

void SGBotic_RGB_LCD::lcdCommand(uint8_t data)
{
    Wire.beginTransmission(LCD_ADDRESS);
    Wire.write(0x00);
    Wire.write((byte)data);
    Wire.endTransmission(); // stop transmitting
}

void SGBotic_RGB_LCD::lcdData(uint8_t data)
{
    Wire.beginTransmission(LCD_ADDRESS);
    Wire.write(0x40);
    Wire.write((byte)data);
    Wire.endTransmission(); // stop transmitting
}

void SGBotic_RGB_LCD::i2cWrite(uint8_t *data, uint8_t len)
{
    Wire.beginTransmission(LCD_ADDRESS);
    for (int i = 0; i < len; i++)
    {
        Wire.write(data[i]);
        delay(1);
    }
    Wire.endTransmission(); // stop transmitting
}

void SGBotic_RGB_LCD::setRGB(uint8_t r, uint8_t g, uint8_t b)
{
    rgbWriteReg(REG_RED, r);
    rgbWriteReg(REG_GREEN, g);
    rgbWriteReg(REG_BLUE, b);
}

void SGBotic_RGB_LCD::rgbWriteReg(uint8_t registerAddress, uint8_t data)
{

    Wire.beginTransmission(RGB_ADDRESS);
    Wire.write(registerAddress);
    Wire.write(data);
    Wire.endTransmission();
}

uint8_t SGBotic_RGB_LCD::rgbReadReg(uint8_t registerAddress)
{

    Wire.beginTransmission(RGB_ADDRESS);
    Wire.write(registerAddress);
    Wire.endTransmission();

    Wire.requestFrom((uint8_t)RGB_ADDRESS, (uint8_t)1);

    if (Wire.available() == 1)
    {
        return Wire.read();
    }

    return -1;
}

/*
void SGBotic_RGB_LCD::printstr(const char c[])
{
    ///< This function is not identical to the function used for "real" I2C displays
    ///< it's here so the user sketch doesn't have to be changed
    print(c);
}*/
