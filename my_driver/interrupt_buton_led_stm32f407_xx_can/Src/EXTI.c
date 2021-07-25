/*
 * EXTI.c
 *
 *  Created on: 24 Tem 2021
 *      Author: CAN AHMET ACAR
 */



#include "EXTI.h"


/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief 	 EXTI_LineConfig, configuration port and pins for SYSCFG
 *
 * @param	 EXTI_PortSource ----- @def group PORT SOURCE
 *
 * @param 	 EXTI_LineSource ----- @def group LINE SOURCE
 *
 * @ret_val  void
 *
 */
void EXTI_LineConfig(uint8_t EXTI_PortSource, uint8_t EXTI_LineSource)
{
	uint32_t tempValue 							 = 0;

	tempValue 		   							 = SYSCFG -> EXTICR[EXTI_LineSource >> 2U];   			//Kullanilcak CR registiri bulunur
	tempValue 								    &= ~(0XFU << ((EXTI_LineSource & 0x3U) * 4)); 			//kullanilacak bitler temizlenir
	tempValue 									 = (EXTI_PortSource << ((EXTI_LineSource & 0x3U) * 4));	//kullanilacak bitlere port un degeri girilir
	SYSCFG -> EXTICR[EXTI_LineSource >> 2U]      = tempValue;											//registera dogru konum ve dogru port degeri girilir


	/*
	 * LİNE_SOURCE7 ---------------------------  7 / 4 = 1 ------ EXTICR[2]
	 * LİNE_SOURCE7 ---------------------------  7 % 4 = 3 ------ 8 12 bit arasina port bilgisini yerleştir
	 * 7 / 4        ---------------------------  yazilimda kaydirma islemi ile bolmek daha cok tercih edilir. Yariya bolmek icin bir bit saga kaydiririz dolayisiyla 4 e bolmek icin 2 bit saga kaydirilir
	 * 7 % 4        ---------------------------  2^2  ----------- 0011(0x3U) ifadesi ile and lendiginde mod degerini verir mod islemini cozumleriz
	 */
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief 	 EXTI_Init, configuration port and pins for EXTI
 *
 * @param 	 EXTI_InitStructure  Configuration Struct
 *
 * @ret_val  void
 *
 */
void EXTI_Init(EXTI_InitTypeDef_t *EXTI_InitStructure)
{
	uint32_t tempValue = 0;

	/*
	 * Ofset degerlerini kullanarak kodlama yapildi
	 * 1- Mode kontrolu yapilacak --- Interrupt veya event mode belirlenecek
	 * 2- Belirlenen mod kadar ofset eklenerek maskeleme islemi yapilacak
	 * 3- Maskeleme islemi ilgili pinin degerini 1 e cekerek kaldirma islemidir
	 *
	 */
	tempValue = (uint32_t)EXTI_BASE_ADDR;

	/*
	 * ilgili registerlarin bitleri temizlendi
	 */
	EXTI -> IMR &= ~(0x1U << EXTI_InitStructure -> EXTI_LineNumber);
	EXTI -> EMR &= ~(0x1U << EXTI_InitStructure -> EXTI_LineNumber);

	if(EXTI_InitStructure -> EXTI_LineCmd == ENABLE)
	{

			/*moda göre offset ekleme */
			tempValue += EXTI_InitStructure -> EXTI_Mode;
			/*tempvalue adresdir, *((_IO uint32_t *)tempValue ) kullanarak o adresdeki register a ulasilarak isle yapidli */
			*((_IO uint32_t *)tempValue ) |= (0x1U << EXTI_InitStructure -> EXTI_LineNumber);



			/*
			 *  Trigger modu icinde usteki yontem kullanildi
			 * 1- Trigger Mode icin belirlienmis pinler temizlenecek
			 * 2- Secilen mod icin offset ekleme
			 * 3- İlgili pini high yapma
			 *
			 */
			tempValue = 0;

			tempValue = (uint32_t)EXTI_BASE_ADDR;

			/*ilgili registerlar temizlenecek */
			EXTI -> FTSR &= ~(0X1U << EXTI_InitStructure -> EXTI_LineNumber);
			EXTI -> RTSR &= ~(0X1U << EXTI_InitStructure -> EXTI_LineNumber);

			if(EXTI_InitStructure ->TriggerSelect == EXTI_Trigger_Rising_Falling_Edge){

				/* hem yukselen kenar hem dusen kenar aktifse */
				EXTI -> FTSR |= (0X1U << EXTI_InitStructure -> EXTI_LineNumber);
				EXTI -> RTSR |= (0X1U << EXTI_InitStructure -> EXTI_LineNumber);

			}
			else
			{
				/*mode belirlendi */
				tempValue += EXTI_InitStructure -> TriggerSelect;

				/*ilgili register in pinleri high yapilacak */
				*((_IO uint32_t *)tempValue) |= (0X1U << EXTI_InitStructure -> EXTI_LineNumber);

			}


	}
	else
	{

		/*disable ise clearlama islemi yapilir */
		tempValue = 0;

		tempValue = (uint32_t)EXTI_BASE_ADDR;

		tempValue += EXTI_InitStructure -> EXTI_Mode;
		*((_IO uint32_t*)tempValue)     &= ~(0X1U << EXTI_InitStructure -> EXTI_LineNumber);
}}


/*-------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 	 NVIC_EnableInterrupt
 *
 * @param 	 IRQNumber ---- Priority for EXTI
 *
 * @ret_val  void
 *
 */

void NVIC_EnableInterrupt(NVIC_InitTypeDef_t IRQNumber)
{
	uint32_t tempValue = 0;

	/*
	 * gelen oncelige gore register bulmak icin degerin 32 bolunmesi gerekir
	 * ex : IRQNumber = 64 ---------- 64 / 32 ------------ NVIC_ISER_2 kullanilir
	 */
	tempValue =  *((IRQNumber >> 0X5U) + NVIC_ISER_0);
	/*
	 * bulunan registerda bitin bulunmasi gerekir
	 * ex : IRQNumber = 64 -------- 64 % 32 = 0  ------------- NVIC_ISER_2 ---- 0. biti kullanilir
	 * bulunan bit önce temizlenir ardindan high a cekilir
	 */
	tempValue &= ~(0X1U << (IRQNumber & 0X1FU));
	tempValue |=  (0X1U << (IRQNumber & 0X1FU));
	*((IRQNumber >> 0X5U) + NVIC_ISER_0) = tempValue;

}


















