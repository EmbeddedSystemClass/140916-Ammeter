
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include "init.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
void delay_us(unsigned int time)
{
	time = time*4;
	while(time--)
 	 {
 	 }
}

/*********************************************************************************
  * @brief  Инициализация PVD с прерыванием
  * @param  None
  * @retval None
*********************************************************************************/
void Init_PVD(void)
{  

}
	
/*********************************************************************************
  * @brief  Тактирование от внутреннего 8МГц.
	* Настройка  проводится по порядку по схеме из даташита.
  * @param  None
  * @retval None
*********************************************************************************/
void SetSysClockToHSI(void)
{	   //Коэффициент умножения PLL = 6, источник - HSI/2 = 4MHz  
/*	RCC_DeInit();
	
	RCC->CFGR &=~((RCC_CFGR_PLLSRC|RCC_CFGR_PLLXTPRE|RCC_CFGR_PLLMULL)); // Предочистка	
	RCC->CR |= RCC_CR_HSION;  //Internal High Speed clock enable
	while ((RCC->CR & RCC_CR_HSIRDY)==0); //Ожидание готовности HSI		
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_Div2; //Тактировать PLL от HSI/PREDIV2
	RCC->CFGR|=((6 - 2)<<18); //Умножать частоту на PLL_MUL
	RCC->CR |= RCC_CR_PLLON; //Запустить PLL
	while ((RCC->CR & RCC_CR_PLLRDY)==0); // Ожидание готовности PLL
	RCC->CFGR &=~RCC_CFGR_SW; // Очистить биты SW0, SW1
	RCC->CFGR |= RCC_CFGR_SW_PLL; //Тактирование с выхода PLL
	while ((RCC->CFGR&RCC_CFGR_SWS)!=0x08); // Ожидание переключения на PLL	
	RCC->CR &= ~RCC_CR_HSEON;  //External High Speed clock disable
*/
	RCC_DeInit();
	
	RCC_HSICmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET) {};
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);
	RCC_PLLCmd(ENABLE);
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	while (RCC_GetSYSCLKSource() != 0x08) {};		
}


/*********************************************************************************
  * @brief  Инициализация EEPROM
  * @param  None
  * @retval None
*********************************************************************************/
//void Init_EEPROM(void)
//{
//	FLASH_Unlock();										// Unlock the Flash Program Erase controller
//	
//	if ((*(__IO uint16_t*) EEPROM_START_ADDRESS ) == 0xFFFF)
//	{
//		FLASH_ProgramHalfWord(EEPROM_START_ADDRESS, 0x0000);
//	}
//	
////	ShowDigit = (*(__IO uint16_t*)EEPROM_START_ADDRESS);
//	
//	FLASH_ErasePage(EEPROM_START_ADDRESS);	
//	
//}


/*********************************************************************************
  * @brief  Событие TAMPER
  * @param  None
  * @retval None
*********************************************************************************/
void Init_Tamper (void)
{
	
}


/**********************************************************************
  * @brief  Leds.
  * @param  None
  * @retval None
   ********************************************************************/
void Leds_Init (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA , ENABLE);	//Clocking GPIOC
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init (GPIOA, &GPIO_InitStructure);
	
	//-------------------------------------------------------------
/*	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);	//Enable PB3, PB4, PA15
	GPIO_PinRemapConfig(GPIO_Remap_PD01, ENABLE);				//Enable PD0, PD1
*/
	//-------------------------------------------------------------
}

/**********************************************************************
  * @brief  Кнопка PA0
  * @param  None
  * @retval None
   ********************************************************************/
void init_button (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
//Инициализация кнопки PA0
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init (GPIOA, &GPIO_InitStructure);
}



