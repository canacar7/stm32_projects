#include "stm32f10x.h"                  // Device header
#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI


void gpioConfig(){

	GPIO_InitTypeDef Gpio_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //LEDLER ICIN
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); //BUTON ICIN
	
	
	//ledler
	Gpio_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	Gpio_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	Gpio_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&Gpio_InitStructure);
	
	//BUTON
	Gpio_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	Gpio_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOC,&Gpio_InitStructure);
	
}

//KESME  AYARLARINI YAPMAM GEREKLI
void extiConfig(){  											//kesme  fonksiyon olusturmam gerekli
	
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;    //structute yapilarini olusturduk
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);   																		//Interruptlarin clk lariniu açmamiz gererkli
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource6);                                //INTERRUPT UN HANGI HATTA OLDUGUU BILDIRECEK 
		
	
	
	
	//EXTERNAL INTERRUPT																																										
	EXTI_InitStructure.EXTI_Line    = EXTI_Line6;																								//INTERRUPT U TANITMAK ICIN CONFIG KULLANILDI BUTON C PORTUNDA VE 6. PINDE
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;                                     //KESME IZNINI VERDI
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;                                     //YÜKSELEN KENAR DEMEK YANI CLK UN YÜKSELEN KENARINDA INTERRRUPT ISLEVI VASA BASLATACAK
	
	EXTI_Init(&EXTI_InitStructure);
	
	//NVIC PARTI;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;                                                    //interrupt gerçeklestiginde hangi fonk çagrilmasi gerektigini söyler
	//BIZ6. PINE BAGLI OLDUMUZDAN BUNU SEÇMKE ZORUNDAYIZ KAFAMIZA GÖRE YAZAMIYORUZ DATASHHETTDEN BAKIP YAZCAZ
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             																					 //kesme iznini
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 																						 //1 tane interrupt oldugu icin 1 verdim
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	
	NVIC_Init(&NVIC_InitStructure);

}


void delay(uint32_t time){

	while(time--);

}


//BUTONA BASTIMIZDA ÇALISMASI GEREK FONSKIYON
void EXTI9_5_IRQHandler(){                                                                //fonksiyonun adi kullanilacak kesmenin adi ile ayni olamlidir 
																																										//kesmeler kullanilan pine göre ayarlandi
	if(EXTI_GetITStatus(EXTI_Line6) != RESET){
		
			for(int i = 0; i < 4; i++ ){
					GPIO_WriteBit(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2  ,Bit_SET);
					delay(3600000);
					GPIO_WriteBit(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2  ,Bit_RESET);
					delay(3600000);
			
			}
			EXTI_ClearITPendingBit(EXTI_Line6);                                             //INTERRUP TEKRAR OLURSA DIYEREK INTERRUPT U SIIFIRLADIK
	}
}

int main(){
	gpioConfig();
	extiConfig();
	int ledArray[3] = {GPIO_Pin_0 , GPIO_Pin_1 , GPIO_Pin_2};

while(1){
	
		for(int i=0; i <3; i++){
		 
					GPIO_WriteBit(GPIOB,ledArray[i],Bit_SET);
					delay(3600000);
					GPIO_WriteBit(GPIOB, ledArray[i] ,Bit_RESET);
					delay(3600000);
		
		}
		for(int i=1; i > 0; i--){
		 
					GPIO_WriteBit(GPIOB,ledArray[i],Bit_SET);
					delay(3600000);
					GPIO_WriteBit(GPIOB, ledArray[i] ,Bit_RESET);
					delay(3600000);
		
		}
	
}

}


