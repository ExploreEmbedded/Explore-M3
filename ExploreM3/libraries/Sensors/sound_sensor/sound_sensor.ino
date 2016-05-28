// Function: If the sound sensor senses a sound that is up to the threshold you set in the code, the LED is on for 200ms.
 
/*macro definitions of the sound sensor and the LED*/
#define SOUND_SENSOR A1
#define LED 3      // the number of the LED pin
unsigned int sensorTemp =0,i,sensorTemp1=0;
 
#define THRESHOLD_VALUE 350//The threshold level
void setup()
{
    Serial.begin(9600);
    pins_init();
}
 
void loop()
{
    
    for(i=0;i<10;i++)  // taken average from 10 value
    {
     int sensorValue = analogRead(SOUND_SENSOR);//use A1 to read the electrical signal  
     sensorTemp =+sensorValue;    
    }
    
    Serial.println(sensorTemp);
    sensorTemp1 =sensorTemp/10;
    
    
    Serial.print("sensorTemp1 ");
    Serial.println(sensorTemp1);
    if(sensorTemp1 > THRESHOLD_VALUE)
    {
        turnOnLED();//if the value read from A0 is larger than 400,then light the LED
        delay(200);
    }
    turnOffLED();
}
 
void pins_init()
{
    pinMode(LED, OUTPUT);
    pinMode(SOUND_SENSOR, INPUT);
}
void turnOnLED()
{
    digitalWrite(LED,HIGH);
}
void turnOffLED()
{
    digitalWrite(LED,LOW);
}
