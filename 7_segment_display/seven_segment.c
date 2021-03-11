#include "stm32f10x.h"                  // Device header
#include "GPIO_STM32F10x.h"             // Keil::Device:GPIO
#include <stdlib.h> 



//PORT DEFINITIONS
#define portA GPIOA
#define portB GPIOB
#define portC GPIOC

//PIN DEFINITIONS
#define PIN0 (uint16_t)GPIO_Pin_0 
#define PIN1 (uint16_t)GPIO_Pin_1 
#define PIN2 (uint16_t)GPIO_Pin_2 
#define PIN3 (uint16_t)GPIO_Pin_3 
#define PIN4 (uint16_t)GPIO_Pin_4 
#define PIN5 (uint16_t)GPIO_Pin_5 
#define PIN6 (uint16_t)GPIO_Pin_6 
#define PIN7 (uint16_t)GPIO_Pin_7 
#define PIN8 (uint16_t)GPIO_Pin_8 
#define PIN9 (uint16_t)GPIO_Pin_9 
#define PIN10 (uint16_t)GPIO_Pin_10 
#define PIN11 (uint16_t)GPIO_Pin_11
#define PIN12 (uint16_t)GPIO_Pin_12 
#define PIN13 (uint16_t)GPIO_Pin_13 
#define PIN14 (uint16_t)GPIO_Pin_14 
#define PIN15 (uint16_t)GPIO_Pin_15 

#define number_size        10
#define letter_size         8 
#define chracter_size       4
#define clean_display_size  6

uint32_t numberArray[]         = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x07,0x7F,0x67};
uint32_t letterArray[]         = {0x77,0x7F,0x39,0x3F,0x79,0x71,0x7D,0x76};
uint32_t chracterArray[]       = {0x40,0x49,0x5C,0X52};
uint32_t clean_Display_Array[] = {0x01,0x02,0x04,0x08,0x10,0x20};


//portlari gpio_typedef den aliyor
void seg7DisplayInit(GPIO_TypeDef* port,
                    uint16_t pin0,
                    uint16_t pin1,
                    uint16_t pin2,
                    uint16_t pin3,
                    uint16_t pin4,
                    uint16_t pin5,
                    uint16_t pin6){

   if(port == portA){
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		 }else if(port == portB){
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		 }else if(port == portC){
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		 }
		 
		 GPIO_InitTypeDef GPIO_InitStructure;
		 
		 GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF_PP;
		 GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
		 GPIO_InitStructure.GPIO_Pin    = pin0 | pin1 | pin2 | pin3 | pin4 | pin5 | pin6;
		 
		 GPIO_Init(port,&GPIO_InitStructure);
		 }
										
void delay(uint32_t time){

while(time--);
}
										
void print_number(GPIO_TypeDef* port,uint16_t number){
	
	if(number == 0)
		port -> ODR = numberArray[0];   //port -> ODR islemi ile hexcadecimel tanimilamayla prot a gönderebilyotuz
	else if(number == 1)
		port -> ODR = numberArray[1];
	else if(number == 2)
		port -> ODR = numberArray[2];
	else if(number == 3)
		port -> ODR = numberArray[3];
	else if(number == 4)
		port -> ODR = numberArray[4];
	else if(number == 5)
		port -> ODR = numberArray[5];
	else if(number == 6)
		port -> ODR = numberArray[6];
	else if(number == 7)
		port -> ODR = numberArray[7];
	else if(number == 8)
		port -> ODR = numberArray[8];
	else if(number == 1)
		port -> ODR = numberArray[9];
	else 
		port -> ODR = chracterArray[1];
}
void print_letter(GPIO_TypeDef* port,char letter){

		if(letter == 'A' || letter == 'a')
			port -> ODR = letterArray[0];
		else if(letter == 'B' || letter == 'b')
			port -> ODR = letterArray[1];
		else if(letter == 'C' || letter == 'c')
			port -> ODR = letterArray[2];
		else if(letter == 'D' || letter == 'd')
			port -> ODR = letterArray[3];
		else if(letter == 'E' || letter == 'e')
			port -> ODR = letterArray[4];
		else if(letter == 'F' || letter == 'f')
			port -> ODR = letterArray[5];
		else if(letter == 'G' || letter == 'g')
			port -> ODR = letterArray[6];
		else if(letter == 'H' || letter == 'h') 
			port -> ODR = letterArray[7];
		else
			port -> ODR = chracterArray[1];
 
}

void ileri_sayma(GPIO_TypeDef* port,uint32_t time){
	
	for(int i = 0; i< number_size ; i++ ){
			port -> ODR = numberArray[i];
			delay(time);
	}
	
}


void geri_sayma(GPIO_TypeDef* port,uint32_t time){
	
	for(int i = number_size - 1; i > 0 ; i-- ){
			port -> ODR = numberArray[i];
			delay(time);
	}
	
}

void clean_display(GPIO_TypeDef* port){

for(int i=0 ; i < clean_display_size ;i--){
	port -> ODR = clean_Display_Array[i];
	delay(3500000);

}
}

void random_sayi_uretme(GPIO_TypeDef* port){
	
	uint16_t random = rand()%9;
	print_number(portA,random);
	delay(3600000);

}

int main(){
	seg7DisplayInit(portA,PIN0,PIN1,PIN2,PIN3,PIN4,PIN5,PIN6);
while(1){
	print_number(portA, 7);
	delay(360000);
  print_letter(portA,'a');
	delay(360000);	
	//ileri_sayma(portA,3600000);
	//geri_sayma(portA,3600000);
  //clean_display(portA);
	random_sayi_uretme(portA);

}

}

