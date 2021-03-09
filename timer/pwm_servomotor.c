#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM



void gpioConfig(){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //tim2 icin channler a protuna tanimlidir
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void timerConfig(){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);                 //tim2 apb1 fazina baglidir
	
	 TIM_TimeBaseInitStructure.TIM_Prescaler     = 100;                // f = (Timer_clock/prescaler) /(Timer_period + 1)  
																								                     // f= 50	Hz ise periyod 4799 gelir

	 TIM_TimeBaseInitStructure.TIM_Period        = 4799;
	 TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	 TIM_TimeBaseInitStructure.TIM_CounterMode   = TIM_CounterMode_Up;
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

	TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM2;         //pwm2 modunda çalissin istedik,: Çikti karsilastirma modunu belirler 
	TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;  //CIKIS ALMAK ISTERSEK ENABLE
	TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;     //çikis kanalini yükseten veya alçaktan baslamasini tanimlar
	TIM_OCInitStructure.TIM_Pulse        = time_pulse  ;            //Bu alanin içerigi CCRx kaydinin içinde saklanir ve çikti tetiklemek için kullanilir.
	
	//TIMpulse = ((timer_period + 1) * Duty_Cycle / 100) - 1	
 
	TIM_OC2Init(TIM2,&TIM_OCInitStructure);                         //ATAMAMI CH2 KISMINA YAPTIK
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);

}

void delay(uint32_t time){

while(time--);
}

int main(){
	gpioConfig();
	timerConfig();
	

while(1){

		pwmConfig(359); //0 derece     TIM_PULSE = ((Timer_period + 1) * Duty_Cycle) / 100 - 1
	  delay(7200000);
	  pwmConfig(480); //90 derece
		delay(7200000);
	  pwmConfig(240); //90 derece
		delay(7200000);
	
	  pwm2Config(359); //0 derece     
	  delay(7200000);
	  pwm2Config(480); //90 derece
		delay(7200000);
	  pwm2Config(240); //90 derece
		delay(7200000);

	
		//toplam periyot 20ms idi 0 derece icin pwm sinyalinin 1.5ms on olsun 18.5ms off olsun.. 
}}

