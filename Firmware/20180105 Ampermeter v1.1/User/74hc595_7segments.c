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
#include "stdio.h"	
#include "string.h"

#include "main.h"
#include "74hc595_7segments.h"
#include "workspace.h"
#include "led_module.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define AD7799_INTEGR			20

#define SPI1_DR_8bit          (*(__IO uint8_t *)((uint32_t)&(SPI1->DR))) 		

#define LATCHH		GPIOA->BSRR = GPIO_Pin_2					
#define LATCHL		GPIOA->BRR =  GPIO_Pin_2						

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

HC595_t 		HC595;

/*u8	Segments[] = { 
		0b11000000, 	// 0
		0b11111001, 	// 1
		0b10100100, 	// 2
		0b10110000, 	// 3
		0b10011001, 	// 4
		0b10010010, 	// 5
		0b10000010, 	// 6
		0b11111000, 	// 7
		0b10000000, 	// 8
		0b10010000 		// 9 
};*/

u8 Segments[] = {			// Рисование единичками
		0x3F,		// 0
		0x06,		// 1
		0x5B,		// 2
		0x4F,		// 3
		0x66,		// 4
		0x6D,		// 5
		0x7D,		// 6
		0x07,		// 7
		0x7F,		// 8
		0x6F,		// 9 
		0x00		// " " 
};
	
u8	Digit[] = {
		0xFE,  			// K1
		0xFD,  			// K2
		0xFB,  			// K3
		0xF7,  			// K4
		0xEF,			// K5
		0xDF,			// K6		
};

u8	Segmentsh[] = {			// Рисование ноликами
			0xC0, //0
			0xF9, //1
			0xA4, //2
			0xB0, //3
			0x99, //4
			0x92, //5
			0x82, //6
			0xF8, //7
			0x80, //8
			0x90, //9
			0x88, //A
			0x83, //b
			0xC6, //C
			0xA1, //d
			0x86, //E
			0x8E, //F
			0xC2, //G
			0x89, //H
			0xF9, //I
			0xF1, //J
			0xC3, //L
			0xA9, //n
			0xC0, //O
			0x8C, //P
			0x98, //q
			0x92, //S
			0xC1, //U
			0x91, //Y
			0xFE //hight -
};
	
/* Exported variables --------------------------------------------------------*/		
/* Private function prototypes -----------------------------------------------*/

void SPI1_LowLevel_Init (void);
uint8_t Spi1_send (uint8_t data);

/* Private functions ---------------------------------------------------------*/
/*********************************************************************************
  * @brief  
  * @param  None
  * @retval None
*********************************************************************************/
void HC595_Init(void)
{
	SPI1_LowLevel_Init();
}

/*********************************************************************************
  * @brief  
  * @param  None
  * @retval None
*********************************************************************************/
void HC595_Processing(void)
{
	
}

/*********************************************************************************
  * @brief  Вывод на верхний индикатор
  * @param  None
  * @retval None
*********************************************************************************/
void HC595_PrintTop(u16 Val)
{
	HC595.Digit[0] =  Val /100;
	
	if(HC595.Digit[0] == 0)
		HC595.Digit[0] = 10;
	
	HC595.Digit[1] = ((Val %100) /10);
	HC595.Digit[2] =  Val %10;
}

/*********************************************************************************
  * @brief  Вывод на нижний индикатор
  * @param  None
  * @retval None
*********************************************************************************/
void HC595_PrintBot(u16 Val)
{
	HC595.Digit[3] =  Val /100;	
	HC595.Digit[4] = (Val %100) /10;
	HC595.Digit[5] =  Val %10;
}

/*********************************************************************************
  * @brief  
  * @param  None
  * @retval None
*********************************************************************************/
void HC595_PeriodicHandle(void)
{
	static u8 Cnt = 0;
	
	LATCHL;
	Spi1_send(Digit[Cnt]);					//	Разряд
	
	if( (Cnt == 1) || (Cnt == 3))
		Spi1_send(Segments[HC595.Digit[Cnt]] | 0x80);	// 	Сегмент
	else
		Spi1_send(Segments[HC595.Digit[Cnt]]);
		

	
	LATCHH;
	
	Cnt++;
	Cnt = Cnt % 6;
}

/*********************************************************************************
  * @brief  SPI
  * @param  None
  * @retval None
*********************************************************************************/
void SPI1_LowLevel_Init (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	
	//--- GPIOs -----------------------------------------------
	RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOA, ENABLE);
  
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_0);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//--- LATCH Pin	-------------------------------------------
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//--- NVIC ------------------------------------------------
	NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//--- SPI -------------------------------------------------
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_SPI1, ENABLE);
	
	SPI_I2S_DeInit(SPI1);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 0;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_Init(SPI1, &SPI_InitStructure);
	
	SPI_RxFIFOThresholdConfig(SPI1, SPI_RxFIFOThreshold_QF);
  
//  SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);
//  SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_ERR, ENABLE);
  
//	SPI_SSOutputCmd(SPI1, ENABLE);
	SPI_Cmd(SPI1, ENABLE);
}

/*********************************************************************************
  * @brief  Послать 1 байт
  * @param  None
  * @retval None
*********************************************************************************/
uint8_t Spi1_send (uint8_t data)
{   
	while (!(SPI1->SR & SPI_SR_TXE));     
	SPI1_DR_8bit = data;                       
	while (!(SPI1->SR & SPI_SR_RXNE));     
	
	return (SPI1_DR_8bit); 
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
/*
int32_t AdcIntegrator (AdcIntegrator_t* Integr, uint32_t var, u16 n_integr)
{
	int32_t rez;
	
	if(n_integr > 1)
	{
		Integr->Sum -= Integr->Buffer[Integr->Index] ;
		Integr->Buffer[Integr->Index] = var;
		Integr->Sum += var;
		Integr->Index++;
		

//		if		(var > Integr->MaxValue)
//			Integr->MaxValue = var;
//		else if	(var < Integr->MinValue)
//			Integr->MinValue = var;
		
		
		if (Integr->Index > n_integr-1)
		{		
	//		Integr->MaxValue = Integr->Sum/n_integr;;
	//		Integr->MinValue = Integr->Sum/n_integr;;
			Integr->Index = 0;	
		}
	//	rez = (Integr->Sum - Integr->MaxValue - Integr->MinValue)/n_integr-2;
		
		rez = Integr->Sum/n_integr;
	}
	else
	{
		rez = var;
	}
	return rez;
}
*/





