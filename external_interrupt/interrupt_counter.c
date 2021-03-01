#include "stm32f10x.h"                  // Device header
#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI

uint16_t counter=0;
void gpioConfig(){
GPIO_InitTypeDef GPIO_InitStructure;
	
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
//LED
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOB,&GPIO_InitStructure);
	
//button
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;
GPIO_Init(GPIOC,&GPIO_InitStructure);
}

void extiConfig(){
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;   												 	//INTERRUPT KONTROLU YAPAR, ONCELIKLIK SIRALAMASINI BELIRLER
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  						//INTERRUPT UN CLK UNU ACTIK
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource6);  		//INTERRUPT BUTON ILE CALISACAGI ICIN  C PORTUNU 6 PININI BELIRTITM
	
	//KESME AYARALRININ YAPALIM
	EXTI_InitStructure.EXTI_Line     = EXTI_Line6;
	EXTI_InitStructure.EXTI_LineCmd  = ENABLE;
	EXTI_InitStructure.EXTI_Mode     = EXTI_Mode_Interrupt; 				//MODUMUZU BELIRTIK INTERRUPT OLCAK DEDIK
	EXTI_InitStructure.EXTI_Trigger  = EXTI_Trigger_Rising;    			//INTERRUPT IMIZI YUKSELEN KENARDA CALISTIRDIK
	
	EXTI_Init(&EXTI_InitStructure);
	
	//NVIC AYARLARI
	NVIC_InitStructure.NVIC_IRQChannel									 = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd								 = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
	NVIC_Init(&NVIC_InitStructure);
}
void EXTI9_5_IRQHandler(){       //her pinin kesme fonsiyonu oldugundan fonk adimiz ozel olamlidir

	if(EXTI_GetITStatus(EXTI_Line6) != RESET){
		counter++;
	}
	EXTI_ClearITPendingBit(EXTI_Line6);
}

void delay(uint32_t time){

while(time--);

}

int main(){
gpioConfig();
EXTI9_5_IRQHandler();

while(1){
	GPIO_WriteBit(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2,Bit_SET);
	delay(360000);	
	GPIO_WriteBit(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2,Bit_RESET);
	delay(360000);
}
}
