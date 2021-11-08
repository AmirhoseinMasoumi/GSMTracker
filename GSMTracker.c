#include "GSMTracker"
#include "GSMTracker_Config.h"



/******************************* VARIABLE ****************************************/
uint8_t    SendATCommand[400];
uint8_t    ReceiveAnswer[400];
uint8_t    Index[18];	
char       Coordinates[4][20];
char       HTTPurl[400];
int 		 	 StrLen;
uint8_t 	 Temp[25];

/******************************* SEND AT COMMAND ****************************************/
void SendAtCommand (char *AtCommand,int32_t  MaxWaitingTX_ms,int32_t  MaxWaitingRX_ms,int32_t  Delay){
	
	memset(SendATCommand,0,sizeof(SendATCommand));
	memset(ReceiveAnswer,0,sizeof(ReceiveAnswer));
	strcpy((char *)SendATCommand, AtCommand);
	
	#if (_SIM80X_DMA_TRANSMIT)
	HAL_UART_Transmit_DMA(&_SIM80X_USART,SendATCommand,strlen(AtCommand));
	while(__HAL_UART_GET_FLAG(&_SIM80X_USART,UART_FLAG_RXNE) == RESET);
	HAL_UART_Receive_DMA(&_SIM80X_USART,ReceiveAnswer, sizeof(ReceiveAnswer));
	#else
	HAL_UART_Transmit(&_SIM80X_USART,(uint8_t *)SendATCommand,strlen(AtCommand),MaxWaitingTX_ms);
	while(__HAL_UART_GET_FLAG(&_SIM80X_USART,UART_FLAG_RXNE) == RESET);
	HAL_UART_Receive(&_SIM80X_USART,(uint8_t *)ReceiveAnswer, sizeof(ReceiveAnswer),MaxWaitingRX_ms);
	#endif	
}

/******************************* FIND ANSWER ****************************************/
bool FindAnswer (const char *NewData){
	
	char *ret;
	
  ret = strstr((char *)ReceiveAnswer, NewData);
	if(ret){
		return 1;
	}
	else{
		return 0;
	}	
}

/******************************* SET POWER ****************************************/
void  SetPower(void){
	
	uint8_t    Try = 0;	
	
	SendAtCommand("AT\n\r",200,1000,1000);
	if(FindAnswer ("ERROR")){
		while(Try < 3){
			SendAtCommand("AT\n\r",200,1000,1000);
			if(FindAnswer ("OK")){
				Try = 0;
				break;
			}
			Try++;
		}
		if(Try == 2){
			ResetModule();
			SetPower();
			Try = 0;
		}
	}
}
	
/******************************* RESET MODULE ****************************************/
void ResetModule(void){
	
	HAL_GPIO_WritePin(_SIM80X_POWER_KEY_GPIO,_SIM80X_POWER_KEY_PIN,GPIO_PIN_RESET);
	HAL_Delay(1500);
	HAL_GPIO_WritePin(_SIM80X_POWER_KEY_GPIO,_SIM80X_POWER_KEY_PIN,GPIO_PIN_SET);
	HAL_Delay(5000);
}
	
/********************************* SET APN *******************************************/
void  SetAPN(char *APN){
	
	uint8_t Temp[200];
	uint8_t Flag;
	uint8_t Try;
	
	strcpy((char *)Temp,"AT+SAPBR=3,1,\"APN\",\"");
	strcat((char *)Temp, APN);
	strcat((char *)Temp, "\"\n\r");
	SendAtCommand((char *)Temp,200,1000,1000);
	if(FindAnswer ("OK")){
		Flag = 1;		
	}
	if((FindAnswer ("ERROR")) && Flag == 0){
		while(Try < 3){
			SetAPN(APN);
			Try++;
		}
		if(Try == 2){
			ResetModule();
			SetPower();
			Try = 0;
		}		
	}
	memset(Temp,0,sizeof(Temp));
	initialiseGSM();	
}

/******************************* INITIALISE GSM ****************************************/
void initialiseGSM (void){
	
	uint8_t Try_GSM = 0;
	
	SendAtCommand("AT+SAPBR =1,1\n\r",200,1000,1000);
	if(FindAnswer ("ERROR")){
		while(Try_GSM < 3){
			SendAtCommand("AT+SAPBR =1,1\n\r",200,1000,1000);
			if(FindAnswer ("OK")){
				Try_GSM = 0;
				break;
			}
			Try_GSM++;
		}
		if(Try_GSM == 2){
			ResetModule();
			SetPower();
			Try_GSM = 0;
		}
	}
	initialiseHTTP();
}

