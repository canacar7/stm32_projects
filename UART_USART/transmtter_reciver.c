#include "stm32f10x.h"                  // Device header
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART

char test[25] = "can_acar";
uint16_t veri = 0;
void gpioConfig(){
	 GPIO_InitTypeDef GPIO_InitStructure;	
	 

	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	 //TX
	 //TC--pa9 a bagli
	 //TX e ait ayarlar
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	 GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	 GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	 //RX
	 //RX--pa10 a bagli
	 //RX e ait ayarlar
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //okuma islemi yapcaz
	 GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;
	
	 GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	 //led icin
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	 GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
}

void uartConfig(){
	USART_InitTypeDef UART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	UART_InitStructure.USART_BaudRate            = 9600;
	UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //kullanmicaz
	UART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Tx;  //tx ve rx aktif ettim
	UART_InitStructure.USART_Parity              = USART_Parity_No;
	UART_InitStructure.USART_StopBits            = USART_StopBits_1;               //1 stop biti iceriyor
	UART_InitStructure.USART_WordLength          = USART_WordLength_8b;						 //8bit uzuugunda veriler gönderiliyor
	
	USART_Init(USART1,&UART_InitStructure);
	USART_Cmd(USART1,ENABLE);
}
void uartTransmit(char *string){
	
		//biz verileri tek karakter olarak gönderebilirz onun iicn dongu icerisinde gondermeliyiz
		while(*string){
			
				while(!USART1 -> SR & 0x00000040); //sr registri bos ise  datalariimizi gonderecek 
				//gonderimin tamamlanip tamamlanmadigina bakar eger datamiz gönderilmisse bir sonraki adima gecebilir
				USART_SendData(USART1,*string);
				*string++;
			
		}

}

void delay(uint32_t time)
{
	while(time--);
}
int main(){
gpioConfig();
uartConfig();
	while(1){
	//uartTransmit(test);
	veri = USART_ReceiveData(USART1); //sistemde hali hazirda bulunan bir fonksiyon olusturmamiza gerek yoktu	
	
		if(veri == '1'){
				GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
				delay(72000000);
		}
		else	
				GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);
		
	}
}
