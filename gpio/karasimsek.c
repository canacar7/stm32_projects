#include "stm32f10x.h"                  // Device header

void gpioConfig()
{

	GPIO_InitTypeDef  GPIOInit_Structute;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  //apb2 faz hattina bagl enable mi disable mii
	
	GPIOInit_Structute.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOInit_Structute.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;  // 3 tane pin tanimladik
	GPIOInit_Structute.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIOInit_Structute);
	
}

void DELAY(uint32_t time)
{
	while(time -- );
}




int main(){
					gpioConfig();		
					int ledArray[3] = {GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2};
	
	while(1){
		
//			GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
//			DELAY(1231);
//			GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);
//			DELAY(12312);
//			GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);
//			DELAY(12312);
//			GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);
//			DELAY(123120);
//			GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_SET);
//			DELAY(12312);
//			GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_RESET);
//			DELAY(12312);
//			GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);
//			DELAY(12312);
//			GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);
//			DELAY(123120);
//			GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
//			DELAY(1231);
//			GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);
//			DELAY(12312);

		//ileri yönde
		for(int i = 0 ; i <3 ; i++)
		{
				GPIO_WriteBit(GPIOB,ledArray[i],Bit_SET);
				DELAY(1231);
				GPIO_WriteBit(GPIOB,ledArray[i],Bit_RESET);
				DELAY(12312);
		}
		
		//geri yönde
				for(int i = 1 ; i >= 0 ; i--)
		{
				GPIO_WriteBit(GPIOB,ledArray[i],Bit_SET);
				DELAY(1231);
				GPIO_WriteBit(GPIOB,ledArray[i],Bit_RESET);
				DELAY(12312);
		}
	}
	
	
	
}