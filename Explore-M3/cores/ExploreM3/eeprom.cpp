#include "eeprom.h"
#include "Arduino.h"
#include "iap_drv.h"


uint8_t commitFlag=0;


EEPROMClass::EEPROMClass()
{
   begin();       
}

void EEPROMClass::begin()
{
   iap_init(); 
   iap_read(29,0,eepMem.ResetString,sizeof(eepMem));  
   commitFlag = 0;        
}


uint8_t EEPROMClass::read(int address)
{
  uint8_t retValue =0;
  if((address>=0x00) && (address<EEMULATED_EEPROM_SIZE))
  {
    retValue = eepMem.fdata[address];
  }  
  return retValue;
}


void EEPROMClass::write(int address, uint8_t val)
{
  if((address>=0x00) && (address<EEMULATED_EEPROM_SIZE))
  {
    if(eepMem.fdata[address] != val)
    {
     eepMem.fdata[address] = val;
     commitFlag = 1;
    }
  } 
}


uint8_t EEPROMClass::commit()
{
    if(commitFlag == 1)
    {
     iap_erase(29);
     iap_write(29,0,eepMem.ResetString,sizeof(eepMem));
     commitFlag = 0;
    }
}

EEPROMClass EEPROM;


