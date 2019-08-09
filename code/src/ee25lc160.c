/**
  ******************************************************************************
  * @file    eeprom_25lc160.c 
  * @author  Pablo Fuentes
	* @version V1.0.1
  * @date    2019
  * @brief   EEPROM 25LC160 Functions
  ******************************************************************************
*/

#include "ee25lc160.h"

/** 
 ===============================================================================
              ##### Definitions #####
 ===============================================================================
 */

#define EEPROM_25LC160_Select() gpio_reset(ee->cs)
#define EEPROM_25LC160_Deselect() gpio_set(ee->cs)

/* Registros de la EEPROM */
#define EEPROM_25LC160_REG_READ 0x03  //Read data from memory array beginning at selected address
#define EEPROM_25LC160_REG_WRITE 0x02 //Write data to memory array beginning at selected address
#define EEPROM_25LC160_REG_WREN 0x06  //Set the write enable latch (enable write operations)
#define EEPROM_25LC160_REG_WRDI 0x04  //Reset the write enable latch (disable write operations)
#define EEPROM_25LC160_REG_RDSR 0x05  //Read STATUS register
#define EEPROM_25LC160_REG_WRSR 0x01  //Write STATUS register
#define EEPROM_25LC160_REG_PE 0x42    //Page Erase � erase one page in memory array
#define EEPROM_25LC160_REG_SE 0xD8    //Sector Erase � erase one sector in memory array
#define EEPROM_25LC160_REG_CE 0xC7    //Chip Erase � erase all sectors in memory array
#define EEPROM_25LC160_REG_RDID 0xAB  //Release from Deep power-down and read electronic signature
#define EEPROM_25LC160_REG_DPD 0xB9   //Deep Power-Down mode

/** 
 ===============================================================================
              ##### Public functions #####
 ===============================================================================
 */

static void wait_eeprom_ready(ee25lc160_t *ee)
{
  EEPROM_25LC160_Select();
  spi_write8(ee->SPIx, EEPROM_25LC160_REG_RDSR);
  while ((spi_read8(ee->SPIx) & 0x01) != 0)
    ;
  EEPROM_25LC160_Deselect();
}

void ee25lc160_init(ee25lc160_t *ee)
{
  gpio_mode(ee->cs, OUTPUT_PP, NOPULL, SPEED_HIGH);
  EEPROM_25LC160_Deselect();
}

void ee25lc160_write(ee25lc160_t *ee, uint32_t address, uint8_t data)
{

  wait_eeprom_ready(ee);

  EEPROM_25LC160_Select();
  spi_write8(ee->SPIx, EEPROM_25LC160_REG_WREN);
  EEPROM_25LC160_Deselect();

  EEPROM_25LC160_Select();
  spi_write8(ee->SPIx, EEPROM_25LC160_REG_WRITE);
  spi_write8(ee->SPIx, (uint8_t)(address >> 8));
  spi_write8(ee->SPIx, (uint8_t)address);
  spi_write8(ee->SPIx, (uint8_t)data);
  EEPROM_25LC160_Deselect();
}

uint8_t ee25lc160_read(ee25lc160_t *ee, uint32_t address)
{
  uint8_t data = 0;

  wait_eeprom_ready(ee);

  EEPROM_25LC160_Select();
  spi_write8(ee->SPIx, EEPROM_25LC160_REG_READ);
  spi_write8(ee->SPIx, (uint8_t)(address >> 8));
  spi_write8(ee->SPIx, (uint8_t)address);
  data = (uint8_t)spi_read8(ee->SPIx);
  EEPROM_25LC160_Deselect();

  return (data);
}