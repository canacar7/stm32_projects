#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

void gpioConfig(){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //tim2 icin channler a protuna tanimlidir
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void timerConfig(){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);                 //tim2 apb1 fazina baglidir
	
	 TIM_TimeBaseInitStructure.TIM_Prescaler     = 10;                // f = (Timer_clock/prescaler) /(Timer_period + 1)  
																								                     // f=  1kHz ise periyod 2399 gelir

	 TIM_TimeBaseInitStructure.TIM_Period        = 2399;
	 TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	 TIM_TimeBaseInitStructure.TIM_CounterMode   = TIM_CounterMode_Up;
	
	 TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	 TIM_Cmd(TIM2,ENABLE);
}

void pwmConfig(uint16_t time_pulse){

	TIM_OCInitTypeDef TIM_OCInitStructure;

	TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;         //pwm1 modunda çalissin istedik,: Çikti karsilastirma modunu belirler 
	TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;  //CIKIS ALMAK ISTERSEK ENABLE
	TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;     //çikis kanalini yükseten veya alçaktan baslamasini tanimlar
	TIM_OCInitStructure.TIM_Pulse        = time_pulse  ;            //Bu alanin içerigi CCRx kaydinin içinde saklanir ve çikti tetiklemek için kullanilir.
	
	//TIMpulse = ((timer_period + 1) * Duty_Cycle / 100) - 1	
 
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);                         //ATAMAMI CH1 KISMINA YAPTIK
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);

}

void pwm2Config(uint16_t time_pulse){
	
	TIM_OCInitTypeDef TIM_OCInitStructure;

	TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;         //pwm1 modunda çalissin istedik,: Çikti karsilastirma modunu belirler 
	TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;  //CIKIS ALMAK ISTERSEK ENABLE
	TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;     //çikis kanalini yükseten veya alçaktan baslamasini tanimlar
	TIM_OCInitStructure.TIM_Pulse        = time_pulse  ;            //Bu alanin içerigi CCRx kaydinin içinde saklanir ve çikti tetiklemek için kullanilir.
	
	//TIMpulse = ((timer_period + 1) * Duty_Cycle / 100) - 1	
 
	TIM_OC2Init(TIM2,&TIM_OCInitStructure);                         //ATAMAMI CH2 KISMINA YAPTIK
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);

}

void pwm3Config(uint16_t time_pulse){
	
	TIM_OCInitTypeDef TIM_OCInitStructure;

	TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;         //pwm1 modunda çalissin istedik,: Çikti karsilastirma modunu belirler 
	TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;  //CIKIS ALMAK ISTERSEK ENABLE
	TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;     //çikis kanalini yükseten veya alçaktan baslamasini tanimlar
	TIM_OCInitStructure.TIM_Pulse        = time_pulse  ;            //Bu alanin içerigi CCRx kaydinin içinde saklanir ve çikti tetiklemek için kullanilir.
	
	//TIMpulse = ((timer_period + 1) * Duty_Cycle / 100) - 1	
 
	TIM_OC3Init(TIM2,&TIM_OCInitStructure);                         //ATAMAMI CH2 KISMINA YAPTIK
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);

}

void delay(uint32_t time){

while(time--);
}

int main(){
	gpioConfig();
	timerConfig();
	

while(1){

	for(int i= 0; i<= 2399; i++){
		pwmConfig(i);
		delay(3600);
	}	
	for(int i= 0; i<= 2399; i++){
		pwm2Config(i);
		delay(3600);
	}	
	for(int i= 0; i<= 2399; i++){
		pwm3Config(i);
		delay(3600);
	}	
}}

