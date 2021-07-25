/*
 * RCC.h
 *
 *  Created on: 18 Tem 2021
 *      Author: can ahmet acar
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_

#include "stm32f407xx_can.h"

//GPIO PORTLARININ CLK LARINI AKTIF ETME
//ENABLE ISLEMI SET BIT ILE YAPILIR
//SET BIT REGISTER ADRESI VE HANGI ADRESDEKI PINI HIGH CEKECEKSEM O DEGER GONDERILIR
#define RCC_GPIOA_CLK_ENABLE()			do{ uint32_t  tempValue = 0; 								  \
											SET_BIT(RCC -> AHB1ENR, RCC_AHB1ENR_GPIOAEN);			  \
											tempValue = READ_BIT(RCC -> AHB1ENR, RCC_AHB1ENR_GPIOAEN);	 \
											UNUSED(tempValue); \
											}while(0)

#define RCC_GPIOB_CLK_ENABLE()			do{ uint32_t  tempValue = 0; 								  \
											SET_BIT(RCC -> AHB1ENR, RCC_AHB1ENR_GPIOBEN);			  \
											tempValue = READ_BIT(RCC -> AHB1ENR, RCC_AHB1ENR_GPIOBEN);	 \
											UNUSED(tempValue); \
											}while(0)

#define RCC_GPIOC_CLK_ENABLE()			do{ uint32_t  tempValue = 0; 								  \
											SET_BIT(RCC -> AHB1ENR, RCC_AHB1ENR_GPIOCEN);			  \
											tempValue = READ_BIT(RCC -> AHB1ENR, RCC_AHB1ENR_GPIOCEN);	 \
											UNUSED(tempValue); \
											}while(0)

#define RCC_GPIOD_CLK_ENABLE()			do{ uint32_t  tempValue = 0; 								  \
											SET_BIT(RCC -> AHB1ENR, RCC_AHB1ENR_GPIODEN);			  \
											tempValue = READ_BIT(RCC -> AHB1ENR, RCC_AHB1ENR_GPIODEN);	 \
											UNUSED(tempValue); \
											}while(0)

#define RCC_SYSCFG_CLK_ENABLE()			do{ uint32_t  tempValue = 0; 								     \
											SET_BIT(RCC -> APB2ENR, RCC_APB2ENR_SYSCFGEN);			     \
											tempValue = READ_BIT(RCC -> APB1ENR, RCC_APB2ENR_SYSCFGEN);	 \
											UNUSED(tempValue); \
											}while(0)



//GPIO PORTLARININ CLK LARINI PASIF ETME
#define RCC_GPIOA_CLK_DISABLE()				CLEAR_BIT(RCC -> AHB1ENR, RCC_AHB1ENR_GPIOAEN)
#define RCC_GPIOB_CLK_DISABLE()				CLEAR_BIT(RCC -> AHB1ENR, RCC_AHB1ENR_GPIOBEN)
#define RCC_GPIOC_CLK_DISABLE()				CLEAR_BIT(RCC -> AHB1ENR, RCC_AHB1ENR_GPIOCEN)
#define RCC_GPIOD_CLK_DISABLE()				CLEAR_BIT(RCC -> AHB1ENR, RCC_AHB1ENR_GPIODEN)
#define RCC_SYSCFG_CLK_DISABLE()			CLEAR_BIT(RCC -> APB2ENR, RCC_APB2ENR_SYSCFGEN)






#endif /* INC_RCC_H_ */
