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
#include "sketchwithfriends.h"

#define STICKX 1
#define STICKY 2
#define INTERRUPT_CLICK 2 // interrupt can use digital pins 2 or 3
#define SLAVE_ADDR 8 // these will probably need to be different for each slave

List* pointHistory;

List* initList () {
  Point startPoint;
  startPoint.x = 320/3; // 1/3rd length of screen
  startPoint.y = 240/2; // half height of screen
  
  Node* startNode = malloc(sizeof(Node));
  startNode->point = startPoint;
  startNode->next = NULL;
  
  List *l = malloc(sizeof(List));
  l->length = 0;
  l->head = startNode;

  return l;
}

void addPoint (Point p) {
  Node* head = pointHistory->head;
  Node* newNode = malloc(sizeof(Node));
  newNode->point = p;
  newNode->next = head;
  pointHistory->head = newNode;
}

Point getHeadPoint () {
  return pointHistory->head->point;
}

void setup()
{
  pointHistory = initList();
  pinMode(STICKX, INPUT);
  pinMode(STICKY, INPUT);
  pinMode(INTERRUPT_CLICK, INPUT_PULLUP);
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDR);
  Wire.onRequest(requestEvent);
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

Point getNextPoint (Direction dir) {
  Point lastPoint = getHeadPoint();

  switch(dir) {
    case north: lastPoint.y -= 1;
                break;
    case neast: lastPoint.y -= 1;
                lastPoint.x += 1;
                break;
    case east:  lastPoint.x += 1;
                break;
    case seast: lastPoint.y += 1;
                lastPoint.x += 1;
                break;
    case south: lastPoint.y += 1;
                break;
    case swest: lastPoint.y += 1;
                lastPoint.x -= 1;
                break;
    case west:  lastPoint.x -= 1;
                break;
    case nwest: lastPoint.y -= 1;
                lastPoint.x -= 1;
                break;
    default: break;
  }

  return lastPoint;
}

/**
 * This function executes whenever the master
 *  asks for input
 */
void requestEvent()
{
  byte x = cMap(analogRead(STICKX));
  delay(1); // delay needed in between two analog reads, see https://www.arduino.cc/en/Tutorial/JoyStick
  byte y = cMap(analogRead(STICKY));
  Serial.print("X: ");
  Serial.println(x);
  Serial.print("Y: ");
  Serial.println(y);

  Direction dir = getDirection(x,y);
  Point lastPoint = getHeadPoint();
  Point nextPoint = getNextPoint(dir);
  if (lastPoint.x != nextPoint.x || lastPoint.y != nextPoint.y) {
    addPoint(nextPoint);  
  }
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
  Node* runner = pointHistory->head;
  while (runner != NULL) {
    Point p = runner->point;
    Serial.println(p.x);
    runner = runner->next;
  }
}

void loop()
{
//  byte x = cMap(analogRead(STICKX));
//  byte y = cMap(analogRead(STICKY));
//  Direction dir = getDirection(x, y);
//  Serial.println(dir);
  delay(100);
}
