#include "stm32f10x.h"                  // Device header
#include "stm32f10x_dac.h"              // Keil::Device:StdPeriph Drivers:DAC

uint16_t i;
void GPIO_config(){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //dac kontrolü için 
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4 |GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);


}
void DAC_config(){

  DAC_InitTypeDef DAC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE); 															//apb1 e bagli oldugundan clock ayarlari ona göre ayarlandi
	
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DISABLE; 								 //olusan dalgamizin voltaj degerini belirtir
	DAC_InitStructure.DAC_OutputBuffer                 = ENABLE;  								 //empadansi düsürmek için enable dedim
	DAC_InitStructure.DAC_Trigger                      = DAC_Trigger_None;				 //herhangi bir trigger kullanmicamiz icin none secildi
	DAC_InitStructure.DAC_WaveGeneration               = DAC_WaveGeneration_None;  //bir dalga üretmicemiz icin none oldu

	DAC_Init(DAC_Channel_1,&DAC_InitStructure);    //pa4 oldugu iicn channel1 secilir,
	DAC_Init(DAC_Channel_2,&DAC_InitStructure); 	 //PA5 IDE CHANNEL 2 DE AKTIFLEDIM
	DAC_Cmd(DAC_Channel_1,ENABLE);								 //dac e izin vermek icin kullandik
	DAC_Cmd(DAC_Channel_2,ENABLE);
}
void delay(uint32_t time)
{

while(time--);
}

int main(){
  DAC_config();
	GPIO_config();

while(1){

	for(i=0; i<255 ; i++){
		DAC_SetChannel1Data(DAC_Align_8b_R,i);
		DAC_SetChannel2Data(DAC_Align_8b_R,i);
		delay(360000);
	
}
		for(i=254; i> 0 ; i--){
		DAC_SetChannel1Data(DAC_Align_8b_R,i);
		DAC_SetChannel2Data(DAC_Align_8b_R,i);
		delay(360000);
	
}
}
}
