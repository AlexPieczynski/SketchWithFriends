/*
 * This is the code that will run on the slave arduinos
 * The slaves will:
 *  -read values from an analog stick
 *  -convert these values into a direction
 *  -send direction values to the master
 *  
 *  Created by Alex Pieczynski, Ryan Fogarty, and Diego Vega
 */

#include <Wire.h>

#define STICKX 1
#define STICKY 2
#define SLAVE_ADDR 8 // these will probably need to be different for each slave

enum Direction
{
  north, neast, east, seast, south, swest, west, nwest, none
};

void setup()
{
  pinMode(STICKX, INPUT);
  pinMode(STICKY, INPUT);
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDR);
}

Direction getDirection(byte x, byte y)
{
  if (x == 0 && y == 0)
    return none;
  return 1;
}

/**
 * This function executes whenever the master
 *  asks for input
 */
void requestEvent()
{
  byte x = map(analogRead(STICKX), 0, 1023, 0, 3);
  delay(1); // delay needed in between two analog reads, see https://www.arduino.cc/en/Tutorial/JoyStick
  byte y = map(analogRead(STICKY), 0, 1023, 0, 3);
  Serial.print("X: ");
  Serial.println(x);
  Serial.print("Y: ");
  Serial.println(y);

  Direction dir = getDirection(x,y);
  Wire.write(dir);
}

void loop()
{
  delay(100); // idk, saw it here https://www.arduino.cc/en/Tutorial/MasterReader
}
