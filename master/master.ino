/*
 * This is the code that will run on the master arduino
 * The master will:
 *  -accept input from all slaves
 *  -draw to an LCD screen using this input
 *  
 *  Created by Alex Pieczynski, Ryan Fogarty, and Diego Vega
 */

#include <Wire.h>
#include <Adafruit_TFTLCD.h>
#include "sketchwithfriends.h"

// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

Point cursor1;
Point cursor2;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  tft.reset();
  tft.begin(tft.readID());

  // center cursors on opposite sides
  cursor1.x = 106;
  cursor1.y = 120;
  cursor2.x = 213;
  cursor2.y = 120;
}

void updateCursors(Point* p, Direction dir)
{
  switch(dir)
  {
    case north:
      p->y++;
      break;
    case neast:
      p->x++;
      p->y++;
      break;
    case east:
      p->x++;
      break;
    case seast:
      p->x++;
      p->y--;
      break;
    case south:
      p->y--;
      break;
    case swest:
      p->x--;
      p->y--;
      break;
    case west:
      p->x--;
      break;
    case nwest:
      p->x--;
      p->y++;
      break;
  }
}

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
  // get two bytes from device 8. We must standardize the device addresses somewhere.
  Wire.requestFrom(8, 2);
  while (Wire.available() < 2){};
  Direction dir1 = Wire.read();
  Serial.print("SLAVE1: ");
  Serial.println(dir1);

//  Wire.requestFrom(SLAVE2, 2);
//  Direction dir2 = Wire.read();
//  Serial.println("SLAVE2: " + dir2);

  if (dir1 != none)
    updateCursor(&cursor1, dir1);
  else {                            // undo request
    // UNDO HERE
  }
  
//  updateCursor(&cursor2, dir2);
    

  // draw rectangle at the new cursor position
  tft.fillRect(cursor1.x, cursor1.y, BRUSH1, BRUSH1, COLOR1);
//  tft.fillRect(cursor2.x, cursor2.y, BRUSH2, BRUSH2, COLOR2);
  delay(500);
}
