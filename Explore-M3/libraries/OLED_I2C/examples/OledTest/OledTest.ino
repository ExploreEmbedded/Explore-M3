// OLED_I2C_NumberFonts
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// A quick demo of how to use my OLED_I2C library.
//


#include <OLED_I2C.h>

OLED  myOLED(8, 9); //SDA->8,  SCL->9
extern uint8_t BigNumbers[];
uint8_t ledStatus=0;

void setup()
{
  myOLED.begin();
  myOLED.setFont(BigNumbers);
  
  for (int i=0; i<=1000; i++)
  {
    myOLED.printNumI(i, CENTER, 00);
    myOLED.update();
  }
  
  myOLED.printNumI(millis(), CENTER, 30); //Print the time taken to display 0-10000.
  myOLED.update();
  
  pinMode(12,OUTPUT);
}

void loop()
{
  digitalWrite(13,ledStatus);
  ledStatus = !ledStatus;      //Toggle the gpio pins without delay to measure the speed
}  