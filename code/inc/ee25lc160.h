/**
  ******************************************************************************
  * @file    ee25lc160.h 
  * @author  Pablo Fuentes
	* @version V1.0.0
  * @date    2016
  * @brief   EEPROM 25LC160 Library
  ******************************************************************************
*/

#ifndef __EEPROM_25LC160_H
#define __EEPROM_25LC160_H

#include <stdint.h>
#include "eonOS.h"

typedef struct
{
  SPI_TypeDef *SPIx;
  pin_t cs;
} ee25lc160_t;

/** 
 ===============================================================================
              ##### Public functions #####
 ===============================================================================
 */

void ee25lc160_init(ee25lc160_t *ee);
void ee25lc160_write(ee25lc160_t *ee, uint32_t address, uint8_t data);
uint8_t ee25lc160_read(ee25lc160_t *ee, uint32_t address);

#endif