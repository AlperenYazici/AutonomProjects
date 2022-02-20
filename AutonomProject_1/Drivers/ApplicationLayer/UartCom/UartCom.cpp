
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

UartCom::UartCom(IBsp* IBoardSP,  IRtos* IRealTimeOS	,uint8_t *uart_data_buff , ILedManager* ILed_Manager)
{
	this->uart_data_buff = uart_data_buff;
	this->IBoardSP = IBoardSP;
	this->IRealTimeOS = IRealTimeOS;
	this->ILed_Manager = ILed_Manager;
	uart_app_msg.len = 0;
	is_running_echo = ECHO_ACTIVE;
	
}

void UartCom::Uart_Com_ISR_Process()
{
	static uint16_t index = 0;
	if(uart_data_buff[0] == ASCII_ENTER_CHAR_VAL) // "/n" asci karakterini sorguluyor.
	{
		uart_app_msg.len = index;
		
		if(uart_cmd_parse() == MSG_VALID)
		{
			switch(uart_app_cmd_type)
			{
				case START:	UART_Com_Start_Cmd_Handle(); break;
				case STOP:	UART_Com_Stop_Cmd_Handle(); break;
				case SET_LED_ON_MS:	 UART_Com_LedOn_Cmd_Handle(); break;
				case SET_LED_OFF_MS: UART_Com_LedOff_Cmd_Handle(); break;
			}
		}
		
		if(is_running_echo == ECHO_ACTIVE)
				IRealTimeOS->UartComEventFlagSet();
		
		index = 0;
	}
	else
	{
		uart_app_msg.uart_strng[index] =  uart_data_buff[0];
		index++;
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

void UartCom::Uart_Com_Echo()
{
	IRealTimeOS->UartComEventFlagWait();
	IBoardSP->Uart_Tx((uint8_t*)uart_app_msg.uart_strng,uart_app_msg.len,10);
}

uart_com_cmd_valid UartCom::uart_cmd_parse()
{
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
		
		return MSG_UNVALID;
}
