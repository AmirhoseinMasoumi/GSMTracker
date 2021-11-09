# Discription
GSMTracker is a library with use SIM808 module to send GPS data to the web server.      
This Library using STM32_HAL_UART library. You should first add STM32_HAL_UART for your STM32 family to your project.       
This Library also supports UART DMA.

### This Library supports:

#### MCU:

| STM32         | Required Library     |
| ------------- |:--------------------:|
| STM32F0xx     | stm32f0xx_hal_uart.h |
| STM32F1xx     | stm32f1xx_hal_uart.h |
| STM32F2xx     | stm32f2xx_hal_uart.h |
| STM32F3xx     | stm32f3xx_hal_uart.h |
| STM32F4xx     | stm32f4xx_hal_uart.h |
| STM32F7xx     | stm32f7xx_hal_uart.h |
| STM32G0xx     | stm32g0xx_hal_uart.h |
| STM32G4xx     | stm32g4xx_hal_uart.h |
| STM32H7xx     | stm32h7xx_hal_uart.h |
| STM32L0xx     | stm32l0xx_hal_uart.h |
| STM32L1xx     | stm32l1xx_hal_uart.h |
| STM32L4xx     | stm32l4xx_hal_uart.h |
| STM32L5xx     | stm32l5xx_hal_uart.h |

#### GSM Module:
- SIM808

## Setup:
- Enable UART (Enable DMA if you want).
- Enable a gpio as output and open drain to connect gsm power button.
- Add GSMTracker and UART library to your project.
- Configure `GSMTracker_Config.h' file.
- Call `SetPower()`.
- Call `SendCoordinates()` in infinit loop.
