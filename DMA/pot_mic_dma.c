#include "stm32f10x.h"                  // Device header
#include "stm32f10x_dma.h"              // Keil::Device:StdPeriph Drivers:DMA
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC

int16_t adcValue[2];                    //dma de array kullanarak okuma islemi yapilir
void gpioConfig(){

		GPIO_InitTypeDef	GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		
	  //adc pin0 config
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
	
		//adc pin1 config
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
	
}
void adcConfig(){

		ADC_InitTypeDef	ADC_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
		
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;
	  ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;
		ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent;        //TETIKLEME ISLEMI YAPMICAZ
		ADC_InitStructure.ADC_NbrOfChannel       = 2;														//2 adet okuma
		ADC_InitStructure.ADC_ScanConvMode       = ENABLE;											//1 den fazla okuma oldugu icin
	
		ADC_Init(ADC1,&ADC_InitStructure);
		
		ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
		ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5); //channel 1 secildi ve renk 2 secildi
		ADC_Cmd(ADC1,ENABLE);
		ADC_DMACmd(ADC1,ENABLE);
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

void dmaConfig(){

	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE); //ADC OKUMASI DMA 1 DE CHANNLEL 1 DE DIR
	DMA_Cmd(DMA1_Channel1,DISABLE);                   //adc dmade channel 1 e bagli ilkonce disable ederiz
	DMA_DeInit(DMA1_Channel1); 	
	
	DMA_InitStructure.DMA_BufferSize     			= 2;
	DMA_InitStructure.DMA_DIR          			  = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_M2M            			= DISABLE;
	DMA_InitStructure.DMA_MemoryBaseAddr 			= (uint32_t)adcValue; // registerlar 32 bit oldugundan dolayi
	DMA_InitStructure.DMA_MemoryDataSize 			= DMA_MemoryDataSize_HalfWord; //hadizadan gelinin saklanacagi boyut
	DMA_InitStructure.DMA_MemoryInc      			= DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode           	 		= DMA_Mode_Circular;
	DMA_InitStructure.DMA_PeripheralBaseAddr  = (uint32_t) & ADC1-> DR;  //ADC1 Data Register ina yazilsin dedik
	DMA_InitStructure.DMA_PeripheralDataSize 	=	DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc       = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority            = DMA_Priority_High;
	
	
	
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1,ENABLE);

}

int main(){
gpioConfig();
adcConfig();
dmaConfig();
	
while(1){


}

}
