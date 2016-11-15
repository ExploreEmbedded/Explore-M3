 #ifdef __cplusplus
extern "C" {
#endif

#ifndef _IAP_DRV_H_
#define _IAP_DRV_H_

#define EEMULATED_EEPROM_SIZE 4096

typedef struct
{
  char ResetString[8]; 
  volatile uint8_t fdata[EEMULATED_EEPROM_SIZE]; 
}flash_eeprom_st;

extern flash_eeprom_st eepMem;

#pragma once
void *iap_get_ptr(unsigned int sector, unsigned int offset);
int iap_read(unsigned int sector,unsigned int offset, void *buf,unsigned int size);
int iap_write(unsigned int sector,unsigned int offset, const void *buf,unsigned int size);
int iap_cmp(unsigned int sector, unsigned int offset, const void *buf, unsigned int size);
int iap_copy(unsigned int dest_sector, unsigned int src_sector, 
        unsigned int offset, unsigned int size);
int iap_erase(unsigned int sector);
int iap_blank_check(unsigned int sector);
int iap_read_serial(void);
int iap_read_version(void);
int iap_read_id(void);
void iap_init(void);

#endif

#ifdef __cplusplus
}
#endif