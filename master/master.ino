/*
 * This is the code that will run on the master arduino
 * The master will:
 *  -accept input from all slaves
 *  -draw to an LCD screen using this input
 *  
 *  Created by Alex Pieczynski, Ryan Fogarty, and Diego Vega
 *  
 *  TODO - shift Direction enum to slave side, convert to Direction there. Then send 1 byte of direction.
 */

#include <Wire.h>

#define USR1 1
#define USR2 2

void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

enum Direction
{
  north, neast, east, seast, south, swest, west, nwest
};

int cursor1x = 0;
int cursor1y = 0;
int cursor2x = 0;
int cursor2y = 0;

void loop()
{
  // get two bytes from device 0. We must standardize the device addresses somewhere.
  Wire.requestFrom(0, 1);
  Direction dir1 = Wire.read();

  Wire.requestFrom(1, 1);
  Direction dir2 = Wire.read();
}
