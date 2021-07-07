#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


uint8_t adc_value = 0;

void CLK_Config(void){

	//1. adým clk HSE secilir
	RCC -> CR |= 0X00030000;
	//HSE kontrolu icin 17. bitdeki HSERDY kontrol edilir
	while(!(RCC -> CR & 0X00020000));
	//CSS BAYRAGI DA 1 YAPILMALIDIR
	RCC -> CR |= 0X000800000;

	//PLL AYARLARINA GECELÝM
	//PLL AYARLARINDA ILK OLARAK HSE KULLANCAMIZ BELIRTILIR
	//PLLCFGR REGISTERLARINA BAKARIZ
	RCC -> PLLCFGR |= 0X00400000;
	//PLLM = 4 , PLLN = 168, PLLP = 2 OLACAK SEKILDE AYARLICAM
	RCC -> PLLCFGR |= 0X00000004; //PLLM 4
	RCC -> PLLCFGR |= 0X00005A00; //PLLN 168
	RCC -> PLLCFGR |= 0X00000000; //PLLP 2

	//HATLARA GITMESI GEREKEN MAX FREQ
	RCC -> CFGR |= 0X00000000; //AHB 1
	RCC -> CFGR |= 0X00080000; //APB2 2
	RCC -> CFGR |= 0X00000000; //APB1 1

	//KALKAN BAYRAKLARI INDIRCEM
	RCC -> CIR |= 0X00080000;   //HSERDY FLAGI TEMIZLENDI
	RCC -> CIR |= 0X00800080;   //CCS FLAGI TEMIZLENDI

}

void GPIO_Config(void){

	//gpýoa nýn hattý olan AHB1 acýlýr
	RCC -> AHB1ENR |= 0X00000001;

	//GPIO NUN OZELLIKLERINI KONFIRME ETMEM GEREKIR
	GPIOA -> MODER   |= 0X00000003;
	GPIOA -> OSPEEDR |= 0X00000003;
	GPIOA -> OTYPER  |= 0X00000000;
	GPIOA -> PUPDR   |= 0X00000000;

}
void ADC_Config(void){

	//ADC CLK HATTI ACILIR
	RCC -> APB2ENR |= 0X00000100;

	//ADC COZUNURLUK OKUNUR
	ADC1 -> CR1    |= 0X02000000;

	//ADC ACMA BITI ADON AKTIF EDILIR
	ADC1 -> CR2    |= 0X00000001;

	//ADC ORNEKLEME YAZILIR
	ADC1 -> SMPR2  |= 0X00000003;

	//ADC PERSCALER ICIN
	ADC -> CCR    |= 0X00010000;


}

uint8_t Read_ADC() {


	//duzenli kanallarda okuma isleminin baslamasý swstart bitini1 yapmam gerekli
	ADC1 -> CR2 |= 0X40000000;

	//EOC FLAGINI KONTROL EDEREK OKUMA ISLEMINI SAGLARIM
	while(!(ADC1 -> SR && 0X00000002));

	//okunan degerý cekecem, OKUNAN DEGER DR REGISTIRINDA TUTULUR
	adc_value  = ADC1 -> DR;


	return adc_value;



}

int main(void)
{
	CLK_Config();
	GPIO_Config();
	ADC_Config();
  while (1)
  {
	  adc_value = Read_ADC();
  }
}


/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
