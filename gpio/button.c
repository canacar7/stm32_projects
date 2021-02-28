#include "stm32f10x.h"                  									// Device header

uint16_t button_state = 0;  													 				//16 bitlik botundan gelen degiskeni okucak deger aatadik
void gpioConfig(){

	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  	//led b portuna bagli olsun
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);		//buton ise c portuna bagli olsun
	
	//LED AYARLARI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//BUTON AYARLARI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;								//BIZ PULL DOWN KULLANCAZ PULL DOWN GND YE BAGLIDIR
																															//EGER PUUL UP KULLANIRSA 3.3 V A BAGLIDIR						
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;  								//AYRICA IN LERDE SPEED YAZMAMIZA DA GEREK YOK
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}



int main(){

gpioConfig();


	while(1){
		button_state = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6);
		if(button_state == 1)
			GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
		else
			GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);	
}
}








