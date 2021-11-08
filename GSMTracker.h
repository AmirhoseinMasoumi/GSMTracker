#ifndef	_GSMTracker_H
#define	_GSMTracker_H

#include "GSMTracker_Config.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#if (_STM32_family == 10)
	#include "stm32f0xx_hal_uart.h"
#elif (_STM32_family == 11)
	#include "stm32f1xx_hal_uart.h"
#elif (_STM32_family == 12)
	#include "stm32f2xx_hal_uart.h"	
#elif (_STM32_family == 13)
	#include "stm32f3xx_hal_uart.h"	
#elif (_STM32_family == 14)
	#include "stm32f4xx_hal_uart.h"
#elif (_STM32_family == 17)
	#include "stm32f7xx_hal_uart.h"
#elif (_STM32_family == 20)
	#include "stm32g0xx_hal_uart.h"
#elif (_STM32_family == 24)
	#include "stm32g4xx_hal_uart.h"
#elif (_STM32_family == 30)
	#include "stm32h7xx_hal_uart.h"
#elif (_STM32_family == 40)
	#include "stm32l0xx_hal_uart.h"
#elif (_STM32_family == 41)
	#include "stm32l1xx_hal_uart.h"
#elif (_STM32_family == 44)
	#include "stm32l4xx_hal_uart.h"
#elif (_STM32_family == 45)
	#include "stm32l5xx_hal_uart.h"
#else
#error "There is not selected STM32 family used. Check Sim808_Config.h file for configuration!"
#endif

extern UART_HandleTypeDef _SIM80X_USART;

//**************************************************************
//**************************************************************
//**************************************************************
//**************************************************************

//**************************************************************
//************************* At Command *************************
typedef struct
{
  uint8_t               SendATCommand[400];
	uint8_t               ReceiveAnswer[500];  
  
}SendAndReceive_t;
//**************************************************************
//*********************** GPRS SendData ************************
typedef struct
{
  
  //
  SendAndReceive_t     SendAndReceive;
  //
  
}Sim808_t;
//**************************************************************
//**************************************************************
//**************************************************************
//**************************************************************
extern Sim808_t        SIM808;

//**************************************************************
//**************************************************************
//**************************************************************
void SendAtCommand (char *AtCommand,int32_t  MaxWaitingTX_ms,int32_t  MaxWaitingRX_ms,int32_t  Delay);
bool FindAnswer (const char *Word);
void Sim80x_InitValue(void);
void SetPower(void);
void ResetModule(void);
void SetAPN(char *APN);
void initialiseGSM (void);
void initialiseHTTP (void);
void  SetHTTPurl(char *URL);
void ConcatHTTPurl (char *Longitude,char *Latitude,char *Altitude,char *Speed,char *ID);
void HTTPaction (char *Mode);
void initialiseGNS (void);
void FindtLocation(void);
void SplitCoordinates(char* strIn,char* strOut,uint8_t startIndex,uint8_t endIndex);
void SendCoordinates (void);
void SetFactoryDefault (void);
//**************************************************************
//**************************************************************
//**************************************************************
//**************************************************************


#endif

