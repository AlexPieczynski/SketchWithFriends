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
#define INTERRUPT_CLICK 2 // interrupt can use digital pins 2 or 3
#define SLAVE_ADDR 8 // these will probably need to be different for each slave

enum Direction
{
  north, neast, east, seast, south, swest, west, nwest, none
};

void setup()
{
  pinMode(STICKX, INPUT);
  pinMode(STICKY, INPUT);
  pinMode(INTERRUPT_CLICK, INPUT_PULLUP);
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDR);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_CLICK), joystickClicked, FALLING);
}

Direction getDirection(byte x, byte y)
{
  if (x == 1 && y == 1) {
    return none;
  } else if (x == 1 && y == 2) {
    return north;
  } else if (x == 2 && y == 2) {
    return neast;
  } else if (x == 2 && y == 1) {
    return east;
  } else if (x == 2 && y == 0) {
    return seast;
  } else if (x == 1 && y == 0) {
    return south;
  } else if (x == 0 && y == 0) {
    return swest;
  } else if (x == 0 && y == 1) {
    return west;
  } else if (x == 0 && y == 2) {
    return nwest;
  }
}

/**
 * This function executes whenever the master
 *  asks for input
 */
void requestEvent()
{
  byte x = map(analogRead(STICKX), 0, 1023, 0, 2);
  delay(1); // delay needed in between two analog reads, see https://www.arduino.cc/en/Tutorial/JoyStick
  byte y = map(analogRead(STICKY), 0, 1023, 0, 2);
  Serial.print("X: ");
  Serial.println(x);
  Serial.print("Y: ");
  Serial.println(y);

  Direction dir = getDirection(x,y);
  Wire.write(dir);
}

// custom mapping
byte cMap(int rawVal)
{
  if (rawVal < 400) {
    return 0;
  } else if (rawVal < 600) {
    return 1;
  } else {
    return 2;
  }
}

void joystickClicked()
{
  Serial.println("Clicked");
}

void loop()
{
  byte x = cMap(analogRead(STICKX));
  byte y = cMap(analogRead(STICKY));
  Direction dir = getDirection(x, y);
  Serial.println(dir);
  delay(100);
}
