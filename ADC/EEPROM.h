#ifndef __EEPROM_H_
#define __EEPROM_H_

#include <STC15.h>
#define		EE_ADDRESS	0x8000
void	DisableEEPROM(void);
void EEPROM_read_n(u16 EE_address,u8 *DataAddress,u16 number);
void EEPROM_SectorErase(u16 EE_address);
void EEPROM_write_n(u16 EE_address,u8 *DataAddress,u16 number);

#endif