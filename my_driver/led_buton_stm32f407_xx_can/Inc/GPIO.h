/*
 * GPIO.h
 *
 *  Created on: 18 Tem 2021
 *      Author: CAN AHMET ACAR
 */


#ifndef INC_GPIO_H_
#define INC_GPIO_H_


#include <stm32f407xx_can.h>

/*-------------------------------------------------------------------------------------------------------------------------------------------*/
 /* @def_group GPIO_Pins*/
#define GPIO_PIN_0 					(uint16_t)(0x0001) /*gpıo 0 selected   */
#define GPIO_PIN_1					(uint16_t)(0x0002) /*gpıo 1 selected   */
#define GPIO_PIN_2 					(uint16_t)(0x0004) /*gpıo 2 selected   */
#define GPIO_PIN_3 					(uint16_t)(0x0008) /*gpıo 3 selected   */
#define GPIO_PIN_4 					(uint16_t)(0x0010) /*gpıo 4 selected   */
#define GPIO_PIN_5 					(uint16_t)(0x0020) /*gpıo 5 selected   */
#define GPIO_PIN_6 					(uint16_t)(0x0040) /*gpıo 6 selected   */
#define GPIO_PIN_7 					(uint16_t)(0x0080) /*gpıo 7 selected   */
#define GPIO_PIN_8 					(uint16_t)(0x0100) /*gpıo 8 selected   */
#define GPIO_PIN_9 					(uint16_t)(0x0200) /*gpıo 9 selected   */
#define GPIO_PIN_10 				(uint16_t)(0x0400) /*gpıo 10 selected  */
#define GPIO_PIN_11 				(uint16_t)(0x0800) /*gpıo 11 selected  */
#define GPIO_PIN_12					(uint16_t)(0x1000) /*gpıo 12 selected  */
#define GPIO_PIN_13					(uint16_t)(0x2000) /*gpıo 13 selected  */
#define GPIO_PIN_14					(uint16_t)(0x4000) /*gpıo 14 selected  */
#define GPIO_PIN_15 				(uint16_t)(0x8000) /*gpıo 15 selected  */
#define GPIO_PIN_ALL				(uint16_t)(0xFFFF) /*gpıo all selected */

/* @def_group GPIO_Mode*/
#define GPIO_MODE_INPUT				(0X0U)
#define GPIO_MODE_OUTPUT			(0X1U)
#define GPIO_MODE_ALTERNATE			(0X2U)
#define GPIO_MODE_ANALOG			(0X3U)

/* @def_group GPIO_Otype*/
#define GPIO_OTYPE_PP				(0X0U)
#define GPIO_OTYPE_OD				(0X1U)

/* @def_group GPIO_PuPd*/
#define GPIO_PUPD_NO_PULL_DOWN_UP 	(0X0U)
#define GPIO_PUPD_PULL_UP		 	(0X1U)
#define GPIO_PUPD_PULL_DOWN		 	(0X2U)

/* @def_group GPIO_OSpeed*/
#define GPIO_SPEED_YAVAS			(0X0U)
#define GPIO_SPEED_ORTA				(0X1U)
#define GPIO_SPEED_HIZLI			(0X2U)
#define GPIO_SPEED_YUKSEK			(0X3U)


/*-------------------------------------------------------------------------------------------------------------------------------------------*/

typedef struct
{


	uint32_t pinNumber;  /* gpıopin number @def_group GPIO_Pins   */
	uint32_t Mode;		 /* gpıopin number @def_group GPIO_Mode   */
	uint32_t Otype;		 /* gpıopin number @def_group GPIO_Otype  */
	uint32_t PuPd;       /* gpıopin number @def_group GPIO_PuPd   */
	uint32_t Speed;		 /* gpıopin number @def_group GPIO_OSpeed */
	uint32_t Alternate;
}GPIO_InitTypeDef_t;

/*-------------------------------------------------------------------------------------------------------------------------------------------*/


typedef enum
{

	GPIO_Pin_Reset   =  0x0U,
	GPIO_Pin_Set   	 =  !GPIO_Pin_Reset

}GPIO_Pin_State_t;
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
void GPIO_Init(GPIO_TypeDef_t *GPIO_x, GPIO_InitTypeDef_t *GPIO_InitStructure);

void GPIO_Write_Pin(GPIO_TypeDef_t *GPIO_x, uint16_t pinNumber, GPIO_Pin_State_t pinState);

GPIO_Pin_State_t GPIO_Read_Pin(GPIO_TypeDef_t *GPIO_x, uint16_t pinNumber);

void GPIO_Lock_Pin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber);

void GPIO_Toggle_Pin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber);
/*-------------------------------------------------------------------------------------------------------------------------------------------*/







#endif /* INC_GPIO_H_ */
