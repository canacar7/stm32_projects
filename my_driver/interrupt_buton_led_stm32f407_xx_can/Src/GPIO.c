/*
 * GPIO.c
 *
 *  Created on: 18 Tem 2021
 *      Author: CAN AHMET ACAR
 */

#include "GPIO.h"
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief 	 GPIO_Init, configuration the pin of the GPIO_x port
 *
 * @param	 GPIO_x = GPIO PORT BASE ADRESS
 *
 * @param 	 GPIO_InitTypeDef  	Options of Configuration
 *
 * @ret_val  void
 *
 */

void GPIO_Init(GPIO_TypeDef_t *GPIO_x, GPIO_InitTypeDef_t *GPIO_InitStructure){

	/*position kontrolu ile pinleri gercek degerlerine indirgeme yapilacak ve pin degerlerine gore register islemleri yapilacak */
	uint32_t pozisyon;
	uint32_t fakepozisyon = 0;
	uint32_t sonpozisyon = 0;

	for(pozisyon = 0; pozisyon < 16; pozisyon++){

		fakepozisyon = (0x1U << pozisyon);
		sonpozisyon  = (uint32_t)(GPIO_InitStructure -> pinNumber) & (fakepozisyon);


		if(fakepozisyon == sonpozisyon)
		{
			/*MODER Register */
			uint32_t tempValue  =  GPIO_x -> MODER;
			tempValue 		   &= ~(0X3U << (pozisyon * 2));
			tempValue		   |= (GPIO_InitStructure -> Mode << (pozisyon * 2));
			GPIO_x -> MODER     =  tempValue;



			/*OTYPER VE OSPEED REGLERI */
			/*bu registerlar analog ve input da onemsizdir */
			if(GPIO_InitStructure -> Mode == GPIO_MODE_OUTPUT || GPIO_MODE_ALTERNATE)
			{
				/*Otyper Register */
				tempValue		  =  GPIO_x -> OTYPER;
				tempValue 		 &= ~(0X1U << pozisyon);
				tempValue		 |= (GPIO_InitStructure -> Otype << pozisyon);
				GPIO_x -> OTYPER  = tempValue;

				/*Ospeed Register */
				tempValue		 = GPIO_x -> OSPEEDR;
				tempValue 		&= ~(0X3U << (pozisyon * 2));
				tempValue 		|= (GPIO_InitStructure -> Speed << (pozisyon * 2));
				GPIO_x ->OSPEEDR = tempValue;

			}


			/*PUPDR Register */
			tempValue		    = GPIO_x -> PUPDR;
			tempValue 		   &= ~(0X3U << (pozisyon * 2));
			tempValue		   |= (GPIO_InitStructure -> PuPd << (pozisyon * 2));
			GPIO_x ->PUPDR      = tempValue;


		}
	}


}


/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief 	 GPIO_Write, write the pin of the GPIO_x port
 *
 * @param	 GPIO_x = GPIO PORT BASE ADRESS
 *
 * @param 	 pinNumber = GPIO_PIN_0 --------- 15
 *
 * @param 	 GPIO_Pin_State_t = GPIO_Pin_Reset / GPIO_Pin_Set
 *
 * @ret_val  void
 *
 */
void GPIO_Write_Pin(GPIO_TypeDef_t *GPIO_x, uint16_t pinNumber, GPIO_Pin_State_t pinState)
{


	  if( pinState == GPIO_Pin_Set)
	  {
		  GPIO_x ->BSRR = pinNumber;

	  }
	  else
	  {
		  GPIO_x ->BSRR = (pinNumber << 16U);

	  }
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 	 GPIO_ReadPin, reads the pin of the GPIO_x port
 *
 * @param 	 GPIO_x = GPIO PORT BASE ADRESS
 *
 * @param 	 pinNumber = GPIO_PIN_0 --------- 15
 *
 * @ret_val  GPIO_Pin_State_t  = GPIO_Pin_Reset / GPIO_Pin_Set
 */

GPIO_Pin_State_t GPIO_Read_Pin(GPIO_TypeDef_t *GPIO_x, uint16_t pinNumber){

	GPIO_Pin_State_t bitStatus = GPIO_Pin_Reset;

	if((GPIO_x -> IDR & pinNumber ) != GPIO_Pin_Reset){
		bitStatus = GPIO_Pin_Set;
	}

	return bitStatus;

}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief 	 GPIO_Lock_Pin, lock the pin of the GPIO_x port
 *
 * @param 	 GPIO_x = GPIO PORT BASE ADRESS
 *
 * @param 	 pinNumber = GPIO_PIN_0 --------- 15
 *
 * @ret_val  void
 */

void GPIO_Lock_Pin(GPIO_TypeDef_t *GPIO_x, uint16_t pinNumber)
{

		uint32_t tempValue = ((0x01U << 16U) | pinNumber );
		/* 4 ADIMDA YAPILCAK */
		GPIO_x -> LCKR     = tempValue; 			/* WR LCKR[16] = ‘1’ + LCKR[15:0] */
		GPIO_x -> LCKR 	   = pinNumber,				/* WR LCKR[16] = ‘0’ + LCKR[15:0] */
		GPIO_x -> LCKR     = tempValue; 			/* WR LCKR[16] = ‘1’ + LCKR[15:0] */
		tempValue 		   = GPIO_x -> LCKR;		/*read register					  */
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief 	 GPIO_Toggle_Pin, toggle the pin of the GPIO_x port
 *
 * @param 	 GPIO_x = GPIO PORT BASE ADRESS
 *
 * @param 	 pinNumber = GPIO_PIN_0 --------- 15
 *
 * @ret_val  void
 */


void GPIO_Toggle_Pin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber){

	uint32_t tempODRregister = GPIOx -> ODR;
	GPIOx -> BSRR            = ((tempODRregister & pinNumber) << 16U)  | (~tempODRregister & pinNumber);

	/*
	1101 0000 0000 0000 ---- aktif pinler
	1110 0000 0000 0000 ---- toggle icin pinler
	0011 0000 0000 0000 ---- sonuc ---- toggle fonksiyonuna giren pinler
	*/
	/*
	 * tempODRregister & pinNumber << 16U  --- set durumundaki pinler bulunur ve reset edilir
	 *
	 * ~tempODRregister & pinNumber         --- reset durumundaki pinler bulunur ve set edilir
	 */

}



