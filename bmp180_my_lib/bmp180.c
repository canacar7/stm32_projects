/*
 * bmp180.c
 *
 *  Created on: 13 Tem 2021
 *      Author: CAN AHMET ACAR
 */


#include "math.h"
#include "stm32f4xx_hal.h"


extern I2C_HandleTypeDef hi2c1;

//calib degerlerinin tanitilmasi
short AC1 = 0;
short AC2 = 0;
short AC3 = 0;
unsigned short AC4 = 0;
unsigned short AC5 = 0;
unsigned short AC6 = 0;
short B1  = 0;
short B2  = 0;
short MB  = 0;
short MC  = 0;
short MD  = 0;

//ut up ve gerekli parametre tanimlari
long UT   		 = 0;
short oss 		 = 0;
long UP  		 = 0;
long X1     	 = 0;
long X2  	     = 0;
long X3  	     = 0;
long B3   		 = 0;
long B5          = 0;
unsigned long B4 = 0;
long B6          = 0;
unsigned long B7 = 0;

//sicaklik ve basinc
long sicaklik = 0;
long basinc   = 0;

#define atmPress 101325

void BMP180_Init(){

	//deviceden baglanma sinyali alamassam alarm verir
	if(HAL_I2C_IsDeviceReady(&hi2c1, 0XEE, 1 , HAL_MAX_DELAY) != HAL_OK){
		while(1){
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
		HAL_Delay(300);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
		HAL_Delay(300);
		}}
	BMP180_KALIBRASYON_VERILERI();
}

void BMP180_KALIBRASYON_VERILERI(void)
{
	uint8_t  kalib_degerleri[22] = {0};
	uint16_t baslama_adresi      = 0xAA;

	HAL_I2C_Mem_Read(&hi2c1 , 0xEE , baslama_adresi, 1, kalib_degerleri , 22 , HAL_MAX_DELAY);

	//kalib degerlerini atamasini yapalim
	 AC1 = ((kalib_degerleri[0]  << 8)   | kalib_degerleri[1]);
	 AC2 = ((kalib_degerleri[2]  << 8)   | kalib_degerleri[3]);
	 AC3 = ((kalib_degerleri[4]  << 8)   | kalib_degerleri[5]);
	 AC4 = ((kalib_degerleri[6]  << 8)   | kalib_degerleri[7]);
	 AC5 = ((kalib_degerleri[8]  << 8)   | kalib_degerleri[9]);
	 AC6 = ((kalib_degerleri[10] << 8)   | kalib_degerleri[11]);
	 B1  = ((kalib_degerleri[12] << 8)   | kalib_degerleri[13]);
	 B2  = ((kalib_degerleri[14] << 8)   | kalib_degerleri[15]);
	 MB  = ((kalib_degerleri[16] << 8)   | kalib_degerleri[17]);
	 MC  = ((kalib_degerleri[18] << 8)   | kalib_degerleri[19]);
	 MD  = ((kalib_degerleri[20] << 8)   | kalib_degerleri[21]);
}

uint16_t BMP180_UT()
{

	uint8_t yazilacak_deger = 0x2E;
	uint8_t okunan_deger[2]= {0};

	HAL_I2C_Mem_Write(&hi2c1 , 0xEE , 0XF4, 1, &yazilacak_deger , 1 , HAL_MAX_DELAY);
	HAL_Delay(5);


	HAL_I2C_Mem_Read(&hi2c1 , 0xEE , 0xF6, 1, okunan_deger , 2 , HAL_MAX_DELAY);

	//ut degeri
	return ((okunan_deger[0] << 8) + okunan_deger[1]);

}

float BMP180_SICAKLIK (void)
{
	UT = BMP180_UT();
	X1 = ((UT-AC6) * (AC5/(pow(2,15))));
	X2 = ((MC*(pow(2,11))) / (X1+MD));
	B5 = X1+X2;
	sicaklik = (B5+8)/(pow(2,4));
	sicaklik = sicaklik * 0.1;
	return sicaklik;
}

uint32_t BMP180_UP(int oss)   // oversampling setting 0,1,2,3
{
	uint8_t yazilan_deger = 0x34+(oss<<6);
	uint8_t okunan_deger[3] = {0};
	HAL_I2C_Mem_Write(&hi2c1, 0xEE, 0xF4, 1, &yazilan_deger, 1, 1000);
	switch (oss)
	{
		case (0):
			HAL_Delay (5);
			break;
		case (1):
			HAL_Delay (8);
			break;
		case (2):
			HAL_Delay (14);
			break;
		case (3):
			HAL_Delay (26);
			break;
	}
	HAL_I2C_Mem_Read(&hi2c1, 0XEE, 0xF6, 1, okunan_deger, 3, 1000);
	return (((okunan_deger[0]<<16)+(okunan_deger[1]<<8)+okunan_deger[2]) >> (8-oss));
}

float BMP180_Basinc(int oss)
{
	UP = BMP180_UP(oss);
	X1 = ((UT-AC6) * (AC5/(pow(2,15))));
	X2 = ((MC*(pow(2,11))) / (X1+MD));
	B5 = X1+X2;
	B6 = B5-4000;
	X1 = (B2 * (B6*B6/(pow(2,12))))/(pow(2,11));
	X2 = AC2*B6/(pow(2,11));
	X3 = X1+X2;
	B3 = (((AC1*4+X3)<<oss)+2)/4;
	X1 = AC3*B6/pow(2,13);
	X2 = (B1 * (B6*B6/(pow(2,12))))/(pow(2,16));
	X3 = ((X1+X2)+2)/pow(2,2);
	B4 = AC4*(unsigned long)(X3+32768)/(pow(2,15));
	B7 = ((unsigned long)UP-B3)*(50000>>oss);
	if (B7<0x80000000) basinc = (B7*2)/B4;
	else basinc = (B7/B4)*2;
	X1 = (basinc/(pow(2,8)))*(basinc/(pow(2,8)));
	X1 = (X1*3038)/(pow(2,16));
	X2 = (-7357*basinc)/(pow(2,16));
	basinc = basinc + (X1+X2+3791)/(pow(2,4));

	return basinc;
}




float BMP180_Get_Alt (int oss)
{
	BMP180_Basinc(oss);
	return 44330*(1-(pow(((float)basinc/(float)atmPress), 0.19029495718)));
}













