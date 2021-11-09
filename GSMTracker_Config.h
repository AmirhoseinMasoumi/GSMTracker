#ifndef	_SIM808_CONFIG_H
#define	_SIM808_CONFIG_H		

#define	_STM32_family               11                                           //STM32FXxx 1X   ,STM32GXxx 2X   ,STM32H7xx 30   ,STM32LXxx 4X

#define	_USSER_ID                   "123456"                                     //Set your User ID

#define	_SIM80X_USART               huart2                                       //Configur UART

#define _WebServer_URL              "TestAPN"                                    //Set your GSM APN

#define	_GSM_APN                    "http://www.testserver.com/save.php?info="   //Set your WebServer URL

#define	_SIM80X_USE_POWER_KEY       0                                            //Change to 1 if you want to use UART DMA
#define _SIM80X_DMA_TRANSMIT        0                                            //Change to 1 if you want to use Power Key

#define	_SIM80X_POWER_KEY_GPIO      GPIOB                                        //Set Power Key GPIO Group
#define	_SIM80X_POWER_KEY_PIN       GPIO_PIN_7                                   //Set Power key GPIO Pin	 

#endif
