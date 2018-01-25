/**
  ******************************************************************************
  * @file    Led.c
  * @author  
  * @version 
  * @date    
  * @brief   
  ******************************************************************************
  * @attention

  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
	
#include "main.h"
#include "led_module.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/	

#define LEDn	1

GPIO_TypeDef* GPIO_PORT[LEDn] = {	GPIOA };

const uint16_t GPIO_PIN[LEDn] = { 	GPIO_Pin_4 };

LEDs_t LED[LEDn];

/* Exported variables --------------------------------------------------------*/	

extern unsigned long SystemCounter;

/* Private function prototypes -----------------------------------------------*/

//void LED_On(Led_TypeDef Led);
//void LED_Off(Led_TypeDef Led);
//void LED_Toggle(Led_TypeDef Led);
		
/* Private functions ---------------------------------------------------------*/

/**********************************************************************
  * @brief  Leds.
  * @param  None
  * @retval None
   ********************************************************************/
void LED_Init (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);	//Clocking

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init (GPIOA, &GPIO_InitStructure);
	
	//-------------------------------------------------------------
/*	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);				//Enable PB3, PB4, PA15
	GPIO_PinRemapConfig(GPIO_Remap_PD01, ENABLE);							//Enable PD0, PD1
*/
	//-------------------------------------------------------------
}

/**********************************************************************
  * @brief  Зажечь 1 диод.
  * @param  None
  * @retval None
   ********************************************************************/
void LED_On(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BSRR = GPIO_PIN[Led];
}
/**********************************************************************
  * @brief  Потушить светодиод.
  * @param  None
  * @retval None
   ********************************************************************/
void LED_Off(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BRR = GPIO_PIN[Led];  
}
/**********************************************************************
  * @brief  Инвертировать светодиод.
  * @param  None
  * @retval None
   ********************************************************************/
void LED_Toggle(Led_TypeDef Led)
{
  GPIO_PORT[Led]->ODR ^= GPIO_PIN[Led];
}

/**********************************************************************
  * @brief  Поток управления светодиодами
  * @param  None
  * @retval None
  ********************************************************************/
//void LED_Processing(void)
//{
//	static u8 i;
//	
//	for (i = 0; i < LEDn; i++)
//	{
//		if ( (LED[i].Status == SET) && (SystemCounter > LED[i].Counter) )
//		{
//			LED_Off((Led_TypeDef)i);
//			LED[i].Status = RESET;
//		}			
//	}
//}

/**********************************************************************
  * @brief  Включение светодиода на время
  * @param  led: Имя светодиода
  *	@param  time_on: Время, которое светодиод будет светить 
  * @retval None
  ********************************************************************/
void LED_TurnON(Led_TypeDef led, u32 time_ms)
{
	LED_On(led);
	LED[led].Times = 1;
	LED[led].Counter = SystemCounter + time_ms;
}

/**********************************************************************
  * @brief  Включение светодиода на время
  * @param  led: Имя светодиода
  *	@param  time_on: Время, которое светодиод будет светить 
  *	@param  time_off: Время, которое он будет проводить в потушенном состоянии
  *	@param  times: Сколько раз нужно моргнуть
  * @retval None
  ********************************************************************/
void LED_TurnON_Blink(Led_TypeDef led, u16 time_on, u16 time_off, u16 times)
{
	LED_On(led);
	LED[led].Counter = SystemCounter + time_on;
	LED[led].TimeOn = time_on;
	LED[led].TimeOff = time_off;
	LED[led].Times = (times*2)-1;
}

/**********************************************************************
  * @brief  Поток управления светодиодами
  * @param  None
  * @retval None
  ********************************************************************/
void LED_Processing(void)
{
	static u8 i;
	
	for (i = 0; i < LEDn; i++)
	{
		if (LED[i].Times != 0)
		{
			if ( (GPIO_ReadInputDataBit(GPIO_PORT[i], GPIO_PIN[i]) == SET) && (SystemCounter > LED[i].Counter) )
			{
				LED_Off((Led_TypeDef)i);
				LED[i].Counter = SystemCounter + LED[i].TimeOff;
				LED[i].Times--;
			}	
			else if ( (GPIO_ReadInputDataBit(GPIO_PORT[i], GPIO_PIN[i]) == RESET) && (SystemCounter > LED[i].Counter) )
			{
				LED_On((Led_TypeDef)i);
				LED[i].Counter = SystemCounter + LED[i].TimeOn;
				LED[i].Times--;
			}
		}		
	}
}










