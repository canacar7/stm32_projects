#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint32_t count = 0;

void RCC_Config(void){


	RCC -> CR |= 0X00003000; //HSEON ON
	while(!(RCC -> CR & 0X00020000)); //BAYRAK KONTROLÜ
	RCC -> CR |= 0X00080000;  //CCS ON

	//PLL AYARLARI
	RCC -> PLLCFGR &= 0X00000000; 			   //ÖNCE BÝT TEMÝZLÝGÝ
	RCC -> PLLCFGR |= 0X00400000;  			   //pllcser biti ile hse aktif edildi
	RCC -> PLLCFGR |=  0X00400004;   			   //PLLM E 4 YAZDIK
	RCC -> PLLCFGR |=  0X00005A00;  			   //6 BÝT SOLA ÖTELE VE PLLN168 YAZDIM
	RCC -> PLLCFGR |= 0X00000000;

	//faz hatlariini ayarladik
	RCC -> CFGR    |= 0X00000000;				//AHB PERSACALAR  1
	RCC -> CFGR    |= 0X00080000;				//APB2 PERSACALAR 2
	RCC -> CFGR    |= 0X00001400;				//APB1 PERSACALAR 4

	//interrupt bayraklarýný düzenlicem
	RCC -> CIR     |= 0X00080000;				//hserdy flag clear
	RCC -> CIR     |= 0X00800000;				//css flag clear

	//portlarý acmam gerekli
	RCC -> AHB1ENR |= 0X00000009;  				//GPIO A VE D AKTIF

	//GPIO PROTLARININ AYARLARINI YAPCAM
	GPIOD -> MODER  =  0X55000000;  				//MODER DA D PORTU OUTPUT YAPILDI, A PROTU 0 ÝNPUT
	GPIOD -> OTYPER =  0X00000000;					//PSH PULL YAPILDI
	GPIOD -> OSPEEDR = 0XFF000000; 					//12 13 14 15 PÝNÝN HIZI MAX YAPILIR
	GPIOD -> PUPDR   = 0X00000000;					//NO PULL SEÇÝLDÝ



}

void delay(uint32_t time)
{

	while(time--);
}






int main(void)
{
	RCC_Config();

  while (1)
  {
	  	 if(GPIOA -> IDR & 0X00000001){
	  		 //OKUMA ÝÞLEMÝ YAPIYOR MU
	  		 while(GPIOA -> IDR & 0X00000001);
	  		 delay(168000);
	  		 count ++;
	  	 }


  if (count % 2 == 0)
	   GPIOD -> ODR = 0X00000000;
  else
	   GPIOD -> ODR = 0X0000F000;

  }}



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
