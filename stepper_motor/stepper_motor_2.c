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

void fullstate_rotate(int step){

	switch(step){
	
		case 0:
				GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
				GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);
				GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_RESET);
				GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_RESET);
		break;
		
		case 1:
			GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
			GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);
			GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_RESET);
			GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_RESET);
		break;
		
		case 2:
			GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
			GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);
			GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_SET);
			GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_RESET);
		break;
		
		case 3:
	
			GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
			GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);
			GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_RESET);
			GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_SET);
		break;
	
	}

}

void setStepper(float angle, int direction, int speed){

		float per_angle = 0.703125; //360/512 = 0,70(her bir adimdaki acisi)
		int stepNumber  = (int)(angle/per_angle); //istenilen aci icin gitmesi gereken tur

		for(int ilerleme = 0;ilerleme <= stepNumber; ilerleme++){
			
			if(direction == 0){ //saat yönünde dönme yapacak
				for(int step = 0; step < 4; step++){
					fullstate_rotate(step);
					delay(speed);
				}		
			}	
			else if(direction == 1){ //saat yönüne ters dönerse
			for(int step = 0; step < 4; step++){
					fullstate_rotate(step);
					delay(speed);
			
			
			}	
		
		
		}
}	}

int main(){
	gpioConfig();

while(1){
	
	//full_step();
	setStepper(90 1 2);
	delay(500);
}
}
