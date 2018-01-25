/**
  ******************************************************************************
  * @file    workspace.h
  * @author  
  * @version 
  * @date    
  * @brief   
  ******************************************************************************
  * @attention

  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Workspace_H
#define __Workspace_H

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Private typedef -----------------------------------------------------------*/

typedef enum
{
	MEASI = 0,
	VBAT,
	VREF,
	CODSIZE
}AdcCod_e;

typedef struct
{
	u32 Error;
}Flag_t;

typedef struct
{	
	Flag_t	Flag;
	u16 AdcCod[CODSIZE];
	u16	VBat;
	u16	MeasI;
	u16	VRef;
	Integrator_t	IntegrVBAT;
	Integrator_t	IntegrMEASI;
	Integrator_t	IntegrVREF;	
	
	u32	Counter;
}WKSPC_t;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void WKSPC_Init (void);
void WKSPC_Processing (void);


#endif /*__Workspace_H */



/******************END OF FILE*************************************************/











