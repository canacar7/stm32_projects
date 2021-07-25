/*
 * stm32f407xx.h
 *
 *  Created on: Jul 16, 2021
 *      Author: CAN AHMET ACAR
 */

#ifndef INC_STM32F407XX_CAN_H_
#define INC_STM32F407XX_CAN_H_
/*-------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdint.h> //uint veritürlerigibi türleri acmak icindir
#include <string.h>
/*-------------------------------------------------------------------------------------------------------------------------------------------*/

#define	_IO volatile
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
typedef enum
{
	DISABLE = 0X0U,
	ENABLE  = !DISABLE

}FunctionalState_t;
/*-------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * arm m4's adress define
 */
/*pointer olarak tanimlandi!!! */
#define  NVIC_ISER_0				((uint32_t *)(0xE000E100))



/*-------------------------------------------------------------------------------------------------------------------------------------------*/

/*bitlere yazi yazmak okumak sifirlamak icin yazildi */
#define SET_BIT(REG, BIT) 	 ((REG) |=  (BIT))
#define CLEAR_BIT(REG, BIT)  ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)   ((REG) &   (BIT))
#define UNUSED(x)			 (void)x
/*-------------------------------------------------------------------------------------------------------------------------------------------*/


/*
 * MEMORY ADRESLERI TANIMLANDI
 *
 */
/*-------------------------------------------------------------------------------------------------------------------------------------------*/


#define FLASH_BASE_ADDR   (0X08000000UL) /*flash memory base adress (up to 1MB)*/
#define	SRAM1_BASE_ADDR	  (0X20000000UL) /*112KB SRAM1 */
#define	SRAM2_BASE_ADDR	  (0X2001C000UL) /* 16KB SRAM2, 112KB * 1024 -------- 1 C000 */


/*
 * PERIPHERAL ADRESLERI TANIMLANDI
 *
 */
/*-------------------------------------------------------------------------------------------------------------------------------------------*/



#define PERIPH_BASE_ADDR 		(0x40000000UL) 						/* BUTUN REGISTERLARIN BASLANGINC ADRESI*/

#define APB1_BASE_ADDR			(PERIPH_BASE_ADDR) 				    /* APB1 BUS DOMAIN BASE ADRESI 			*/
#define APB2_BASE_ADDR			(PERIPH_BASE_ADDR + 0X00010000UL)	/* APB2 BUS DOMAIN BASE ADRESI 			*/
#define AHB1_BASE_ADDR			(PERIPH_BASE_ADDR + 0X00020000UL)	/* AHB1 BUS DOMAIN BASE ADRESI 			*/
#define AHB2_BASE_ADDR			(PERIPH_BASE_ADDR + 0X10000000UL) 	/* AHB2 BUS DOMAIN BASE ADRESI 			*/



/*
 * APB1 FAZ HATTINA BAGLI OLAN CEVRESEL BIRIMLER
 */
#define TIM2_BASE_ADDR						(APB1_BASE_ADDR)					/* TIM 2 BASE ADRESI	    */
#define TIM3_BASE_ADDR						(APB1_BASE_ADDR + 0x00000400UL)		/* TIM 3 BASE ADRESI 	    */
#define TIM4_BASE_ADDR						(APB1_BASE_ADDR + 0x00000800UL)		/* TIM 4 BASE ADRESI 	    */
#define TIM5_BASE_ADDR						(APB1_BASE_ADDR + 0x00000C00UL)		/* TIM 5 BASE ADRESI  	    */
#define TIM6_BASE_ADDR						(APB1_BASE_ADDR + 0x00001000UL)		/* TIM 6 BASE ADRESI		*/
#define TIM7_BASE_ADDR						(APB1_BASE_ADDR + 0x00001400UL)		/* TIM 7 BASE ADRESI  		*/

#define SPI2_BASE_ADDR						(APB1_BASE_ADDR + 0x00003800UL)		/* SPI2 BASE ADRESI  		*/
#define SPI3_BASE_ADDR						(APB1_BASE_ADDR + 0x00003C00UL)		/* SPI3 BASE ADRESI	    	*/

#define USART2_BASE_ADDR					(APB1_BASE_ADDR + 0x00004400UL)		/* USART2 BASE ADRESI	    */
#define USART3_BASE_ADDR					(APB1_BASE_ADDR + 0x00004800UL)		/* USART2 BASE ADRESI	    */
#define UART4_BASE_ADDR						(APB1_BASE_ADDR + 0x00004C00UL)		/* UART4 BASE ADRESI	    */
#define UART5_BASE_ADDR						(APB1_BASE_ADDR + 0x00005000UL)		/* UART5 BASE ADRESI	    */

