/**
  ******************************************************************************
  * @file    SysTick/main.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Header for main.c module
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

/* Exported types ------------------------------------------------------------*/

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef struct
{
	uint16_t Index;
	int32_t Sum;
	int32_t Buffer[10];
}	Integrator_t;

//typedef struct
//{
//	uint16_t Index;
//	int32_t Sum;
//	int32_t Buffer[120];
//}	IntegratorAdv_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

//#define EEPROM_START_ADDRESS    ((uint32_t)0x00007000)

#define PVD_IRQ_Priority			0

/* Exported functions ------------------------------------------------------- */
void TimingDelay_Decrement(void);
void Delay(uint32_t nTime);
int32_t Integrator (Integrator_t* Integr, int32_t var, u16 n_integr);


#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
