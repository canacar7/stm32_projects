#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO

#define portA GPIOA
#define portB GPIOB
#define portC GPIOC

#define pin0  (uint16_t)GPIO_Pin_0
#define pin1  (uint16_t)GPIO_Pin_1
#define pin2  (uint16_t)GPIO_Pin_2
#define pin3  (uint16_t)GPIO_Pin_3
#define pin4  (uint16_t)GPIO_Pin_4
#define pin5  (uint16_t)GPIO_Pin_5
#define pin6  (uint16_t)GPIO_Pin_6
#define pin7  (uint16_t)GPIO_Pin_7
#define pin8  (uint16_t)GPIO_Pin_8
#define pin9  (uint16_t)GPIO_Pin_9
#define pin10 (uint16_t)GPIO_Pin_10
#define pin11 (uint16_t)GPIO_Pin_11
#define pin12 (uint16_t)GPIO_Pin_12
#define pin13 (uint16_t)GPIO_Pin_13
#define pin14 (uint16_t)GPIO_Pin_14
#define pin15 (uint16_t)GPIO_Pin_15

void motor1(GPIO_TypeDef* port, uint16_t ileriPin , uint16_t geriPin){

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //pwm a pinini kulandigi için girsite kesin aömamiz gerkli
	if(port == portA){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	}else if(port == portB){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	}else if(port == portC){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	}
		
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = ileriPin | geriPin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(port,&GPIO_InitStructure);
	
	//PWM AÇMA
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin   = pin0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure );
	
	//timer açma
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision     = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period            = 2399;
	TIM_TimeBaseInitStructure.TIM_Prescaler         = 10;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;	
	
	TIM_TimeBaseInit (TIM2,&TIM_TimeBaseInitStructure);
	TIM_Cmd(TIM2,ENABLE);

		
}

void PwmConfig(uint32_t tim_pulse){
		
		TIM_OCInitTypeDef TIM_OCInitStructure;
		
	  TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1; 
		TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_Pulse        = tim_pulse;
}

float map(float Adcvalue,float max,float min,float conMax, float conMin){
	
	return Adcvalue*((conMax - conMin) / (max - min));
}


void ileri(GPIO_TypeDef* port, uint16_t ileriPin, uint16_t geriPin, uint16_t hiz){

		GPIO_WriteBit(port,ileriPin,Bit_SET);
		GPIO_WriteBit(port,geriPin,Bit_RESET);
		PwmConfig(map(hiz,255,0,2399,0));  //map fonksiyonu hiz degiskenini 8 bitlik degerlere dünusturur
}
void geri(GPIO_TypeDef* port, uint16_t ileriPin, uint16_t geriPin, uint16_t hiz){

		GPIO_WriteBit(port,geriPin,Bit_SET);
		GPIO_WriteBit(port,ileriPin,Bit_RESET);
		PwmConfig(map(hiz,255,0,2399,0));
}
void dur(GPIO_TypeDef* port, uint16_t ileriPin, uint16_t geriPin){

		GPIO_WriteBit(port,geriPin,Bit_RESET);
		GPIO_WriteBit(port,ileriPin,Bit_RESET);
}


void delay(uint32_t time)
{
while(time--);
}

int main(){


while(1){
	
	motor1(GPIOB,pin0,pin1);
	ileri(GPIOB,pin0,pin1,200);
	delay(72000000);
	geri(GPIOB,pin0,pin1,200);
	delay(72000000);
}
}