#define I2C1_BASE_ADDR					    (APB1_BASE_ADDR + 0x00005400UL)		/* I2C1 BASE ADRESI	   		*/
#define I2C2_BASE_ADDR					    (APB1_BASE_ADDR + 0x00005800UL)		/* I2C2 BASE ADRESI	   	    */
#define I2C3_BASE_ADDR					    (APB1_BASE_ADDR + 0x00005C00UL)		/* I2C3 BASE ADRESI	        */
/* eksik tanimlamalar mevcuttur kullanicak registerlar eklendi */



/*
 * APB2 FAZ HATTINA BAGLI OLAN CEVRESEL BIRIMLER
 */
#define TIM1_BASE_ADDR						(APB2_BASE_ADDR)					/* TIM 1 BASE ADRESI	    */
#define TIM8_BASE_ADDR						(APB2_BASE_ADDR + 0x00000400UL)		/* TIM 8 BASE ADRESI 	    */

#define USART1_BASE_ADDR					(APB2_BASE_ADDR + 0x00001000UL)		/* USART1 BASE ADRESI	    */
#define USART6_BASE_ADDR					(APB2_BASE_ADDR + 0x00001400UL)		/* USART6 BASE ADRESI	    */

#define ADC_BASE_ADDR						(APB2_BASE_ADDR + 0x00002000UL)		/* ADC BASE ADRESI	   		 */


#define SPI1_BASE_ADDR						(APB2_BASE_ADDR + 0x00003000UL)		/* SPI1 BASE ADRESI	   		 */
#define SPI4_BASE_ADDR						(APB2_BASE_ADDR + 0x00003400UL)		/* SPI4 BASE ADRESI	   		 */

#define SYSCFG_BASE_ADDR					(APB2_BASE_ADDR + 0x00003800UL)		/* SYSCFG BASE ADRESI	   	 */
#define EXTI_BASE_ADDR				    	(APB2_BASE_ADDR + 0x00003C00UL)		/* EXTI BASE ADRESI	   		 */
 /* eksik tanimlamalar mevcuttur kullanicak registerlar eklendi */


/*
 * AHB1 FAZ HATTINA BAGLI OLAN CEVRESEL BIRIMLER
 */

#define GPIOA_BASE_ADDR				   		 (AHB1_BASE_ADDR)					/* GPIOA BASE ADRESI	   	*/
#define GPIOB_BASE_ADDR				   		 (AHB1_BASE_ADDR + 0X00000400UL)		/* GPIOB BASE ADRESI	   	*/
#define GPIOC_BASE_ADDR				   		 (AHB1_BASE_ADDR + 0X00000800UL)		/* GPIOC BASE ADRESI	   	*/
#define GPIOD_BASE_ADDR				   		 (AHB1_BASE_ADDR + 0X00000C00UL)		/* GPIOD BASE ADRESI	   	*/
#define GPIOE_BASE_ADDR				  	 	 (AHB1_BASE_ADDR + 0X00001000UL)		/* GPIOE BASE ADRESI	   	*/
#define GPIOF_BASE_ADDR				   		 (AHB1_BASE_ADDR + 0X00001400UL)		/* GPIOF BASE ADRESI	   	*/
#define GPIOG_BASE_ADDR			    		 (AHB1_BASE_ADDR + 0X00001800UL)		/* GPIOG BASE ADRESI	   	*/
#define GPIOH_BASE_ADDR			    		 (AHB1_BASE_ADDR + 0X00001C00UL)		/* GPIOH BASE ADRESI	   	*/
#define GPIOI_BASE_ADDR			    		 (AHB1_BASE_ADDR + 0X00002000UL)		/* GPIOI BASE ADRESI	   	*/
#define GPIOJ_BASE_ADDR			    		 (AHB1_BASE_ADDR + 0X00002400UL)		/* GPIOJ BASE ADRESI	   	*/
#define GPIOK_BASE_ADDR			    		 (AHB1_BASE_ADDR + 0X00002800UL)		/* GPIOK BASE ADRESI	   	*/

