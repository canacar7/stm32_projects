#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC

uint16_t adc_value = 0;

void gpioConfig(){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  //LEDLERIMIZI B PORTUNA POTOSYOMETREYI A PORTUNA BAGLADIK
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //ldr GELECEK DEGER ANALOG DEGERDIR
	
	//led ayarlari
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//ldr ayarlari
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  //ldr okumak icin
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
}
//ADC icin fonksyonin
void adcConfig(){
	ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);  //ADC PININI AKTIF ETTIM
	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  									//sürekli deger almak icin enable
	ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;				//en degerlikli bit saga yasli
	ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None; //herhangi bir tetikleme ile adc aktif edilmiyor
	ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent; 			//bagimsiz modda
	ADC_InitStructure.ADC_NbrOfChannel       = 1; 												//1 adc var
	ADC_InitStructure.ADC_ScanConvMode       = DISABLE; 									//coklu adc lerde tarama yapma amaclidir
	
	ADC_Init(ADC1,&ADC_InitStructure);
	ADC_Cmd(ADC1,ENABLE);                                                 //adc aktiflestirdik
}

uint16_t read_adc(){  //okucamiz degerler 12 bitlik 16 bitlik bir yapi yeterlidir
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5); //1 HANGI ADC 2 ADC PINI 3RENK DEGERI KAÇ ADC OLDU 4ADC SAMPLE ÖRNEGI
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);  //FLAG RESETSE DÖNSÜN
	return ADC_GetConversionValue(ADC1);
 

}

int main(){
	gpioConfig();
	adcConfig();
while(1){
	
	adc_value=read_adc();
	if((adc_value <= 800))
			GPIO_WriteBit(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2,Bit_SET);
	else
		GPIO_WriteBit(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2,Bit_SET);
	
}}



