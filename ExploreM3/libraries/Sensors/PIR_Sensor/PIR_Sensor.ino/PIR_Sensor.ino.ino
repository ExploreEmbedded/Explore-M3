  #include "ST7565.h"
/* * //////////////////////////////////////////////////
 * //making sense of the Parallax PIR sensor's output
 * //////////////////////////////////////////////////
 *
 * Switches a LED according to the state of the sensors output pin.
 * Determines the beginning and end of continuous motion sequences.
 *
 * @author: Kristian Gohlke / krigoo (_) gmail (_) com / http://krx.at
 * @date:   3. September 2006 
 *
 * kr1 (cleft) 2006 
 * released under a creative commons "Attribution-NonCommercial-ShareAlike 2.0" license
 * http://creativecommons.org/licenses/by-nc-sa/2.0/de/
 *
 *
 * The Parallax PIR Sensor is an easy to use digital infrared motion sensor module. 
 * (http://www.parallax.com/detail.asp?product_id=555-28027)
 *
 * The sensor's output pin goes to HIGH if motion is present.
 * However, even if motion is present it goes to LOW from time to time, 
 * which might give the impression no motion is present. 
 * This program deals with this issue by ignoring LOW-phases shorter than a given time, 
 * assuming continuous motion is present during these phases.
 *  
 */

/////////////////////////////

//VARS
//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 30;        

//the time when the sensor outputs a low impulse
long unsigned int lowIn;         

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
long unsigned int pause = 5000;  

boolean lockLow = true;
boolean takeLowTime;  



int pirPin = 3;    //the digital pin connected to the PIR sensor's output
int ledPin = 13;


ST7565 glcd(29, 28, 27, 26, 25);

/////////////////////////////
//SETUP
void setup(){
  
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);

  glcd.begin(0x18);

  //give the sensor some time to calibrate
  glcd.drawstring(0, 0, " calibrating sensor " ); 
  glcd.display();     
    for(int i = 0; i < calibrationTime; i++){
      glcd.drawstring(0, 1, ".................." );      
      glcd.display();     
      delay(1000);
      }
      glcd.clear();
      glcd.drawstring(20, 0, " SENSOR ACTIVE " );
      glcd.display();
   
  }

////////////////////////////
//LOOP
void loop(){

     if(digitalRead(pirPin) == HIGH){
       digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
       if(lockLow){  
         //makes sure we wait for a transition to LOW before any further output is made:
         lockLow = false;
         glcd.drawstring(0, 2, " motion detected at " );         
         glcd.drawNumFloat(30,3,millis()/1000,2);         
         glcd.drawstring(60, 3, " Sec " );
         glcd.display();        
         delay(50);
         }         
         takeLowTime = true;
       }

     if(digitalRead(pirPin) == LOW){       
       digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state

       if(takeLowTime){
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
       //if the sensor is low for more than the given pause, 
       //we assume that no more motion is going to happen
       if(!lockLow && millis() - lowIn > pause){  
           //makes sure this block of code is only executed again after 
           //a new motion sequence has been detected
           lockLow = true;            
           
           glcd.drawstring(0, 5, " motion ended at " );
           glcd.drawNumFloat(30,6,(millis() - pause)/1000,2);
           //Serial.print((millis() - pause)/1000);
           glcd.drawstring(60, 6, " Sec " );
           glcd.display();
           delay(50);
           }
       }
  }
