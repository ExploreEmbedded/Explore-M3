 #ifdef __cplusplus
extern "C" {
#endif

#ifndef _EEPROM_H_
#define _EEPROM_H_
#include "stdutils.h"




class EEPROMClass
{
public:
    EEPROMClass();
    void begin();
    uint8_t read(int address);
    void write(int address, uint8_t val);
    uint8_t commit();
};

extern EEPROMClass EEPROM;


#endif


#ifdef __cplusplus
}
#endif