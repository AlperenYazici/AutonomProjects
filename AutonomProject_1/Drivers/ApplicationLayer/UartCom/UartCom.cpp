
#include "UartCom.h"
#include "math.h"


uint32_t string_to_ui32(char* string_val , uint8_t digit_cnt)
{
	uint32_t ui32_val = 0;
	int k = 0;
	for(int i=(digit_cnt-1); i >=0; i--)
	{
		ui32_val += (string_val[i]-ASCII_ZERO_VAL)*pow(10.0,k);
		k++;
	}
	return ui32_val;
}

Error_Ctrl_Result IS_ALL_DIGIT_NMBR(char* string_val , uint8_t digit_cnt)
{
	for(int i=0; i<digit_cnt;i++)
	{
		if(string_val[i]<ASCII_ZERO_VAL || string_val[i]>ASCII_NINE_VAL)
		{
			return NOT_OK;
		}
	}
	return ALL_IS_OK;
	
}

void UartCom::UartCom_Update_Configuration()
{
	
}

UartCom::UartCom(IBsp* IBoardSP,  IRtos* IRealTimeOS	, ILedManager* ILed_Manager)
{
	this->IBoardSP = IBoardSP;
	this->IRealTimeOS = IRealTimeOS;
	this->ILed_Manager = ILed_Manager;

	
}

void UartCom::Start()
{
	IBoardSP->Uart_Rx_ISR(uart_data_buff,1);
}

void UartCom::Uart_Config_Task()
{
	IBoardSP->Uart_ReConfig();

	IBoardSP->Uart_Rx_ISR(uart_data_buff,1);
	
}
void UartCom::Uart_Com_ISR_Process()
{
	static uint16_t index = 0;
	uart_com_cmd_valid is_msg_valid = MSG_UNVALID;
	if(uart_data_buff[0] == ASCII_ENTER_CHAR_VAL) // "/n" asci karakterini sorguluyor.
	{
		uart_app_msg.len = index;
		is_msg_valid = uart_cmd_parse();
		if(is_msg_valid == MSG_VALID)
		{
			switch(uart_app_cmd_type)
			{
				case START:	UART_Com_Start_Cmd_Handle(); break;
				case STOP:	UART_Com_Stop_Cmd_Handle(); break;
				case SET_LED_ON_MS:	 is_msg_valid = UART_Com_LedOn_Cmd_Handle(); break;
				case SET_LED_OFF_MS: is_msg_valid = UART_Com_LedOff_Cmd_Handle(); break;
				case SET_UART_BAUD:		is_msg_valid = UART_Com_Set_BaudRate_Cmd_Handle();				break;
				case SET_UART_WORDLENGHT : 	is_msg_valid = UART_Com_Set_WordLen_Cmd_Handle();			break;
				case SET_UART_STOP_BIT: 	is_msg_valid = UART_Com_Set_StopBit_Cmd_Handle();				break;
			}
		}
		if(is_msg_valid == MSG_VALID && ((uart_app_cmd_type == SET_UART_STOP_BIT)|| (uart_app_cmd_type == SET_UART_WORDLENGHT) 
		||(uart_app_cmd_type == SET_UART_BAUD) ))
		{
			uart_rx_isr_active = 0;
			Uart_Config_Task();
		}
		else
		if(is_running_echo == ECHO_ACTIVE)
				IRealTimeOS->UartComEventFlagSet();
		
		index = 0;
	}
	else
	{
		uart_app_msg.uart_strng[index] =  uart_data_buff[0];
		index++;
	}
	if(is_msg_valid == MSG_VALID && ((uart_app_cmd_type == SET_UART_STOP_BIT)|| (uart_app_cmd_type == SET_UART_WORDLENGHT) 
		||(uart_app_cmd_type == SET_UART_BAUD) ))
	{
		//IRealTimeOS->UartConfigEventFlagSet();
		uart_rx_isr_active = 0;
	}
	else
	{
		IBoardSP->Uart_Rx_ISR(uart_data_buff,1);
		uart_rx_isr_active = 1;
	}
}

void UartCom::UART_Com_Start_Cmd_Handle()
{
	is_running_echo = ECHO_ACTIVE;
}

