#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

int counter = 0;
void GPIO_config(){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);

}
void TIMER_config(){

		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
		//basic timer kullancaz timer 6 i seçelim
		//apb1 faz hattina baglidir
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
		//device---system_stm32..(startup)  --- sistem clogunu görebiliriz
		//tim6 24Mhz de çalisma olanagi saglar
		
		TIM_TimeBaseInitStructure.TIM_ClockDivision     = 1; 									//clock degerim ayni kalsin 
		TIM_TimeBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_Up; //SAYICI YUKARI YONDE SAYSIN
	  TIM_TimeBaseInitStructure.TIM_Period					  = 3999;
		TIM_TimeBaseInitStructure.TIM_Prescaler         = 5999;	  //BU IKI DEGER BIZIM PERIUODUMUZU AYARLARKEN KULLANMAM GEREKEN ISLEMLERIN DEGERLERIDIR
		TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; 
	
		TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStructure);
		TIM_Cmd(TIM6,ENABLE);
}

int main(){
	GPIO_config();
	TIMER_config();

while(1){

	counter = TIM_GetCounter(TIM6);  //counter degerimizi almak için get ocunter kullandik ve fonksiyon TIM6 degerini verdik
	
	if(counter == 1999)
			GPIO_WriteBit(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2,Bit_SET);

	else if(counter == 3999)
			GPIO_WriteBit(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2,Bit_RESET);
	




}
}


	