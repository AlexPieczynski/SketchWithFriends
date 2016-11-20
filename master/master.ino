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

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// brush colors
uint16_t COLOR1 = BLUE;
uint16_t COLOR2 = RED;
int16_t BGCOLOR = BLACK;

// brush sizes
int16_t BRUSH1 = 10;
int16_t BRUSH2 = 10;

Point cursor1;
Point cursor2;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  tft.reset();
  tft.begin(tft.readID());
  tft.fillScreen(BGCOLOR);
  tft.setRotation(1);

  // center cursors on opposite sides
  cursor1.x = tft.width()/3;
  cursor1.y = tft.height()/2;
  cursor2.x = (tft.width()/3)*2;
  cursor2.y = tft.height()/2;
}

void updateCursor(Point* p, Direction dir) {
  switch(dir){
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

  if (p->x < 0)
    p->x = 0;
  else if (p->x > tft.width())
    p-> x = tft.width();

  if (p->y < 0)
    p->y = 0;
  else if (p->y > tft.height())
    p->y = tft.height();
}


void loop()
{
  // get dir from SLAVE1
  Wire.requestFrom(SLAVE1, 2);
  while (Wire.available() < 2){}
  Direction dir1 = Wire.read();
  Wire.read();

  // draw new point or clear screen
  if (dir1 != none && dir1 != clearPoints) {
    updateCursor(&cursor1, dir1);
    tft.fillRect(cursor1.x, cursor1.y, BRUSH2, BRUSH2, COLOR1);
  }
  else if (dir1 == 9)
    tft.fillScreen(BGCOLOR);
  
  Wire.requestFrom(9, 2);
  while (Wire.available() < 2){}
  Direction dir2 = Wire.read();
  Wire.read();
  
  if (dir2 != none && dir2 != clearPoints) {
    updateCursor(&cursor2, dir2);
    tft.fillRect(cursor2.x, cursor2.y, BRUSH2, BRUSH2, COLOR2);
  }
  else if (dir2 == clearPoints)
    tft.fillScreen(BGCOLOR);
}
