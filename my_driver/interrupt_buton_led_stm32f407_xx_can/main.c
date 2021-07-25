#include <stm32f407xx_can.h>

static void GPIO_Config();
static void EXTI_Buton_Config();

static void delay(uint32_t time);
void EXTI0_IRQHandler ()
{
	if(EXTI -> PR & 0X1)
	{
		/*interupt varsa PR bitini 1 ile temizlemem gerekli */
		EXTI -> PR |= (0X1U << 0U);

		/*interrupt da yapilmasi gereken isleri yapsin */
		GPIO_Toggle_Pin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);


	}
}

int main(void)
{

	GPIO_Config();
	EXTI_Buton_Config();


	for(;;)
	{




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

	memset(&GPIO_InitStructure, 0, sizeof(GPIO_InitStructure));

	GPIO_InitStructure.Mode  	 = GPIO_MODE_INPUT;
	GPIO_InitStructure.pinNumber = GPIO_PIN_0;
	GPIO_InitStructure.PuPd      = GPIO_PUPD_PULL_DOWN;

	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

static void EXTI_Buton_Config()
{
	EXTI_InitTypeDef_t EXTI_InitStructure = {0};


	RCC_SYSCFG_CLK_ENABLE();

	EXTI_LineConfig(EXTI_PortSource_GPIOA, EXTI_LineSource_Pin0);

	EXTI_InitStructure.EXTI_LineCmd 	= ENABLE;
	EXTI_InitStructure.EXTI_LineNumber  = EXTI_LineSource_Pin0;
	EXTI_InitStructure.EXTI_Mode  		= EXTI_Interrupt_Mode;
	EXTI_InitStructure.TriggerSelect    = EXTI_Trigger_Rising_Edge;



	EXTI_Init(&EXTI_InitStructure);

	NVIC_EnableInterrupt(EXTI0_IRQNumber);
}

static void delay(uint32_t time)
{
	while(time--);
}