#define RCC_BASE_ADDR						 (AHB1_BASE_ADDR + 0X00003800UL)		/* RCC BASE ADRESI	 	  	*/


/*-------------------------------------------------------------------------------------------------------------------------------------------*/

typedef enum
{
	 EXTI0_IRQNumber = 6,				/*IRQNumber Values for EXTI0 												 */
	 EXTI1_IRQNumber = 7,				/*IRQNumber Values for EXTI1 												 */
	 EXTI2_IRQNumber = 8,				/*IRQNumber Values for EXTI2 												 */
	 EXTI3_IRQNumber = 9				/*IRQNumber Values for EXTI3 												 */


}NVIC_InitTypeDef_t;

typedef struct
{
	 _IO uint32_t MODER;				/*GPIO port mode register        					Address offset: 0x00 	 */
	 _IO uint32_t OTYPER;				/*GPIO port output type register   					Address offset: 0x04	 */
	 _IO uint32_t OSPEEDR;				/*GPIO port output speed register					Address offset: 0x08   	 */
	 _IO uint32_t PUPDR;				/*GPIO port pull-up/pull-down register				Address offset: 0x0C     */
	 _IO uint32_t IDR;					/*GPIO port input data register						Address offset: 0x10	 */
	 _IO uint32_t ODR;					/*GPIO port output data register					Address offset: 0x14	 */
	 _IO uint32_t BSRR;					/*GPIO port bit set/reset register					Address offset: 0x18	 */
	 _IO uint32_t LCKR;					/*GPIO port configuration lock register 			Address offset: 0x1C	 */
	 _IO uint32_t AFR[2];				/*GPIO alternate function register 					Address offset: 0x20	 */

}GPIO_TypeDef_t;


typedef struct
{
	 _IO uint32_t CR;						/* clock control register 	     */
	 _IO uint32_t PLLCFGR;					/*PLL configuration register     */
	 _IO uint32_t CFGR;						/*clock configuration register   */
	 _IO uint32_t CIR;						/*clock interrupt register       */
	 _IO uint32_t AHB1RST;					/*AHB1 peripheral reset register */
	 _IO uint32_t AHB2RST;					/*AHB2 peripheral reset register */
	 _IO uint32_t AHB3RST;					/*AHB3 peripheral reset register */
	 _IO uint32_t Reserved0;				/*PLL configuration register */
	 _IO uint32_t APB1RSTR;					/*PLL configuration register */
	 _IO uint32_t APB2RSTR;					/*PLL configuration register */
	 _IO uint32_t Reserved1[2];				/*PLL configuration register */
	 _IO uint32_t AHB1ENR;					/*PLL configuration register */
	 _IO uint32_t AHB2ENR;					/*PLL configuration register */
	 _IO uint32_t AHB3ENR;					/*PLL configuration register */
	 _IO uint32_t Reserved2;				/*PLL configuration register */
	 _IO uint32_t APB1ENR;					/*PLL configuration register */
	 _IO uint32_t APB2ENR;					/*PLL configuration register */
	 _IO uint32_t Reserved3[2];				/*PLL configuration register */
	 _IO uint32_t AHB1LPENR;				/*PLL configuration register */
	 _IO uint32_t AHB2LPENR;				/*PLL configuration register */
	 _IO uint32_t AHB3LPENR;				/*PLL configuration register */
	 _IO uint32_t Reserved4;				/*PLL configuration register */
	 _IO uint32_t APB1LPENR;				/*PLL configuration register */
	 _IO uint32_t APB2LPENR;				/*PLL configuration register */
	 _IO uint32_t Reserved5[2];				/*PLL configuration register */
	 _IO uint32_t BDCR;						/*PLL configuration register */
	 _IO uint32_t CSR;						/*PLL configuration register */
	 _IO uint32_t Reserved6[2];				/*PLL configuration register */
	 _IO uint32_t SSCGR;					/*PLL configuration register */
	 _IO uint32_t PLLI2SCFGR;				/*PLL configuration register */

}RCC_TypeDef_t;


typedef struct {


	 _IO uint32_t MEMRMP;					/*SYSCFG memory remap register 						*/
	 _IO uint32_t PMC;						/*SYSCFG peripheral mode configuration register 	*/
	 _IO uint32_t EXTICR[4];				/*SYSCFG external interrupt configuration register  */
	 _IO uint32_t CMPCR;					/*Compensation cell control register                */


}SYSCFG_TypeDef_t;


