#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC

uint16_t adc_value = 0;
float map_value = 0;
void gpioConfig(){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  //LEDLERIMIZI B PORTUNA POTOSYOMETREYI A PORTUNA BAGLADIK
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //POTTAN GELECEK DEGER ANALOG DEGERDIR
	
	//led ayarlari
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//potosyometre ayarlari
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  //ANALOG OKUMA ICIN AIN SECILIR
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
}

//ADC icin fonksyonin
void adcConfig(){
	ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);  //ADC PININI AKTIF ETTIM
	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  //sürekli deger almak icin enable
	ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right; //en degerlikli bit saga yasli
	ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None; //herhangi bir tetikleme ile adc aktif edilmiyor
	ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent; //bagimsiz modda
	ADC_InitStructure.ADC_NbrOfChannel       = 1; //1 adc var
	ADC_InitStructure.ADC_ScanConvMode       = DISABLE; //coklu adc lerde tarama yapma amaclidir
	
	ADC_Init(ADC1,&ADC_InitStructure);
	ADC_Cmd(ADC1,ENABLE); 
}

uint16_t read_adc(){  //okucamiz degerler 12 bitlik 16 bitlik bir yapi yeterlidir
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5); //1 HANGI ADC 2 ADC PINI 3RENK DEGERI KAÇ ADC OLDU 4ADC SAMPLE ÖRNEGI
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);  //FLAG RESETSE DÖNSÜN
	return ADC_GetConversionValue(ADC1);
 

} 
float map(float adc_value , float adc_max ,float adc_min , float conv_max, float conv_min){//1 cevrilmesini istedigimiz parametre, 2 adc_value icin max 3ç adc_value icin min
						//4 istedimiz deger araliklari max // 5 min
		return adc_value * ((conv_max-conv_min) / (adc_max-adc_min));


}


int main(){
	adcConfig();
	gpioConfig();

while(1){

	adc_value = read_adc();
	map_value = map(adc_value,4030,0,180,0);
	if((map_value >= 0) && (map_value <= 60)){
		GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
		GPIO_WriteBit(GPIOB,GPIO_Pin_1 | GPIO_Pin_2,Bit_RESET);
	}
	if((map_value >= 60) && (map_value <= 150)){
		GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);
		GPIO_WriteBit(GPIOB,GPIO_Pin_0 | GPIO_Pin_2,Bit_RESET);
	}
	if((map_value >= 150) && (map_value <= 180)){
		GPIO_WriteBit(GPIOB,GPIO_Pin_0 | GPIO_Pin_0 | GPIO_Pin_2,Bit_SET);
	}
}
}








