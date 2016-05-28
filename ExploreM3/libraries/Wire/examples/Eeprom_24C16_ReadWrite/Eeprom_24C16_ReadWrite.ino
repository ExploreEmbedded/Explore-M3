// --------------------------------------
// Eeprom 24C16 read/write demo
// This program reads the data from eeprom, increments and writes it back at same address
// Eeprom address is set to 0
// 24C16 device Id 0x50

#include <Wire.h>

#define EEPROM_ADDRESS   0
#define EEPROM_24C16_ID  0x50

void setup() 
{
  Wire.begin();
  Serial.begin(9600);
}

void loop() 
{
  byte num;
  
  // set the 24C16 eeprom address to 0
  Wire.beginTransmission(EEPROM_24C16_ID);
  Wire.write(EEPROM_ADDRESS);  // Set the read address
  Wire.endTransmission();
  
  // read 1 byte, from EEPROM_ADDRESS
  Wire.requestFrom(EEPROM_24C16_ID, 1);
  while(Wire.available()) {
    num = Wire.read();
  }
  Serial.print("num = ");
  Serial.println(num, DEC);

  // increment num
  num = num+1;
  
  // write "num" to 24C16 eeprom at address zero
  Wire.beginTransmission(EEPROM_24C16_ID);
  Wire.write(EEPROM_ADDRESS);    // address low byte
  Wire.write(num);  // any more write starts writing
  Wire.endTransmission();
  
  // next time loop runs, it should retrieve the
  // same number it wrote last time... even if you
  // shut off the power
  delay(500);
}
