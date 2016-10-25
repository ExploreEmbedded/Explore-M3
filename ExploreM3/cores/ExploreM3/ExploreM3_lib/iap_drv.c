#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "iap_drv.h"


flash_eeprom_st eepMem;

static const unsigned int flash_sector_addrs[] = {
    0x0000,    0x1000,    0x2000,    0x3000,
    0x4000,    0x5000,    0x6000,    0x7000,
    0x8000,    0x9000,    0xa000,    0xb000,
    0xc000,    0xd000,    0xe000,    0xf000,
    0x10000,    0x18000,    0x20000,    0x28000,
    0x30000,    0x38000,    0x40000,    0x48000,
    0x50000,    0x58000,    0x60000,    0x68000,
    0x70000,    0x78000
};

static const unsigned int flash_sector_sizes[] = {
    0x1000,    0x1000,    0x1000,    0x1000,
    0x1000,    0x1000,    0x1000,    0x1000,
    0x1000,    0x1000,    0x1000,    0x1000,
    0x1000,    0x1000,    0x1000,    0x1000,
    0x8000,    0x8000,    0x8000,    0x8000,
    0x8000,    0x8000,    0x8000,    0x8000,
    0x8000,    0x8000,    0x8000,    0x8000,
    0x8000,    0x8000
};

enum command_code{
    IAPCommand_Prepare_sector_for_write_operation = 50,
    IAPCommand_Copy_RAM_to_Flash,
    IAPCommand_Erase_sector,
    IAPCommand_Blank_check_sector,
    IAPCommand_Read_part_ID,
    IAPCommand_Read_Boot_Code_version,
    IAPCommand_Compare,
    IAPCommand_Reinvoke_ISP,
    IAPCommand_Read_device_serial_number
};


typedef void (*iap_entry_t)(unsigned int [], unsigned int []);

static iap_entry_t iap_entry = (iap_entry_t)0x1fff1ff1;

static int cclk_kHz = 0;
extern uint32_t SystemCoreClock;

void iap_init(void)
{
    cclk_kHz = SystemCoreClock/1000;
}

int iap_read_id(void)
{
    unsigned int cmd[5], res[5];
    cmd[0] = IAPCommand_Read_part_ID;
    iap_entry(cmd, res);
    return ((int)res[1]);
}

int iap_read_version(void)
{
    unsigned int cmd[5], res[5];
    cmd[0] = IAPCommand_Read_Boot_Code_version;
    iap_entry(cmd, res);
    return ((int)res[1]);    //NOTE: different from document UM10360, P635
}


int iap_read_serial(void)
{
    unsigned int cmd[5], res[5];
    cmd[0] = IAPCommand_Read_device_serial_number;
    iap_entry(cmd, res);
    return ((int)res[1]);
}

int iap_blank_check(unsigned int sector)
{
    unsigned int cmd[5], res[5];
    cmd[0] = IAPCommand_Blank_check_sector;
    cmd[1] = (unsigned int)sector;
    cmd[2] = (unsigned int)sector;
    iap_entry(cmd, res);
    return ((int)res[0]);
}

static int iap_prepare(unsigned int sector)
{
    unsigned int cmd[5], res[5];
    cmd[0] = IAPCommand_Prepare_sector_for_write_operation;
    cmd[1] = (unsigned int)sector;
    cmd[2] = (unsigned int)sector;
    iap_entry(cmd, res);
    if(res[0]){
        //printf("iap_prepare:result:%d\n",res[0]);
    }
    return ((int)res[0]);
}

int iap_erase(unsigned int sector)
{
    unsigned int cmd[5], res[5];
    iap_prepare(sector);
    cmd[0] = IAPCommand_Erase_sector;
    cmd[1] = (unsigned int)sector;
    cmd[2] = (unsigned int)sector;
    cmd[3] = cclk_kHz;
    iap_entry(cmd, res);
    if(res[0]){
        //printf("iap_erase:result:%d\n",res[0]);
    }
    while(iap_blank_check(sector)){
        ;
    }
    return ((int)res[0]);
}

static int iap_compare(unsigned int src_addr, unsigned int dest_addr, unsigned int size)
{
    unsigned int cmd[5], res[5];

    cmd[0] = IAPCommand_Compare;
    cmd[1] = (unsigned int)dest_addr;
    cmd[2] = (unsigned int)src_addr;
    cmd[3] = size;
    iap_entry(cmd, res);
    if(res[0]){
        //printf("\niap_compare(0x%x,0x%x,0x%x) result:%d,pos[0x%x]", src_addr, dest_addr, size, res[0],res[1]);
    }
    return ((int)res[0]);
}
int iap_write(unsigned int sector, unsigned int offset, 
        const void *buf, unsigned int size)
{
    unsigned int cmd[5], res[5];
    char wbuf[256]; // this buffer is to make 256byte boundary, according to IAP requirement
    unsigned int i;
    unsigned int dest_addr = flash_sector_addrs[sector] + offset;
    for(i = 0; i<size; i+=sizeof(wbuf)){
        unsigned int s = size-i;
        iap_prepare(sector);
        if (s>sizeof(wbuf)) s = sizeof(wbuf);
        memset(wbuf, 0, sizeof(wbuf));
        memcpy(wbuf, buf+i, s);
        cmd[0] = IAPCommand_Copy_RAM_to_Flash;
        cmd[1] = (unsigned int)dest_addr+i;
        cmd[2] = (unsigned int)wbuf;
        cmd[3] = sizeof(wbuf);
        cmd[4] = cclk_kHz;
        iap_entry(cmd, res);
        if(res[0]){
            //printf("cmd[%x,%x,%x], result:%d\n",cmd[1], cmd[2], cmd[3], res[0]);
        }
        if(iap_compare(dest_addr+i, (unsigned int)wbuf, sizeof(wbuf))){
            return -1;
        }
        if(memcmp((const void *)(dest_addr+i), wbuf, sizeof(wbuf))){
            //printf("iap_write failed\n");
            return -1;
        }
        if(res[0]) return (int)res[0];
    }
    return ((int)res[0]);
}

void *iap_get_ptr(unsigned int sector, unsigned int offset)
{
    unsigned int src_addr = flash_sector_addrs[sector] + offset;
    return (void *)src_addr;
}


int iap_read(unsigned int sector, unsigned int offset,
        void *buf, unsigned int size)
{
    memcpy(buf, iap_get_ptr(sector, offset), size);
    return 0;
}

int iap_copy(unsigned int dest_sector, unsigned int src_sector, 
        unsigned int offset, unsigned int size)
{
    unsigned int i;
    char buf[256];
    unsigned int s;
    for(i=0; i<size; i+= sizeof(buf)){
        s = sizeof(buf);
        if(i+s>size) s = size-i;
        iap_read(src_sector, offset+i, buf, s);
        iap_prepare(dest_sector);
        iap_write(dest_sector, offset+i, buf, s);
    }
    return 0;
}

int iap_cmp(unsigned int sector, unsigned int offset,
        const void *buf, unsigned int size)
{
    return memcmp(buf, iap_get_ptr(sector, offset), size);
}