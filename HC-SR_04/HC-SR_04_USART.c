#include "GPIO_STM32F10x.h"             // Keil::Device:GPIO
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include	<stdio.h>
  

float distance = 0; 
char message[20];

void GPIO_Config(){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//trig pin GPIO islemleri yap
	GPIO_InitStructure.GPIO_Mode        = GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Pin         = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed       = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//echo pin GPIO ayarlari
	GPIO_InitStructure.GPIO_Mode 				= GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin  				= GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed				= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	//TX
	GPIO_InitStructure.GPIO_Mode     		= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin         = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed 			= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//LED ICIN
	GPIO_InitStructure.GPIO_Mode        = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin					= GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed 			= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
}

void delayUS(uint32_t time)
{
	//gercekci bir delay yapmak icin 
	uint32_t newTime = time*24;                               	//gercekcibir deger olusturmak icin yapdik 	
	while(newTime--);																						//kartimizda bir islem 0.0417us de yapliolr bu bir cycle dir 1 us icin 24 cycle gelmekdedir
}

float HCSR04READ(){

		//zaman hesabi gerekli
		uint32_t time     			= 0;
		float 	 anlik_distance = 0;
	
		//sensoru baslatmak icin trig pinine 10 us high vercez
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		delayUS(10);
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		delayUS(10);
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);     
		delayUS(10);
	
		while(!(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)));  //sensor trig pini tetiklendikden sonra belli sure okumaya gecmeden durur while dongusu ile bu sureyi tuketmeyi amacladik
		
		//okuma islemeri
		while (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
		{
		
				time++;
				delayUS(1);
		}
		
		anlik_distance = (float)time/58;                            //zamani 58 e bölerek cm cinsinden mesafe degerlerini aliriz
		if(distance > 400) 
			anlik_distance = 400;
		if(distance < 2)
			anlik_distance = 2; 
		delayUS(1000);
		
		
		return anlik_distance;
}

void usartConfig(){

	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	 
	//usart ayarlari
	USART_InitStructure.USART_BaudRate						 = 9600;
	USART_InitStructure.USART_HardwareFlowControl	 = USART_HardwareFlowControl_None;  //RS232 Donanim Akis Kontrol 
	USART_InitStructure.USART_Mode 								 = USART_Mode_Tx;
	USART_InitStructure.USART_Parity							 = USART_Parity_No;
	USART_InitStructure.USART_StopBits						 = USART_StopBits_1;
	USART_InitStructure.USART_WordLength					 = USART_WordLength_8b; 
	
	USART_Init(USART1,&USART_InitStructure);
	USART_Cmd(USART1,ENABLE);

}

void uartTransmitter(char *string){

	while(*string){
			while(!(USART1 -> SR & 0X00000040)){
					USART_SendData(USART1,*string);
					*string++; 
			}
			}

}

int main(){
			GPIO_Config();
			usartConfig();
				
while(1){
				
			distance = HCSR04READ();
			sprintf(message,"mesafe %f dir \n",distance);
			uartTransmitter(message);
			
			if(distance > 5){
			GPIO_SetBits(GPIOB,GPIO_Pin_0); 			//mesafe 5 den kucukse pin0 a bagi led yansin
			GPIO_ResetBits(GPIOB,GPIO_Pin_1);			//mesafe 5 den kucukse pin1 e bagi led sonsun
			}
			
			if(distance < 5){
			GPIO_SetBits(GPIOB,GPIO_Pin_0); 			
			GPIO_ResetBits(GPIOB,GPIO_Pin_1);			
			}
			
			delayUS(100000);
}
}

