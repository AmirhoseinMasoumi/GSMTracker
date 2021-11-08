#ifndef	_GSMTracker_CONFIG_H
#define	_GSMTracker_CONFIG_H		

#define	_STM32_family								11					 	//STM32FXxx 1X   ,STM32GXxx 2X   ,STM32H7xx 30   ,STM32LXxx 4X

#define	_USSER_ID				        		"123456"

#define	_SIM80X_USART				        huart2

#define	_SIM80X_USE_POWER_KEY   	  0

#define _SIM80X_DMA_TRANSMIT        0


#define	_SIM80X_POWER_KEY_GPIO		  GPIOB          
#define	_SIM80X_POWER_KEY_PIN		    GPIO_PIN_7		 

#endif
