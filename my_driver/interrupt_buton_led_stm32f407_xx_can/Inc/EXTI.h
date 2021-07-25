/*
 * EXTI.h
 *
 *  Created on: 24 Tem 2021
 *      Author: CAN AHMET ACAR
 */

#ifndef INC_EXTI_H_
#define INC_EXTI_H_

#include "stm32f407xx_can.h"


/*-------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 *@def group PORT SOURCE
 */
#define EXTI_PortSource_GPIOA  			(uint8_t)(0x0)
#define EXTI_PortSource_GPIOB  			(uint8_t)(0x1)
#define EXTI_PortSource_GPIOC 			(uint8_t)(0x2)
#define EXTI_PortSource_GPIOD 			(uint8_t)(0x3)
#define EXTI_PortSource_GPIOE  			(uint8_t)(0x4)
#define EXTI_PortSource_GPIOF  			(uint8_t)(0x5)
#define EXTI_PortSource_GPIOG  			(uint8_t)(0x6)
#define EXTI_PortSource_GPIOH  			(uint8_t)(0x7)
#define EXTI_PortSource_GPIOI 			(uint8_t)(0x8)
#define EXTI_PortSource_GPIOJ 			(uint8_t)(0xA)
#define EXTI_PortSource_GPIOK 			(uint8_t)(0xB)


/*
 *@def group LINE SOURCE
 */
#define EXTI_LineSource_Pin0			(uint8_t)(0x0)
#define EXTI_LineSource_Pin1			(uint8_t)(0x1)
#define EXTI_LineSource_Pin2			(uint8_t)(0x2)
#define EXTI_LineSource_Pin3			(uint8_t)(0x3)
#define EXTI_LineSource_Pin4			(uint8_t)(0x4)
#define EXTI_LineSource_Pin5			(uint8_t)(0x5)
#define EXTI_LineSource_Pin6			(uint8_t)(0x6)
#define EXTI_LineSource_Pin7			(uint8_t)(0x7)
#define EXTI_LineSource_Pin8			(uint8_t)(0x8)
#define EXTI_LineSource_Pin9			(uint8_t)(0x9)
#define EXTI_LineSource_Pin10			(uint8_t)(0xA)
#define EXTI_LineSource_Pin11			(uint8_t)(0xB)
#define EXTI_LineSource_Pin12			(uint8_t)(0xC)
#define EXTI_LineSource_Pin13			(uint8_t)(0xD)
#define EXTI_LineSource_Pin14			(uint8_t)(0xE)
#define EXTI_LineSource_Pin15			(uint8_t)(0xF)

/*
 * @def group EXTI MODE
 */
#define EXTI_Interrupt_Mode 			(uint8_t)(0x00U)
#define EXTI_Event_Mode 			   	(uint8_t)(0x04U)

/*
 * @def group EXTI Trigger Mode
 */
#define EXTI_Trigger_Rising_Edge 				(uint8_t)(0x08U)
#define EXTI_Trigger_Falling_Edge 				(uint8_t)(0x0CU)
#define EXTI_Trigger_Rising_Falling_Edge 		(uint8_t)(0x10U)
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
typedef struct
{
	uint8_t EXTI_LineNumber;				/*@def group LINE SOURCE 			*/
	uint8_t TriggerSelect;					/*@def group EXTI Trigger Mode			*/
	uint8_t EXTI_Mode;						/*@def group EXTI Mode 				*/
	FunctionalState_t EXTI_LineCmd;			/* mask or unmask the line number   */

}EXTI_InitTypeDef_t;
/*-------------------------------------------------------------------------------------------------------------------------------------------*/



void EXTI_LineConfig(uint8_t EXTI_PortSource, uint8_t EXTI_LineSource);

void EXTI_Init(EXTI_InitTypeDef_t *EXTI_InitStructure);

void NVIC_EnableInterrupt(NVIC_InitTypeDef_t IRQNumber);

#endif /* INC_EXTI_H_ */
