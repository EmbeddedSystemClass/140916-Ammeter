/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void Init_PVD(void);
void Init_EEPROM(void);
void Init_Tamper (void);

void Leds_Init (void);
void init_button (void);
void SetSysClockToHSI(void);
void init_nvic (void);
void init_exti (void);
void init_timer1 (void);
void init_timer2 (void);
void init_timer16 (void);
void init_uart2 (void);

void init_adc (void);
void init_adc_comp (void);


void delay_us(unsigned int time);
void delay_ms(uint16_t time);
