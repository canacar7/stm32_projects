#include <stm32f407xx_can.h>

static void GPIO_Config();


int main(void)
{

	GPIO_Config();



	for(;;)
	{


		if(GPIO_Read_Pin(GPIOA, GPIO_PIN_0) == GPIO_Pin_Set){

			GPIO_Write_Pin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15,  GPIO_Pin_Set);
		}
		else{
			GPIO_Write_Pin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15,  GPIO_Pin_Reset);
		}
	}
}

static void GPIO_Config(){

	//led ler icin config
	GPIO_InitTypeDef_t GPIO_InitStructure = {0};

	RCC_GPIOD_CLK_ENABLE();
	RCC_GPIOA_CLK_ENABLE();

	GPIO_InitStructure.Mode  	 = GPIO_MODE_OUTPUT;
	GPIO_InitStructure.Otype 	 = GPIO_OTYPE_PP;
	GPIO_InitStructure.pinNumber = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15 ;
	GPIO_InitStructure.Speed     = GPIO_SPEED_YUKSEK;
	GPIO_InitStructure.PuPd      = GPIO_PUPD_NO_PULL_DOWN_UP;

	GPIO_Init(GPIOD, &GPIO_InitStructure);

	//buton icin config
	//ayarlamalarda structure yapisini zero ya cekdik

	GPIO_InitStructure.Mode  	 = GPIO_MODE_INPUT;
	GPIO_InitStructure.pinNumber = GPIO_PIN_0;
	GPIO_InitStructure.PuPd      = GPIO_PUPD_PULL_DOWN;

	GPIO_Init(GPIOA, &GPIO_InitStructure);


}





