#include "GPIO_STM32F10x.h"             // Keil::Device:GPIO
#include "GPIO_STM32F10x.h"             // Keil::Device:GPIO


void gpioConfig(){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
void delay(uint32_t time){

while(time--);
}

void full_step(){

	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_RESET);
	
	delay(2);
	
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_RESET);
	
	delay(2);
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_RESET);
	
	delay(2);
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_SET);
	
	delay(2);
	
	
}

void half_step(){

	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_SET);
	
	delay(2);
	
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_RESET);
	
	delay(2);
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_RESET);
	
	delay(2);
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_RESET);
	
	delay(2);
	
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_RESET);
	
	delay(2);
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_RESET);
	
	delay(2);
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_SET);
	
	delay(2);
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_SET);
	
	
}


int main(){
	gpioConfig();

while(1){
	
	full_step();
	delay(500);
}
}
