
#ifndef UART_COM_H
#define UART_COM_H

#include "UartCom_Conf.h"
#include "stdint.h"
#include "string.h"
#include "IRtos.h"
#include "IBsp.h"
#include "ILedManager.h"

typedef enum Error_Ctrl_Result
{
	ALL_IS_OK,
	NOT_OK
}Error_Ctrl_Result;

typedef enum Echo_State{
	ECHO_ACTIVE,
	ECHO_PASIVE
}Echo_State;

typedef struct uart_com_msg{
	char uart_strng[16];
	uint8_t len; 
}uart_com_msg;

typedef enum uart_com_cmd_type{
	START,
	STOP,
	SET_LED_ON_MS,
	SET_LED_OFF_MS
}uart_com_cmd_type;

typedef enum uart_com_cmd_valid{
	MSG_VALID,
	MSG_UNVALID
}uart_com_cmd_valid;


class UartCom
{
	public:
	IBsp* IBoardSP;
	IRtos* IRealTimeOS;
	ILedManager* ILed_Manager;
	uint8_t *uart_data_buff;
	uart_com_msg uart_app_msg; //= {0,0};
	uart_com_cmd_type uart_app_cmd_type;
	Echo_State is_running_echo;// = ECHO_ACTIVE;// = 0;
	
	
	UartCom( IBsp* IBoardSP, IRtos* IRealTimeOS	,uint8_t *uart_data_buff , ILedManager* ILed_Manager);

	void Uart_Com_ISR_Process();
	
	void UART_Com_Start_Cmd_Handle();

	void UART_Com_Stop_Cmd_Handle();

	uart_com_cmd_valid UART_Com_LedOn_Cmd_Handle();

	uart_com_cmd_valid UART_Com_LedOff_Cmd_Handle();
	
	uart_com_cmd_valid uart_cmd_parse();
	
	void Uart_Com_Echo();
	
	void UartCom_Update_Configuration();
};

#endif
