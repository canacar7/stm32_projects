#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC


uint16_t adc_value = 0;
float voltage = 0;
float map_value = 0;

void gpioConfig(){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;         //analog veri okucamiz icin analog in sectik
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);                 //speed kullanmadik veri okumasi icin

}

void adcConfig(){
	ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  									//sürekli cevrim olsun istedimizden enable
	ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right; 			//en degerlikli bitin ne tarafa dayali olmasi gereklidir dio
	ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;	//trigger kulanmmasak none olur
	ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent;
  ADC_InitStructure.ADC_NbrOfChannel       = 1;                          //kaç kanal oldugunu söyler 1 adc kullandimiz icin 1 tane
	ADC_InitStructure.ADC_ScanConvMode       =  DISABLE;									 //çoklu modda kullaniliyor gelen verilerin taranmasini sagliyor
	
	ADC_Init(ADC1,&ADC_InitStructure);
	ADC_Cmd(ADC1,ENABLE);
}

uint16_t readADC(){
	
ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
//adc nin türü, adc nin channel i, renk (birden fazla adc de  okuma önceligi icin), 1 veriiyi kaç cycle da okumasi gerekli
ADC_SoftwareStartConvCmd(ADC1,ENABLE);  //ADC MIZI BASLATIRKEN HANGI ADC OLDUGUNU BELIRTIK VE IIZN VERIDK

while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
return ADC_GetConversionValue(ADC1);

}

float map(float adc_value,float max, float min, float conv_max, float conv_min){  //1 adcvalue 2alinan max deger 3 min degeri 4 donuturulmesi icin max deger 180 5 0

return adc_value  * ((conv_max-conv_min)/(max-min));
	
}


int main(){

gpioConfig();
adcConfig();
while(1){

	adc_value = readADC();
	voltage   = adc_value * (2.98/4095);
	map_value = map(adc_value,4030,0,180,0);
}

}