void UartCom::UART_Com_Stop_Cmd_Handle()
{
	is_running_echo = ECHO_PASIVE;
	ILed_Manager->SetGreenLedOffTime(TIME_LED_MS_STOP_CMD);
	ILed_Manager->SetGreenLedOnTime(TIME_LED_MS_STOP_CMD);
}


uint32_t led_on_ms = 0;
uart_com_cmd_valid UartCom::UART_Com_LedOn_Cmd_Handle()
{
	char string_buff[10];
	uint32_t led_on_ms_buff = 0;
	uint16_t digit_cnt = uart_app_msg.len-CNT_CARACTER_CMD_LED_ON;
	strncpy(string_buff,(uart_app_msg.uart_strng+CNT_CARACTER_CMD_LED_ON),digit_cnt);
	
	/*Error Control*/
	if(IS_ALL_DIGIT_NMBR(string_buff , digit_cnt)!= ALL_IS_OK)
		return MSG_UNVALID;
	/*Error Control*/
	
	led_on_ms_buff = string_to_ui32(string_buff , digit_cnt);
	ILed_Manager->SetGreenLedOnTime(led_on_ms_buff);
	return MSG_VALID;
}


uart_com_cmd_valid UartCom::UART_Com_LedOff_Cmd_Handle()
{
	char string_buff[10];
	uint32_t led_off_ms_buff = 0;
	uint16_t digit_cnt = uart_app_msg.len-CNT_CARACTER_CMD_LED_OFF;
	strncpy(string_buff,(uart_app_msg.uart_strng+CNT_CARACTER_CMD_LED_OFF),digit_cnt);
	
		/*Error Control*/
	if(IS_ALL_DIGIT_NMBR(string_buff , digit_cnt)!= ALL_IS_OK)
		return MSG_UNVALID;
	/*Error Control*/
	
	led_off_ms_buff = string_to_ui32(string_buff , digit_cnt);
	ILed_Manager->SetGreenLedOffTime(led_off_ms_buff);
	
	return MSG_VALID;
}

uart_com_cmd_valid UartCom::UART_Com_Set_BaudRate_Cmd_Handle()
{
	char string_val[15];
	uint8_t digit =	uart_app_msg.len - CNT_CARACTER_CMD_BAUDRATE;
	strncpy(string_val , uart_app_msg.uart_strng+CNT_CARACTER_CMD_BAUDRATE,digit);
	switch(digit)
	{
		case CNT_CARACTER_BAUD_115200:  
		{
			if(strncmp(string_val,VALUE_SET_BAUD_115200,digit) == 0)
				IBoardSP->uart_config_values.BaudRate = BAUD_115200;
			else
				return MSG_UNVALID;
			break;
		}
		case CNT_CARACTER_BAUD_28800_19200_14400 : 
		{
			if(strncmp(string_val,VALUE_SET_BAUD_28800,digit) == 0)
				IBoardSP->uart_config_values.BaudRate = BAUD_28800;
			else if(strncmp(string_val,VALUE_SET_BAUD_19200,digit) == 0)
				IBoardSP->uart_config_values.BaudRate = BAUD_19200;
			else if(strncmp(string_val,VALUE_SET_BAUD_14400,digit) == 0)
				IBoardSP->uart_config_values.BaudRate = BAUD_14400;
			else
				return MSG_UNVALID;
			
			break;
		}
		case CNT_CARACTER_BAUD_9600 :
		{
			if(strncmp(string_val,VALUE_SET_BAUD_9600,digit) == 0)
				IBoardSP->uart_config_values.BaudRate = BAUD_9600;
			else
				return MSG_UNVALID;
			break;
		}
		default: return MSG_UNVALID; 
	}
	
	
	return MSG_VALID;
}
uart_com_cmd_valid UartCom::UART_Com_Set_WordLen_Cmd_Handle()
{
	char string_val[15];
	uint8_t digit =	uart_app_msg.len - CNT_CARACTER_CMD_WORDLEN;
	strncpy(string_val , uart_app_msg.uart_strng+CNT_CARACTER_CMD_WORDLEN,digit);
	switch(digit)
	{
		case CNT_CARACTER_WORDLEN_7_8_9:
		{
			if(strncmp(string_val,VALUE_SET_WORDLEN_7,digit) == 0)
				IBoardSP->uart_config_values.WordLen = WordLen_7;
			else if(strncmp(string_val,VALUE_SET_WORDLEN_8,digit) == 0)
				IBoardSP->uart_config_values.WordLen = WordLen_8;
			else if(strncmp(string_val,VALUE_SET_WORDLEN_9,digit) == 0)
				IBoardSP->uart_config_values.WordLen = WordLen_9;
			else
				return MSG_UNVALID;
			
			break;
		}			
			
	
	}

	return MSG_VALID;
}
uart_com_cmd_valid UartCom::UART_Com_Set_StopBit_Cmd_Handle()
{
	
	char string_val[15];
	uint8_t digit =	uart_app_msg.len - CNT_CARACTER_CMD_STOPBIT;
	strncpy(string_val , uart_app_msg.uart_strng+CNT_CARACTER_CMD_STOPBIT,digit);
	switch(digit)
	{
		case CNT_CARACTER_STOPBIT_1_STOPBIT_2:
		{
			if(strncmp(string_val,VALUE_SET_STOPBIT_1,digit) == 0)
				IBoardSP->uart_config_values.StopBit = StopBit_1;
			else if(strncmp(string_val,VALUE_SET_STOPBIT_2,digit) == 0)
				IBoardSP->uart_config_values.StopBit = StopBit_2;
			else
				return MSG_UNVALID;
			
			break;
		}	
		case CNT_CARACTER_STOPBIT_0_5_STOPBIT_1_5:
		{
			if(strncmp(string_val,VALUE_SET_STOPBIT_0_5,digit) == 0)
				IBoardSP->uart_config_values.StopBit = StopBit_0_5;
			else if(strncmp(string_val,VALUE_SET_STOPBIT_1_5,digit) == 0)
				IBoardSP->uart_config_values.StopBit = StopBit_1_5;
			else
				return MSG_UNVALID;
			
			break;
		}				
			
	
	}

	return MSG_VALID;
}
void UartCom::Uart_Com_Echo()
{
	IRealTimeOS->UartComEventFlagWait();
	IBoardSP->Uart_Tx((uint8_t*)uart_app_msg.uart_strng,uart_app_msg.len,100);
}

