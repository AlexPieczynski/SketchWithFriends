/*
 * This is the code that will run on the master arduino
 * The master will:
 *  -accept input from all slaves
 *  -draw to an LCD screen using this input
 *  
 *  Created by Alex Pieczynski, Ryan Fogarty, and Diego Vega
 */

#include <Wire.h>
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include "sketchwithfriends.h"

// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  tft.reset();
  tft.begin(tft.readID());
}

// cursor positions
int cursor1x = 0;
int cursor1y = 0;
int cursor2x = 0;
int cursor2y = 0;

// brush sizes
// TODO - define some way of changing brush size.
//        Probably using buttons on the slave side.
int16_t BRUSH1 = 3;
int16_t BRUSH2 = 3;

// brush colors
// TODO - perhaps allow user to change color?
uint16_t COLOR1 = BLUE;
uint16_t COLOR2 = RED;

void loop()
{
  // get two bytes from device 0. We must standardize the device addresses somewhere.
  Wire.requestFrom(8, 2);
  while (Wire.available() < 2){};
  Direction dir1 = Wire.read();
  Serial.print("SLAVE1: ");
  Serial.println(dir1);

//  Wire.requestFrom(SLAVE2, 2);
//  Direction dir2 = Wire.read();
//  Serial.println("SLAVE2: " + dir2);

  // CHANGE CURSOR POSITIONS HERE

  // draw rectangle at the new cursor position
  tft.fillRect(cursor1x, cursor1y, BRUSH1, BRUSH1, COLOR1);
//  tft.fillRect(cursor2x, cursor2y, BRUSH2, BRUSH2, COLOR2);
  delay(500);
}
