# Discription
GSMTracker is a library with use SIM808 module to send GPS data to the web server.      
This Library using STM32_HAL_UART library. You should first add STM32_HAL_UART for your STM32 family to your project.       
This Library also supports UART DMA.

### This Library supports:

#### MCU:

| STM32         | Required Library     | Configuration code |
| ------------- |:--------------------:| ------------------:|
| STM32F0xx     | stm32f0xx_hal_uart.h |         10         |
| STM32F1xx     | stm32f1xx_hal_uart.h |         11         |
| STM32F2xx     | stm32f2xx_hal_uart.h |         12         |
| STM32F3xx     | stm32f3xx_hal_uart.h |         13         |
| STM32F4xx     | stm32f4xx_hal_uart.h |         14         |
| STM32F7xx     | stm32f7xx_hal_uart.h |         17         |
| STM32G0xx     | stm32g0xx_hal_uart.h |         20         |
| STM32G4xx     | stm32g4xx_hal_uart.h |         24         |
| STM32H7xx     | stm32h7xx_hal_uart.h |         37         |
| STM32L0xx     | stm32l0xx_hal_uart.h |         40         |
| STM32L1xx     | stm32l1xx_hal_uart.h |         41         |
| STM32L4xx     | stm32l4xx_hal_uart.h |         44         |
| STM32L5xx     | stm32l5xx_hal_uart.h |         45         |

#### GSM Module:
- SIM808

## Setup:
- Enable UART (Enable DMA if you want).
- Enable a gpio as output and open drain to connect gsm power button.
- Add GSMTracker and UART library to your project.
- Configure `GSMTracker_Config.h` file.
- Call `SetPower()`.
- Call `SendCoordinates()` in infinit loop.

---

## example:
- GSMTracker_Config.h 
```
#define	_STM32_family               11                                           //STM32FXxx 1X   ,STM32GXxx 2X   ,STM32H7xx 30   ,STM32LXxx 4X
#define	_USSER_ID                   "123456"                                     //Set your User ID
#define	_SIM80X_USART               huart2                                       //Configur UART
#define _WebServer_URL              "TestAPN"                                    //Set your GSM APN
#define	_GSM_APN                    "http://www.testserver.com/save.php?info="   //Set your WebServer URL
#define	_SIM80X_USE_POWER_KEY       0                                            //Change to 1 if you want to use UART DMA
#define _SIM80X_DMA_TRANSMIT        0                                            //Change to 1 if you want to use Power Key
#define	_SIM80X_POWER_KEY_GPIO      GPIOB                                        //Set Power Key GPIO Group
#define	_SIM80X_POWER_KEY_PIN       GPIO_PIN_7                                   //Set Power key GPIO Pin
```
- main.c
```
#include "GSMTracker.h"

int main()
{
  GSMTracker_init();
  while (1)
  {
    SendCoordinates();
  }  
}
```