uart_com_cmd_valid UartCom::uart_cmd_parse()
{
	if(uart_app_msg.len == 0)
	{
		return MSG_UNVALID;
	}
	uint8_t result = strncmp(uart_app_msg.uart_strng, CMD_STOP,uart_app_msg.len);
	if(result == 0)
	{
		uart_app_cmd_type = STOP;
		return MSG_VALID;
	}
	
	result = strncmp(uart_app_msg.uart_strng, CMD_START,uart_app_msg.len);
	if(result == 0)
	{
		uart_app_cmd_type = START;
		return MSG_VALID;
	}
	
	result = strncmp(uart_app_msg.uart_strng, CMD_LED_ON,CNT_CARACTER_CMD_LED_ON);
	if(result == 0)
	{
		uart_app_cmd_type = SET_LED_ON_MS;
		return MSG_VALID;
	}
	
	result = strncmp(uart_app_msg.uart_strng, CMD_LED_OFF,CNT_CARACTER_CMD_LED_OFF);
	if(result == 0)
	{
		uart_app_cmd_type = SET_LED_OFF_MS;
		return MSG_VALID;
	}
		
	result = strncmp(uart_app_msg.uart_strng, CMD_SET_UART_BAUDRATE,CNT_CARACTER_CMD_BAUDRATE);
	if(result == 0)
	{
		uart_app_cmd_type = SET_UART_BAUD;
		return MSG_VALID;
	}
	
	result = strncmp(uart_app_msg.uart_strng, CMD_SET_UART_WORD_LENGTH,CNT_CARACTER_CMD_WORDLEN);
	if(result == 0)
	{
		uart_app_cmd_type = SET_UART_WORDLENGHT;
		return MSG_VALID;
	}
	
	result = strncmp(uart_app_msg.uart_strng, CMD_SET_UART_STOP_BIT,CNT_CARACTER_CMD_STOPBIT);
	if(result == 0)
	{
		uart_app_cmd_type = SET_UART_STOP_BIT;
		return MSG_VALID;
	}
	
	
	return MSG_UNVALID;
}
