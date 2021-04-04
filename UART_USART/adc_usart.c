#include "stm32f10x.h"                  // Device header
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include <stdio.h>                      // ADC verilerini string ifadelere cevirmek iicn eklendi

uint16_t veri = 0;
char message[20];

void GpioConfig(){

	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  
	
	//ADC AYARLARI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;   //PA0  
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	

}
 
void adcConfig(){

	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel       = 1;                              // 1 adet okuma
	ADC_InitStructure.ADC_ScanConvMode       =DISABLE; 												 // farkli bir okuma yapilmadii

	ADC_Init(ADC1,&ADC_InitStructure);
	ADC_Cmd(ADC1,ENABLE);  //adc komutlarinin baslamini soyledik
}	

void uartConfig(){

	USART_InitTypeDef  UART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	UART_InitStructure.USART_BaudRate            = 9600;
	UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	UART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
	UART_InitStructure.USART_Parity              = USART_Parity_No;
	UART_InitStructure.USART_StopBits            = USART_StopBits_1;
	UART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	
	USART_Init(USART1,&UART_InitStructure);
	USART_Cmd(USART1,ENABLE);
	
}

uint16_t readADC(){

	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	//adc1 e bagli, channel 0 , 1 adet okuma,	sapling time 55 cycle
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) ==RESET);
	
	return ADC_GetConversionValue(ADC1);
}

void uarttransmit(char *string){
	while(*string){
	while(!(USART1 -> SR & 0X00000040)); //SR REGISTIR INDA VERI YOKSA BIR SONRAKI ADIMA
	USART_SendData(USART1,*string);
	*string++;

	}}
	
void delay(uint32_t time){	

	while(time--);

}


int main(){
  GpioConfig();
	adcConfig();
	uartConfig();
	
while(1){

	veri = readADC();
	sprintf(message,'verilerimizi string iafadeye cevirebilmek icin %d \r\n',veri); //verilerin mesaage arrayine göderilerek cerilecek
	uarttransmit(message);
	delay(7200000);
}


}






