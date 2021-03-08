#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

void gpioConfig(){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //tim2 a portuna bagli oldugu icin!!! gpio apb2 faz hattina bagli
	//tim2_ch_1 pa0 a bagli, tim2_ch_2 pa1 a bagli...
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA,&GPIO_InitStructure);
 
}
void timerConfig(){
	TIM_TimeBaseInitTypeDef TIM_TimBaseInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);                   //tim2 apb1 faz hatiina bagli

	TIM_TimBaseInitStructure.TIM_ClockDivision     = TIM_CKD_DIV1;        //cLk DIVISON 1 SEVILDI
	TIM_TimBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_Up ; //YUKARI DOGRU SAYSIN ISTEDIK
	TIM_TimBaseInitStructure.TIM_Period						 = 2399;
	TIM_TimBaseInitStructure.TIM_Prescaler				 = 10;
	TIM_TimBaseInitStructure.TIM_RepetitionCounter = 0;
	

		// f = TIMERclk / (timer(period) + 1)

	TIM_TimeBaseInit(TIM2,&TIM_TimBaseInitStructure);
	TIM_Cmd(TIM2,ENABLE);
	
}

void pwmConfig(uint32_t time_pulse){
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	//clk açmamiza gerek yok pwm ler zaten timer a bagli aisior
	
	
	TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;         //pwm1 modunda çalissin istedik,: Çikti karsilastirma modunu belirler 
	TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;  //CIKIS ALMAK ISTERSEK ENABLE
	TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;     //çikis kanalini yükseten veya alçaktan baslamasini tanimlar
	TIM_OCInitStructure.TIM_Pulse        = time_pulse  ;            //Bu alanin içerigi CCRx kaydinin içinde saklanir ve çikti tetiklemek için kullanilir.
																																  //kalan özellikler TIM1 VE TIM8 icin (advance timer) içindir
 

	//TIMpulse = ((timer_period + 1) * Duty_Cycle / 100) - 1	
 
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);                          //ATAMAMI CH1 KISMINA YAPTIK
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
}


void delay(uint32_t time){

while(time--);
	
}





int main(){
	gpioConfig();
	timerConfig();
	
	

while(1){
	pwmConfig(599);  //%25
	delay(360000);
	pwmConfig(1199); //%50	
	delay(360000);
	pwmConfig(1799); //%75
	delay(360000);
	pwmConfig(2399); //%100
	delay(360000);
};
}

