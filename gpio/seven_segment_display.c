#include "stm32f10x.h" // Device header



void gpioconfig(){



GPIO_InitTypeDef GPIOInitStructure ;

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);





GPIOInitStructure.GPIO_Mode=GPIO_Mode_Out_PP;

GPIOInitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 ;

GPIOInitStructure.GPIO_Speed=GPIO_Speed_50MHz;

GPIO_Init(GPIOB,&GPIOInitStructure);

}

void delay(uint32_t time){



while(time--){





}



}



void allsetHIGH(){

GPIO_SetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 |GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8) ;



}



void zero(){

GPIO_SetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_5);

GPIO_ResetBits(GPIOB, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8) ;





}



void one(){



GPIO_SetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_8) ;

GPIO_ResetBits(GPIOB,GPIO_Pin_4 | GPIO_Pin_6);

}



void two(){



GPIO_SetBits(GPIOB,GPIO_Pin_2 | GPIO_Pin_5 | GPIO_Pin_6);

GPIO_ResetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_7 | GPIO_Pin_8) ;

}



void three(){



GPIO_SetBits(GPIOB,GPIO_Pin_2 | GPIO_Pin_5 | GPIO_Pin_8);

GPIO_ResetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7) ;



}



void four(){



GPIO_SetBits(GPIOB, GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_8) ;

GPIO_ResetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_6);



}



void five(){





GPIO_SetBits(GPIOB, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8);

GPIO_ResetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7 ) ;



}



void six (){



GPIO_SetBits(GPIOB,GPIO_Pin_4 |GPIO_Pin_5);

GPIO_ResetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8) ;



}



void seven(){



GPIO_SetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_8) ;

GPIO_ResetBits(GPIOB,GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6);



}

void eight(){





GPIO_SetBits(GPIOB,GPIO_Pin_5);

GPIO_ResetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8) ;



}



void nine(){

GPIO_SetBits(GPIOB,GPIO_Pin_5 | GPIO_Pin_8);

GPIO_ResetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7 ) ;





}



int main(){



gpioconfig();



while(1){



allsetHIGH();

delay(3600000);

zero();

delay(3600000);

one();

delay(3600000);

two();

delay(3600000);

three();

delay(3600000);

four();

delay(3600000);

five();

delay(3600000);

six();

delay(3600000);

seven();

delay(3600000);

eight();

delay(3600000);

nine();

delay(3600000);

eight();

delay(3600000);

seven();

delay(3600000);

six();

delay(3600000);

five();

delay(3600000);

four();

delay(3600000);

three();

delay(3600000);

one();

delay(3600000);

zero();

delay(3600000);





}



}



