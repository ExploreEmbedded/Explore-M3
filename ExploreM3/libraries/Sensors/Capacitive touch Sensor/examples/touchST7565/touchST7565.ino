#include "ST7565.h"

int ledPin =  13;    // LED connected to digital pin 13
int touch =  2;    // LED connected to digital pin 13

// the LCD backlight is connected up to a pin so you can turn it on & off
//#define BACKLIGHT_LED 10

// pin 9 - Serial data out (SID)
// pin 8 - Serial clock out (SCLK)
// pin 7 - Data/Command select (RS or A0)
// pin 6 - LCD reset (RST)
// pin 5 - LCD chip select (CS)
ST7565 glcd(29, 28, 27, 26, 25);

// The setup() method runs once, when the sketch starts
int touchstate = 0;
void setup()   {  

pinMode(2,INPUT);  
pinMode(13,OUTPUT);      

        // initialize and set the contrast to 0x18
  glcd.begin(0x18);   
  
  // draw a string at location (0,0)
  glcd.drawstring(0, 0, "      Welcome to        Explore Embedded");  
  glcd.display();  
}


void loop()                     
{

  touchstate = digitalRead(touch);
  
   
  if( touchstate != LOW )
  {
  glcd.drawstring(0, 6, " oopppss u did it!!!" );
  glcd.display(); 
  digitalWrite(ledPin,HIGH);
  
  }

  else
  {
  glcd.drawstring(0, 6, "  Don't touch me!!!" );
  glcd.display(); 
  delay(500);
  glcd.drawstring(0, 6, "                    " );
  glcd.display();     
  delay(600);
  digitalWrite(ledPin,LOW);
  }
  
}


