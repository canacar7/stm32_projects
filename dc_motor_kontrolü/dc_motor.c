#include "stm32f10x.h"                  // Device header
#include "GPIO_STM32F10x.h"             // Keil::Device:GPIO
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC


void gpioConfig(void);
void adcConfig(void);
void TimerConfig(void);
void AdcConfig(void);
void PWMConfig(uint32_t timerpulse);
void delay(uint32_t time);
float map(float adc_value , float adc_max ,float adc_min , float conv_max, float conv_min);
uint16_t readADC(void);
extern uint16_t potvalue;

extern  uint16_t buttonstate;
extern uint16_t flag;
extern uint16_t mapValue;

void gpioConfig(){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //a portunda pwm sinyaliyle sürmek istersek
	
	//MOTOR 0 A 2 LEDE 1 VE2 YA EKLENIR
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//BUTON
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
	
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//potansiyometre gpiolaro
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
}

void TimerConfig(){

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	TIM_TimeBaseInitStructure.TIM_ClockDivision     = TIM_CKD_DIV1;  
	TIM_TimeBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period            = 2399;
	TIM_TimeBaseInitStructure.TIM_Prescaler            = 10;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	//f = (Timer_clock/prescaler) /(Timer_period + 1) 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	TIM_Cmd(TIM2,ENABLE);

}

void PWMConfig(uint32_t timerpulse){

	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse       = timerpulse;
	
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
	


}

void AdcConfig(){

	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 											//sürekli deger almak icin
	ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right; 				//en degerlikli bit
	ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;		//herhangi bir tetikleme ile adc aktiflessir
	ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent;        //bagimsiz modda
	ADC_InitStructure.ADC_NbrOfChannel       = 1;                           //1 adc var
	ADC_InitStructure.ADC_ScanConvMode       = DISABLE;                     //coklu adc lerin tarama yapmasi için

	ADC_Init(ADC1,&ADC_InitStructure);
	ADC_Cmd(ADC1,ENABLE);
}

uint16_t readADC(){

	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5); //1 HANGI ADC 2 ADC PINI 3RENK DEGERI KAÇ ADC OLDU 4ADC SAMPLE ÖRNEGI
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);  //FLAG RESETSE DÖNSÜN
	return ADC_GetConversionValue(ADC1);
 

}
float map(float adc_value , float adc_max ,float adc_min , float conv_max, float conv_min){//1 cevrilmesini istedigimiz parametre, 2 adc_value icin max 3ç adc_value icin min
						//4 istedimiz deger araliklari max // 5 min
		return adc_value * ((conv_max-conv_min) / (adc_max-adc_min));


}


void delay(uint32_t time){

while(time--);

}

int main(){
	gpioConfig();
	TimerConfig();
	AdcConfig(); 
while(1){
	 
	//motor kontrolü açma kapama
//	GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
//	delay(7200000);
//	GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);
//	delay(7200000);

		//motorun kontrolü buton ile
//	buttonstate = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6);
//	
//	if(buttonstate){
//			GPIO_WriteBit(GPIOB,GPIO_Pin_0 | GPIO_Pin_1,Bit_SET);
//			GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_RESET);
//	}
//	else{
//			GPIO_WriteBit(GPIOB,GPIO_Pin_0 | GPIO_Pin_1,Bit_RESET);
//			GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_SET);
//	}
		
	
	//motor kontrolü kalici buton ile
//	buttonstate = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6);
//	
//	if(buttonstate){
//		if(flag == 0){
//			flag = 1;
//			GPIO_WriteBit(GPIOB,  GPIO_Pin_0,Bit_SET);
//			GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_SET);
//			GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);
//		}else{
//			GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);
//			GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_RESET);
//			GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);
//		}
//		
//		//butuon arklarinni engellmek icin delay
//		delay(360000);
//	}
	
	//PWM ile motor kontrolü
//	for (uint32_t i=0; i< 2399; i++){
//	
//		PWMConfig(i);
//		delay(720);
//	}

//potosyometre ile lullanma

	potvalue = readADC();
	mapValue = map(potvalue,4095,0,2399,0);
	PWMConfig(mapValue);
	
}
}


