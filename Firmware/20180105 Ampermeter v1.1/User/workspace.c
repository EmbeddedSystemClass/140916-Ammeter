/**
  ******************************************************************************
  * @file    workspace.c
  * @author  
  * @version 
  * @date    
  * @brief   
  ******************************************************************************
  * @attention

  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#include "string.h"
#include "stdio.h"

#include "main.h"
#include "workspace.h"
#include "led_module.h"
#include "font_tahoma8.h"
#include "74hc595_7segments.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ADC1_DR_Address   	0x40012440

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/	

WKSPC_t	WKSPC;

/* Exported variables --------------------------------------------------------*/

extern u32	SystemCounter;

/* Private function prototypes -----------------------------------------------*/
void ADC_LowLevel_Init(void);

/* Private functions ---------------------------------------------------------*/

/*********************************************************************************
  * @brief  
  * @param  None
  * @retval None
*********************************************************************************/
void DMA1_Channel1_IRQHandler (void)
{
	if(DMA_GetITStatus(DMA1_IT_TC1))
	{
		DMA_ClearITPendingBit(DMA1_IT_GL1);
//		LED_On(LED9);
				
		WKSPC.IntegrVBAT.Sum += WKSPC.AdcCod[VBAT];
		WKSPC.IntegrMEASI.Sum += WKSPC.AdcCod[MEASI];
		WKSPC.IntegrVREF.Sum += WKSPC.AdcCod[VREF];		
		
		if(WKSPC.IntegrVBAT.Index == 9)
		{
			WKSPC.VRef =   ( WKSPC.IntegrVREF.Sum * 330) /0xFFF;			// Опорное напряжение АЦП
			WKSPC.VBat = ( ( WKSPC.IntegrVBAT.Sum * 330) /4096 *1224 /WKSPC.VRef) *100/13;
			WKSPC.MeasI =( ( WKSPC.IntegrMEASI.Sum * 330) /4096 *1224 /WKSPC.VRef);	
			
			WKSPC.MeasI = WKSPC.MeasI *1000 /165;
			
			WKSPC.IntegrVBAT.Index = 0;
			WKSPC.IntegrVBAT.Sum = 0;
			WKSPC.IntegrMEASI.Sum = 0;
			WKSPC.IntegrVREF.Sum = 0;
		}	
		else
			WKSPC.IntegrVBAT.Index++;
	}
}

/*********************************************************************************
  * @brief  
  * @param  None
  * @retval None
*********************************************************************************/
void WKSPC_Init (void)
{
	ADC_LowLevel_Init();
	memset(&WKSPC, 0, sizeof(WKSPC_t) );
}
	
/*********************************************************************************
  * @brief  Алгоритм работы весов
  * @param  None
  * @retval None
*********************************************************************************/
void WKSPC_Processing (void)
{
	if(WKSPC.Counter < SystemCounter)
	{
		WKSPC.Counter = SystemCounter + 200;
		
		HC595_PrintTop(WKSPC.VBat/100);
		HC595_PrintBot(WKSPC.MeasI/210);			// Коэф. для резисторов 209К и 10к неинвертирующего усилителя.
	}	
	
}


/*********************************************************************************
  * @brief  Тут можно проанализировать принятые данные
  * @param  None
  * @retval None
*********************************************************************************/
void WKSPC_PacketHandle (void)
{
	
}

/*********************************************************************************
  * @brief  
  * @param  None
  * @retval None
*********************************************************************************/
void ADC_LowLevel_Init(void)
{	
	GPIO_InitTypeDef    GPIO_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;
	ADC_InitTypeDef     ADC_InitStructure;
	DMA_InitTypeDef   	DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd (RCC_AHBPeriph_DMA1 , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	//--- GPIO ------------------------------------------------------------
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//--- NVIC ------------------------------------------------------------
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//--- DMA -------------------------------------------------------------
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address; //0x40012440
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)WKSPC.AdcCod;	//DataTmp
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 3;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	DMA_ITConfig(DMA1_Channel1, DMA1_IT_TC1, ENABLE);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	//--- ADC -------------------------------------------------------------
	
	ADC_DeInit(ADC1);	
//	ADC_ClockModeConfig(ADC1, ADC_ClockMode_SynClkDiv4);
	ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);
	
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
	ADC_Init(ADC1, &ADC_InitStructure); 
	
	ADC_ChannelConfig(ADC1, ADC_Channel_6 , ADC_SampleTime_239_5Cycles);
	ADC_ChannelConfig(ADC1, ADC_Channel_9 , ADC_SampleTime_239_5Cycles);
	
	ADC_ChannelConfig(ADC1, ADC_Channel_Vrefint , ADC_SampleTime_239_5Cycles); 
	ADC_VrefintCmd(ENABLE);
	
	ADC_GetCalibrationFactor(ADC1);
	ADC_Cmd(ADC1, ENABLE);  
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)); 
	//--- Start -----------------------------------------------------------
	//ADC_DMARequestModeConfig
//	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	ADC_DMACmd(ADC1, ENABLE); 
	ADC_StartOfConversion(ADC1);
}


/*********************************************************************************
  * @brief  
  * @param  None
  * @retval None
*********************************************************************************/
int32_t Adc_Integrator (Integrator_t* Integr, uint32_t var, u16 n_integr)
{
	static int32_t rez;
	
	Integr->Sum -= Integr->Buffer[Integr->Index] ;
	Integr->Buffer[Integr->Index] = var;
	Integr->Sum += var;
	Integr->Index++;
	
	if (Integr->Index > n_integr-1)
		Integr->Index = 0;
	
	rez = Integr->Sum/n_integr;
	
	return rez;
}

/**********************************************************************
  * @brief  Фильтр Калмана для температуры.
  * @param  None
  * @retval None
  ********************************************************************/
s32	AdcKalmanFilter(s32 val)
{
	static s32 K = 200;		// 1000/2 = 0.5
	static s32 prev_val = 0;
	s32	result;
	s32	result1;
	s32	result2;
	
//	result = (((K*val)+((1000000-K)*prev_val))/1000000);
	result1 = (K*val);
	result2 = ((1000-K)*prev_val);
	result = (result1 + result2);
	result = result/1000;
	
	prev_val = result;
	return result;
}

/*********************************************************************************
  * @brief  
  * @param  None
  * @retval None
*********************************************************************************/
/*********************************************************************************
  * @brief  
  * @param  None
  * @retval None
*********************************************************************************/

/*********************************************************************************
  * @brief  
  * @param  None
  * @retval None
*********************************************************************************/

/*********************************************************************************
  * @brief  
  * @param  None
  * @retval None
*********************************************************************************/

/*********************************************************************************
  * @brief  
  * @param  None
  * @retval None
*********************************************************************************/






























