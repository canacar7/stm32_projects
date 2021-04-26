#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "stdio.h"
#include "math.h"

uint16_t adcValue = 0;
uint16_t sicaklikC = 0;
char message[25] = "";

void gpioConfig(){
	
	GPIO_InitTypeDef 	GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	//ADC PIN AYARLARI
	GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AIN; //analog okuma yapmak icin
	GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//TX ISLEMLERI
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
}
void adcConfig(){
	
	ADC_InitTypeDef	ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv	 = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode							 = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel			 = 1;
	ADC_InitStructure.ADC_ScanConvMode			 = DISABLE;
	
	ADC_Init(ADC1,&ADC_InitStructure);
	ADC_Cmd(ADC1,ENABLE);

}
void UsartConfig(){

	USART_InitTypeDef	USART_InitStructure;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	USART_InitStructure.USART_BaudRate            = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode								=	USART_Mode_Tx| USART_Mode_Rx;
	USART_InitStructure.USART_Parity							= USART_Parity_No;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_WordLength					= USART_WordLength_8b;
	
	USART_Init(USART1,&USART_InitStructure);
	USART_Cmd(USART1,ENABLE);
	
}
void uartTransmitter(char *string){

	while(*string){
		while(!(USART1 -> SR & 0X00000040));
		USART_SendData(USART1,*string);
		*string++;
	}

}


uint16_t readADC(){

		//okuma islemi
		ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		//adc islemleri kontrolü
		while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
		return ADC_GetConversionValue(ADC1);
}



double Termistor(uint16_t adcValue) {
  double sicaklik;
  sicaklik = log(((40950000 / adcValue) - 10000));  //16 bitlik bir okuma oldugu icin 40950000 kullanilmistir 10 bit olasaydi 10240000 olurdu
  sicaklik = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * sicaklik * sicaklik)) * sicaklik);
  sicaklik = sicaklik - 273.15;
  return sicaklik;
}

void delay(uint32_t time){

while(time--);
}


int main(){
		gpioConfig();
		adcConfig();
	  UsartConfig();
	
	while(1){
		
			adcValue = readADC();
			sicaklikC = Termistor(adcValue);
		  sprintf(message,"sicaklik: %d C \r\n",sicaklikC); //message formatini olusturduk
			uartTransmitter(message);
		  delay(3600000);
			
		

}
}

