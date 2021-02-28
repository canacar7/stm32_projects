#include "stm32f10x.h"                  // Device header

uint16_t button_state = 0;
void gpioConfig(){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	//led ayarlari
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin  	= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//buton ayarlari
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin  	= GPIO_Pin_6; 
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
}

void delay(uint32_t time){

while(time--);

}

int main(){
gpioConfig();
int ledArray[3] = {GPIO_Pin_0 , GPIO_Pin_1 , GPIO_Pin_2};

	
	while(1){
		button_state = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6);
		if(button_state == 1){            //butona basilirsa daha hizli yanip sönecek ledler
		//ileri gitme
		for(int i = 0; i < 3; i++ ){
				GPIO_WriteBit(GPIOB,ledArray[i],Bit_SET);
				delay(360000);
				GPIO_WriteBit(GPIOB,ledArray[i],Bit_RESET);
				delay(360000);
		}
		//geri girme
		for(int i = 1; i > 0; i-- ){
				GPIO_WriteBit(GPIOB,ledArray[i],Bit_SET);
				delay(360000);
				GPIO_WriteBit(GPIOB,ledArray[i],Bit_RESET);
				delay(360000);
		}
		
		}else{
		
		//ileri gitme
		for(int i = 0; i < 3; i++ ){
				GPIO_WriteBit(GPIOB,ledArray[i],Bit_SET);
				delay(360000);
				GPIO_WriteBit(GPIOB,ledArray[i],Bit_RESET);
				delay(360000);
		}
		//geri girme
		for(int i = 1; i > 0; i-- ){
				GPIO_WriteBit(GPIOB,ledArray[i],Bit_SET);
				delay(3600000);
				GPIO_WriteBit(GPIOB,ledArray[i],Bit_RESET);
				delay(3600000);
		}
		
}
}

}
	