typedef struct {


	 _IO uint32_t IMR;					/*Interrupt mask register  							*/
	 _IO uint32_t EMR;					/*Event mask register								*/
	 _IO uint32_t RTSR;					/*Rising trigger selection register 			    */
	 _IO uint32_t FTSR;					/*Falling trigger selection register                */
	 _IO uint32_t SWIER;				/*Software interrupt event register            	    */
	 _IO uint32_t PR;					/*Pending register              					*/


}EXTI_TypeDef_t;
/*-------------------------------------------------------------------------------------------------------------------------------------------*/

#define GPIOA								((GPIO_TypeDef_t *)(GPIOA_BASE_ADDR))
#define GPIOB								((GPIO_TypeDef_t *)(GPIOB_BASE_ADDR))
#define GPIOC								((GPIO_TypeDef_t *)(GPIOC_BASE_ADDR))
#define GPIOD								((GPIO_TypeDef_t *)(GPIOD_BASE_ADDR))
#define GPIOE								((GPIO_TypeDef_t *)(GPIOE_BASE_ADDR))
#define GPIOF								((GPIO_TypeDef_t *)(GPIOF_BASE_ADDR))
#define GPIOG								((GPIO_TypeDef_t *)(GPIOG_BASE_ADDR))
#define GPIOH								((GPIO_TypeDef_t *)(GPIOH_BASE_ADDR))
#define GPIOI								((GPIO_TypeDef_t *)(GPIOI_BASE_ADDR))
#define GPIOJ								((GPIO_TypeDef_t *)(GPIOJ_BASE_ADDR))
#define GPIOK								((GPIO_TypeDef_t *)(GPIOK_BASE_ADDR))

#define RCC									((RCC_TypeDef_t *)(RCC_BASE_ADDR))

#define SYSCFG								((SYSCFG_TypeDef_t *)(SYSCFG_BASE_ADDR))

#define EXTI								((EXTI_TypeDef_t *)(EXTI_BASE_ADDR))
/*-------------------------------------------------------------------------------------------------------------------------------------------*/


/*ENABLE & DISABLE*/
/* gpıo a clk hattı icin */
#define RCC_AHB1ENR_GPIOAEN_Pos				((0U))									/*BİT POSİTİON*/
#define RCC_AHB1ENR_GPIOAEN_Msk				((0x1 << RCC_AHB1ENR_GPIOAEN_Pos))
#define RCC_AHB1ENR_GPIOAEN					(RCC_AHB1ENR_GPIOAEN_Msk)

/* gpıo b clk hattı icin */
#define RCC_AHB1ENR_GPIOBEN_Pos				((1U))									/*BİT POSİTİON*/
#define RCC_AHB1ENR_GPIOBEN_Msk				((0x1 << RCC_AHB1ENR_GPIOBEN_Pos))
#define RCC_AHB1ENR_GPIOBEN					(RCC_AHB1ENR_GPIOBEN_Msk)

/* gpıo c clk hattı icin */
#define RCC_AHB1ENR_GPIOCEN_Pos				((2U))									/*BİT POSİTİON*/
#define RCC_AHB1ENR_GPIOCEN_Msk				((0x1 << RCC_AHB1ENR_GPIOCEN_Pos))
#define RCC_AHB1ENR_GPIOCEN					(RCC_AHB1ENR_GPIOCEN_Msk)

/* gpıo d clk hattı icin */
#define RCC_AHB1ENR_GPIODEN_Pos				((3U))									/*BİT POSİTİON*/
#define RCC_AHB1ENR_GPIODEN_Msk				((0x1 << RCC_AHB1ENR_GPIODEN_Pos))
#define RCC_AHB1ENR_GPIODEN					(RCC_AHB1ENR_GPIODEN_Msk)

/* syscfg clk hattı icin */
#define RCC_APB2ENR_SYSCFGEN_Pos			((14U))									/*BİT POSİTİON*/
#define RCC_APB2ENR_SYSCFGEN_Msk			((0x1 << RCC_APB2ENR_SYSCFGEN_Pos))
#define RCC_APB2ENR_SYSCFGEN				(RCC_APB2ENR_SYSCFGEN_Msk)
/*-------------------------------------------------------------------------------------------------------------------------------------------*/




#include "RCC.h"
#include "GPIO.h"
#include "EXTI.h"
#endif /* INC_STM32F407XX_CAN_H_ */









































