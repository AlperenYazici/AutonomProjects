
#include "UartCom.h"

UartCom::UartCom(IBsp* IBoardSP,  IRtos* IRealTimeOS	,uint8_t *uart_data_buff)
{
	this->uart_data_buff = uart_data_buff;
	this->IBoardSP = IBoardSP;
	this->IRealTimeOS = IRealTimeOS;
}

void UartCom::Uart_Com_ISR_Process()
{
	static uint16_t index = 0;
	if(uart_data_buff[0] == 0x0A) // "/n" asci karakterini sorguluyor.
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
		
		if(is_running_echo)
				IRealTimeOS->EventFlagSet();
		
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
	
}

void UartCom::UART_Com_Stop_Cmd_Handle()
{
	
}

void UartCom::UART_Com_LedOn_Cmd_Handle()
{
	
}

void UartCom::UART_Com_LedOff_Cmd_Handle()
{
	
}

void UartCom::Uart_Com_Echo()
{
	IRealTimeOS->EventFlagWait();
	IBoardSP->Uart_Tx((uint8_t*)uart_app_msg.uart_strng,uart_app_msg.len,10);
}

uart_com_cmd_valid UartCom::uart_cmd_parse()
{
	return MSG_UNVALID;

}
