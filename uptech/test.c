/**********************************************************************
* @file		test.c
* @brief	Example description file
* @version	1.0
* @date		20. Jul. 2015
* @author	Dubuqingfeng
*
* Copyright(C) 2015, Taigu Dubuqingfeng
* All rights reserved.
**********************************************************************/
//Definition of some header files.

#include "lpc18xx_gpio.h"
//#include "lpc_types.h"
#include "lpc18xx_libcfg.h"

#include "lpc18xx_timer.h"

#include "debug_frmwrk.h"
#include "lpc18xx_cgu.h"
#include "lpc18xx_scu.h"


/************************** PRIVATE DEFINITIONS *************************/

/*****GPIO pin define**************************************/
#define PA_4      0xA, 4             //FUNC4: GPIO5[19]
#define LED1      5, (1<<19)         //GPIO5[19]

/*****gpio input/output mode define************************/
#define INPUT_MODE       0
#define OUTPUT_MODE      1

/*****A welcome message************************************/
uint8_t welcome[] =
"*************************************************\n\r"
"Hello EveryOne \n\r"
"I am a rubik solver robot. \n\r"
"I am from SXAU. \n\r"
"\t - MCU: LPC1850 \n\r"
"\t - Core: ARM Cortex-M3 \n\r"
"\t - Communicate via: UART0 - 115200 bps \n\r"
"I am Tested. \n\r"
"By Dubuqingfeng \n\r"
"*************************************************\n\r";
//timer init
TIM_TIMERCFG_Type TIM_ConfigStruct;
TIM_MATCHCFG_Type TIM_MatchConfigStruct;

/************************** PRIVATE FUNCTIONS *************************/
/*****private function pre-define**************************/
void print_menu(void);
void GPIO_Servo_init(void);
void Timers_init(void);
void TIMER0_IRQHandler(void);
void delay(uint32_t);
/*********************************************************************//**
 * @brief		Print menu
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void print_menu(void)
{
	_DBG(welcome);
}

/*********************************************************************//**
 * @brief		GPIO_Servo_init
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void GPIO_Servo_init(void)
{
	scu_pinmux(PA_4, MD_PLN_FAST, FUNC4);
  	GPIO_SetDir(LED1, OUTPUT_MODE);

  	GPIO_ClearValue(LED1);
}

/*********************************************************************//**
 * @brief		Timers_init
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void Timers_init(void)
{
	// Initialize timer 0, prescale count time of 100uS
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
	TIM_ConfigStruct.PrescaleValue	= 100;

	// use channel 0, MR0
	TIM_MatchConfigStruct.MatchChannel = 0;
	// Disable interrupt when MR0 matches the value in TC register
	TIM_MatchConfigStruct.IntOnMatch   = TRUE;
	//Enable reset on MR0: TIMER will reset if MR0 matches it
	TIM_MatchConfigStruct.ResetOnMatch = TRUE;
	//Stop on MR0 if MR0 matches it
	TIM_MatchConfigStruct.StopOnMatch  = FALSE;
	//Toggle MR0.0 pin if MR0 matches it
	TIM_MatchConfigStruct.ExtMatchOutputType =TIM_EXTMATCH_TOGGLE;
	// Set Match value, count value of 10000 (10000 * 100uS = 1000mS --> 1Hz)
	TIM_MatchConfigStruct.MatchValue   = 10000;

	// Set configuration for Tim_config and Tim_MatchConfig
	TIM_Init(LPC_TIMER0, TIM_TIMER_MODE,&TIM_ConfigStruct);
	TIM_ConfigMatch(LPC_TIMER0,&TIM_MatchConfigStruct);
}

/*********************************************************************//**
 * @brief		Timer0_IRQ
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void TIMER0_IRQHandler(void)
{
	//TIM_ClearIntPending
      TIM_ClearIntPending(LPC_TIM0,0);
      GPIO_SetValue(LED1);
      GPIO_ClearValue(LED1);
}

void delay(uint32_t n)
{
  uint32_t i;
  while(n--)
  {
    i = 1000;
    while(i--);
  }
}

/*********************************************************************//**
 * @brief		Main program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
/****
 *
 *
 **/
int c_entry (void) {                       /* Main Program                       */
	SystemInit();
	CGU_Init();

	/* Initialize debug via UART0
	 * 115200bps
	 * 8 data bit
	 * No parity
	 * 1 stop bit
	 * No flow control
	 */
	debug_frmwrk_init();

	print_menu();

	GPIO_Servo_init();

	Timers_init();

	NVIC_SetPriority(TIMER0_IRQn, ((0x01<<3)|0x01));

	NVIC_EnableIRQ(TIMER0_IRQn);

	TIM_Cmd(LPC_TIM0,ENABLE);

	return 0;
}
/* With ARM and GHS toolsets, the entry point is main() - this will
   allow the linker to generate wrapper code to setup stacks, allocate
   heap area, and initialize and copy code and data segments. For GNU
   toolsets, the entry point is through __start() in the crt0_gnu.asm
   file, and that startup code will setup stacks and data */
int main(void)
{
    return c_entry();
}