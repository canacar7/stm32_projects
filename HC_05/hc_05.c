#include "stm32f10x.h"                  // Device header
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART

char test_message[20] = "can_acar";
char gelen_veri = 0;

void GPIO_Config(){
	
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	//usart pinleri PA9 ve PA10 baglidir
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//TX islemleri  TX---PA9
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//rx islemleri   RX-----PA10
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;   //okuma islemlerinde 
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//led islemleri
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void USART_Config(){
	
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	USART_InitStructure.USART_BaudRate					  = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity              = USART_Parity_No;
	USART_InitStructure.USART_StopBits						= USART_StopBits_1;
	USART_InitStructure.USART_WordLength					= USART_WordLength_8b;
	
	USART_Init(USART1,&USART_InitStructure);
	USART_Cmd(USART1,ENABLE);
}

void usartTranmitter(char *string){

		while(*string){
			while(!(USART1 -> SR & 0X00000040));   //USART BITININ MESGUL OLUO OLMADIGINI ONTROL EDERIZ
			USART_SendData(USART1,*string);
			*string++;	
		}}

void delay(uint32_t time){
		
	while(time--);
}		
		
int main(){
	GPIO_Config();
	USART_Config();

	while(1){
		
//		usartTranmitter(test_message);
//		delay(3500000);
	
		gelen_veri= USART_ReceiveData(USART1);
		
		if(gelen_veri == '0')
			GPIO_SetBits(GPIOB,GPIO_Pin_0);
		if(gelen_veri == '1')
			GPIO_SetBits(GPIOB,GPIO_Pin_1);
		if(gelen_veri == '2')
			GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		if(gelen_veri == '3')
			GPIO_ResetBits(GPIOB,GPIO_Pin_1);

}
}
