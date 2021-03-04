#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM


void GPIO_Config(){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //ledlerimiz için
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);

}


void timer_config(){
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	//iki timer kullancam tanimlamalar üsteki gibi
	
	//tim3 icin ayarlamalar f=4hz
	TIM_TimeBaseInitStructure.TIM_ClockDivision     = 1;
	TIM_TimeBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period            = 5999;
	TIM_TimeBaseInitStructure.TIM_Prescaler         =	999;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	TIM_Cmd(TIM3,ENABLE);
	
	//tim4 için f=1hz
	TIM_TimeBaseInitStructure.TIM_ClockDivision     = 1;
	TIM_TimeBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period            = 5999;
	TIM_TimeBaseInitStructure.TIM_Prescaler         =	3999;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	TIM_Cmd(TIM3,ENABLE);
	
	
	 //FORMUL ILE PERIOD VE PRESCALER BULMA;
	 //  MAIN_CLK / ((PERIOD+1 ) * (PRESCALER + 1))   = 1/TIME
	
}

//nvic ayarlari için ayri bir fonskiyon açtim kesme 1 den fazla

void nvicConfig(){

	NVIC_InitTypeDef NVIC_InitStructure;
	//iki adet gurubumuz oldugu için NVIC_PrirityGrup da 1 i seçebilirim
	//bir kesme 0 diger eksme 1 degerini alicak
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	
	//TIM3 AYARLAMAR
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //oncelik olarak onde
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
	
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);             //timer güncellemesi yapiyor
	NVIC_Init(&NVIC_InitStructure);
	
	
	//TIM4 AYARLAMAR
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //oncelik olarak sonra
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
	
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);             //timer güncellemesi yapiyor
	NVIC_Init(&NVIC_InitStructure);
}

void toogle_led(uint16_t pin){

	uint16_t read_led = GPIO_ReadInputDataBit(GPIOB,pin);
	if(read_led == (uint16_t)Bit_SET)
		GPIO_WriteBit(GPIOB, pin ,Bit_RESET);
	else 
		GPIO_WriteBit(GPIOB,pin ,Bit_SET);
		
}


//inerrupt fonskiyonlari
void TIM3_IRQHandler(){
	toogle_led(GPIO_Pin_0);
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //BAYRAK TEMIZLEDIK HER DEFASINDA UPDATE OLSUN DEDIK
}

void TIM4_IRQHandler(){
	toogle_led(GPIO_Pin_1);
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //BAYRAK TEMIZLEDIK HER DEFASINDA UPDATE OLSUN DEDIK
}
 


int main(){
	GPIO_Config();
	timer_config();
	nvicConfig();

while(1){



}
}
	
