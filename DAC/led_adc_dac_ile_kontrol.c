#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include "stm32f10x_dac.h"              // Keil::Device:StdPeriph Drivers:DAC

uint16_t adc_value = 0;
void gpioConfig(){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 					//dac ve adc icin an secilcenden sorun yok
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_4;  //dac 4 pinde adc 0 pine baglidri 
																													 //adc verisnini potosyometrenin degisimnden saglicaz
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
}

void adcConfig(){
	ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                   //surekli deger alcamiz icin aktif
	ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;      //EN YUKSEK BIT SAGA DAYALI
	ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel       = 1;
	ADC_InitStructure.ADC_ScanConvMode       = DISABLE;                  //BASKA OKUMA YOK
	
	ADC_Init(ADC1,&ADC_InitStructure);
	ADC_Cmd(ADC1,ENABLE);
}

uint16_t read_adc(){
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	//1 KULLANCAMIZ ADC 2 ADC KANALI 3 KAC ADET OKUMA 4 ORNEKLEME CYCLI
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
	
	return ADC_GetConversionValue(ADC1);

}

void dacConfig(){
	
	DAC_InitTypeDef DAC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
	
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DISABLE;
	DAC_InitStructure.DAC_OutputBuffer                 = ENABLE;
	DAC_InitStructure.DAC_Trigger                      = DAC_Trigger_None;
	DAC_InitStructure.DAC_WaveGeneration               = DAC_WaveGeneration_None;
	
	DAC_Init(DAC_Channel_1,&DAC_InitStructure);
	DAC_Cmd(DAC_Channel_1,ENABLE);
}
int main(){
	gpioConfig();
	adcConfig();
	dacConfig();
while(1){

	adc_value = read_adc();	
	DAC_SetChannel1Data(DAC_Channel_1,adc_value);


}
}
