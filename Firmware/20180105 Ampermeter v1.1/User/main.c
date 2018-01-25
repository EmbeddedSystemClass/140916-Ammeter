/**
  ******************************************************************************
  * @file    main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    01-September-2014
  * @brief   Main program body.
  ******************************************************************************
  * @attention
  *
  */ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "init.h"
#include "74hc595_7segments.h"
#include "led_module.h"
#include "workspace.h"
#include "74hc595_7segments.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t TimingDelay;
RCC_ClocksTypeDef RCC_Clocks;

u32	DelayCounter;
u8	Trigg = 0;
/* Exported variables --------------------------------------------------------*/
extern u32	SystemCounter;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*********************************************************************************
  * @brief  Main program.
  * @param  None
  * @retval None
*********************************************************************************/
int main(void)
{
	__disable_irq();
	
	SysTick_Config(SystemCoreClock / 1000);
	NVIC_SetPriority(SysTick_IRQn, 0x0);
	SetSysClockToHSI();							// Настройка HSI 48MHz	
	RCC_GetClocksFreq(&RCC_Clocks);
	
	__enable_irq();

	LED_Init();			// PB12
	HC595_Init();  	// PA3, PA5, PB4
	WKSPC_Init();
		
	while (1)
	{    

		HC595_Processing();
		WKSPC_Processing();
		LED_Processing();
		
		if(DelayCounter < SystemCounter)
		{
			DelayCounter = SystemCounter + 500;
			
//			LED_TurnON(LED4, 10);
/*			if(Trigg )
			{
				Trigg = !Trigg;
				LED_On(LED12);
			}
			else
			{
				Trigg = !Trigg;
				LED_Off(LED12);
			}	*/
		}	
	}
}



/**********************************************************************
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  ********************************************************************/
void Delay(uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**********************************************************************
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  ********************************************************************/
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

/*********************************************************************************
  * @brief  
  * @param  None
  * @retval None
*********************************************************************************/
int32_t Integrator (Integrator_t* Integr, int32_t var, u16 n_integr)
{
	int32_t rez;
	
	Integr->Sum -= Integr->Buffer[Integr->Index] ;
	Integr->Buffer[Integr->Index] = var;
	Integr->Sum += var;
	Integr->Index++;
	
	if (Integr->Index > n_integr-1)
		Integr->Index = 0;
	
	rez = Integr->Sum/n_integr;
	
	return rez;
}



/**
  * @brief  Writes data Backup DRx registers.
  * @param  FirstBackupData: data to be written to Backup data registers.
  * @retval None
  */






/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