/******************************* INITIALISE HTTP ***************************************/
void initialiseHTTP (void){
	
	uint8_t Try_HTTP = 0;
	
	SendAtCommand("AT+HTTPINIT\n\r",200,1000,1000);
	while(Try_HTTP < 3){
			SendAtCommand("AT+HTTPINIT\n\r",200,1000,1000);
			if(FindAnswer ("OK")){
				Try_HTTP = 0;
				break;
			}
			Try_HTTP++;
		}
	SendAtCommand("AT+HTTPPARA=\"CID\",1\n\r",200,1000,1000);
	if(FindAnswer ("ERROR")){
		Try_HTTP = 0;
		while(Try_HTTP < 3){
			SendAtCommand("AT+HTTPPARA=\"CID\",1\n\r",200,1000,1000);
			if(FindAnswer ("OK")){
				Try_HTTP = 0;
				break;		
			}
			Try_HTTP++;
		}
		if(Try_HTTP == 2){
			ResetModule();
			SetPower();
			Try_HTTP = 0;
		}
	}
	initialiseGNS();
}

/********************************* SET HTTP URL *******************************************/
void  SetHTTPurl(char *URL){
	strcpy(HTTPurl,URL);
}

/******************************** Concat HTTP URL *****************************************/
void ConcatHTTPurl (char *Longitude,char *Latitude,char *Altitude,char *Speed,char *ID){
	
	uint8_t TempURL[103];
		
	strcpy((char *)TempURL,"AT+HTTPPARA=\"URL\",\"");
	strcat((char *)TempURL,URL);
	strcat((char *)TempURL, ",");
	strcat((char *)TempURL,Longitude);
	strcat((char *)TempURL, ",");
	strcat((char *)TempURL,Latitude);
	strcat((char *)TempURL, ",");
	strcat((char *)TempURL,Altitude);
	strcat((char *)TempURL, ",");
	strcat((char *)TempURL,Speed);
	strcat((char *)TempURL, ",");
	strcat((char *)TempURL,ID);
	strcat((char *)TempURL, "\"\n\r");
	SendAtCommand((char *)TempURL,200,1000,1000);
	
	memset(TempURL,0,sizeof(TempURL));
}

/********************************* HTTP ACTION *****************************************/
void HTTPaction (char *Mode){
	
	uint8_t TempAction[17];
	
	strcpy((char *)TempAction,"AT+HTTPACTION=");
	strcat((char *)TempAction,Mode);
	strcat((char *)TempAction, "\n\r");
	SendAtCommand((char *)TempAction,200,1000,1000);			
	
	memset(TempAction,0,sizeof(TempAction));	

}

/******************************** INITIALISE GNS ****************************************/
void initialiseGNS (void){
	
	uint8_t Try_GNS = 0;
	
	SendAtCommand("AT+CGNSPWR=1\n\r",200,1000,1000);
	if(FindAnswer ("ERROR")){
		Try_GNS = 0;
		while(Try_GNS < 3){
			SendAtCommand("AT+CGNSPWR=1\n\r",200,1000,1000);
			if(FindAnswer ("OK")){
				Try_GNS = 0;
				break;			
			}
			Try_GNS++;
		}
		if(Try_GNS == 2){
			ResetModule();
			SetPower();
			Try_GNS = 0;
		}
	}
}

/********************************* FIND LOCATION *****************************************/
void FindtLocation(void){
	
	int 	i , j = 0 , Z , E;

	memset(Temp,0,sizeof(Temp));
	for(E = 0 ; E < 4 ;E++){
	memset(Coordinates[E],0,sizeof(Coordinates[E]));
	}
	
	StrLen  = strlen((const char *)ReceiveAnswer);
	
	for(i=0; i < StrLen; i++) {
        if (ReceiveAnswer[i] == ',' ){
            Temp[j] = i;
            j++;
        }
			}
	
    for(Z = 0; Z < 4 ;Z++){    
			SplitCoordinates((char *)ReceiveAnswer, &Coordinates[Z][0], (uint8_t)Temp[Z+2], (uint8_t)Temp[Z+3]);
		}
}

/******************************* SPLIT CORDINATES ***************************************/
void SplitCoordinates(char* strIn,char* strOut,uint8_t startIndex,uint8_t endIndex){
    uint8_t i = startIndex +1;
    uint8_t j = 0;
    for(;i<endIndex;i++){
        strOut[j]=strIn[i];
        j++;
    }
    strOut[j]=0;
}


/******************************** GET GNS INFO ******************************************/
void SendCoordinates (void){
	
	SendAtCommand("AT+CGNSINF\n\r",200,1000,1000);
	
	FindtLocation();
	ConcatHTTPurl (Coordinates[0],Coordinates[1],Coordinates[2],Coordinates[3],_USSER_ID);
	HTTPaction ("1");
}

/***************************** SET FACTORY DEFAULT **************************************/
void SetFactoryDefault (void){
	uint8_t    Try = 0;	
	
	SendAtCommand("AT&F0\r\n",200,1000,1000);
	if(FindAnswer ("ERROR")){
		while(Try < 3){
			SendAtCommand("AT&F0\r\n",200,1000,1000);
			if(FindAnswer ("OK")){
				Try = 0;
				break;
			}
			Try++;
		}
		if(Try == 2){
			ResetModule();
			SetPower();
			Try = 0;
		}
	}
}

