#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM


void GPIO_Config(){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //ledlerimiz için
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);

}

void timer_config(){
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef        NVIC_InitStructure;
	
	//hem kesme hemde timer imin structure yapisii olusturdum
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision     = 1;
	TIM_TimeBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period            =
	TIM_TimeBaseInitStructure.TIM_Prescaler         =     //2 SN DE INTERUPTA A GIRSIN...
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	TIM_Cmd(TIM3,ENABLE);
	
	
	//FORMUL ILE PERIOD VE PRESCALER BULMA;
	//  MAIN_CLK / ((PERIOD+1 ) * (PRESCALER + 1))   = 1/TIME
	//  24mHZ /  ((11999+1)*(3999+1))  = 1/2  ----- FREAKNS 2 OLUR 
	
	
	//NVI ILE KESMENIN ÖNCELIGINI BELIRLEMEM GEREKLI
	NVIC_InitStructure.NVIC_IRQChannel   								 = TIM3_IRQn;   			//TIM IN HANGI FONSKSIOYNA GIRMESI GEREKTIGINI BELIRTIK
	NVIC_InitStructure.NVIC_IRQChannelCmd 							 = ENABLE;     			 //FONSKSIYONA GIRMESINI SITIORUZ
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			 = 0;

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);       													//timerin güncellenmesini sagliyacak config ayari
	
	//interrupt u init edebiliriz
	
	NVIC_Init(&NVIC_InitStructure); 
}

void toogle_led(){

	uint16_t read_led = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2);
	if(read_led == (uint16_t)Bit_SET)
		GPIO_WriteBit(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2,Bit_RESET);
	else 
		GPIO_WriteBit(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2,Bit_SET);
		
}
	
void TIM3_IRQHandler(){
	
	toogle_led(); 
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //BAYRAK TEMIZLEDIK HER DEFASINDA UPDATE OLSUN DEDIK
}


int main(){
	timer_config();
	GPIO_Config();
while(1);
}