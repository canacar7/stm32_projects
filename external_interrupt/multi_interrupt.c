#include "stm32f10x.h"                  // Device header
#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI


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
GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_2;
GPIO_Init(GPIOC,&GPIO_InitStructure);
} 
 
void delay(uint32_t time){

while(time--);

}
void extiConfig(){

EXTI_InitTypeDef EXTI_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;

RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource2);
GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource6);                 //IKI BUTONUMUZ VAR BU YÜZDEN IKISINI TAIMLADIM

	
EXTI_InitStructure.EXTI_Line 		= EXTI_Line2 | EXTI_Line6;
EXTI_InitStructure.EXTI_LineCmd = ENABLE;
EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;

	EXTI_Init(&EXTI_InitStructure);	
	
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);                       //2 KESME OLDUGU ICIN KESME SAYISNI BOYLE TANIMLAMAM GEREKLI 

//1. butona ait tanimlamalarimiz
NVIC_InitStructure.NVIC_IRQChannel	 								 = EXTI2_IRQn;
NVIC_InitStructure.NVIC_IRQChannelCmd 							 = ENABLE;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;               //LINE 2 YE BAGLI OLAN BUTON DAHA ÖNCELIKLI OLSUN DEDIK
NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;

NVIC_Init(&NVIC_InitStructure);

//2. butona ait tanimlamalarimiz
NVIC_InitStructure.NVIC_IRQChannel	 								 = EXTI9_5_IRQn;
NVIC_InitStructure.NVIC_IRQChannelCmd 							 = ENABLE;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;               
NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;

NVIC_Init(&NVIC_InitStructure);
}
//1. INTERRUPT FONK
void  EXTI2_IRQHandler(){

if(EXTI_GetITStatus(EXTI_Line2) != RESET){

	GPIO_WriteBit(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2,Bit_SET);
	delay(3600000);
	}
	EXTI_ClearITPendingBit(EXTI_Line2);

}
//2. INTERRUPT FONK
void  EXTI9_5_IRQHANDLER(){

if(EXTI_GetITStatus(EXTI_Line6) != RESET){

	GPIO_WriteBit(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2,Bit_RESET);
	delay(3600000);
	}
	EXTI_ClearITPendingBit(EXTI_Line6);

}  	

int main(){
gpioConfig();
extiConfig();

while(1){

	GPIO_WriteBit(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2,Bit_SET);
	delay(3600000);
	GPIO_WriteBit(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2,Bit_RESET);
	delay(3600000);


}
}
