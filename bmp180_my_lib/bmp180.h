/*
 * bmp180.h
 *
 *  Created on: 13 Tem 2021
 *      Author: CAN AHMET ACAR
 */

#ifndef SRC_BMP180_H_
#define SRC_BMP180_H_

#include "stm32f4xx_hal.h"

void BMP180_Init(void);
float BMP180_SICAKLIK(void);
float BMP180_Basinc (int oss);
float BMP180_Get_Alt (int oss);
uint32_t BMP180_UP(int oss);
uint16_t BMP180_UT(int oss);
void BMP180_KALIBRASYON_VERILERI(void);


#endif /* SRC_BMP180_H_ */
